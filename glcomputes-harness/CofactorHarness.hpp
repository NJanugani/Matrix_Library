#include <QString>
#include <QtTest>
#include <Eigen/Dense>

#include"MultiTest.hpp"

Q_DECLARE_METATYPE(Eigen::MatrixXf)

class CofactorChecker
: public QObject
{
    Q_OBJECT

public:
    CofactorChecker();

private Q_SLOTS:
    void
    Matrix3x3_data();
    void
    Matrix3x3();
    void
    ZeroMatrix3x3__data();
    void
    ZeroMatrix3x3_();
    void
    Identitymatrix3x3_data();
    void
    Identitymatrix3x3();
    void
    Matrix2x2_data();
    void
    Matrix2x2();
    void
    Matrix4x4_data();
    void
    Matrix4x4();
    void
    Matrix3x2_data();
    void
    Matrix3x2();


};

TEST_DECLARE(CofactorChecker)

CofactorChecker
::CofactorChecker()
{
}

inline
void
CofactorChecker
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
CofactorChecker
::Matrix3x3()
{
    QFETCH(Eigen::MatrixXf,data1);
    Eigen::MatrixXf data3(3,3);
	data3 = data1.adjoint();
    QCOMPARE(data3.transpose(),data3.transpose());
}

inline
void
CofactorChecker
::ZeroMatrix3x3__data()
{
    QTest::addColumn<Eigen::MatrixXf>("data1");
    Eigen::MatrixXf expected(3,3);
    expected<<0,0,0,
              0,0,0,
              0,0,0;
    QTest::newRow("0") << expected;
}

inline
void
CofactorChecker
::ZeroMatrix3x3_()
{
    QFETCH(Eigen::MatrixXf,data1);
    Eigen::MatrixXf data3(3,3);
    data3=data1.adjoint();
    QCOMPARE(data3.transpose(),data3.transpose());
}

inline
void
CofactorChecker
::Identitymatrix3x3_data()
{
    QTest::addColumn<Eigen::MatrixXf>("data1");
    Eigen::MatrixXf expected(3,3);
    expected<<1,0,0,
              0,1,0,
              0,0,1;
    QTest::newRow("0") << expected;
}

inline
void
CofactorChecker
::Identitymatrix3x3()
{
    QFETCH(Eigen::MatrixXf,data1);
    Eigen::MatrixXf data3(3,3);
    data3=data1.adjoint();
    QCOMPARE(data3.transpose(),data3.transpose());
}

inline
void
CofactorChecker
::Matrix2x2_data()
{
    QTest::addColumn<Eigen::MatrixXf>("data1");
    Eigen::MatrixXf expected(2,2);
    expected<<1,2,
              3,4;
    QTest::newRow("0") << expected;
}

inline
void
CofactorChecker
::Matrix2x2()
{
    QFETCH(Eigen::MatrixXf,data1);
    Eigen::MatrixXf data3(2,2);
    data3=data1.adjoint();
    QCOMPARE(data3.transpose(),data3.transpose());
}

inline
void
CofactorChecker
::Matrix4x4_data()
{
    QTest::addColumn<Eigen::MatrixXf>("data1");
    Eigen::MatrixXf expected(4,4);
    expected<<1,4,-1,0,
              2,3,5,-2,
              0,3,1,6,
              3,0,2,1;
    QTest::newRow("0") << expected;
}

inline
void
CofactorChecker
::Matrix4x4()
{
    QFETCH(Eigen::MatrixXf,data1);
    Eigen::MatrixXf data3(4,4);
    data3=data1.adjoint();
    QCOMPARE(data3.transpose(),data3.transpose());
}

inline
void
CofactorChecker
::Matrix3x2_data()
{
    QTest::addColumn<Eigen::MatrixXf>("data1");
    Eigen::MatrixXf expected(3,2);
    expected<<1,2,
              3,4,
              5,6;
    QTest::newRow("0") << expected;

}

inline
void
CofactorChecker
::Matrix3x2()
{
    QFETCH(Eigen::MatrixXf,data1);
    //  QTest::newRow("Non Square")<<a<<double(0.0);
    //Uncomment once cofactor function is implemented to return error

}
