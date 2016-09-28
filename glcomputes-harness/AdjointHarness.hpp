#include <QString>
#include <QtTest>
#include <Eigen/Eigen>
#include <eigenHeader.hpp>

#include"MultiTest.hpp"

using namespace QTest;

class AdjointChecker
: public QObject
{
    Q_OBJECT

public:
	AdjointChecker();

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

inline
AdjointChecker
::AdjointChecker()
{
}

inline
void
AdjointChecker
::Matrix4x4_data()
{
    addColumn<Eigen::Matrix4f>("data1");
	Eigen::Matrix4f expected;
	expected <<
	2, 1, 1, 2,
	2, 1, 1, 1,
	2, 2, 2, 2,
	1, 1, 2, 1;

    newRow("real 4x4 Matrix") << expected;

}

inline
void
AdjointChecker
::Matrix4x4()
{
    QFETCH(Eigen::Matrix4f,data1);
    QCOMPARE(data1.adjoint(),data1.adjoint());
}

inline
void
AdjointChecker
::Matrix2x2_data()
{
    addColumn<Eigen::Matrix2f>("data2");
    Eigen::Matrix2f expected;
    expected <<
    2, 6,
    1, 3;

    newRow("real 2x2 Matrix") << expected;

}

inline
void
AdjointChecker
::Matrix2x2()
{
    QFETCH(Eigen::Matrix2f,data2);
    QCOMPARE(data2.adjoint(),data2.adjoint());
}

inline
void
AdjointChecker
::Matrix3x3A_data()
{
    addColumn<Eigen::Matrix3f>("data3");
    Eigen::Matrix3f expected;
    expected <<
    -0.3034, 0.8884,-0.8095,
     0.2939,-1.1471,-2.9443,
     0.7873,-1.0689, 1.4384;
    newRow("float 3x3 matrix") << expected;

}

inline
void
AdjointChecker
::Matrix3x3A()
{
    QFETCH(Eigen::Matrix3f,data3);
    QCOMPARE(data3.adjoint(),data3.adjoint());
}

inline
void
AdjointChecker
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
AdjointChecker
::Matrix3x3B()
{
    QFETCH(Eigen::Matrix3f,data4);
    QCOMPARE(data4.adjoint(),data4.adjoint());
}

TEST_DECLARE(AdjointChecker)
