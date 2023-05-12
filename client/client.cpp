#include "client.h"
#include "singleclient.h"

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
    connect(SingletonClient::getInstance(), &SingletonClient::serverAnswer, this, this->parser);

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
    user_login = login;
    user_pass = password;
    SingletonClient::getInstance()->sendToServer("auth " + login + " " + password + "\n");
}

void Client::reg(QString login, QString password, QString  email)
{
    SingletonClient::getInstance()->sendToServer("reg " + login + " " + password + " " + email + "\n");
}

void Client::exit()
{
    if (auth_stat)
        SingletonClient::getInstance()->sendToServer("user_logout " + user_login + " " + user_pass + "\n");
    SingletonClient::getInstance()->~SingletonClient();
    this->close();
}

void Client::selectTask(int task)
{
    SingletonClient::getInstance()->sendToServer("get_task " + QString::number(task) + "\n");
}

void Client::sendAnswer(int task, int seed, QString answer)
{
    SingletonClient::getInstance()->sendToServer("task " + QString::number(task) + " " + QString::number(seed) + " " + answer + "\n");
    this->qsw->setCurrentIndex(1);
}

void Client::authVer(int result)
{
    if (result == 1)
    {
        this->qsw->setCurrentIndex(1);
        auth_stat = true;
    }
}

void Client::selectTaskVer(int task, int seed, QString task_text)
{
    emit this->selectTaskGenerated(task, seed, task_text);
    this->qsw->setCurrentIndex(2);
}

void Client::parser(QString serv_answer)
{
    QStringList data = serv_answer.split(' ');
    data[data.size()-1].chop(2);
    for (int i = 0; i < data.size(); i++) {
        qDebug() << data[i] << " ";
    }
    if (data[1] == "auth")
        authVer(data[2].toInt());
    else if (data[1] == "get_task")
        selectTaskVer(data[2].toInt(), data[3].toInt(), data[4]);
}
