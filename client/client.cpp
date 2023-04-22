#include "client.h"

Client::Client(QWidget* parent)
    : QMainWindow(parent)
{
    this->qsw = new QStackedWidget();
    this->mf = new mainForm();
    this->af = new authForm();
    this->tf = new taskForm();

    connect(af, af->reg, this, this->reg);
    connect(af, af->auth, this, this->auth);
    connect(mf, mf->exit, this, this->exit);
    connect(mf, mf->selectTask, this, this->selectTask);
    connect(this, this->selectTaskGenerated, tf, tf->selectTask);
    connect(tf, tf->sendAnswer, this, this->sendAnswer);

    this->qsw->addWidget(this->af);
    this->qsw->addWidget(this->mf);
    this->qsw->addWidget(this->tf);

    this->setCentralWidget((QWidget*)this->qsw);
    this->qsw->setCurrentIndex(0);
}

Client::~Client()
{

}

void Client::auth(QString login, QString password)
{
    qDebug() << "auth " << login << " " << password << "\n";
    this->qsw->setCurrentIndex(1);
}

void Client::reg(QString login, QString password, QString email)
{
    qDebug() << "reg " << login << " " << password << " " << email << "\n";
}

void Client::exit()
{
    // TODO: отрубить соединение с сервером и послать запрос о выходе пользователя в DB
    this->close();
}

void Client::selectTask(int task)
{
    // Нужно получить с сервера сид
    qDebug() << "get_task " << task << "\n";
    emit this->selectTaskGenerated(task, task * 1234 /* это просто пример */);
    this->qsw->setCurrentIndex(2);
}

void Client::sendAnswer(int task, int seed, QString answer)
{
    qDebug() << "task " << task << " " << seed << " " << answer << "\n";
    // отправить ответ на сервер на проверку
    this->qsw->setCurrentIndex(1);
}
