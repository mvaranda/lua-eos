#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QImage>
#include <QTimer>
#include "termdlg.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QImage display_image;
    Ui::MainWindow *ui;

private slots:
  void timerEvent(QTimerEvent *event);
  void onMousePressed(int x, int y);
  void onMouseReleased(int x, int y);
  void writeDataFromTerm(const QByteArray &data);


private:
  int timerId;
  TermDlg * m_term;
  Console * m_term_console;

};
#endif // MAINWINDOW_H
