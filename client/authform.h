#ifndef AUTHFORM_H
#define AUTHFORM_H

#include <QWidget>
#include "singleton.h"

namespace Ui {
class authForm;
}
///
/// \brief The authForm class
///
/// Форма авторизации и регистрации.
/// Открывается при запуске программы.
///
class authForm : public QWidget, public Singleton<authForm>
{
    Q_OBJECT

signals:
    ///
    /// \brief auth
    /// \param login
    /// \param password
    ///
    /// Вызывается при нажатии на кнопку авторизации.
    /// Принимается в классе Client
    ///
    void auth(QString login, QString password);
    ///
    /// \brief reg
    /// \param login
    /// \param password
    /// \param email
    ///
    /// Вызывается при нажатии на кнопку регистрации.
    /// Принимается в классе Client
    ///
    void reg(QString login, QString password, bool studentOrTeacher, QString teacherCode);

private:
    friend class Singleton<authForm>;
    explicit authForm(QWidget *parent = nullptr);
    ~authForm();

public:
    ///
    /// \brief auth_user
    /// Проводит авторизацию пользователя
    ///
    void auth_user();

private slots:
    void on_pushButton_switch_clicked();

    void on_pushButton_auth_or_reg_clicked();

    void on_pushButton_regtype_clicked();

private:
    ///
    /// \brief uiReset
    ///
    /// Изменяет видимость кнопок и полей в зависимости от
    /// того, что происходит: регистрация или авторизация
    ///
    void uiReset();

private:
    Ui::authForm *ui;
    ///
    /// \brief authOrReg
    ///
    /// Хранит текущее состояние формы: авторизация
    /// или регистрация
    ///
    bool authOrReg;
    ///
    /// \brief studentOrTeacher
    ///
    /// Хранит тип учетной записи при регистрации:
    /// Студент или Преподаватель
    ///
    bool studentOrTeacher;
};

#endif // AUTHFORM_H
