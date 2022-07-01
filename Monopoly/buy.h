#ifndef BUY_H
#define BUY_H

#include <QDialog>
#include <Property.h>

namespace Ui {
class Buy;
}

class Buy : public QDialog
{
    Q_OBJECT

public:
    explicit Buy(Property *,QWidget *parent = nullptr);
    ~Buy();

private:
    Ui::Buy *ui;

    Property * property;
};

#endif // BUY_H
