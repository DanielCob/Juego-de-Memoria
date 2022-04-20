#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void delay();

    void victoryMessage();

    void saveLastCard(int num);

    void changeTurn();

    void getPoints();

    void setLastCardsEnabled();

    void checkPair();

    QIcon readImage();

    void on_playButton_clicked();

    void on_exitButton_clicked();

    void on_button_00_clicked();

    void on_button_01_clicked();

    void on_button_05_clicked();

    void on_button_02_clicked();

    void on_button_03_clicked();

    void on_button_04_clicked();

    void on_button_10_clicked();

    void on_button_11_clicked();

    void on_button_12_clicked();

    void on_button_13_clicked();

    void on_button_14_clicked();

    void on_button_15_clicked();

    void on_button_20_clicked();

    void on_button_21_clicked();

    void on_button_22_clicked();

    void on_button_23_clicked();

    void on_button_24_clicked();

    void on_button_25_clicked();

    void on_button_30_clicked();

    void on_button_31_clicked();

    void on_button_32_clicked();

    void on_button_33_clicked();

    void on_button_34_clicked();

    void on_button_35_clicked();

    void on_button_40_clicked();

    void on_button_41_clicked();

    void on_button_42_clicked();

    void on_button_43_clicked();

    void on_button_44_clicked();

    void on_button_45_clicked();

    void on_doubleTurn_1_clicked();

    void on_doubleTurn_2_clicked();

    void on_pointsX2_1_clicked();

    void on_pointsX2_2_clicked();

    void on_pointsX3_1_clicked();

    void on_pointsX3_2_clicked();

private:
    Ui::MainWindow *ui;
    bool temp = true;
    int turn;
    int lastCard1;
    int lastCard2;
    bool doubleTurn = false;
    int pointsMultiplier = 1;
    int cardsClicked = 0;
    int cardsLeft = 30;
};
#endif // MAINWINDOW_H
