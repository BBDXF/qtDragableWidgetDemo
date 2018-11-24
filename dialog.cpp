#include "dialog.h"
#include "ui_dialog.h"
#include "qdragablewidget.h"
#include "dlgshow.h"
#include <QBoxLayout>
#include "qflowlayout.h"

QFlowLayout* pFlow = NULL;

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
    pShow->setGeometry(0,0,300,300);
    pShow->show();

    DlgShow* pReal = new DlgShow(pShow);
    pShow->setContent(pReal);

    if(pFlow)
        pFlow->addWidget(pShow);
}


void Dialog::on_pushButton_2_clicked()
{
    if( pFlow == NULL ){
        pFlow = new QFlowLayout();
        QRect rc = this->rect();
        rc.adjust(5,50,-5,0);
        ui->frame->setGeometry(rc);
        pFlow->setGeometry(rc);
        ui->frame->setLayout(pFlow);
    }
}

void Dialog::on_pushButton_3_clicked()
{
    if(pFlow)
        pFlow->takeAt(0);
}

void Dialog::on_pushButton_4_clicked()
{
    static int index = 0;
    if( pFlow ){
        QPushButton* btn = new QPushButton(QString(u8"Btn-%1").arg(++index));
        QRect rc(0,0,60+rand()%40, 40+rand()%60);
        btn->setGeometry(rc);
        pFlow->addWidget(btn);
    }
}
