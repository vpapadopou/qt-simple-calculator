#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Set up empty display panel
    ui->displayPanel->clear();

    //Set operator and store number flags to false
    operatorClicked = false;
    hasStoredNumber = false;

    //Set number button group listener
    ui->numberGroup->connect(ui->numberGroup,SIGNAL(buttonClicked(QAbstractButton*)),
                             this, SLOT(numberGroup_clicked(QAbstractButton*)));
    //Set operator button group listener
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

    //Get string from display
    QString displayLabel = ui->displayPanel->text();

    /* Check if the previous button that was clicked was an operator button.
     * If so, clear the display and set the flag to false. Then proceed to
     * add the digit requested. */
    if (operatorClicked) {
        displayLabel.clear();
        operatorClicked = false;
    }

    //Append the digit only if we are not exceeding the digit limit
    if (displayLabel.length() >= DIGIT_LIMIT) {
        return;
    }

    //Append requested digit
    displayLabel.append(button->text());

    //Set number back to display
    ui->displayPanel->setText(displayLabel);

    //Convert string to double
    //double displayNumber = displayLabel.toDouble();

    //displayLabel = QString::number(displayNumber,'g', DIGIT_LIMIT);
}

// Called whenever an action button is clicked
void MainWindow::actionGroup_clicked(QAbstractButton* button)
{
    std::cout << "You have clicked button: " << button->text().toStdString() << std::endl;

    /* If the previous button that was clicked was not an operator, then we just need to save the operator
     * that was requested and exit.
     * If it was though, we need to see whether we just need to save the number that is
     * displayed or if there is already a number stored in memory, perform the calculation and
     * store the result.
     * Example for this case: 5 + 7 + -> We need to save 12 in memory and then save operator. */

    if (operatorClicked) {
        storedOperator = button->text().at(0);
        std::cout << "Change Operator " << std::endl;
    }
    else {
        std::cout << "New Operator " << std::endl;

        //Get string from display
        QString displayLabel = ui->displayPanel->text();

        if (hasStoredNumber) {
            //calculate here
            std::cout << "calculate " << std::endl;
            on_actionCalc_clicked();
        }
        else {
            //Set the flag to indicate that we now have a number stored in memory
            hasStoredNumber = true;
            //Convert string to double and save
            storedNumber = displayLabel.toDouble();
        }
        //Set the flag that the last button that was clicked was an operator
        operatorClicked = true;
        //Store operator in memory
        storedOperator = button->text().at(0);
    }
}

void MainWindow::on_actionDel_clicked()
{
    //Get string from display
    QString displayLabel = ui->displayPanel->text();

    //Check if label is empty
    if (displayLabel.length() == 0) {
        return;
    }

    //Delete last digit from string
    displayLabel.QString::chop(1);
    //Set number back to display
    ui->displayPanel->setText(displayLabel);
}

void MainWindow::on_actionCalc_clicked()
{
    //Get string from display
    QString displayLabel = ui->displayPanel->text();
    /* A number must be saved in memory to be able calculate a result.
     * In addition, a number with at least one digit should be present in the display and
     * The last button that was clicked should not be an operator */

    if (!hasStoredNumber || displayLabel.length() < 1 || operatorClicked) {
        std::cout << "Nope" << std::endl;
        return;
    }

   //If the displayed number ends with a comma, drop the comma.
    if (displayLabel.endsWith('.',Qt::CaseSensitive)) {
        displayLabel.QString::chop(1);
    }

    //Decide what to do according to operation

    if (storedOperator == '+') {
        storedNumber += displayLabel.toDouble();
    }
    else if (storedOperator == '-') {
        storedNumber -= displayLabel.toDouble();
    }
    else if (storedOperator == 'x') {
        storedNumber *= displayLabel.toDouble();
    }
    else if (storedOperator == '/') {
        storedNumber /= displayLabel.toDouble();
    }

    //Since there might be an overflow, its best to convert the number carefully
    displayLabel = QString::number(storedNumber,'g', DIGIT_LIMIT);

    //Set number back to display
    ui->displayPanel->setText(displayLabel);



    std::cout << "Result: " << storedNumber << std::endl;
}

void MainWindow::on_comma_clicked()
{
    //Get string from display
    QString displayLabel = ui->displayPanel->text();

    /* Append the digit only if we are not exceeding the digit limit.
     * More specifically in this case, we need 2 digits to be available.
     * One for the comma and at least another one for a remaining digit.
     * Also check if whether there is another comma already present. */
    if (displayLabel.length() >= (DIGIT_LIMIT - 1) ||
        displayLabel.contains('.', Qt::CaseSensitive)) {
        return;
    }

    //If label is empty, add zero and then append comma
    if (displayLabel.length() == 0) {
        displayLabel = "0";
    }

    //Append comma
    displayLabel.append('.');
    //Set number back to display
    ui->displayPanel->setText(displayLabel);
}

void MainWindow::on_actionClear_clicked()
{
    //Clear display label (for now)
    ui->displayPanel->clear();
    //Set operator and store number flags to false
    operatorClicked = false;
    hasStoredNumber = false;
}
