#ifndef DLGSHOW_H
#define DLGSHOW_H

#include <QDialog>

namespace Ui {
class DlgShow;
}

class DlgShow : public QDialog
{
    Q_OBJECT

public:
    explicit DlgShow(QWidget *parent = 0);
    ~DlgShow();

private:
    Ui::DlgShow *ui;
};

#endif // DLGSHOW_H
