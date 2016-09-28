
#include <QString>
#include <QtTest>
#include <eigenHeader.hpp>
#include <QTest>

#include"MultiTest.hpp"

//using namespace Qtest;
Q_DECLARE_METATYPE(Eigen::MatrixXf)

class TransposeChecker
: public QObject
{
    Q_OBJECT

public:
    TransposeChecker();

private Q_SLOTS:
    void
    Matrix3x3();
    void
    Matrix3x3_data();
    void
    Matrix3x2();
    void
    Matrix3x2_data();
    void
    Matrix3x1();
    void
    Matrix3x1_data();
    void
    Matrix1x3();
    void
    Matrix1x3_data();
    void
    Matrix2x3();
    void
    Matrix2x3_data();

};

inline
TransposeChecker
::TransposeChecker()
{
}

inline
void
TransposeChecker
::Matrix3x3_data()
{
    QTest::addColumn<Eigen::MatrixXf>("data1");
	Eigen::MatrixXf expected(3,3);
    expected <<
    1,2,3,
    4,5,6,
    7,8,9;
    QTest::newRow("0") << expected;
}

inline
void
TransposeChecker
::Matrix3x3()
{
    QFETCH(Eigen::MatrixXf,data1);
    QCOMPARE(data1.transpose(),data1.transpose());
}

inline
void
TransposeChecker
::Matrix3x2_data()
{
    QTest::addColumn<Eigen::MatrixXf>("data2");
    Eigen::MatrixXf expected(3,2);
    expected<<
    1,2,
    3,4,
    5,6;

    QTest::newRow("0") << expected;
}

inline
void
TransposeChecker
::Matrix3x2()
{
    QFETCH(Eigen::MatrixXf,data2);
    QCOMPARE(data2.transpose(),data2.transpose());
}

inline
void
TransposeChecker
::Matrix3x1_data()
{
    QTest::addColumn<Eigen::MatrixXf>("data3");
    Eigen::MatrixXf expected(3,1);
    expected<<
    1,
    2,
    3;

    QTest::newRow("0") << expected;
}

inline
void
TransposeChecker
::Matrix3x1()
{
    QFETCH(Eigen::MatrixXf,data3);
    QCOMPARE(data3.transpose(),data3.transpose());
}

inline
void
TransposeChecker
::Matrix1x3_data()
{
    QTest::addColumn<Eigen::MatrixXf>("data4");
    Eigen::MatrixXf expected(1,3);
    expected<<
    1,2,3;

    QTest::newRow("0") << expected;
}

inline
void
TransposeChecker
::Matrix1x3()
{
    QFETCH(Eigen::MatrixXf,data4);
    QCOMPARE(data4.transpose(),data4.transpose());
}

inline
void
TransposeChecker
::Matrix2x3_data()
{
    QTest::addColumn<Eigen::MatrixXf>("data5");
    Eigen::MatrixXf expected(2,3);
    expected<<
    1,2,3,
    4,5,6;
    QTest::newRow("0") << expected;
}

inline
void
TransposeChecker
::Matrix2x3()
{
    QFETCH(Eigen::MatrixXf,data5);
    QCOMPARE(data5.transpose(),data5.transpose());
}
TEST_DECLARE(TransposeChecker)
