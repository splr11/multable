#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString dir_path = a.applicationDirPath();

    /* Проверяем ресурсы */
    QFile file;
    file.setFileName(dir_path + "/res/icon.png");
    if(!file.exists())
    {
        QString error = QString::fromUtf8("Файл ") + file.fileName() + QString::fromUtf8(" не существует!");

        QMessageBox msg;
        msg.setWindowTitle(QString::fromUtf8("Ошибка!"));
        msg.setText(error);
        msg.exec();
        a.exit(-1);
        return -1;
    }
    file.setFileName(dir_path + "/res/tbl2.jpg");
    if(!file.exists())
    {
        QString error = QString::fromUtf8("Файл ") + file.fileName() + QString::fromUtf8(" не существует!");

        QMessageBox msg;
        msg.setWindowTitle(QString::fromUtf8("Ошибка!"));
        msg.setText(error);
        msg.exec();
        a.exit(-1);
        return -1;
    }

    MainWindow w(dir_path);
    w.show();

    return a.exec();
}
