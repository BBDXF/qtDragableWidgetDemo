#ifndef QFLOWLAYOUT_H
#define QFLOWLAYOUT_H

#include <QtCore>
#include <QLayout>
#include <QtWidgets>

class QFlowLayout : public QLayout
{
    Q_OBJECT
public:
    explicit QFlowLayout(QWidget *parent = nullptr);

signals:

public slots:

private:
    QList<QLayoutItem*> m_ItemList;
    QRect m_rcLayout;
    void _adjustItems();
    int m_szLenX, m_szLenY;
public:
    QSize sizeHint() const; // 子控件 首选大小
    void addItem(QLayoutItem *itemLay);
    QLayoutItem *itemAt(int index) const;
    QLayoutItem *takeAt(int index);
    int count() const;

public:
    QSize minimumSize() const;
    QSize maximumSize() const;
    Qt::Orientations expandingDirections() const;
    void setGeometry(const QRect &rc);
    QRect geometry() const;
    bool isEmpty() const;
    void invalidate();
    QLayout *layout();
    QSizePolicy::ControlTypes controlTypes() const;
    void childEvent(QChildEvent *event);
};

#endif // QFLOWLAYOUT_H
