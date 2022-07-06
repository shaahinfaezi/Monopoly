#ifndef SELL_PROPERTY_H
#define SELL_PROPERTY_H

#include <QDialog>
#include <gameboard.h>

namespace Ui {
class sell_property;
}

class sell_property : public QDialog
{
    Q_OBJECT

public:
    explicit sell_property(int,QWidget *parent = nullptr);
    ~sell_property();

private slots:
    void on_pushButton_clicked();

private:
    Ui::sell_property *ui;

     GameBoard * gameBoard;

     int Iterator;
};

#endif // SELL_PROPERTY_H
