#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QStackedWidget>
#include "mainform.h"
#include "authform.h"
#include "taskform.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QStackedWidget* qsw;
    authForm* af;
    mainForm* mf;
    taskForm* tf;

private slots:
    void auth(QString login, QString password);
    void reg(QString login, QString password, QString email);
    void exit();
    void selectTask(int task);
    void sendAnswer(int task, int seed, QString answer);
};
#endif // MAINWINDOW_H
