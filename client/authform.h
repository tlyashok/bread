#ifndef AUTHFORM_H
#define AUTHFORM_H

#include <QWidget>

namespace Ui {
class authForm;
}

class authForm : public QWidget
{
    Q_OBJECT

signals:
    void auth(QString login, QString password);
    void reg(QString login, QString password, QString email);

public:
    explicit authForm(QWidget *parent = nullptr);
    ~authForm();

private slots:
    void on_pushButton_switch_clicked();

    void on_pushButton_auth_or_reg_clicked();

private:
    void setAuthOrReg();

private:
    Ui::authForm *ui;
    bool authOrReg;
};

#endif // AUTHFORM_H
