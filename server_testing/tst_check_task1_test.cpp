#include <QtTest>

// add necessary includes here
#include "..\server\functions.h"

class check_task1_test : public QObject
{
    Q_OBJECT

public:
    check_task1_test();
    ~check_task1_test();

private slots:
    void test_case1();

};

check_task1_test::check_task1_test()
{

}

check_task1_test::~check_task1_test()
{

}

void check_task1_test::test_case1()
{
    QVERIFY2(Functions::getInstance()->parse("yerunda") == QByteArray(QString("invalid_command").toUtf8()),
             Functions::getInstance()->parse("yerunda"));
}

QTEST_APPLESS_MAIN(check_task1_test)

#include "tst_check_task1_test.moc"
