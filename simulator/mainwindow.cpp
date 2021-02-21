#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lv_conf.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , display_pixelmap(LV_HOR_RES_MAX,LV_VER_RES_MAX)
    , display_image(LV_HOR_RES_MAX,LV_VER_RES_MAX, QImage::Format_RGB16)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    display_pixelmap.fill(Qt::red);
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
            ui->lb_display->setPixmap(QPixmap::fromImage(display_image));
            display_image.fill(Qt::green);
            //ui->lb_display->setPixmap(QPixmap::fromImage(display_image));
            //ui->lb_display->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

