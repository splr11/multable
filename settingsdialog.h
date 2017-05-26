#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QCheckBox>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

    bool isReqLineChecked();
    bool isReqRandChecked();

    bool isMul2Checked();
    bool isMul3Checked();
    bool isMul4Checked();
    bool isMul5Checked();
    bool isMul6Checked();
    bool isMul7Checked();
    bool isMul8Checked();
    bool isMul9Checked();

    int reqCount();
private slots:
    void on_mul2_clicked();
    void on_mul3_clicked();
    void on_mul4_clicked();
    void on_mul5_clicked();
    void on_mul6_clicked();
    void on_mul7_clicked();
    void on_mul8_clicked();
    void on_mul9_clicked();

private:
    Ui::SettingsDialog *ui;

    void initAll();
    void checkReqCount(QCheckBox* box);
};

#endif // SETTINGSDIALOG_H
