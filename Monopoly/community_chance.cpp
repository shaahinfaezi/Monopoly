#include "community_chance.h"
#include "ui_community_chance.h"

Community_Chance::Community_Chance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Community_Chance)
{
    ui->setupUi(this);
}

Community_Chance::~Community_Chance()
{
    delete ui;
}
