#include "client.h"
#include "singleclient.h"

Client::Client(QWidget* parent)
    : QMainWindow(parent)
{
    this->qsw = new QStackedWidget();
    this->mf = mainForm::getInstance();
    this->af = authForm::getInstance();
    this->tf = taskForm::getInstance();

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
    // SingletonClient::getInstance()->sendToServer("user_logout " + login + " " + password);

    SingletonClient::getInstance()->sendToServer("auth " + login + " " + password);
}

void Client::reg(QString login, QString password, bool studentOrTeacher, QString teacherCode)
{
    // Если тип учетной записи - преподаватель, то teacherCode пустой, это может вызвать ошибку на сервере
    SingletonClient::getInstance()->sendToServer("reg " + login + " " + password + " " + QString::number(int(studentOrTeacher)) + " " + teacherCode);
}

void Client::exit()
{
    if (auth_stat)
        SingletonClient::getInstance()->sendToServer("user_logout " + user_login + " " + user_pass);
    auth_stat = false;
    this->qsw->setCurrentIndex(0);
}

void Client::closeEvent(QCloseEvent *event)
{
    if (auth_stat)
        SingletonClient::getInstance()->sendToServer("user_logout " + user_login + " " + user_pass);
    SingletonClient::getInstance()->~SingletonClient();
    event->accept();
}

void Client::selectTask(int task)
{
    SingletonClient::getInstance()->sendToServer("get_task " + QString::number(task));
}

void Client::sendAnswer(int task, int seed, QString answer)
{
    SingletonClient::getInstance()->sendToServer("task " + QString::number(task) + " " + QString::number(seed) + " " + answer);
    this->qsw->setCurrentIndex(1);
}

void Client::authVer(int result)
{
    if (result == 1)
    {
        this->qsw->setCurrentIndex(1);
        auth_stat = true;
    }
    else
    {
        QMessageBox qmb;
        qmb.setText("При авторизации произошла ошибка!");
        qmb.exec();
    }
}

void Client::regVer(int result)
{
    if (result == 0)
    {
        QMessageBox qmb;
        qmb.setText("При регистрации произошла ошибка!");
        qmb.exec();
    }
}

void Client::selectTaskVer(int task, int seed, QString task_text)
{
    emit this->selectTaskGenerated(task, seed, task_text);
    this->qsw->setCurrentIndex(2);
}

void Client::parser(QString serv_answer)
{
    QStringList data = serv_answer.split(" ");
    qDebug() << "segmented_data: ";
    for (int i = 0; i < data.size(); i++)
        qDebug() << data[i] << " ";
    qDebug() << "\n";
    if (data.size() == 2 and data[0] == "auth") {
        authVer(data[1].toInt());
    }
    if (data.size() == 2 and data[0] == "reg") {
        regVer(data[1].toInt());
        if (data[1].toInt() == 1) {
            af->auth_user();
        }
    }
    else if (data.size() == 4 and data[0] == "get_task")
        selectTaskVer(data[1].toInt(), data[2].toInt(), data[3]);
}
