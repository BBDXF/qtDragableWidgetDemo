#include "qdragablewidget.h"
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>

QDragableWidget::QDragableWidget(QWidget *parent) : QWidget(parent)
{
//    this->setAttribute(Qt::WA_Hover, true);
    m_bIsDrag = false;
    m_bResize = false;

    m_imgResize.load(u8":/resize.png");
    m_pImgShow = new QLabel(this);
    m_pImgShow->setGeometry(0,0,16,16);
    m_pImgShow->setPixmap(m_imgResize);
    m_pImgShow->raise();

    m_pContent = NULL;
}

void QDragableWidget::setContent(QWidget *pContent)
{
    m_pContent = pContent;
    if( m_pContent ){
        m_pContent->setParent(this);
        m_pContent->setWindowFlag(Qt::Window, false);
        m_pContent->move(0,0);
        m_pContent->show();
        m_pContent->lower();
        // resize
        m_pContent->setGeometry(this->rect());
    }
}

void QDragableWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    this->style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);

    // draw resize pic
    QRect rc = this->rect();
    m_pImgShow->move(rc.bottomRight()-QPoint(17,17));
}

void QDragableWidget::mousePressEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton ){
        m_pStart = event->globalPos();
        m_rcStart = this->rect();
        QPoint ptLT = mapToParent(QPoint(0,0));
        m_rcStart.moveTo(ptLT);
        QPoint curPos = event->pos();
        if( (m_rcStart.width() - curPos.x()) < 16 && ( m_rcStart.height() - curPos.y() )<16 ){
            m_bResize = true;
            setCursor(Qt::SizeFDiagCursor);
        }else{
            m_bIsDrag = true;
            setCursor(Qt::SizeAllCursor);
        }
//        qDebug()<<curPos<<m_rcStart<<m_bResize<<m_bIsDrag;
    }
}

void QDragableWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton ){
        m_bIsDrag = false;
        m_bResize = false;
        setCursor(Qt::ArrowCursor);
    }
}

void QDragableWidget::mouseMoveEvent(QMouseEvent *event)
{
    if( m_bIsDrag ){
        QPoint distance = event->globalPos() - m_pStart;
        QPoint pt = m_rcStart.topLeft()+distance;
        // limit min x,y
        if( pt.x() < 0 ){
            pt.setX(0);
        }
        if( pt.y() < 0 ){
            pt.setY(0);
        }
        this->move(pt);
    }
    if( m_bResize ){
        QPoint distance = event->globalPos() - m_pStart;
        QRect rc = m_rcStart.adjusted(0,0,distance.x(),distance.y());
        // limit min width and height
        if( rc.width() < 32 ){
            rc.setWidth(32);
        }
        if( rc.height() < 32 ){
            rc.setHeight(32);
        }
        this->setGeometry(rc);
    }
}

void QDragableWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    // resize content size
    if( m_pContent ){
        QRect rc = this->rect();
        m_pContent->setGeometry(rc);
    }
}
