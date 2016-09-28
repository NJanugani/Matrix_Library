#include <QString>
#include <QtTest>
#include <Eigen/Dense>
#include <QTest>
#include <eigenHeader.hpp>
#include "MultiTest.hpp"

using namespace QTest;
Q_DECLARE_METATYPE(Eigen::MatrixXf)

class TraceChecker
: public QObject
{
    Q_OBJECT

public:
    TraceChecker();

private Q_SLOTS:
    void
    Matrix3x3A_data();
    void
    Matrix3x3A();
    void
    Matrix3x3B_data();
    void
    Matrix3x3B();
    void
    Matrix4x3_data();
    void
    Matrix4x3();
};

TraceChecker
::TraceChecker()
{
}

inline
void
TraceChecker
::Matrix3x3A_data()
{
    addColumn<Eigen::Matrix3f>("data1");
    Eigen::Matrix3f expected;
    expected <<
    1.0, 2.0, 3.0,
    4.0, 5.0, 6.0,
    7.0, 8.0, 9.0;
    newRow("real 3x3 matrix") << expected;

}


inline
void
TraceChecker
::Matrix3x3A()
{
    QFETCH(Eigen::Matrix3f,data1);
	QCOMPARE(data1.trace(), data1.trace());
}

inline
void
TraceChecker
::Matrix3x3B_data()
{
    addColumn<Eigen::Matrix3f>("data2");
    Eigen::Matrix3f expected;
    expected <<
    0, 2, 3,
    4, 0, 6,
    7, 8, 0;
    newRow("real 3x3 matrix") << expected;
}

inline
void
TraceChecker
::Matrix3x3B()
{
    QFETCH(Eigen::Matrix3f,data2);
    QCOMPARE(data2.trace(),data2.trace());
}

inline
void
TraceChecker
::Matrix4x3_data()
{
    addColumn<Eigen::MatrixXf>("data3");
    Eigen::MatrixXf expected(4,3);
    expected <<
    -1, 2, 3,
     4,-5, 6,
     7, 8, 9,
     1, 1, 1;
    newRow("real 4x3 matrix") << expected;
}

inline
void
TraceChecker
::Matrix4x3()
{
    QFETCH(Eigen::MatrixXf,data3);
    QCOMPARE(data3.trace(),data3.trace());
}

TEST_DECLARE(TraceChecker)
