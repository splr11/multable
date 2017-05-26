#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    initAll();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::initAll()
{
    setModal(true);
}

bool SettingsDialog::isReqLineChecked()
{
    return ui->req_line->isChecked();
}

bool SettingsDialog::isReqRandChecked()
{
    return ui->req_rand->isChecked();
}

bool SettingsDialog::isMul2Checked()
{
    return ui->mul2->isChecked();
}

bool SettingsDialog::isMul3Checked()
{
    return ui->mul3->isChecked();
}

bool SettingsDialog::isMul4Checked()
{
    return ui->mul4->isChecked();
}

bool SettingsDialog::isMul5Checked()
{
    return ui->mul5->isChecked();
}

bool SettingsDialog::isMul6Checked()
{
    return ui->mul6->isChecked();
}

bool SettingsDialog::isMul7Checked()
{
    return ui->mul7->isChecked();
}

bool SettingsDialog::isMul8Checked()
{
    return ui->mul8->isChecked();
}

bool SettingsDialog::isMul9Checked()
{
    return ui->mul9->isChecked();
}

void SettingsDialog::checkReqCount(QCheckBox* box)
{
    int req_count = ui->req_count->value();
    if(box->isChecked()) ui->req_count->setValue(req_count + 10);
    else
    {
        if(req_count != 10) ui->req_count->setValue(req_count - 10);
        else box->setChecked(true);
    }
}

void SettingsDialog::on_mul2_clicked()
{
    checkReqCount(ui->mul2);
}

void SettingsDialog::on_mul3_clicked()
{
    checkReqCount(ui->mul3);
}

void SettingsDialog::on_mul4_clicked()
{
    checkReqCount(ui->mul4);
}

void SettingsDialog::on_mul5_clicked()
{
    checkReqCount(ui->mul5);
}

void SettingsDialog::on_mul6_clicked()
{
    checkReqCount(ui->mul6);
}

void SettingsDialog::on_mul7_clicked()
{
    checkReqCount(ui->mul7);
}

void SettingsDialog::on_mul8_clicked()
{
    checkReqCount(ui->mul8);
}

void SettingsDialog::on_mul9_clicked()
{
    checkReqCount(ui->mul9);
}

int SettingsDialog::reqCount()
{
    return ui->req_count->value();
}
