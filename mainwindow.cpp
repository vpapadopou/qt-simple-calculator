#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //Set up lcd panel
    lcdPanel = ui->lcdNumber;
    lcdPanel->display(0);
    //Set up numbers deque (just push zero value to denote an empty number slot)
    numbers.push_back("0");
    //Set number button group listener
    ui->numberGroup->connect(ui->numberGroup,SIGNAL(buttonClicked(QAbstractButton*)),
                             this, SLOT(numberGroup_clicked(QAbstractButton*)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::numberGroup_clicked(QAbstractButton* button)
{
    std::cout << "You have clicked button: " << button->text().toStdString() << std::endl;

    //Note: Need to prevent overflow as well

    //Check whether there is an empty number slot in numbers deque (denoted by a simple zero value)
    if (QString::compare(numbers.back(), "0", Qt::CaseSensitive)) {
        //If there is not an empty slot, append the requested number at the end of the string
        numbers.back().QString::append(button->text());
    }
    else {
        /* If there is an empty slot, insert the requested number and remove zero
        First of course, make sure that the number requested is not actually zero itself */
        if (QString::compare(button->text(), "0", Qt::CaseSensitive)) {
            numbers.push_back(button->text());
        }
    }

    /* Finally set the number to the lcd screen
    Note: Since the lcd screen has only 8 digits, update only if our number is less than that
    Otherwise we will eventually get 0 because of overflow */
    if (numbers.back().QString::length() <= 8) {
        lcdPanel->display(numbers.back().toInt());
    }




    std::cout << "Number: " << numbers.back().toStdString() << std::endl;

    //lcdPanel->display(button->text().toInt());

}
