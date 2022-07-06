#ifndef MY_PROPERTIES_H
#define MY_PROPERTIES_H

#include <QDialog>
#include "gameboard.h"

namespace Ui {
class my_Properties;
}

class my_Properties : public QDialog
{
    Q_OBJECT

public:
    explicit my_Properties(QWidget *parent = nullptr);
    ~my_Properties();

    bool ColorMortgaged();

    bool EqualityCheck(int);

    bool MaxOrMinCheck(int);


private slots:
    void on_pushButton_8_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::my_Properties *ui;

    GameBoard * gameBoard;

    void listPrint();

    int iterator;//shomarandeyi baray neshon dadn amlak

};

#endif // MY_PROPERTIES_H
