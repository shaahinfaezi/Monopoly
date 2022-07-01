#ifndef SELL_PROPERTY_H
#define SELL_PROPERTY_H

#include <QDialog>

namespace Ui {
class sell_property;
}

class sell_property : public QDialog
{
    Q_OBJECT

public:
    explicit sell_property(QWidget *parent = nullptr);
    ~sell_property();

private:
    Ui::sell_property *ui;
};

#endif // SELL_PROPERTY_H
