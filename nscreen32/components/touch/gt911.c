/*
 *  GT911 TP driver for arduino/esp8266/esp32
 * auther: simon@yeacreate.com
 * I2C TP:
 * SCL:D22[GPIO22]
 * SDA:D21[GPIO21]
 * INT:D5
 * RST:D23
 */

#include "gt911.h"
#include "mos.h"
#include "driver/gpio.h"

#define I2C_SPEED 400000
#define TP_SCL 22
#define TP_SDA 21
#define TP_INT 5
#define TP_RST 23


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
        char product_id[4];        //0x8140-0x8143
        uint16_t firmware_version; //0x8144-0x8145
        uint16_t x_resolution;     //0x8146-0x8147
        uint16_t y_resolution;     //0x8148-0x8149
        uint8_t vendor_id;         //0x814A
    } finfo;
#endif

    typedef struct touch_info
    {
        uint16_t x : 16;   //0x8150-0x8151
        uint16_t y : 16;   //0x8152-0x8153
        bool touch : 1; //0x814E(bit:7)
    } tpxy;
    /* =============================end structs================================== */
    /* ==============================variables=================================== */
    uint64_t act_time = 0;
    /* ============================end variables================================= */

static uint64_t millis(void)
{
  return esp_timer_get_time() / 1000;
}

#define highByte(w) ((w >> 8) & 0x000000ff)
#define lowByte(w) (w & 0x000000ff)

static  tpxy get_xy;

#define HIGH 1
#define LOW  0
#define INPUT 0
#define OUTPUT 1

static void digitalWrite(int pin, int v)
{
  gpio_set_level(1<<pin, v);
}

static void pinMode(int pin, int mode)
{
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
  io_conf.mode = GPIO_MODE_OUTPUT;
  io_conf.pin_bit_mask = 1 << pin;
  io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
  io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
  gpio_config(&io_conf);

  if (mode == OUTPUT)
	  gpio_set_direction(1 << pin, GPIO_MODE_OUTPUT);
  else
    gpio_set_direction(1 << pin, GPIO_MODE_INPUT);
}

static int wire_begin(uint8_t sda, uint8_t scl, uint32_t speed)
{

  return 0;
}

static int wire_beginTransmission(uint8_t addr)
{

  return 0;
}


static int wire_endTransmission(bool stop)
{

  return 0;
}

static int wire_write(uint8_t b)
{

  return 0;
}

static int wire_requestFrom(uint8_t addr, int size)
{

  return 0;
}

static int wire_available(void)
{

  return 0;
}
  
static int wire_read(void)
{

  return 0;
}

/* =============================icache functions========================= */
void ICACHE_FLASH_ATTR readi2c(uint16_t addr, uint8_t *inputbuff, size_t size)
{
  uint8_t pos = 0;

  wire_beginTransmission(GOODIX_I2C_ADDR);
  wire_write(highByte(addr));
  wire_write(lowByte(addr));
#ifdef _TP_DEBUG_
  Serial.printf("[INFO][TP] I2C writen 0x%02x to 0x%02x \n", highByte(addr), GOODIX_I2C_ADDR);
  Serial.printf("[INFO][TP] I2C writen 0x%02x to 0x%02x \n", lowByte(addr), GOODIX_I2C_ADDR);

  uint8_t res;
  res = wire_endTransmission(true);
  if (res != 0)
  {
    Serial.printf("[ERR][TP] I2C tranmission error\n");
  }
#else
  wire_endTransmission(true);
#endif

  wire_requestFrom(GOODIX_I2C_ADDR, size);

  while (wire_available()) // slave may send less than requested
  {
    inputbuff[pos] = wire_read(); // receive a byte as character
    pos++;

#ifdef _TP_DEBUG_
    Serial.printf("[INFO][TP][DATA] Reg:0x%04x Data[%d] is 0x%02x \n", addr, pos - 1, inputbuff[pos - 1]);
#endif
  }

  wire_endTransmission(false); //send nack end
} //end readi2c()

void ICACHE_FLASH_ATTR setup()
{
#ifdef _TP_DEBUG_
  LOG("[INFO][TP] GT911 TP driver for arduino/esp8266/esp32 !");
#endif

#ifdef _TP_DEBUG_
  LOG("[INFO][TP] I2C speed is ");
  LOG(I2C_SPEED);
#endif

  wire_begin(TP_SDA, TP_SCL, I2C_SPEED);
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
  LOG("[INFO][TP] TP initial finished !");
  LOG("[INFO][TP] Check ACK on addr request on 0x");
  LOG(GOODIX_I2C_ADDR, HEX);
  wire_beginTransmission(GOODIX_I2C_ADDR);
  int error = wire_endTransmission(true);
  if (error == 0)
  {
    LOG(": SUCCESS");
  }
  else
  {
    LOG(": ERROR #");
    LOG(error);
  }
  // read_firmware_info();
#endif
  mos_thread_sleep(100);
  update_config();
#ifdef _TP_DEBUG_
  read_firmware_info();
  Serial.printf("[INFO][GT911][UPTIME] %ld \n", millis());
#endif

  get_xy.touch = false;
#ifdef USE_INTERRUPT
  attachInterrupt(TP_INT, irq_handle, RISING);
#endif
} //end setup()

void ICACHE_FLASH_ATTR update_config()
{
  //get chksum
  for (uint8_t c = 0; c < (GOODIX_I2C_CONFIG_SIZE - 3); c++)
  {
    gt911FW[GOODIX_I2C_CONFIG_SIZE - 2] += gt911FW[c];
  }
  gt911FW[GOODIX_I2C_CONFIG_SIZE - 2] = (~gt911FW[GOODIX_I2C_CONFIG_SIZE - 2]) + 1;
#ifdef _TP_DEBUG_
  Serial.printf("[INFO][TP][UPDATE_CONFIG] Chksum is 0x%02x \n", gt911FW[GOODIX_I2C_CONFIG_SIZE - 2]);
#endif
  //end get chksum

  //send configs
  for (uint8_t w = 0; w < GOODIX_I2C_CONFIG_SIZE; w++)
  {
//     wire_beginTransmission(GOODIX_I2C_ADDR);
//     wire_write(highByte(GOODIX_I2C_CONFIG_START_ADDR + w));
//     wire_write(lowByte(GOODIX_I2C_CONFIG_START_ADDR + w));
//     wire_write(gt911FW[w]);
// #ifdef _TP_DEBUG_
//     Serial.printf("[INFO][TP][UPDATE_CONFIG] Witren configs[%d] 0x%02x \n", w, gt911FW[w]);
// #endif
//     wire_endTransmission(true); //sent end
  }

#ifdef _TP_DEBUG_
  uint8_t config_buff1[I2C_BUFFER_LENGTH];
  uint8_t config_buff2[GOODIX_I2C_CONFIG_SIZE - I2C_BUFFER_LENGTH];

  readi2c(GOODIX_I2C_CONFIG_START_ADDR, config_buff1, I2C_BUFFER_LENGTH);                                              //the 1st 128 configs
  readi2c(GOODIX_I2C_CONFIG_START_ADDR + I2C_BUFFER_LENGTH, config_buff2, GOODIX_I2C_CONFIG_SIZE - I2C_BUFFER_LENGTH); //the resets configs

  for (int i = 0; i < I2C_BUFFER_LENGTH; i++)
  {
    Serial.printf("[INFO][TP][DATA] The new config is 0x%02x \n", config_buff1[i]);
  }

  for (int j = 0; j < (GOODIX_I2C_CONFIG_SIZE - I2C_BUFFER_LENGTH); j++)
  {
    Serial.printf("[INFO][TP][DATA] The new config is 0x%02x \n", config_buff2[j]);
  }

  cinfo configs;
  configs.config_version = config_buff1[0];
  configs.x_max_output = (config_buff1[2] << 8) + config_buff1[1];
  configs.y_max_output = (config_buff1[4] << 8) + config_buff1[3];
  configs.touch_number = config_buff1[5];

  Serial.printf("[INFO][TP][CONFIGS] The Config Version is: %d \n", configs.config_version);
  Serial.printf("[INFO][TP][CONFIGS] The X Output Max is: %d \n", configs.x_max_output);
  Serial.printf("[INFO][TP][CONFIGS] The Y Output Max is: %d \n", configs.y_max_output);
  Serial.printf("[INFO][TP][CONFIGS] Total Touch Number is: %d \n", configs.touch_number);
#endif

} //end update_config()

#ifdef _TP_DEBUG_
void ICACHE_FLASH_ATTR read_firmware_info()
{
  finfo fwinfos;
  uint8_t buff[FW_INFO_SIZE];
  readi2c(GOODIX_I2C_FW_ADDR, buff, FW_INFO_SIZE);
  fwinfos.product_id[0] = buff[0];
  fwinfos.product_id[1] = buff[1];
  fwinfos.product_id[2] = buff[2];
  fwinfos.product_id[3] = buff[3];

  fwinfos.firmware_version = buff[4] + (buff[5] << 8);
  fwinfos.x_resolution = buff[6] + (buff[7] << 8);
  fwinfos.y_resolution = buff[8] + (buff[9] << 8);
  fwinfos.vendor_id = buff[10];

  LOG("[INFO][TP][FW] The Product ID is:");
  LOG(fwinfos.product_id);
  Serial.printf("[INFO][TP][FW] The Firmware version is: %d \n", fwinfos.firmware_version);
  Serial.printf("[INFO][TP][FW] The X coordinate resolution is: %d \n", fwinfos.x_resolution);
  Serial.printf("[INFO][TP][FW] The Y coordinate resolution is: %d \n", fwinfos.y_resolution);
  Serial.printf("[INFO][TP][FW] The Vendor ID is: %d \n", fwinfos.vendor_id);
} //end read_firmware_info()
#endif

void ICACHE_FLASH_ATTR read_coordinate()
{

  uint8_t buff[GOODIX_I2C_READXY_SIZE];
  readi2c(GOODIX_I2C_READXY_ADDR, buff, GOODIX_I2C_READXY_SIZE);

  get_xy.x = buff[2] + (buff[3] << 8);
  get_xy.y = buff[4] + (buff[5] << 8);
  get_xy.touch = buff[0] >> 6;

#ifdef _TP_DEBUG_
  Serial.printf("[INFO][TP][TOUCH] X is %d \n", get_xy.x);
  Serial.printf("[INFO][TP][TOUCH] Y is %d \n", get_xy.y);
  Serial.printf("[INFO][TP][TOUCH] Touch status is %d \n", get_xy.touch);
#endif

  if (get_xy.touch == 1)
  {
    wire_beginTransmission(GOODIX_I2C_ADDR);
    wire_write(highByte(GOODIX_I2C_READXY_ADDR));
    wire_write(lowByte(GOODIX_I2C_READXY_ADDR));
    wire_write(0x00);

#ifdef _TP_DEBUG_
    Serial.printf("[INFO][TP][RBS] Reseted buffer status \n");
#endif
    wire_endTransmission(true); //sent end
  }

} //end read_coordinate()

bool ICACHE_FLASH_ATTR get_touch(uint16_t pressthou)
{

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
        return false;
      return true;
    }
  }
  return false;
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

// void loop()
// {

//   if (get_touch(50))
//   {
//     Serial.printf("[INFO][TP] X is %d \n", get_xy.x);
//     Serial.printf("[INFO][TP] Y is %d \n", get_xy.y);
//     Serial.printf("[INFO][TP] Touch status is %d \n", get_xy.touch);
//     Serial.printf("[INFO][UPTIME] %ld \n", millis());
//   }
// }
