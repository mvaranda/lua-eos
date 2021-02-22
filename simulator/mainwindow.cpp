#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lv_conf.h"
#include "lvgl.h"

#define LVGL_TICK_TIME 10 // 10 milliseconds

MainWindow * mainObj;


static void updateDisplay (const lv_area_t * area, lv_color_t * color_p, bool last)
{
    int32_t x, y;
    lv_color_t pixel;
    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
            pixel = *color_p;
            mainObj->display_image.setPixelColor(x,y, (QRgb) (*color_p).full);
            color_p++;
        }
    }
    if (last) {
        mainObj->ui->lb_display->setPixmap(QPixmap::fromImage(mainObj->display_image));
    }



}

extern "C" {
static lv_indev_drv_t indev_drv;
static lv_disp_drv_t disp_drv;               /*Descriptor of a display driver*/
static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * LV_VER_RES_MAX / 10];                     /*Declare a buffer for 1/10 screen size*/
static int touchpad_x = 0, touchpad_y = 0;
static int touchpad_state = LV_INDEV_STATE_REL;
static int touchpad_old_state = LV_INDEV_STATE_REL;


extern void lv_ex_get_started_1(void);

void my_disp_flush(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p)
{
  bool last = lv_disp_flush_is_last( disp);
  updateDisplay(area, color_p, last);
  lv_disp_flush_ready(disp);         /* Indicate you are ready with the flushing*/
}

bool lvgl_input_read(lv_indev_drv_t * drv, lv_indev_data_t*data)
{
  Q_UNUSED(drv);
    bool ret = false;
  data->point.x = touchpad_x;
  data->point.y = touchpad_y;
  data->state = touchpad_state; //LV_INDEV_STATE_REL; //LV_INDEV_STATE_PR or LV_INDEV_STATE_REL;
  if ( touchpad_state != touchpad_old_state) {
      touchpad_old_state = touchpad_state;
      //ret = true;
      printf("mouse down\n");
  }
  return ret; /*No buffering now so no more data read*/
}

static void runNative(void) {

  lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * LV_VER_RES_MAX / 10);    /*Initialize the display buffer*/

  lv_init();


  lv_disp_drv_init(&disp_drv);          /*Basic initialization*/
  disp_drv.flush_cb = my_disp_flush;    /*Set your driver function*/
  disp_drv.buffer = &disp_buf;          /*Assign the buffer to the display*/
  lv_disp_drv_register(&disp_drv);      /*Finally register the driver*/

  lv_indev_drv_init(&indev_drv);      /*Basic initialization*/
  indev_drv.type = LV_INDEV_TYPE_POINTER;  /*See below.*/
  indev_drv.read_cb = lvgl_input_read;              /*See below.*/
  /*Register the driver in LVGL and save the created input device object*/
  lv_indev_t * my_indev = lv_indev_drv_register(&indev_drv);

  lv_ex_get_started_1();

}

    static void nativeTimer(void) {
      static int cnt = 0;
      lv_tick_inc(LVGL_TICK_TIME);
//      if (cnt++ > 10) {
//        cnt = 0;
//        lv_task_handler();
//      }
      lv_task_handler();
    }



};

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , display_image(LV_HOR_RES_MAX,LV_VER_RES_MAX, QImage::Format_RGB16)
  , ui(new Ui::MainWindow)

{
  ui->setupUi(this);

  mainObj = this;


#if 0
    int val = 0;
    int w,h;

    display_image.fill(Qt::blue);

    for (h=0; h < LV_VER_RES_MAX; h++)  {
      if (h & 0b10000)
        val = -1;
      else
        val = 0;
      for (w=0; w < LV_HOR_RES_MAX; w++) {
       display_image.setPixel(w,h,val);
      }
    }
#endif

    connect(ui->lb_display, SIGNAL(mousePressed(int, int)), this, SLOT(onMousePressed(int, int)));
    connect(ui->lb_display, SIGNAL(mouseReleased(int, int)), this, SLOT(onMouseReleased(int, int)));

    // ui->lb_display->setPixmap(display_pixelmap);
    //ui->lb_display->setPixmap(QPixmap::fromImage(display_image));
    //display_image.fill(Qt::green);
    //ui->lb_display->setPixmap(QPixmap::fromImage(display_image));
    //ui->lb_display->update();

 runNative();

 timerId = startTimer(LVGL_TICK_TIME);

}

void MainWindow::onMousePressed(int x, int y)
{
    printf("Mouse pressed %d, %d\n", x, y);
    touchpad_x = 0;
    touchpad_y = y;
    touchpad_state = LV_INDEV_STATE_PR;
}

void MainWindow::onMouseReleased(int x, int y)
{
    printf("Mouse released %d, %d\n", x, y);
    touchpad_x = 0;
    touchpad_y = y;
    touchpad_state = LV_INDEV_STATE_REL;
}



void MainWindow::timerEvent(QTimerEvent *event)
{
  Q_UNUSED(event);
  nativeTimer();
}

MainWindow::~MainWindow()
{
  delete ui;
  killTimer(timerId);
}

