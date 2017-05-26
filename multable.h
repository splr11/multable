#ifndef MULTABLE_H
#define MULTABLE_H

#define STATE_WAITING 0
#define STATE_RUNNING 1

#define NO_QUESTION 0
#define WAIT_ANSWER 1
#define REQUEST_ACOMPLISHED 2

#define ANSWER_TIME 10

#include <QLabel>
#include <QString>
#include <QTime>

/**
 * @brief The MulTable class
 * Interactive multiplication table
 * (c) Mikhail 'splr11' Solomatin, 2017
 */
class MulTable
{
public:
    struct settings_t
    {
        bool req_line; // Опрашивать последовательно или в случайном порядке
        bool active_lines[10]; // По каким числам будет проводиться опрос
        int questions_count; // Количество заданных вопросв
        int answer_time; // Время на ответ
    };

    MulTable();
    ~MulTable();

    void setSettings(settings_t new_settings);
    void setState(int new_state);

    void setLabel(int i, int j, QLabel* label);

    int getState();
    int getQuestionState();
    int getAnswerTime();

    QString request();

    void checkAnswer(int answer);
    void decAnswerTime();
    void checkResults(QLabel* resultLabel);
    void resetStates();
private:
    settings_t settings;
    QLabel* labels[11][11];
    int results[11][11];
    int state;
    int question_state;

    /**
     * @brief cur_answers
     * Текущее количество ответов
     */
    int cur_answers;

    void initSettings();

    int mainI;
    int mainJ;

    QString lineRequest();
    QString randRequest();

    void generateILine();
    void generateJLine();
    void generateIRand();
    void generateJRand();

    QString updateLabel();
};

#endif // MULTABLE_H
