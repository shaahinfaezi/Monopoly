#ifndef COMMUNITY_CHANCE_H
#define COMMUNITY_CHANCE_H

#include <QDialog>
#include "gameboard.h"


namespace Ui {
class Community_Chance;
}

class Community_Chance : public QDialog
{
    Q_OBJECT

public:
    explicit Community_Chance(bool CommunityOrChance,QWidget *parent = nullptr);
    ~Community_Chance();

private:
    Ui::Community_Chance *ui;



    GameBoard * gameboard;
};

#endif // COMMUNITY_CHANCE_H
