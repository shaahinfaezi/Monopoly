#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameboard.h"
#include "QPixmap"
#include <QMessageBox>

bool empty_string_check(string s){

    if(all_of(s.begin(),s.end(),isspace)||s.empty()){
        return true;
    }
    else{
        return false;
    }

}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->pushButton->setIcon(QIcon(":/res/Images/push_buuton/7.png"));
    //ui->pushButton->setIconSize(QSize(700,500));


   QPixmap pic(":/res/Images/pic5.png");
   ui->labal2->setPixmap(pic.scaled(ui->labal2->width(),ui->labal2->height(),Qt::KeepAspectRatio));


   LineEdits.push_back(ui->lineEdit);

   LineEdits.push_back(ui->lineEdit_2);

   LineEdits.push_back(ui->lineEdit_3);

   LineEdits.push_back(ui->lineEdit_4);

   LineEdits.push_back(ui->lineEdit_5);

   LineEdits.push_back(ui->lineEdit_6);

   LineEdits.push_back(ui->lineEdit_7);

   LineEdits.push_back(ui->lineEdit_8);



    Labels.push_back(ui->label);

    Labels.push_back(ui->label_2);

    Labels.push_back(ui->label_3);

    Labels.push_back(ui->label_4);

    Labels.push_back(ui->label_5);

    Labels.push_back(ui->label_6);

    Labels.push_back(ui->label_7);

    Labels.push_back(ui->label_8);


    for(int i=0;i<8;i++){

        LineEdits.at(i)->hide();

        LineEdits.at(i)->setEnabled(false);

        Labels.at(i)->hide();

        Labels.at(i)->setEnabled(false);



    }

    ui->label_10->hide();

    ui->label_10->setEnabled(false);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{


    int number_of_players=ui->comboBox->currentText().toInt();

    bool empty_check=false;

    for(int i=0;i<number_of_players;i++){

        if(empty_string_check(LineEdits.at(i)->text().toUtf8().constData())){

            empty_check=true;

        }

    }
    bool DifferentNames=true;

    for(int i=0;i<number_of_players;i++){

        for(int j=0;j<number_of_players && i!=j;j++){

            if(LineEdits.at(i)->text()==LineEdits.at(j)->text()){
                DifferentNames=false;
            }


        }



    }

    if(ui->comboBox->currentIndex()==-1){


        QMessageBox::warning(this,"Warning","Please enter the number of players.");

    }
    else{

    if(empty_check==true){

         QMessageBox::warning(this,"Warning","Please enter all the names.");


    }
    if(DifferentNames==false){

        QMessageBox::warning(this,"Warning","Please enter different names.");

    }

    else if(DifferentNames==true && empty_check==false){

        vector<string> names;

        for(int i=0;i<number_of_players;i++){

            names.push_back(LineEdits.at(i)->text().toUtf8().constData());

        }


        GameBoard * gameboard=GameBoard::get_instance(names,this,number_of_players);

        this->hide();

        gameboard->show();
    }
}

}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    int number=arg1.toInt();

    ui->label_10->show();

    ui->label_10->setEnabled(true);

    for(int i=0;i<8;i++){



        LineEdits.at(i)->hide();

        LineEdits.at(i)->setEnabled(false);

        Labels.at(i)->hide();

        Labels.at(i)->setEnabled(false);



    }


    for(int i=0;i<number;i++){

        LineEdits.at(i)->show();

        LineEdits.at(i)->setEnabled(true);

        Labels.at(i)->show();

        Labels.at(i)->setEnabled(true);

        LineEdits.at(i)->setText("");


    }


}
