#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <deque>
#include <QMainWindow>
#include <QLCDNumber>
#include <QAbstractButton>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void numberGroup_clicked(QAbstractButton*);
    void actionGroup_clicked(QAbstractButton*);

    void on_actionDel_clicked();

    void on_actionCalc_clicked();

    void on_comma_clicked();

    void on_actionClear_clicked();

private:
    Ui::MainWindow *ui;
    //Digit limit
    const int DIGIT_LIMIT = 16;
    //Flag to check whether the previous button that was clicked was an operator
    bool operatorClicked;
    //Last operator requested
    QChar storedOperator;
    //Flag to check whether a number is stored in memory
    bool hasStoredNumber;
    //Stored number
    double storedNumber;
};

#endif // MAINWINDOW_H
