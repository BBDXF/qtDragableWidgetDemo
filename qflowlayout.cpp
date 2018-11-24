#include "qflowlayout.h"

QFlowLayout::QFlowLayout(QWidget *parent) : QLayout(parent)
{
    m_rcLayout = QRect(0,0,100,100);
    if( this->parent() ){
        QWidget* pParent = (QWidget*)this->parent();
        m_rcLayout = pParent->rect();
    }
    m_szLenX = m_rcLayout.width();
    m_szLenY = m_rcLayout.height();
}

void QFlowLayout::_adjustItems()
{
    // 保留长宽，调整xy
    QRect rcMax = m_rcLayout;

    // margins and space
    QMargins margs = this->contentsMargins();
    int spcs = this->spacing();
    // calc start
    int x = margs.left();
    int y = margs.top();
    int ymax = 0;

    // items
    foreach (QLayoutItem* pItem, m_ItemList) {
        QRect rcItem = pItem->geometry();
        // pre calc
        if( (x+rcItem.width()) > rcMax.width() ){
            // new row
            x =  margs.left();
            y += ymax + spcs;
            ymax = 0;
        }
        // set
        rcItem.moveTo(x, y);
        if( pItem->widget() ){
            pItem->widget()->setGeometry(rcItem);
        }else{
            pItem->setGeometry(rcItem); // adjust child item
        }
        // after calc
        x += rcItem.width() + spcs;
        if( rcItem.height() > ymax ){
            ymax = rcItem.height();
        }
    }
    m_szLenX = rcMax.width();
    m_szLenY = y+ymax; // 估计的最终大小
}

QSize QFlowLayout::sizeHint() const
{
    return QSize(m_szLenX, m_szLenY);
}

void QFlowLayout::addItem(QLayoutItem *itemLay)
{
    m_ItemList.append(itemLay);
    _adjustItems();
}

QLayoutItem *QFlowLayout::itemAt(int index) const
{
    return m_ItemList.at(index);
}

QLayoutItem *QFlowLayout::takeAt(int index)
{
    if( index < 0 || index >= m_ItemList.size() ){
        return NULL;
    }
    QLayoutItem* pTake = m_ItemList.takeAt(index);
    if( pTake->widget() ){
        pTake->widget()->close();
    }
    _adjustItems();
    return pTake;
}

int QFlowLayout::count() const
{
    return m_ItemList.count();
}

QSize QFlowLayout::minimumSize() const
{
    return QSize(32,32);
}

QSize QFlowLayout::maximumSize() const
{
    if( this->parent() ){
        QWidget* pParent = (QWidget*)this->parent();
        return pParent->size();
    }
    return sizeHint();
}

Qt::Orientations QFlowLayout::expandingDirections() const
{
    return Qt::Vertical; // 垂直方向滚动条
}

void QFlowLayout::setGeometry(const QRect &rc)
{
    // 界面发生变化时，会主动调用这个，在这里主动改变子控件大小
    qDebug()<<"setGeometry:"<<rc;
    m_rcLayout = rc;
    _adjustItems();
}

QRect QFlowLayout::geometry() const
{
    return m_rcLayout;
}

bool QFlowLayout::isEmpty() const
{
    return m_ItemList.empty();
}

void QFlowLayout::invalidate()
{

}

QLayout *QFlowLayout::layout()
{
    return (QLayout*)this;
}

QSizePolicy::ControlTypes QFlowLayout::controlTypes() const
{
    return QSizePolicy::Frame;
}

void QFlowLayout::childEvent(QChildEvent *event)
{
    // add removed polished ...events for items
}
