#include <QString>
#include <QtTest>
#include <Eigen/Dense>
#include <eigenHeader.hpp>

#include"MultiTest.hpp"


class InitializeChecker
: public QObject
{
    Q_OBJECT

public:
    InitializeChecker();

private Q_SLOTS:
    void
    Matrix2_data();
    void
    Matrix2();
    void
    Matrix1_data();
    void
    Matrix1();
    void
    Null_data();
    void
    Null();
    void
    Col5_data();
    void
    Col5();
};

TEST_DECLARE(InitializeChecker)

inline
InitializeChecker
::InitializeChecker()
{
}

void InitializeChecker
::Matrix2_data()
{
    QTest::addColumn<int>("M");
    QTest::addColumn<int>("N");
    QTest::addColumn<int>("Value");

    int actual1=4;
    int actual2=3;
    int actual3=2;

    QTest::newRow("Matrix2") << actual1 << actual2 << actual3;
}

inline
void InitializeChecker
::Matrix2()
{
    QFETCH(int, M);
    QFETCH(int, N);
    //QFETCH(int, Value);

    Eigen::MatrixXd expected(M,N);
    expected <<
    2, 2, 2,
    2, 2, 2,
    2, 2, 2,
    2, 2, 2;

    QCOMPARE(expected,expected);
}

inline
void InitializeChecker
::Matrix1_data()
{
    QTest::addColumn<int>("M");
    QTest::addColumn<int>("N");
    QTest::addColumn<int>("Value");

    int actual1=3;
    int actual2=3;
    int actual3=1;

    QTest::newRow("Matrix1") << actual1 << actual2 << actual3;
}

inline
void InitializeChecker
::Matrix1()
{
    QFETCH(int, M);
    QFETCH(int, N);
    //QFETCH(int, Value);

    Eigen::MatrixXd expected(M,N);
    expected <<
    1, 1, 1,
    1, 1, 1,
    1, 1, 1;

    QCOMPARE(expected,expected);
}

inline
void InitializeChecker
::Null_data()
{
    QTest::addColumn<int>("M");
    QTest::addColumn<int>("N");
    QTest::addColumn<int>("Value");

    int actual1=2;
    int actual2=2;
    int actual3=0;

    QTest::newRow("Null") << actual1 << actual2 << actual3;
}

inline
void InitializeChecker
::Null()
{
    QFETCH(int, M);
    QFETCH(int, N);
    //QFETCH(int, Value);

    Eigen::MatrixXd expected(M,N);
    expected <<
    0, 0,
    0, 0;

    QCOMPARE(expected,expected);
}

inline
void InitializeChecker
::Col5_data()
{
    QTest::addColumn<int>("M");
    QTest::addColumn<int>("N");
    QTest::addColumn<int>("Value");

    int actual1=4;
    int actual2=1;
    int actual3=5;

    QTest::newRow("Col5") << actual1 << actual2 << actual3;
}

inline
void InitializeChecker
::Col5()
{
    QFETCH(int, M);
    QFETCH(int, N);
    //QFETCH(int, Value);

    Eigen::MatrixXd expected(M,N);
    expected <<
    5,5,5,5;

    QCOMPARE(expected,expected);
}
