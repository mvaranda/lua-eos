/***************************************************************
 *
 *                 This code is part of LUA_EOS
 *
 * Copyrights 2021 - Varanda Labs Inc.
 *
 * License:
 *   Creative Commons: CC BY-NC-SA 4.0
 *   Attribution-NonCommercial-ShareAlike 4.0 International
 *   https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
 *
 *   Note: for purchasing a commertial license contact:
 *     m@varanda.ca
 *
 ***************************************************************
 */

#include <QDebug>
#include <QThread>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lv_conf.h"
#include "lvgl.h"
#include "lvgl_integr.h"
#include "log.h"
#include "eos_init.h"

#define LUA_EOS_VERSION "0.0"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , display_image(LV_HOR_RES_MAX,LV_VER_RES_MAX, QImage::Format_RGB16)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    gMainObj = this;

    setWindowTitle("LUA EOS Simulator - version " LUA_EOS_VERSION);

    connect(ui->lb_display, SIGNAL(mousePressed(int, int)), this, SLOT(onMousePressed(int, int)));
    connect(ui->lb_display, SIGNAL(mouseReleased(int, int)), this, SLOT(onMouseReleased(int, int)));

    // ui->lb_display->setPixmap(display_pixelmap);
    //ui->lb_display->setPixmap(QPixmap::fromImage(display_image));
    //display_image.fill(Qt::green);
    //ui->lb_display->setPixmap(QPixmap::fromImage(display_image));
    //ui->lb_display->update();
#if 0
    m_term = new TermDlg(0);
    m_term_console = m_term->m_console;
    m_term->show();
    connect(m_term_console, &Console::getData, this, &MainWindow::writeDataFromTerm);
#endif

    lv_integr_run();

    timerId = startTimer(LVGL_TICK_TIME);
    luaCppInit();

}

void MainWindow::writeDataFromTerm(const QByteArray &data)
{
    // LOG("writeDataFromTerm: '%s', len=%u", data.toStdString().c_str(), data.length());
    static char msg[1024] = {0};
    static int msg_len = 0;

    if (data.size() == 0) return;

    int to_transfer = data.size();
    int fit = sizeof(msg) - (msg_len + 1);
    if (to_transfer > fit)
        to_transfer = fit;
    if (to_transfer <= 0) {
        LOG("there is no room for line terminal buffer");
        msg_len = 0;
        memset(msg, 0, sizeof(msg));
        return;
    }
    memcpy(&msg[msg_len], data.data(), to_transfer);
    msg_len += to_transfer;

    // if last char is either CR or LF we send to camera
    if (msg[msg_len - 1] != '\r') {
        return;
    }

    LOG("Line completed");

    // dispatch line to C program
    //protoSendToCamConsole(msg);
    msg_len = 0;
    memset(msg, 0, sizeof(msg));
}

void MainWindow::onMousePressed(int x, int y)
{
    printf("Mouse pressed %d, %d\n", x, y);
    lv_integr_update_pointer(x, y, LV_INDEV_STATE_PR);
}

void MainWindow::onMouseReleased(int x, int y)
{
    printf("Mouse released %d, %d\n", x, y);
    lv_integr_update_pointer(x, y, LV_INDEV_STATE_REL);
}



void MainWindow::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    lv_integr_timer();
}

MainWindow::~MainWindow()
{
    delete ui;
    killTimer(timerId);
}

