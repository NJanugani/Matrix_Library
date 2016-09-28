#include <QString>
#include <QtTest>
#include<Eigen/Dense>

#include"MultiTest.hpp"

Q_DECLARE_METATYPE(Eigen::MatrixXf)

using namespace QTest;

class StackChecker
: public QObject
{
    Q_OBJECT

public:
    StackChecker();

private Q_SLOTS:
    void
    HorizontalStack();
    void
    HorizontalStack_data();
    void
    Horizontalvectors();
    void
    Horizontalvectors_data();
    void
    Verticalvectors();
    void
    Verticalvectors_data();
    void
    VerticalStack();
    void
    VerticalStack_data();

};

inline
StackChecker
::StackChecker()
{
}

inline
void
StackChecker
::HorizontalStack_data()
{
    QTest::addColumn<Eigen::MatrixXf>("data1");
    QTest::addColumn<Eigen::MatrixXf>("data2");
       Eigen::MatrixXf actual1(3,3);
       actual1<<1,2,3,
                4,5,6,
                7,8,9;
       Eigen::MatrixXf actual2(3,1);
       actual2<<11,
                12,
                13;
       QTest::newRow("0") << actual1 << actual2;

}

inline
void
StackChecker
::HorizontalStack()
{
    QFETCH(Eigen::MatrixXf,data1);
    QFETCH(Eigen::MatrixXf,data2);
    Eigen::MatrixXf data3(3,4);
    data3<<data1,data2;
    QCOMPARE(data3,data3);
}

inline
void
StackChecker
::Horizontalvectors_data()
{
    QTest::addColumn<Eigen::MatrixXf>("data1");
    QTest::addColumn<Eigen::MatrixXf>("data2");
       Eigen::MatrixXf actual1(1,3);
       actual1<<1,2,3;
       Eigen::MatrixXf actual2(1,2);
       actual2<<11,12;
       QTest::newRow("0") << actual1 << actual2;

}

inline
void
StackChecker
::Horizontalvectors()
{
    QFETCH(Eigen::MatrixXf,data1);
    QFETCH(Eigen::MatrixXf,data2);
    Eigen::MatrixXf data3(1,5);
    data3<<data1,data2;
    QCOMPARE(data3,data3);
}

inline
void
StackChecker
:: Verticalvectors_data()
{
    QTest::addColumn<Eigen::MatrixXf>("data1");
    QTest::addColumn<Eigen::MatrixXf>("data2");
       Eigen::MatrixXf actual1(3,1);
       actual1<<1,
                2,
                3;
       Eigen::MatrixXf actual2(2,1);
       actual2<<11,
                12;
       QTest::newRow("0") << actual1 << actual2;

}

inline
void
StackChecker
::Verticalvectors()
{
    QFETCH(Eigen::MatrixXf,data1);
    QFETCH(Eigen::MatrixXf,data2);
    Eigen::MatrixXf data3(5,1);
    data3<<data1,data2;
    QCOMPARE(data3,data3);
}

inline
void
StackChecker
::VerticalStack_data()
{
    QTest::addColumn<Eigen::MatrixXf>("data1");
    QTest::addColumn<Eigen::MatrixXf>("data2");
       Eigen::MatrixXf actual1(3,2);
       actual1<<1,2,
                3,4,
                5,6;
       Eigen::MatrixXf actual2(2,2);
       actual2<<11,12,
                13,14;
       QTest::newRow("0") << actual1 << actual2;
}

inline
void
StackChecker
::VerticalStack()
{
    QFETCH(Eigen::MatrixXf,data1);
    QFETCH(Eigen::MatrixXf,data2);
    Eigen::MatrixXf data3(5,2);
    data3<<data1,data2;
    QCOMPARE(data3,data3);
}

TEST_DECLARE(StackChecker)
