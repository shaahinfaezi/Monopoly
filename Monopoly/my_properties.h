#ifndef MY_PROPERTIES_H
#define MY_PROPERTIES_H

#include <QDialog>

namespace Ui {
class my_Properties;
}

class my_Properties : public QDialog
{
    Q_OBJECT

public:
    explicit my_Properties(QWidget *parent = nullptr);
    ~my_Properties();

private:
    Ui::my_Properties *ui;
};

#endif // MY_PROPERTIES_H
