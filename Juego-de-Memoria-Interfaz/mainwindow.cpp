#include <unistd.h>
#include <string.h>
#include <iostream>
#include <QTime>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "base64.h"

client c;
int lastCard1;
int lastCard2;
bool doubleTurn = false;
int pointsMultiplier = 1;
int turn;
int cardsClicked = 0;
int cardsLeft = 30;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->gameWindow->hide();
    ui->playerBoxShadow1->hide();
    ui->playerBoxShadow2->hide();
    ui->winMessage->hide();
    c.connectToServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::victoryMessage() {
    if (cardsLeft == 0) {
        if (ui->points1->text().toInt() > ui->points2->text().toInt()) {
            QString msg = "¡";
            msg.append(ui->playerName1->text());
            msg.append(" ganó la partida!");
            ui->winText->setText(msg);
        } else if (ui->points2->text().toInt() > ui->points1->text().toInt()) {
            QString msg = "¡";
            msg.append(ui->playerName2->text());
            msg.append(" ganó la partida!");
            ui->winText->setText(msg);
        } else {
            ui->winText->setText("¡Empate!");
        }
        ui->winMessage->show();
    }
}

void MainWindow::saveLastCard(int num)
{
    if (temp) {
        lastCard1 = num;
        temp = false;
    } else {
        lastCard2 = num;
        temp = true;
    }
}

void MainWindow::setLastCardsEnabled(){
    switch (lastCard1) {
        case 00:
            ui->button_00->setEnabled(true);
            ui->button_00->setIcon(QIcon());
        break;
        case 01:
            ui->button_01->setEnabled(true);
            ui->button_01->setIcon(QIcon());
        break;
        case 02:
            ui->button_02->setEnabled(true);
            ui->button_02->setIcon(QIcon());
        break;
        case 03:
            ui->button_03->setEnabled(true);
            ui->button_03->setIcon(QIcon());
        break;
        case 04:
            ui->button_04->setEnabled(true);
            ui->button_04->setIcon(QIcon());
        break;
        case 05:
            ui->button_05->setEnabled(true);
            ui->button_05->setIcon(QIcon());
        break;
        case 10:
            ui->button_10->setEnabled(true);
            ui->button_10->setIcon(QIcon());
        break;
        case 11:
            ui->button_11->setEnabled(true);
            ui->button_11->setIcon(QIcon());
        break;
        case 12:
            ui->button_12->setEnabled(true);
            ui->button_12->setIcon(QIcon());
        break;
        case 13:
            ui->button_13->setEnabled(true);
            ui->button_13->setIcon(QIcon());
        break;
        case 14:
            ui->button_14->setEnabled(true);
            ui->button_14->setIcon(QIcon());
        break;
        case 15:
            ui->button_15->setEnabled(true);
            ui->button_15->setIcon(QIcon());
        break;
        case 20:
            ui->button_20->setEnabled(true);
            ui->button_20->setIcon(QIcon());
        break;
        case 21:
            ui->button_21->setEnabled(true);
            ui->button_21->setIcon(QIcon());
        break;
        case 22:
            ui->button_22->setEnabled(true);
            ui->button_22->setIcon(QIcon());
        break;
        case 23:
            ui->button_23->setEnabled(true);
            ui->button_23->setIcon(QIcon());
        break;
        case 24:
            ui->button_24->setEnabled(true);
            ui->button_24->setIcon(QIcon());
        break;
        case 25:
            ui->button_25->setEnabled(true);
            ui->button_25->setIcon(QIcon());
        break;
        case 30:
            ui->button_30->setEnabled(true);
            ui->button_30->setIcon(QIcon());
        break;
        case 31:
            ui->button_31->setEnabled(true);
            ui->button_31->setIcon(QIcon());
        break;
        case 32:
            ui->button_32->setEnabled(true);
            ui->button_32->setIcon(QIcon());
        break;
        case 33:
            ui->button_33->setEnabled(true);
            ui->button_33->setIcon(QIcon());
        break;
        case 34:
            ui->button_34->setEnabled(true);
            ui->button_34->setIcon(QIcon());
        break;
        case 35:
            ui->button_35->setEnabled(true);
            ui->button_35->setIcon(QIcon());
        break;
        case 40:
            ui->button_40->setEnabled(true);
            ui->button_40->setIcon(QIcon());
        break;
        case 41:
            ui->button_41->setEnabled(true);
            ui->button_41->setIcon(QIcon());
        break;
        case 42:
            ui->button_42->setEnabled(true);
            ui->button_42->setIcon(QIcon());
        break;
        case 43:
            ui->button_43->setEnabled(true);
            ui->button_43->setIcon(QIcon());
        break;
        case 44:
            ui->button_44->setEnabled(true);
            ui->button_44->setIcon(QIcon());
        break;
        case 45:
            ui->button_45->setEnabled(true);
            ui->button_45->setIcon(QIcon());
        break;
    }
    switch (lastCard2) {
        case 00:
            ui->button_00->setEnabled(true);
            ui->button_00->setIcon(QIcon());
        break;
        case 01:
            ui->button_01->setEnabled(true);
            ui->button_01->setIcon(QIcon());
        break;
        case 02:
            ui->button_02->setEnabled(true);
            ui->button_02->setIcon(QIcon());
        break;
        case 03:
            ui->button_03->setEnabled(true);
            ui->button_03->setIcon(QIcon());
        break;
        case 04:
            ui->button_04->setEnabled(true);
            ui->button_04->setIcon(QIcon());
        break;
        case 05:
            ui->button_05->setEnabled(true);
            ui->button_05->setIcon(QIcon());
        break;
        case 10:
            ui->button_10->setEnabled(true);
            ui->button_10->setIcon(QIcon());
        break;
        case 11:
            ui->button_11->setEnabled(true);
            ui->button_11->setIcon(QIcon());
        break;
        case 12:
            ui->button_12->setEnabled(true);
            ui->button_12->setIcon(QIcon());
        break;
        case 13:
            ui->button_13->setEnabled(true);
            ui->button_13->setIcon(QIcon());
        break;
        case 14:
            ui->button_14->setEnabled(true);
            ui->button_14->setIcon(QIcon());
        break;
        case 15:
            ui->button_15->setEnabled(true);
            ui->button_15->setIcon(QIcon());
        break;
        case 20:
            ui->button_20->setEnabled(true);
            ui->button_20->setIcon(QIcon());
        break;
        case 21:
            ui->button_21->setEnabled(true);
            ui->button_21->setIcon(QIcon());
        break;
        case 22:
            ui->button_22->setEnabled(true);
            ui->button_22->setIcon(QIcon());
        break;
        case 23:
            ui->button_23->setEnabled(true);
            ui->button_23->setIcon(QIcon());
        break;
        case 24:
            ui->button_24->setEnabled(true);
            ui->button_24->setIcon(QIcon());
        break;
        case 25:
            ui->button_25->setEnabled(true);
            ui->button_25->setIcon(QIcon());
        break;
        case 30:
            ui->button_30->setEnabled(true);
            ui->button_30->setIcon(QIcon());
        break;
        case 31:
            ui->button_31->setEnabled(true);
            ui->button_31->setIcon(QIcon());
        break;
        case 32:
            ui->button_32->setEnabled(true);
            ui->button_32->setIcon(QIcon());
        break;
        case 33:
            ui->button_33->setEnabled(true);
            ui->button_33->setIcon(QIcon());
        break;
        case 34:
            ui->button_34->setEnabled(true);
            ui->button_34->setIcon(QIcon());
        break;
        case 35:
            ui->button_35->setEnabled(true);
            ui->button_35->setIcon(QIcon());
        break;
        case 40:
            ui->button_40->setEnabled(true);
            ui->button_40->setIcon(QIcon());
        break;
        case 41:
            ui->button_41->setEnabled(true);
            ui->button_41->setIcon(QIcon());
        break;
        case 42:
            ui->button_42->setEnabled(true);
            ui->button_42->setIcon(QIcon());
        break;
        case 43:
            ui->button_43->setEnabled(true);
            ui->button_43->setIcon(QIcon());
        break;
        case 44:
            ui->button_44->setEnabled(true);
            ui->button_44->setIcon(QIcon());
        break;
        case 45:
            ui->button_45->setEnabled(true);
            ui->button_45->setIcon(QIcon());
        break;
    }
}

void MainWindow::changeTurn() {
    if (turn == 1) {
        turn = 2;
        ui->playerBoxShadow1->hide();
        ui->playerBoxShadow2->show();
    } else {
        turn = 1;
        ui->playerBoxShadow1->show();
        ui->playerBoxShadow2->hide();
    }
}

void MainWindow::getPoints() {
    c.sendToServer("Points?");
    if (turn == 1) {
        ui->points1->setText(c.readSocket());
    } else {
        ui->points2->setText(c.readSocket());
    }
}

void MainWindow::checkPair() {
    cardsClicked++;
    if (cardsClicked%2 == 0) {
        c.sendToServer(std::to_string(pointsMultiplier).c_str());
        pointsMultiplier = 1;
        c.readSocket(); //Server: ok
        c.sendToServer("Is Pair?");
        std::string isPair = c.readSocket();
        std::cout << "Server: "<< isPair << std::endl;
        if (isPair == "0") {
            delay();
            setLastCardsEnabled();
        } else {
            cardsLeft -= 2;
        }
        victoryMessage();
        getPoints();
        if (!doubleTurn) {
            c.sendToServer("false"); //doubleTurn equals to false
            c.readSocket();
            changeTurn();
        } else {
            c.sendToServer("true"); //doubleTurn equals to true
            c.readSocket();
            doubleTurn = false;
        }
    }
}

QIcon MainWindow::readImage() {
    QPixmap image;
    QIcon icon;
    image.loadFromData(QByteArray::fromBase64(c.readSocket()));
    icon.addPixmap(image,QIcon::Disabled, QIcon::On);
    return icon;
}

void MainWindow::on_playButton_clicked()
{
    ui->name1->setText(ui->playerName1->text());
    c.sendToServer(ui->playerName1->text().toStdString().c_str());
    ui->points1->setText(c.readSocket());
    ui->name2->setText(ui->playerName2->text());
    c.sendToServer(ui->playerName2->text().toStdString().c_str());
    ui->points2->setText(c.readSocket());
    c.sendToServer("Starting player?");
    if ((QString) c.readSocket() == "1") {
        turn = 1;
        ui->playerBoxShadow1->show();
    } else {
        turn = 2;
        ui->playerBoxShadow2->show();
    }
    ui->gameWindow->show();
}

void MainWindow::on_exitButton_clicked()
{
    MainWindow::close();
}

void MainWindow::on_button_00_clicked()
{
    c.sendToServer("0,0");
    ui->button_00->setIcon(readImage());
    ui->button_00->setDisabled(true);
    saveLastCard(00);
    checkPair();
}


void MainWindow::on_button_01_clicked()
{
    c.sendToServer("0,1");
    ui->button_01->setIcon(readImage());
    ui->button_01->setDisabled(true);
    saveLastCard(01);
    checkPair();
}


void MainWindow::on_button_02_clicked()
{
    c.sendToServer("0,2");
    ui->button_02->setIcon(readImage());
    ui->button_02->setDisabled(true);
    saveLastCard(02);
    checkPair();
}


void MainWindow::on_button_03_clicked()
{
    c.sendToServer("0,3");
    ui->button_03->setIcon(readImage());
    ui->button_03->setDisabled(true);
    saveLastCard(03);
    checkPair();
}


void MainWindow::on_button_04_clicked()
{
    c.sendToServer("0,4");
    ui->button_04->setIcon(readImage());
    ui->button_04->setDisabled(true);
    saveLastCard(04);
    checkPair();
}


void MainWindow::on_button_05_clicked()
{
    c.sendToServer("0,5");
    ui->button_05->setIcon(readImage());
    ui->button_05->setDisabled(true);
    saveLastCard(05);
    checkPair();
}


void MainWindow::on_button_10_clicked()
{
    c.sendToServer("1,0");
    ui->button_10->setIcon(readImage());
    ui->button_10->setDisabled(true);
    saveLastCard(10);
    checkPair();
}


void MainWindow::on_button_11_clicked()
{
    c.sendToServer("1,1");
    ui->button_11->setIcon(readImage());
    ui->button_11->setDisabled(true);
    saveLastCard(11);
    checkPair();
}


void MainWindow::on_button_12_clicked()
{
    c.sendToServer("1,2");
    ui->button_12->setIcon(readImage());
    ui->button_12->setDisabled(true);
    saveLastCard(12);
    checkPair();
}


void MainWindow::on_button_13_clicked()
{
    c.sendToServer("1,3");
    ui->button_13->setIcon(readImage());
    ui->button_13->setDisabled(true);
    saveLastCard(13);
    checkPair();
}


void MainWindow::on_button_14_clicked()
{
    c.sendToServer("1,4");
    ui->button_14->setIcon(readImage());
    ui->button_14->setDisabled(true);
    saveLastCard(14);
    checkPair();
}


void MainWindow::on_button_15_clicked()
{
    c.sendToServer("1,5");
    ui->button_15->setIcon(readImage());
    ui->button_15->setDisabled(true);
    saveLastCard(15);
    checkPair();
}


void MainWindow::on_button_20_clicked()
{
    c.sendToServer("2,0");
    ui->button_20->setIcon(readImage());
    ui->button_20->setDisabled(true);
    saveLastCard(20);
    checkPair();
}


void MainWindow::on_button_21_clicked()
{
    c.sendToServer("2,1");
    ui->button_21->setIcon(readImage());
    ui->button_21->setDisabled(true);
    saveLastCard(21);
    checkPair();
}


void MainWindow::on_button_22_clicked()
{
    c.sendToServer("2,2");
    ui->button_22->setIcon(readImage());
    ui->button_22->setDisabled(true);
    saveLastCard(22);
    checkPair();
}


void MainWindow::on_button_23_clicked()
{
    c.sendToServer("2,3");
    ui->button_23->setIcon(readImage());
    ui->button_23->setDisabled(true);
    saveLastCard(23);
    checkPair();
}


void MainWindow::on_button_24_clicked()
{
    c.sendToServer("2,4");
    ui->button_24->setIcon(readImage());
    ui->button_24->setDisabled(true);
    saveLastCard(24);
    checkPair();
}


void MainWindow::on_button_25_clicked()
{
    c.sendToServer("2,5");
    ui->button_25->setIcon(readImage());
    ui->button_25->setDisabled(true);
    saveLastCard(25);
    checkPair();
}


void MainWindow::on_button_30_clicked()
{
    c.sendToServer("3,0");
    ui->button_30->setIcon(readImage());
    ui->button_30->setDisabled(true);
    saveLastCard(30);
    checkPair();
}


void MainWindow::on_button_31_clicked()
{
    c.sendToServer("3,1");
    ui->button_31->setIcon(readImage());
    ui->button_31->setDisabled(true);
    saveLastCard(31);
    checkPair();
}


void MainWindow::on_button_32_clicked()
{
    c.sendToServer("3,2");
    ui->button_32->setIcon(readImage());
    ui->button_32->setDisabled(true);
    saveLastCard(32);
    checkPair();
}


void MainWindow::on_button_33_clicked()
{
    c.sendToServer("3,3");
    ui->button_33->setIcon(readImage());
    ui->button_33->setDisabled(true);
    saveLastCard(33);
    checkPair();
}


void MainWindow::on_button_34_clicked()
{
    c.sendToServer("3,4");
    ui->button_34->setIcon(readImage());
    ui->button_34->setDisabled(true);
    saveLastCard(34);
    checkPair();
}


void MainWindow::on_button_35_clicked()
{
    c.sendToServer("3,5");
    ui->button_35->setIcon(readImage());
    ui->button_35->setDisabled(true);
    saveLastCard(35);
    checkPair();
}


void MainWindow::on_button_40_clicked()
{
    c.sendToServer("4,0");
    ui->button_40->setIcon(readImage());
    ui->button_40->setDisabled(true);
    saveLastCard(40);
    checkPair();
}


void MainWindow::on_button_41_clicked()
{
    c.sendToServer("4,1");
    ui->button_41->setIcon(readImage());
    ui->button_41->setDisabled(true);
    saveLastCard(41);
    checkPair();
}


void MainWindow::on_button_42_clicked()
{
    c.sendToServer("4,2");
    ui->button_42->setIcon(readImage());
    ui->button_42->setDisabled(true);
    saveLastCard(42);
    checkPair();
}


void MainWindow::on_button_43_clicked()
{
    c.sendToServer("4,3");
    ui->button_43->setIcon(readImage());
    ui->button_43->setDisabled(true);
    saveLastCard(43);
    checkPair();
}


void MainWindow::on_button_44_clicked()
{
    c.sendToServer("4,4");
    ui->button_44->setIcon(readImage());
    ui->button_44->setDisabled(true);
    saveLastCard(44);
    checkPair();
}


void MainWindow::on_button_45_clicked()
{
    c.sendToServer("4,5");
    ui->button_45->setIcon(readImage());
    ui->button_45->setDisabled(true);
    saveLastCard(45);
    checkPair();
}

void MainWindow::on_doubleTurn_1_clicked()
{
    doubleTurn = true;
    ui->doubleTurn_1->hide();
}


void MainWindow::on_doubleTurn_2_clicked()
{
    doubleTurn = true;
    ui->doubleTurn_2->hide();
}


void MainWindow::on_pointsX2_1_clicked()
{
    pointsMultiplier = 2;
    ui->pointsX2_1->hide();
}


void MainWindow::on_pointsX2_2_clicked()
{
    pointsMultiplier = 2;
    ui->pointsX2_2->hide();
}


void MainWindow::on_pointsX3_1_clicked()
{
    pointsMultiplier = 3;
    ui->pointsX3_1->hide();
}


void MainWindow::on_pointsX3_2_clicked()
{
    pointsMultiplier = 3;
    ui->pointsX3_2->hide();
}
