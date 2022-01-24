#include "arzi.h"
#include "ui_arzi.h"

arzi::arzi(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::arzi)
{
    ui->setupUi(this);

    connect (ui->b_green, &QPushButton::clicked, this, &arzi::gotopage);
    connect (ui->b_blue, &QPushButton::clicked, this, &arzi::gotopage);
    connect (ui->b_yellow, &QPushButton::clicked, this, &arzi::gotopage);

    connect (ui->b_gback, &QPushButton::clicked, this, &arzi::back);
    connect (ui->b_bback, &QPushButton::clicked, this, &arzi::back);
    connect (ui->b_yback, &QPushButton::clicked, this, &arzi::back);
}

arzi::~arzi()
{
    delete ui;
}

void arzi::gotopage()
{
    QPushButton *button = (QPushButton*)sender();

        if (button == ui->b_green) ui->stackedWidget->setCurrentIndex(1);
        if (button == ui->b_blue) ui->stackedWidget->setCurrentIndex(2);
        if (button == ui->b_yellow) ui->stackedWidget->setCurrentIndex(3);
}

void arzi::back()
{
    ui->stackedWidget->setCurrentIndex(0);
}

