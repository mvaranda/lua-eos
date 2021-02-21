#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lv_conf.h"
#include "lvgl.h"

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

static lv_disp_drv_t disp_drv;               /*Descriptor of a display driver*/
static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * LV_VER_RES_MAX / 10];                     /*Declare a buffer for 1/10 screen size*/

    extern void lv_ex_get_started_1(void);

    void my_disp_flush(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p)
    {
        bool last = lv_disp_flush_is_last( disp);
        updateDisplay(area, color_p, last);
        lv_disp_flush_ready(disp);         /* Indicate you are ready with the flushing*/
    }

    static void runNative(void) {

        lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * LV_VER_RES_MAX / 10);    /*Initialize the display buffer*/

        lv_init();


        lv_disp_drv_init(&disp_drv);          /*Basic initialization*/
        disp_drv.flush_cb = my_disp_flush;    /*Set your driver function*/
        disp_drv.buffer = &disp_buf;          /*Assign the buffer to the display*/
        lv_disp_drv_register(&disp_drv);      /*Finally register the driver*/

        lv_ex_get_started_1();

        for (int i = 0; i<1000; i++) {
            lv_tick_inc(1);
            lv_task_handler();
        }
    }
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    //, display_pixelmap(LV_HOR_RES_MAX,LV_VER_RES_MAX)
    , display_image(LV_HOR_RES_MAX,LV_VER_RES_MAX, QImage::Format_RGB16)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    mainObj = this;

    //display_pixelmap.fill(Qt::red);
    display_image.fill(Qt::blue);

#if 1
    int val = 0;
    int w,h;

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


    // ui->lb_display->setPixmap(display_pixelmap);
    //ui->lb_display->setPixmap(QPixmap::fromImage(display_image));
    //display_image.fill(Qt::green);
    //ui->lb_display->setPixmap(QPixmap::fromImage(display_image));
    //ui->lb_display->update();

   runNative();

}

MainWindow::~MainWindow()
{
    delete ui;
}

