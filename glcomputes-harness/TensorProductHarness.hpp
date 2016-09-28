#include <QTest>
#include <QString>
#include <QMatrix4x4>
#include <eigenHeader.hpp>
#include <Eigen/KroneckerProduct>
#include <iostream>
#include "MultiTest.hpp"

class TensorProductChecker : public QObject
{
	Q_OBJECT

public:
    TensorProductChecker();
    ~TensorProductChecker();

private Q_SLOTS:
	void initTestCase();
	void cleanupTestCase();

    void testCase1_data();
    void testCase1();

    void testCase2_data();
    void testCase2();

    void testCase3_data();
    void testCase3();
};

inline TensorProductChecker::TensorProductChecker()
{
}

inline TensorProductChecker::~TensorProductChecker()
{

}

inline void TensorProductChecker::initTestCase()
{
}

inline void TensorProductChecker::cleanupTestCase()
{
}

inline void TensorProductChecker::testCase1_data()
{
    QTest::addColumn<Eigen::Matrix2d>("data1");
    QTest::addColumn<Eigen::Matrix2d>("data2");
    QTest::addColumn<Eigen::Matrix4d>("expected");
    Eigen::Matrix2d inputMatrix1;
    inputMatrix1<<1,2,3,4;

    Eigen::Matrix2d inputMatrix2;
    inputMatrix2<<1,2,3,4;

    Eigen::Matrix4d outputMatrix;
    outputMatrix <<1,2,2,4,3,4,6,8,3,6,4,8,9,12,12,16;

    QTest::newRow("2x2 Tensor Product") << inputMatrix1 << inputMatrix2 << outputMatrix;
}

inline void TensorProductChecker::testCase1()
{
    QFETCH(Eigen::Matrix2d, data1);
    QFETCH(Eigen::Matrix2d, data2);
    QFETCH(Eigen::Matrix4d, expected);

    Eigen::Matrix4d result;
    result=kroneckerProduct(data1,data2).eval();
    QCOMPARE(result,expected);
}

inline void TensorProductChecker::testCase2_data()
{

    QTest::addColumn<Eigen::Matrix3d>("data1");
    QTest::addColumn<Eigen::Matrix3d>("data2");
    QTest::addColumn<Eigen::MatrixXd>("expected");
    Eigen::Matrix3d inputMatrix1;
    inputMatrix1=Eigen::MatrixXd::Random(3,3);

    Eigen::Matrix3d inputMatrix2;
    inputMatrix2=Eigen::MatrixXd::Random(3,3);

    Eigen::MatrixXd outputMatrix(9,9);
    outputMatrix=kroneckerProduct(inputMatrix1,inputMatrix2).eval();

    QTest::newRow("3x3 Tensor Product") << inputMatrix1 << inputMatrix2 << outputMatrix ;
}

inline void TensorProductChecker::testCase2()
{
    QFETCH(Eigen::Matrix3d, data1);
    QFETCH(Eigen::Matrix3d, data2);
    QFETCH(Eigen::MatrixXd,expected );

    Eigen::MatrixXd result;
    result=kroneckerProduct(data1,data2).eval();
    QCOMPARE(result,expected);
}


inline void TensorProductChecker::testCase3_data()
{

    QTest::addColumn<Eigen::Matrix4d>("data1");
    QTest::addColumn<Eigen::Matrix4d>("data2");
    QTest::addColumn<Eigen::MatrixXd>("expected");

    Eigen::Matrix4d inputMatrix1;
    inputMatrix1=Eigen::MatrixXd::Random(4,4);

    Eigen::Matrix4d inputMatrix2;
    inputMatrix2=Eigen::MatrixXd::Random(4,4);

    Eigen::MatrixXd outputMatrix(16,16);
    outputMatrix=kroneckerProduct(inputMatrix1,inputMatrix2).eval();

    QTest::newRow("4x4 Tensor Product") << inputMatrix1 << inputMatrix2 << outputMatrix ;
}

inline void TensorProductChecker::testCase3()
{
    QFETCH(Eigen::Matrix4d, data1);
    QFETCH(Eigen::Matrix4d, data2);
    QFETCH(Eigen::MatrixXd, expected);

    Eigen::MatrixXd result;
    result=kroneckerProduct(data1,data2).eval();
    QCOMPARE(result,expected);
}
TEST_DECLARE(TensorProductChecker)
