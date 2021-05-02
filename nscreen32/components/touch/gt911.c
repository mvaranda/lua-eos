/*
 *  GT911 TP driver for arduino/esp8266/esp32
 * original auther: simon@yeacreate.com
 * port to C and using espressit driver: Marcelo Varanda
 * 
 * I2C TP:
 * SCL:D22[GPIO22]
 * SDA:D21[GPIO21]
 * INT:D5
 * RST:D23
 */
#include <stdio.h>
//#include "esp_attr.h"

#include "gt911.h"
#include "mos.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "memory.h"

#define I2C_SPEED 400000
#define TP_SCL 22
#define TP_SDA 21
#define TP_INT 5
#define TP_RST 23
#define I2C_NUM I2C_NUM_1

#define _TP_DEBUG_

#define TP_RST_SETUP (pinMode(TP_RST, OUTPUT))
#define TP_RST_ON (digitalWrite(TP_RST, HIGH))
#define TP_RST_OFF (digitalWrite(TP_RST, LOW))
#define TP_INT_SETUP_OUT (pinMode(TP_INT, OUTPUT))
#define TP_INT_ON (digitalWrite(TP_INT, HIGH))
#define TP_INT_OFF (digitalWrite(TP_INT, LOW))
#define TP_INT_SETUP_IN (pinMode(TP_INT, INPUT))
// 8bit Device read address:0xBB
// 8bit Device write address:0x29
// so, 0xBB/0x29 >> 1 is 0x5D/0x14(7bit)
#define GOODIX_I2C_ADDR 0x5D


#define GOODIX_I2C_CONFIG_START_ADDR 0X8047
#define GOODIX_I2C_CONFIG_SIZE 186

#define GOODIX_I2C_READXY_ADDR 0x814E
#define GOODIX_I2C_READXY_SIZE 6

#ifdef _TP_DEBUG_
// firmware information
#define GOODIX_I2C_FW_ADDR 0X8140
#define FW_INFO_SIZE 11
#endif

#define highByte(w) ((w >> 8) & 0x000000ff)
#define lowByte(w) (w & 0x000000ff)

#define HIGH 1
#define LOW  0
#define INPUT 0
#define OUTPUT 1

#define ESP_SLAVE_ADDR GOODIX_I2C_ADDR
#define I2C_TIMEOUT_MS 1000
#define ACK_EN 1

static  uint8_t gt911FW[GOODIX_I2C_CONFIG_SIZE] = {
        0x41, //0x8047 config_version
        0x40, //0x8048 X output Max(Low byte)
        0x01, //0x8049 X output Max(High byte)
        0xe0, //0x804A Y output Max(Low byte)
        0x01, //0x804B Y output Max(High byte)
        0x01, //0x804C Touch Number
        0xf5, //0x804D Module_switch1(Bit[0-1]:INT trigger,[2]:Software noise reduction,[3]:x/y exchange,[4-5]:reversal,[6]:x2x reversal,[7]:y2y reversal)
        0x00,
        0x01, //0x804F Shake_count
        0x08, 0x1e, 0x0f, 0x50, 0x32, 0x03, 0x05, 0x00, 0x00,0x00, 
        0x00,
        0x00, //space FF is max per 4 bit. [4:7] uper space, [0:3]:down space
        0x00, //space FF is max per 4 bit. [4:7] left space, [0:3]:right space
        0x00, 0x18, 0x1a, 0x1e, 0x14, 0x87, 0x28, 0x0a, 0x3c, 0x3e, 
        0xeb, 0x04, 0x00, 0x00, 0x00, 0xb0, 0x03, 0x2d, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x03, 0x64, 0x32, 0x00, 0x00, 0x00, 0x19, 
        0x64, 0x94, 0xc5, 0x02, 0x02, 0x00, 0x00, 0x04, 0xdd, 0x1c, 
        0x00, 0xae, 0x26, 0x00, 0x8f, 0x32, 0x00, 0x79, 0x42, 0x00, 
        0x68, 0x57, 0x00, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e, 0x10, 0x12, 0x14, 
        0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x26, 0x24, 0x22, 0x21, 0x20, 0x1f, 0x1e, 0x1d, 0x0c, 0x0a, 
        0x08, 0x06, 0x04, 0x02, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00,
        0x00, //chuksum, should be 0 for calculating by function
        0x01  //data_fresh
};
    /* ==================================structs================================= */
#ifdef _TP_DEBUG_
typedef struct config_info
{
    uint8_t config_version : 8;
    uint16_t x_max_output : 16;
    uint16_t y_max_output : 16;
    uint8_t touch_number : 3;
} cinfo;

typedef struct firmware_info
{
    // 0x8140
    char product_id[5];        //0x8140-0x8143
    uint16_t firmware_version; //0x8144-0x8145
    uint16_t x_resolution;     //0x8146-0x8147
    uint16_t y_resolution;     //0x8148-0x8149
    uint8_t vendor_id;         //0x814A
} finfo;
#endif


/* =============================end structs================================== */


/* ==============================variables=================================== */
uint64_t act_time = 0;
static bool IRQ = false;
static  touch_info_t get_xy;
/* ============================end variables================================= */

void  read_firmware_info();

static uint64_t millis(void)
{
  return esp_timer_get_time() / 1000;
}

static void digitalWrite(uint32_t pin, int v)
{
  printf("digitalWrite for %d, v = %d\r\n", pin, v);
  gpio_set_level(pin, v);
}

static void pinMode(uint64_t pin, int mode)
{
  printf("pinMode for %lld, mode = %d\r\n", pin, mode);
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
  io_conf.mode = GPIO_MODE_OUTPUT;
  io_conf.pin_bit_mask = 1 << pin;
  io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
  io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
  gpio_config(&io_conf);

  if (mode == OUTPUT)
	  gpio_set_direction(pin, GPIO_MODE_OUTPUT);
  else
    gpio_set_direction(pin, GPIO_MODE_INPUT);
}

static int i2c_config(uint8_t sda, uint8_t scl, uint32_t speed)
{
	i2c_config_t conf;
	conf.mode = I2C_MODE_MASTER;
	conf.sda_io_num = sda;
	conf.scl_io_num = scl;
	conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
	conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
	conf.master.clk_speed = speed;
	ESP_ERROR_CHECK(i2c_param_config(I2C_NUM, &conf));
	printf("- i2c controller configured\r\n");

	// install the driver
	ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM, I2C_MODE_MASTER, 0, 0, 0));

  return 0;
}


static esp_err_t __attribute__((unused)) i2c_master_write_slave(
  uint16_t reg_addr, 
  uint8_t *data_wr, 
  size_t size)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (ESP_SLAVE_ADDR << 1) | I2C_MASTER_WRITE, ACK_EN); //WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, highByte(reg_addr), ACK_EN);
    i2c_master_write_byte(cmd, lowByte(reg_addr), ACK_EN);
    if (size > 0) {
      i2c_master_write(cmd, data_wr, size, ACK_EN);
    }
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_NUM, cmd, I2C_TIMEOUT_MS / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    if (ret) {
      LOG_E("*** i2c_master_write_slave: error 0x%x\r\n", ret);
    }
    else {
      LOG("*** i2c_master_write_slave: OK\r\n");
    }
    return ret;
}

static esp_err_t __attribute__((unused)) i2c_master_read_slave(
  uint16_t reg_addr, 
  uint8_t *data_rd, 
  size_t size)
{
    if (size == 0) {
        return ESP_OK;
    }

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (ESP_SLAVE_ADDR << 1) | I2C_MASTER_WRITE, ACK_EN); //WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, highByte(reg_addr), ACK_EN);
    i2c_master_write_byte(cmd, lowByte(reg_addr), ACK_EN);

    // Send repeated start
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (ESP_SLAVE_ADDR << 1) | I2C_MASTER_READ, ACK_EN); //READ_BIT, ACK_CHECK_EN);
 
    if (size > 1) {
        i2c_master_read(cmd, data_rd, size - 1, I2C_MASTER_ACK);
    }
    i2c_master_read_byte(cmd, data_rd + size - 1, I2C_MASTER_LAST_NACK); //I2C_MASTER_NACK);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_NUM, cmd, I2C_TIMEOUT_MS / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}
/* =============================icache functions========================= */

void  touch_setup()
{
#ifdef _TP_DEBUG_
  LOG("[INFO][TP] GT911 TP driver for arduino/esp8266/esp32 !");
#endif

#ifdef _TP_DEBUG_
  LOG("[INFO][TP] I2C speed is %d\r\n", I2C_SPEED);
#endif

  i2c_config(TP_SDA, TP_SCL, I2C_SPEED);
#ifdef _TP_DEBUG_
  LOG("[INFO][TP] I2C wire begin \n");
#endif
  mos_thread_sleep(200);

  TP_INT_SETUP_OUT;
  TP_RST_SETUP;
  TP_RST_OFF;
  TP_INT_OFF;
  /* T2: > 10ms */
  mos_thread_sleep(50);

  //    TP_INT_ON;
  // /* T3: > 100us */
  //   mos_thread_sleep(1);

  TP_RST_ON;
  /* T4: > 5ms */
  // mos_thread_sleep(10);
  // TP_INT_OFF;
  /* end select I2C slave addr */

  /* T5: 50ms */
  mos_thread_sleep(60);
  TP_INT_SETUP_IN; // INT pin has no pullups so simple set to floating input

#ifdef _TP_DEBUG_
  LOG("[INFO][TP] TP initial finished !\r\n");
  LOG("[INFO][TP] Check ACK on addr request on 0x%x", GOODIX_I2C_ADDR);
#endif
  mos_thread_sleep(100);

  update_config();

  mos_thread_sleep(50);
#ifdef _TP_DEBUG_
  read_firmware_info();
  LOG("[INFO][GT911][UPTIME] %lld \n", millis());
#endif

  get_xy.touch = false;
#ifdef USE_INTERRUPT
  attachInterrupt(TP_INT, irq_handle, RISING);
#endif
} //end setup()

void  update_config()
{
  //get chksum
  for (uint8_t c = 0; c < (GOODIX_I2C_CONFIG_SIZE - 3); c++)
  {
    gt911FW[GOODIX_I2C_CONFIG_SIZE - 2] += gt911FW[c];
  }
  gt911FW[GOODIX_I2C_CONFIG_SIZE - 2] = (~gt911FW[GOODIX_I2C_CONFIG_SIZE - 2]) + 1;
#ifdef _TP_DEBUG_
  LOG("[INFO][TP][UPDATE_CONFIG] Chksum is 0x%02x \n", gt911FW[GOODIX_I2C_CONFIG_SIZE - 2]);
#endif
  //end get chksum

  i2c_master_write_slave(GOODIX_I2C_CONFIG_START_ADDR, gt911FW, GOODIX_I2C_CONFIG_SIZE);

} //end update_config()

#ifdef _TP_DEBUG_
void  read_firmware_info()
{
  finfo fwinfos;
  uint8_t buff[FW_INFO_SIZE];
  memset(buff,0,sizeof(buff));
  i2c_master_read_slave(GOODIX_I2C_FW_ADDR, buff, FW_INFO_SIZE);
  fwinfos.product_id[0] = buff[0];
  fwinfos.product_id[1] = buff[1];
  fwinfos.product_id[2] = buff[2];
  fwinfos.product_id[3] = buff[3];
  fwinfos.product_id[4] = 0;

  fwinfos.firmware_version = buff[4] + (buff[5] << 8);
  fwinfos.x_resolution = buff[6] + (buff[7] << 8);
  fwinfos.y_resolution = buff[8] + (buff[9] << 8);
  fwinfos.vendor_id = buff[10];

  LOG("[INFO][TP][FW] The Product ID is: %s\r\n", fwinfos.product_id);
  LOG("[INFO][TP][FW] The Firmware version is: %d \r\n", fwinfos.firmware_version);
  LOG("[INFO][TP][FW] The X coordinate resolution is: %d \r\n", fwinfos.x_resolution);
  LOG("[INFO][TP][FW] The Y coordinate resolution is: %d \r\n", fwinfos.y_resolution);
  LOG("[INFO][TP][FW] The Vendor ID is: %d \r\n", fwinfos.vendor_id);
} //end read_firmware_info()
#endif

void  read_coordinate()
{

  uint8_t buff[GOODIX_I2C_READXY_SIZE];
  i2c_master_read_slave(GOODIX_I2C_READXY_ADDR, buff, GOODIX_I2C_READXY_SIZE);

  get_xy.x = buff[2] + (buff[3] << 8);
  get_xy.y = buff[4] + (buff[5] << 8);
  get_xy.touch = buff[0] >> 6;

#if 0 //def _TP_DEBUG_
  LOG("[INFO][TP][TOUCH] X is %d \n", get_xy.x);
  LOG("[INFO][TP][TOUCH] Y is %d \n", get_xy.y);
  LOG("[INFO][TP][TOUCH] Touch status is %d \n", get_xy.touch);
#endif

  if (get_xy.touch == 1) {
    uint8_t v = 0;
    i2c_master_write_slave(GOODIX_I2C_READXY_ADDR, &v, 1);
  }

} //end read_coordinate()

void  get_touch(touch_info_t * info)
{
#if 1
  read_coordinate();
  *info = get_xy;
#else
  if (act_time > millis() && millis() < 5000)
    act_time = millis(); //prevent millis reset
  if (millis() > act_time)
  {
    act_time = millis() + pressthou;
    if (IRQ == true)
    {
      IRQ = false;
      read_coordinate();
      if (get_xy.touch == false)
        return NULL;
      return &get_xy;
    }
  }
  return NULL;
#endif
} //end get_touch()

/* =========================end icache functions======================== */
/* =========================== iram functions=========================== */
#ifdef USE_INTERRUPT
void IRAM_ATTR irq_handle()
{
  IRQ = true;
} //end irq_handle()
#endif

/* ===========================end iram functions=========================== */

