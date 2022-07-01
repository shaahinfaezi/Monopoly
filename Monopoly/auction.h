#ifndef AUCTION_H
#define AUCTION_H

#include <QDialog>

namespace Ui {
class auction;
}

class auction : public QDialog
{
    Q_OBJECT

public:
    explicit auction(QWidget *parent = nullptr);
    ~auction();

private:
    Ui::auction *ui;
};

#endif // AUCTION_H
