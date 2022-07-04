#ifndef AUCTION_H
#define AUCTION_H

#include <QDialog>
#include "gameboard.h"
#include <vector>

using std::vector;

namespace Ui {
class auction;
}

class auction : public QDialog
{
    Q_OBJECT

public:
    explicit auction(QWidget *parent = nullptr);
    ~auction();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::auction *ui;

    GameBoard * gameBoard;

    Property* property;

    void print();

    int iterator;

    int HighestBid;

    vector<Player*> Bidders;

    int round;

    Player * HighestBidder;

    int BidderFinder(Player *);



};

#endif // AUCTION_H
