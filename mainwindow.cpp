#include "mainwindow.h"
#include "ui_mainwindow.h"

const QPoint points_deafult[10] = {
    QPoint(0, 0),
    QPoint(0, 0),
    QPoint(121, 68), // 2
    QPoint(264, 68), // 3
    QPoint(404, 68), // 4
    QPoint(548, 68), // 5
    QPoint(168, 264), // 6
    QPoint(312, 264), // 7
    QPoint(453, 264), // 8
    QPoint(597, 264) // 9
};

MainWindow::MainWindow(QString path, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    dir_path = path;

    ui->setupUi(this);
    initAll();
}

MainWindow::~MainWindow()
{
    delete [] questions;
    delete dlg;
    delete main_timer;
    delete ui;
}

/**
 * @brief MainWindow::initQuestions
 * Инициализируем метки с вопросами
 */
void MainWindow::initQuestions()
{
    dlg = new SettingsDialog(this);

    questions = new QLabel[80];
    int index = 0;
    int x;
    int y;
    for(int i = 2; i < 10; i++)
    {
        x = points_deafult[i].x();
        y = points_deafult[i].y();
        for(int j = 1; j < 11; j++)
        {
            questions[index].setParent(ui->bckgnd);
            questions[index].setText(QString("%1 x %2 = %3").arg(i).arg(j).arg(i * j));
            questions[index].move(x, y);
            QFont font = questions[index].font();
            font.setPixelSize(17);
            questions[index].setFont(font);

            table.setLabel(i, j, &questions[index]);

            index++;
            y += 17;
        }
    }
}

/**
 * @brief MainWindow::initAll
 * Инициализируем всё
 */
void MainWindow::initAll()
{
    /* Устанавливаем иконку */
    QIcon logo(dir_path + "/res/icon.png");
    setWindowIcon(logo);

    /* Устанавливаем фон */
    QPixmap pix(dir_path + "/res/tbl2.jpg");
    ui->bckgnd->move(0, 0);
    ui->bckgnd->resize(pix.size());
    ui->bckgnd->setPixmap(pix);

    /* Подгоняем размеры окна */
    resize(ui->bckgnd->width(), ui->bckgnd->height() + ui->menuBar->height() + ui->answer->height() + 3);
    setMinimumSize(ui->bckgnd->width(), ui->bckgnd->height() + ui->menuBar->height() + 3);
    setMaximumSize(ui->bckgnd->width(), ui->bckgnd->height() + ui->menuBar->height() + 3);

    /* Настраиваем поле ввода ответов */
    int x = 200;
    int y = 460;
    deactivateAnswerField();
    ui->answerLabel->move(x, y);
    ui->answer->move(x + ui->answerLabel->width(), y);
    ui->sendAnswer->move(x + ui->answerLabel->width()+ui->answer->width() + 14, y);
    ui->answerTime->move(x + ui->answerLabel->width()+ui->answer->width()+ui->sendAnswer->width() + 24, y);

    QString stylesheet = "color: #000000;";
    ui->answerLabel->setStyleSheet(stylesheet);
    ui->answer->setStyleSheet(stylesheet);
    ui->sendAnswer->setStyleSheet(stylesheet);
    ui->answerTime->setStyleSheet(stylesheet);

    /* Настраиваем главный таймер */
    main_timer = new QTimer();
    main_timer->setInterval(1000);
    connect(main_timer, SIGNAL(timeout()), this, SLOT(onMainTimer()));

    /* Инициализируем метки с, собственно, таблицей умножения */
    initQuestions();
}

/**
 * @brief prepareRequest
 * Подготовить опрос
 */
void MainWindow::prepareRequest()
{
    ui->menu_start->setDisabled(true);
    ui->menu_settings->setDisabled(true);

    for(int i = 0; i < 80; i++)
    {
        questions[i].setStyleSheet("color: rgb(0,0,0)");
        questions[i].hide();
    }

    table.setState(STATE_RUNNING);

    main_timer->start();
}

/**
 * @brief requestAcomplished
 * Опрос окончен
 */
void MainWindow::requestAcomplished()
{
    table.checkResults(ui->answerLabel);
    table.resetStates();

    ui->menu_start->setEnabled(true);
    ui->menu_settings->setEnabled(true);

    for(int i = 0; i < 80; i++) questions[i].show();
}

void MainWindow::activateAnswerField(QString str)
{
    ui->answer->setValue(0);
    ui->answer->setDisabled(false);
    ui->answer->setHidden(false);
    ui->answer->setFocus();
    ui->answer->selectAll();
    ui->answerLabel->setText(str);
    ui->answerLabel->setDisabled(false);
    ui->answerLabel->setHidden(false);
    ui->sendAnswer->setDisabled(false);
    ui->sendAnswer->setHidden(false);
    ui->answerTime->setDisabled(false);
    ui->answerTime->setHidden(false);
}

void MainWindow::deactivateAnswerField()
{
    ui->answer->setDisabled(true);
    ui->answer->setHidden(true);
    ui->answerLabel->setDisabled(true);
    ui->answerLabel->setHidden(true);
    ui->sendAnswer->setDisabled(true);
    ui->sendAnswer->setHidden(true);
    ui->answerTime->setDisabled(true);
    ui->answerTime->setHidden(true);
}

void MainWindow::on_menu_start_triggered()
{
    prepareRequest();
}

/**
 * @brief getNewSettings
 * Получить настройки, если таковые поменялись
 */
void MainWindow::getNewSettings()
{
    if(dlg->exec() == QDialog::Accepted)
    {
        MulTable::settings_t settings;
        qMemSet(&settings, 0, sizeof(MulTable::settings_t));

        if(dlg->isReqLineChecked()) settings.req_line = true;
        if(dlg->isReqRandChecked()) settings.req_line = false;

        settings.active_lines[2] = dlg->isMul2Checked();
        settings.active_lines[3] = dlg->isMul3Checked();
        settings.active_lines[4] = dlg->isMul4Checked();
        settings.active_lines[5] = dlg->isMul5Checked();
        settings.active_lines[6] = dlg->isMul6Checked();
        settings.active_lines[7] = dlg->isMul7Checked();
        settings.active_lines[8] = dlg->isMul8Checked();
        settings.active_lines[9] = dlg->isMul9Checked();

        settings.questions_count = dlg->reqCount();
        settings.answer_time = ANSWER_TIME;

        table.setSettings(settings);
    }
}

void MainWindow::on_menu_settings_triggered()
{
    getNewSettings();
}

void MainWindow::onMainTimer()
{
    if(table.getState() == STATE_RUNNING)
    {
        if(table.getQuestionState() == NO_QUESTION)
        {
            QString str = table.request();
            if(str != "") activateAnswerField(str);
        }
        if(table.getQuestionState() == WAIT_ANSWER)
        {
            checkAnswerTime();
        }
        if(table.getQuestionState() == REQUEST_ACOMPLISHED)
        {
            requestAcomplished();
        }
    }
    else main_timer->stop();
}

void MainWindow::checkAnswerTime()
{
    QString str = QString::fromUtf8("Осталось %1 сек").arg(table.getAnswerTime());
    int w = ui->answerTime->fontMetrics().width(str);
    int h = ui->answerTime->height();
    ui->answerTime->resize(w, h);
    ui->answerTime->setText(str);
    if(table.getAnswerTime() == 0) sendAnswer();
    else table.decAnswerTime();
}

void MainWindow::sendAnswer()
{
    deactivateAnswerField();
    table.checkAnswer(ui->answer->value());
}

void MainWindow::on_sendAnswer_clicked()
{
    sendAnswer();
}

void MainWindow::on_about_triggered()
{
    QMessageBox msg;
    QIcon logo(dir_path + "/res/icon.png");
    msg.setWindowIcon(logo);
    msg.setWindowTitle(QString::fromUtf8("О программе..."));
    msg.setText(QString::fromUtf8("Таблица умножения.\n"
                "Версия '1.0'.\n\n"
                "(c) Михаил 'splr11' Соломатин, 2017 г."));
    msg.exec();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    int key = event->key();
    if(key == Qt::Key_Return)
    {
        if(table.getQuestionState() == WAIT_ANSWER) sendAnswer();
    }
}
