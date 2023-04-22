#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QStackedWidget>
#include "mainform.h"
#include "authform.h"
#include "taskform.h"

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget* parent);
    ~Client();

private:
    ///
    /// \brief qsw
    ///
    /// Хранит в себе все формы: авторизации, главную и задания.
    ///
    QStackedWidget* qsw;
    ///
    /// \brief af
    ///
    /// Форма авторизации.
    ///
    authForm* af;
    ///
    /// \brief mf
    ///
    /// Главная форма, где происходит просмотр и выбор заданий.
    ///
    mainForm* mf;
    ///
    /// \brief tf
    ///
    /// Форма выполнения задания.
    ///
    taskForm* tf;

signals:
    ///
    /// \brief selectTaskGenerated
    /// \param task
    /// \param seed
    ///
    /// Отправляется в taskForm, передает полученные номер задания и сид.
    ///
    void selectTaskGenerated(int task, int seed);

private slots:
    ///
    /// \brief auth
    /// \param login
    /// \param password
    ///
    /// Принимает сигнал из authForm, отправляет запрос аутентификации на сервер.
    ///
    void auth(QString login, QString password);
    ///
    /// \brief reg
    /// \param login
    /// \param password
    /// \param email
    ///
    /// Принимает сигнал из authForm, отправляет запрос регистрации на сервер.
    ///
    void reg(QString login, QString password, QString email);
    ///
    /// \brief exit
    ///
    /// Принимает сигнал из mainForm, закрывает программу.
    ///
    void exit();
    ///
    /// \brief selectTask
    /// \param task
    ///
    /// Принимает сигнал из mainForm, отправляет запрос на получение сида для задания.
    ///
    void selectTask(int task);
    ///
    /// \brief sendAnswer
    /// \param task
    /// \param seed
    /// \param answer
    ///
    /// Принимает сигнал из taskForm, отправляет ответ на задание на сервер, получает сид
    /// и отправляет selectTaskGenerated.
    ///
    void sendAnswer(int task, int seed, QString answer);
};
#endif // MAINWINDOW_H
