#include "controlform.h"
#include "ui_controlform.h"
#include <QIntValidator>
#include "looptest.h"
#include "mainwindow.h"

ControlForm::ControlForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlForm)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QIntValidator(0, 50, this));
}

ControlForm::~ControlForm()
{
    delete ui;
}

void ControlForm::on_pushButton_loopStart_clicked()
{
    nums = ui->lineEdit->text().toInt();
    Q_EMIT sg_control_start(nums);
}

void ControlForm::on_pushButton_reset_clicked()
{
    nums = ui->lineEdit->text().toInt();
    Q_EMIT sg_control_reset(nums);
}

void ControlForm::on_pushButton_loopStop_clicked()
{
    nums = ui->lineEdit->text().toInt();
    Q_EMIT sg_control_stop(nums);
}
