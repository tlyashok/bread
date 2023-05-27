#include <QApplication>
#include <QInputDialog>
#include <QMessageBox>
#include <QTcpSocket>
#include "singleclient.h"

SingletonClient::~SingletonClient()
{
    socket->close();
}

SingletonClient::SingletonClient()
{
    socket = new QTcpSocket(this);
    while (true) {
        // Запрос IP-адреса с помощью диалогового окна
        QString ipAddress = QInputDialog::getText(nullptr, "Подключение к серверу",
                                                  "Введите IP-адрес сервера:");

        if (ipAddress.isEmpty()) {
            ipAddress = "127.0.0.1"; // Установка значения по умолчанию
        }

        // Создание сокета TCP
        socket->connectToHost(ipAddress, 33333);  // Подключение к серверу на указанном порту

        // Проверка успешности подключения
        if (socket->waitForConnected()) {
            // Успешное подключение
            QMessageBox::information(nullptr, "Успех", "Успешное подключение к серверу!");
            break;  // Выход из цикла while
        } else {
            // Ошибка подключения
            QMessageBox::critical(nullptr, "Ошибка", "Не удалось подключиться к серверу!");

            // Диалоговое окно с вопросом о повторной попытке подключения
            QMessageBox retryMessageBox;
            retryMessageBox.setText("Повторить попытку подключения?");
            retryMessageBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Cancel);
            retryMessageBox.setDefaultButton(QMessageBox::Retry);
            int choice = retryMessageBox.exec();

            if (choice == QMessageBox::Cancel) {
                // Отмена - выход из цикла while
                break;
            }
        }
    }
    connect(socket, &QTcpSocket::readyRead, this, &SingletonClient::slot_readFromServer);
    qDebug() << "Клиент запущен";
}

void SingletonClient::slot_readFromServer()
{
    QString data;
    QStringList datas;
    while(socket->bytesAvailable()>0) {
        data.append(socket->readAll());
    }
    if (data.size() > 0) {
        qDebug() << "data: " << data << "\n";
        datas = data.split("\n");
        for (int i = 0; i < datas.size(); i++) {
            qDebug() << "datas["<<i<<"]: " << datas[i] << "\n";
            emit this->serverAnswer(datas[i]);
        }
    }
}

bool SingletonClient::sendToServer(QString answer)
{
    socket->write((answer+QString("\n")).toUtf8());
    return 0;
}
