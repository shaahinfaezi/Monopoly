#include "auction.h"
#include "ui_auction.h"

auction::auction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::auction)
{
    ui->setupUi(this);
}

auction::~auction()
{
    delete ui;
}
