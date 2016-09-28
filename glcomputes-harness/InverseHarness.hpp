#include <QtTest>
#include <QTest>
#include <Eigen/Dense>
#include <eigenHeader.hpp>
#include"MultiTest.hpp"

using namespace QTest;


class InverseChecker
: public QObject
{
    Q_OBJECT

public:
    InverseChecker();

private Q_SLOTS:
    void
    Matrix4x4_data();
    void
    Matrix4x4();
    void
    Matrix2x2_data();
    void
    Matrix2x2();
    void
    Matrix3x3A_data();
    void
    Matrix3x3A();
    void
    Matrix3x3B_data();
    void
    Matrix3x3B();
};

InverseChecker
::InverseChecker()
{
}

inline
void
InverseChecker
::Matrix4x4_data()
{
    addColumn<Eigen::Matrix4f>("data1");
    Eigen::Matrix4f expected;
    expected <<
    2.3, 1.3, 0.4, 0.6,
    0.4, 0.9, 4.7, 0.1,
    0.4, 0.9, 3.7, 0.1,
    7.3, 2.4, 0.1, 1.9;
    newRow("real 4x4 matrix") << expected;

}

inline
void
InverseChecker
::Matrix4x4()
{
    QFETCH(Eigen::Matrix4f,data1);
    QCOMPARE(data1.inverse(),data1.inverse());
}

inline
void
InverseChecker
::Matrix2x2_data()
{
    addColumn<Eigen::Matrix2f>("data2");
    Eigen::Matrix2f expected;
    expected <<
    2, 6,
    1, 3;
    newRow("real 2x2 matrix") << expected;

}

inline
void
InverseChecker
::Matrix2x2()
{
    QFETCH(Eigen::Matrix2f,data2);
    QCOMPARE(data2.inverse(),data2.inverse());
}

inline
void
InverseChecker
::Matrix3x3A_data()
{
    addColumn<Eigen::Matrix3f>("data3");
    Eigen::Matrix3f expected;
    expected <<
    -0.3034, 0.8884,-0.8095,
     0.2939,-1.1471,-2.9443,
    -0.7873,-1.0689, 1.4384;
    newRow("real 3x3 matrix") << expected;

}

inline
void
InverseChecker
::Matrix3x3A()
{
    QFETCH(Eigen::Matrix3f,data3);
    QCOMPARE(data3.inverse(),data3.inverse());
}

inline
void
InverseChecker
::Matrix3x3B_data()
{
    addColumn<Eigen::Matrix3f>("data4");
    Eigen::Matrix3f expected;
    expected <<
     1.4090,-1.2075, 0.4889,
     1.4172, 0.7172, 1.0347,
     0.6715, 1.6302, 0.7269;
    newRow("real 3x3 matrix") << expected;

}

inline
void
InverseChecker
::Matrix3x3B()
{
    QFETCH(Eigen::Matrix3f,data4);
    QCOMPARE(data4.inverse(),data4.inverse());
}

TEST_DECLARE(InverseChecker)
