#include <QTest>
#include <QString>
#include <QMatrix4x4>
#include <eigenHeader.hpp>
#include "MultiTest.hpp"

class rollChecker
: public QObject
{
	Q_OBJECT

public:
    rollChecker();
    ~rollChecker();
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

inline rollChecker::rollChecker()
{
}

inline rollChecker::~rollChecker()
{

}

inline void rollChecker::initTestCase()
{
}

inline void rollChecker::cleanupTestCase()
{
}

inline void rollChecker::testCase1_data()
{
    QTest::addColumn<Eigen::MatrixXd>("data");
    QTest::addColumn<Eigen::MatrixXd>("expected");

    Eigen::MatrixXd inputMatrix(2,2);
    inputMatrix << 12,3,4,5;
    Eigen::MatrixXd outputMatrix(2,2);
    outputMatrix << 5,12,3,4;
    QTest::newRow("2x2 with default axis") << inputMatrix << outputMatrix;

}

inline void rollChecker::testCase1()
{
    QFETCH(Eigen::MatrixXd, data);
    QFETCH(Eigen::MatrixXd, expected);

    Eigen::MatrixXd result(2,2);
    result << 5,12,3,4;

    QCOMPARE(result,expected);

}

inline void rollChecker::testCase2_data()
{
    QTest::addColumn<Eigen::MatrixXd>("data");
    QTest::addColumn<Eigen::MatrixXd>("expected");

    Eigen::MatrixXd inputMatrix(2,2);
    Eigen::MatrixXd outputMatrix(2,2);
    inputMatrix<<12,3,4,5;
    outputMatrix<<4,5,12,3;
    QTest::newRow("2x2 with vertical axis")<<inputMatrix<<outputMatrix;

}

inline void rollChecker::testCase2()
{
    QFETCH(Eigen::MatrixXd, data);
    QFETCH(Eigen::MatrixXd, expected);

    Eigen::MatrixXd result(2,2);
    result << 4,5,12,3;

    QCOMPARE(result,expected);

}

inline void rollChecker::testCase3_data()
{
    QTest::addColumn<Eigen::MatrixXd>("data");
    QTest::addColumn<Eigen::MatrixXd>("expected");

    Eigen::MatrixXd inputMatrix(2,2);
    Eigen::MatrixXd outputMatrix(2,2);
    inputMatrix<<12,3,4,5;
    outputMatrix<<3,12,5,4;
    QTest::newRow("2x2 with horizontal axis")<<inputMatrix<<outputMatrix;

}


inline void rollChecker::testCase3()
{
    QFETCH(Eigen::MatrixXd, data);
    QFETCH(Eigen::MatrixXd, expected);

    Eigen::MatrixXd result(2,2);
    result << 3,12,5,4;

    QCOMPARE(result,expected);

}

TEST_DECLARE(rollChecker)
