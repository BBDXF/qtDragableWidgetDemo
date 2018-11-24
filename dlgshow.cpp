#include "dlgshow.h"
#include "ui_dlgshow.h"

DlgShow::DlgShow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgShow)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Window, false);
    this->move(0,0);
}

DlgShow::~DlgShow()
{
    delete ui;
}
