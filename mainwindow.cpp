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
    //Set number button group
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
    lcdPanel->display(button->text().toInt());

}
