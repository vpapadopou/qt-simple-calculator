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
    //Set up numbers deque (just push "EMPTY" value to denote an empty number slot)
    numbers.push_back("EMPTY");
    //Set number button group listener
    ui->numberGroup->connect(ui->numberGroup,SIGNAL(buttonClicked(QAbstractButton*)),
                             this, SLOT(numberGroup_clicked(QAbstractButton*)));
    //Set action button group listener
    ui->actionGroup->connect(ui->actionGroup,SIGNAL(buttonClicked(QAbstractButton*)),
                             this, SLOT(actionGroup_clicked(QAbstractButton*)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


// Called whenever a number button is clicked
void MainWindow::numberGroup_clicked(QAbstractButton* button)
{
    std::cout << "You have clicked button: " << button->text().toStdString() << std::endl;

    //Note: Need to prevent overflow as well

    //Check whether there is an empty number slot in numbers deque
    if (QString::compare(numbers.back(), "EMPTY", Qt::CaseSensitive)) {
        //If there is not an empty slot, append the requested number at the end of the string
        numbers.back().QString::append(button->text());
    }
    else {
        // If there is an empty slot, insert the requested number
        //numbers.push_back(button->text());
        numbers.back() = button->text();
    }

    /* Finally set the number to the lcd screen
     * Note: Since the lcd screen has only 8 digits, update only if our number is less than that
     * Otherwise we will eventually get 0 because of overflow */
    if (numbers.back().QString::length() <= 8) {
        lcdPanel->display(numbers.back().toInt());
    }




    std::cout << "Number: " << numbers.back().toStdString() << std::endl;

    //lcdPanel->display(button->text().toInt());

}

// Called whenever an action button is clicked
void MainWindow::actionGroup_clicked(QAbstractButton* button)
{
    std::cout << "You have clicked button: " << button->text().toStdString() << std::endl;

    /* If there is an empty slot in the numbers deque, then we need to replace the last action with the
     * current one. Else just push to the actions deque and open a new empty slot in the numbers deque */

    if (QString::compare(numbers.back(), "EMPTY", Qt::CaseSensitive)) {
        std::cout << "Add new" << std::endl;
        operators.push_back(button->text().at(0));
        //Push empty to numbers deqeue to denote empty slot
        numbers.push_back("EMPTY");
        std::cout << "Operator: " << operators.back().toLatin1() << std::endl;
    }
    else {
        /* Check first whether there is at least a valid number store in the numbers deque.
         * If not it would not make sense to add the operator.
         * In layman's terms first button clicked is an operator */
        std::cout << "Replace" << std::endl;
        if (numbers.size() > 1) {
            operators.back() = button->text().at(0);
            std::cout << "Operator: " << operators.back().toLatin1() << std::endl;
        }
    }

}
