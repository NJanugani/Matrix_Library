#include <QTest>
#include <QString>
#include <QMatrix4x4>
#include <eigenHeader.hpp>
#include "MultiTest.hpp"

class isInvertibleChecker : public QObject
{
	Q_OBJECT

public:
    isInvertibleChecker();
    ~isInvertibleChecker();
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

isInvertibleChecker::isInvertibleChecker()
{
}
isInvertibleChecker::~isInvertibleChecker()
{

}

void isInvertibleChecker::initTestCase()
{
}

void isInvertibleChecker::cleanupTestCase()
{
}

void isInvertibleChecker::testCase1_data()
{
    QTest::addColumn<Eigen::Matrix2d>("data");
    QTest::addColumn<double>("result");
    Eigen::Matrix2d inputMatrix;
    inputMatrix << 12,3,4,5;

    QTest::newRow("2x2 InvertibleCheck") << inputMatrix ;
}

void isInvertibleChecker::testCase1()
{
    QFETCH(Eigen::Matrix2d, data);
    double expected = 48;

    QCOMPARE(data.determinant(),expected);
}

void isInvertibleChecker::testCase2_data()
{
    QTest::addColumn<Eigen::Matrix3d>("data");
	QTest::addColumn<double>("result");
    Eigen::Matrix3d inputMatrix;
    inputMatrix<<0,0,0,0,0,0,0,0,0;

    QTest::newRow("3x3 InvertibleCheck") << inputMatrix ;
}

void isInvertibleChecker::testCase2()
{
    QFETCH(Eigen::Matrix3d, data);
    double expected = 0;

    QCOMPARE(data.determinant(),expected);
}


void isInvertibleChecker::testCase3_data()
{

    QTest::addColumn<Eigen::Matrix4d>("data");
    QTest::addColumn<double>("result");
    Eigen::Matrix4d inputMatrix;
    inputMatrix<<0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1;

    QTest::newRow("4x4 InvertibleCheck") << inputMatrix ;
}

void isInvertibleChecker::testCase3()
{
    QFETCH(Eigen::Matrix4d, data);
    double expected = 0;

    QCOMPARE(data.determinant(),expected);
}




TEST_DECLARE(isInvertibleChecker)
