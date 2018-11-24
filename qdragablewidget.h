#ifndef QDRAGABLEWIDGET_H
#define QDRAGABLEWIDGET_H

#include <QtCore>
#include <QtWidgets>

class QDragableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QDragableWidget(QWidget *parent = nullptr);
    void setContent(QWidget* pContent);
    void setActionCtl(bool bDragMove, bool bResize);
signals:

public slots:

private:
    bool m_bEnableDrag, m_bEnableResize;
    bool m_bResize;
    bool m_bIsDrag;
    QRect m_rcStart;
    QPoint m_pStart;

    QPixmap m_imgResize;
    QLabel* m_pImgShow;

    QWidget* m_pContent;
public:
    void paintEvent(QPaintEvent *event);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
};

#endif // QDRAGABLEWIDGET_H
