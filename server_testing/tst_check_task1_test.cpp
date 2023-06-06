#include <QtTest>

// add necessary includes here
#include "..\server\taskmanager.h"

class check_task1_test : public QObject
{
    Q_OBJECT

public:
    check_task1_test();
    ~check_task1_test();

private slots:
    void test_case1();
    void test_case2();
};

check_task1_test::check_task1_test()
{

}

check_task1_test::~check_task1_test()
{

}

void check_task1_test::test_case1()
{
    QVERIFY2(typeid(TaskManager::getInstance()->create_task(1)).name() == QString("7QString"),
            QString("Неверный тип возвращаемого значения: %1. Ожидается - 7QString")
             .arg(typeid(TaskManager::getInstance()->create_task(1)).name()).toUtf8());
}

void check_task1_test::test_case2()
{
    QVERIFY2(TaskManager::getInstance()->check_task(1, 1, "12 23") == true,
             "Неверная проверка задачи 1: false. Ожидается - true");
}

QTEST_APPLESS_MAIN(check_task1_test)

#include "tst_check_task1_test.moc"
