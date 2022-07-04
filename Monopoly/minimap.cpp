#include "minimap.h"
#include "ui_minimap.h"

minimap::minimap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::minimap)
{
    ui->setupUi(this);
}

minimap::~minimap()
{
    delete ui;
}
