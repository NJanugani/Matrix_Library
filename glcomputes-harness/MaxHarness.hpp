#include <QTest>
#include <QString>
#include <QMatrix4x4>
#include <eigenHeader.hpp>
#include "MultiTest.hpp"
class maxChecker : public QObject
{
	Q_OBJECT

public:
    maxChecker();
    ~maxChecker();
private Q_SLOTS:
	void initTestCase();
	void cleanupTestCase();

    void testCase1_data();
    void testCase1();

    void testCase2_data();
    void testCase2();

    void testCase3_data();
    void testCase3();

    void testCase4_data();
    void testCase4();

    void testCase5_data();
    void testCase5();

    void testCase6_data();
    void testCase6();
};

inline maxChecker::maxChecker()
{
}
inline maxChecker::~maxChecker()
{

}

inline void maxChecker::initTestCase()
{
}

inline void maxChecker::cleanupTestCase()
{
}

inline void maxChecker::testCase1_data()
{
    QTest::addColumn<Eigen::MatrixXd>("data");
    QTest::addColumn<Eigen::MatrixXd>("expected");

    Eigen::MatrixXd inputMatrix(2,2);
    inputMatrix<<12,3,4,5;
    Eigen::MatrixXd outputMatrix = inputMatrix.colwise().maxCoeff();
    QTest::newRow("2x2 Col wise")<<inputMatrix<<outputMatrix;
}

inline void maxChecker::testCase1()
{
    QFETCH(Eigen::MatrixXd, data);
    QFETCH(Eigen::MatrixXd, expected);

    Eigen::MatrixXd result = data.colwise().maxCoeff();

    QCOMPARE(result,expected);

}


inline void maxChecker::testCase2_data()
{
    QTest::addColumn<Eigen::MatrixXd>("data");
    QTest::addColumn<Eigen::MatrixXd>("expected");

    Eigen::MatrixXd inputMatrix(4,1);
    inputMatrix << 1.2,3,4,4.1;
    Eigen::MatrixXd outputMatrix = inputMatrix.colwise().maxCoeff();
    QTest::newRow("4x1 Col wise")<<inputMatrix<<outputMatrix;
}

inline void maxChecker::testCase2()
{
    QFETCH(Eigen::MatrixXd, data);
    QFETCH(Eigen::MatrixXd, expected);

    Eigen::MatrixXd result = data.colwise().maxCoeff();

    QCOMPARE(result,expected);

}

inline void maxChecker::testCase3_data()
{
    QTest::addColumn<Eigen::MatrixXd>("data");
    QTest::addColumn<Eigen::MatrixXd>("expected");

    Eigen::MatrixXd inputMatrix(3,3);
    inputMatrix << 1.2,3,4,4.1,2.3,4.3,3,2,5;
    Eigen::MatrixXd outputMatrix = inputMatrix.colwise().maxCoeff();
    QTest::newRow("3x3 Col wise")<<inputMatrix<<outputMatrix;
}

inline void maxChecker::testCase3()
{
    QFETCH(Eigen::MatrixXd, data);
    QFETCH(Eigen::MatrixXd, expected);

    Eigen::MatrixXd result = data.colwise().maxCoeff();

    QCOMPARE(result,expected);

}


inline void maxChecker::testCase4_data()
{
    QTest::addColumn<Eigen::MatrixXd>("data");
    QTest::addColumn<Eigen::MatrixXd>("expected");

    Eigen::MatrixXd inputMatrix(2,2);
    inputMatrix<<12,3,4,5;
    Eigen::MatrixXd outputMatrix = inputMatrix.rowwise().maxCoeff();
    QTest::newRow("2x2 Row wise")<<inputMatrix<<outputMatrix;
}

inline void maxChecker::testCase4()
{
    QFETCH(Eigen::MatrixXd, data);
    QFETCH(Eigen::MatrixXd, expected);

    Eigen::MatrixXd result = data.rowwise().maxCoeff();

    QCOMPARE(result,expected);

}

inline void maxChecker::testCase5_data()
{
    QTest::addColumn<Eigen::MatrixXd>("data");
    QTest::addColumn<Eigen::MatrixXd>("expected");

    Eigen::MatrixXd inputMatrix(1,4);
    inputMatrix<<1.2,3,4,4.1;
    Eigen::MatrixXd outputMatrix = inputMatrix.rowwise().maxCoeff();
    QTest::newRow("1x4 Row wise")<<inputMatrix<<outputMatrix;
}

inline void maxChecker::testCase5()
{
    QFETCH(Eigen::MatrixXd, data);
    QFETCH(Eigen::MatrixXd, expected);

    Eigen::MatrixXd result = data.rowwise().maxCoeff();

    QCOMPARE(result,expected);

}

inline void maxChecker::testCase6_data()
{
    QTest::addColumn<Eigen::MatrixXd>("data");
    QTest::addColumn<Eigen::MatrixXd>("expected");

    Eigen::MatrixXd inputMatrix(3,3);
    inputMatrix<<1.2,3,4,4.1,2.3,4.3,3,2,5;
    Eigen::MatrixXd outputMatrix = inputMatrix.rowwise().maxCoeff();
    QTest::newRow("3x3 Row wise")<<inputMatrix<<outputMatrix;
}

inline void maxChecker::testCase6()
{
    QFETCH(Eigen::MatrixXd, data);
    QFETCH(Eigen::MatrixXd, expected);

    Eigen::MatrixXd result = data.rowwise().maxCoeff();

    QCOMPARE(result,expected);

}

TEST_DECLARE(maxChecker)
