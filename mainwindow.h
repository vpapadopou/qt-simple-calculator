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

private:
    Ui::MainWindow *ui;
    //Lcd panel
    QLCDNumber *lcdPanel;
    //Numbers and operators
    std::deque <QString> numbers;
    std::deque <char> operators;
};

#endif // MAINWINDOW_H
