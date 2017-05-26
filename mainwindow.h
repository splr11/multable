#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "multable.h"
#include "settingsdialog.h"

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QMessageBox>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString path, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_menu_start_triggered();

    void on_menu_settings_triggered();

    void onMainTimer();

    void on_sendAnswer_clicked();

    void on_about_triggered();

private:
    QString dir_path;

    Ui::MainWindow *ui;
    QLabel* questions;
    SettingsDialog* dlg;

    QTimer* main_timer;

    /**
     * @brief table
     * Интерактивная таблица умножения
     */
    MulTable table;

    /**
     * @brief MainWindow::initQuestions
     * Инициализируем метки с вопросами
     */
    void initQuestions();

    /**
     * @brief MainWindow::initAll
     * Инициализируем всё
     */
    void initAll();

    /**
     * @brief getNewSettings
     * Получить настройки, если таковые поменялись
     */
    void getNewSettings();

    /**
     * @brief prepareRequest
     * Подготовить опрос
     */
    void prepareRequest();

    /**
     * @brief requestAcomplished
     * Опрос окончен
     */
    void requestAcomplished();

    void activateAnswerField(QString str);
    void deactivateAnswerField();

    void sendAnswer();
    void checkAnswerTime();

protected:
    virtual void keyPressEvent(QKeyEvent* event);
};

#endif // MAINWINDOW_H
