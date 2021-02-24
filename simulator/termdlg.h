#ifndef TERMDLG_H
#define TERMDLG_H

#include <QDialog>
#include "console.h"

namespace Ui {
class TermDlg;
}

class TermDlg : public QDialog
{
  Q_OBJECT

public:
  explicit TermDlg(QWidget *parent = nullptr);
  ~TermDlg();

private:
  Ui::TermDlg *ui;
public:
  Console * m_console;
};

#endif // TERMDLG_H
