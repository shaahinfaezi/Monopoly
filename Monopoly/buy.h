#ifndef BUY_H
#define BUY_H

#include <QDialog>
#include <Property.h>
#include "gameboard.h"

namespace Ui {
class Buy;
}

class Buy : public QDialog
{
    Q_OBJECT

public:
    explicit Buy(QWidget *parent = nullptr);
    ~Buy();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Buy *ui;

    Property * property;

    GameBoard * gameboard;
};

#endif // BUY_H
