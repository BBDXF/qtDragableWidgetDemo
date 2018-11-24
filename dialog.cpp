#include "dialog.h"
#include "ui_dialog.h"
#include "qdragablewidget.h"
#include "dlgshow.h"
#include <QBoxLayout>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowMinMaxButtonsHint, true);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{

    // widget
    QDragableWidget* pShow = new QDragableWidget(this);
    pShow->setGeometry(0,0,400,400);
    pShow->show();

    DlgShow* pReal = new DlgShow(pShow);
    pShow->setContent(pReal);

}
