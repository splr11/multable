#include "multable.h"

MulTable::MulTable()
{
    state = STATE_WAITING;
    question_state = NO_QUESTION;
    cur_answers = 0;

    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    mainI = 0;
    mainJ = 0;

    qMemSet(&settings, 0, sizeof(settings_t));
    initSettings();

    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            labels[i][j] = NULL;
            results[i][j] = -1;
        }
    }
}

MulTable::~MulTable()
{

}

void MulTable::initSettings()
{
    settings.active_lines[2] = true;
    settings.req_line = true;
    settings.answer_time = 5;
    settings.questions_count = 10;
}

void MulTable::setSettings(settings_t new_settings)
{
    settings = new_settings;
}

void MulTable::setState(int new_state)
{
    state = new_state;
}

void MulTable::setLabel(int i, int j, QLabel* label)
{
    labels[i][j] = label;
}

int MulTable::getState()
{
    return state;
}

int MulTable::getQuestionState()
{
    return question_state;
}

int MulTable::getAnswerTime()
{
    return settings.answer_time;
}

QString MulTable::updateLabel()
{
    if(!labels[mainI][mainJ])
    {
        qWarning("Not label!");
        return "";
    }

    question_state = WAIT_ANSWER;
    labels[mainI][mainJ]->setText(QString("%1 x %2 = ?").arg(mainI).arg(mainJ));
    labels[mainI][mainJ]->setShown(true);
    return QString("%1 x %2 = ").arg(mainI).arg(mainJ);
}

void MulTable::generateILine()
{
    while(!settings.active_lines[mainI] && mainI < 10) mainI++;
}

void MulTable::generateJLine()
{
    mainJ++;
}

QString MulTable::lineRequest()
{
    if(cur_answers == settings.questions_count)
    {
        question_state = REQUEST_ACOMPLISHED;
        return "";
    }

    generateILine();

    if(mainI > 9)
    {
        question_state = REQUEST_ACOMPLISHED;
        return "";
    }

    generateJLine();

    if(mainJ > 10)
    {
        mainJ = 0;
        mainI++;
        return "";
    }

    return updateLabel();
}

void MulTable::generateIRand()
{
    int i = 0;
    do {
        if(i > 144)
        {
            mainI = 10;
            break;
        }
        mainI = qrand() % 9 + 2;
        i++;
    } while(!settings.active_lines[mainI]);
}

void MulTable::generateJRand()
{
    int i = 0;
    int j = 0;
    do {
        if(i > 144)
        {
            i = 0;
            j++;
            generateIRand();
            if(mainI > 9)
            {
                mainJ = 11;
                break;
            }
        }
        if(j > 144)
        {
            mainJ = 11;
            break;
        }
        mainJ = qrand() % 10 + 1;
        i++;
    } while(results[mainI][mainJ] != -1);
}

QString MulTable::randRequest()
{
    if(cur_answers == settings.questions_count)
    {
        question_state = REQUEST_ACOMPLISHED;
        return "";
    }

    generateIRand();

    if(mainI > 9)
    {
        question_state = REQUEST_ACOMPLISHED;
        return "";
    }

    generateJRand();

    if(mainJ > 10)
    {
        question_state = REQUEST_ACOMPLISHED;
        return "";
    }

    return updateLabel();
}

QString MulTable::request()
{
    if(settings.req_line) return lineRequest();
    else return randRequest();
}

void MulTable::checkAnswer(int answer)
{
    QString str;
    if(mainI * mainJ != answer)
    {
        results[mainI][mainJ] = 0;
        labels[mainI][mainJ]->setStyleSheet("color: rgb(255, 0, 0)");
        str = QString::fromUtf8("%1 x %2 = %3, не %4").arg(mainI).arg(mainJ).arg(mainI * mainJ).arg(answer);
    }
    else
    {
        results[mainI][mainJ] = answer;
        labels[mainI][mainJ]->setStyleSheet("color: rgb(45, 134, 22)");
        str = QString("%1 x %2 = %3").arg(mainI).arg(mainJ).arg(answer);
    }

    int w = labels[mainI][mainJ]->fontMetrics().width(str);
    int h = labels[mainI][mainJ]->height();
    labels[mainI][mainJ]->resize(w, h);
    labels[mainI][mainJ]->setText(str);
    settings.answer_time = ANSWER_TIME;
    cur_answers++;
    question_state = NO_QUESTION;
}

void MulTable::decAnswerTime()
{
    settings.answer_time--;
}

void MulTable::checkResults(QLabel* resultLabel)
{
    int success = 0;
    int fail = 0;

    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            if(labels[i][j] && results[i][j] < 0) labels[i][j]->setText(QString("%1 x %2 = %3").arg(i).arg(j).arg(i * j));

            if(results[i][j] > 0) success++;
            if(results[i][j] == 0) fail++;
            results[i][j] = -1;
        }
    }

    if(resultLabel)
    {
        QString str = QString::fromUtf8("Всего ответов: %1; правильных: %2; ошибок: %3").arg(cur_answers).arg(success).arg(fail);
        int w = resultLabel->fontMetrics().width(str);
        int h = resultLabel->height();
        resultLabel->resize(w, h);
        resultLabel->setText(str);
        resultLabel->setDisabled(false);
        resultLabel->show();
    }
}

void MulTable::resetStates()
{
    state = STATE_WAITING;
    question_state = NO_QUESTION;
    cur_answers = 0;

    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    mainI = 0;
    mainJ = 0;
}
