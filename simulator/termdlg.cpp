#include "termdlg.h"
#include "ui_termdlg.h"

TermDlg::TermDlg(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::TermDlg)
{
  ui->setupUi(this);

  Qt::WindowFlags flags = windowFlags();
  //flags |= Qt::WindowMaximizeButtonHint;
  //flags |= Qt::WindowContextHelpButtonHint;
  flags &= ~Qt::WindowContextHelpButtonHint;
  setWindowFlags(flags);

  m_console = new Console();
  m_console->setMode(MODE_TERMINAL);

  ui->verticalLayout_2->addWidget(m_console);

}

TermDlg::~TermDlg()
{
  delete ui;
}
