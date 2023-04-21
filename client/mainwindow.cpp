#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
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
    connect(mf, mf->selectTask, tf, tf->selectTask);
    connect(tf, tf->sendAnswer, this, this->sendAnswer);

    this->qsw->addWidget(this->af);
    this->qsw->addWidget(this->mf);
    this->qsw->addWidget(this->tf);

    this->setCentralWidget((QWidget*)this->qsw);
    this->qsw->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{

}

void MainWindow::auth(QString login, QString password)
{
    qDebug() << "auth " << login << " " << password << "\n";
    this->qsw->setCurrentIndex(1);
}

void MainWindow::reg(QString login, QString password, QString email)
{
    qDebug() << "reg " << login << " " << password << " " << email << "\n";
}

void MainWindow::exit()
{
    // TODO: отрубить соединение с сервером и послать запрос о выходе пользователя в DB
    this->close();
}

void MainWindow::selectTask(int task)
{
    qDebug() << "get_task " << task << "\n";
    this->qsw->setCurrentIndex(2);
}

void MainWindow::sendAnswer(int task, int seed, QString answer)
{
    qDebug() << "task " << task << " " << seed << " " << answer << "\n";
    // отправить ответ на сервер на проверку
    this->qsw->setCurrentIndex(1);
}
