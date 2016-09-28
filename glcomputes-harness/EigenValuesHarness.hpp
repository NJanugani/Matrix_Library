#include <QTest>
#include <QString>
#include <QMatrix4x4>
#include <eigenHeader.hpp>
#include "MultiTest.hpp"

class EigenValuesChecker : public QObject
{
	Q_OBJECT

public:
    EigenValuesChecker();
    ~EigenValuesChecker();
private Q_SLOTS:
	void initTestCase();
	void cleanupTestCase();

    void testCase1_data();
    void testCase1();

    void testCase2_data();
    void testCase2();
};

EigenValuesChecker::EigenValuesChecker()
{
}
EigenValuesChecker::~EigenValuesChecker()
{

}

inline void EigenValuesChecker::initTestCase()
{
}

inline void EigenValuesChecker::cleanupTestCase()
{
}

inline void EigenValuesChecker::testCase1_data()
{
    QTest::addColumn<Eigen::MatrixXd>("data");
    QTest::addColumn<Eigen::MatrixXcd>("expected");

    Eigen::MatrixXd inputMatrix(2,2);
    inputMatrix<<12,3,4,5;

    Eigen::EigenSolver<Eigen::MatrixXd> es(inputMatrix,false);

    Eigen::MatrixXcd outputMatrix(2,1);
    outputMatrix = es.eigenvalues();

    QTest::newRow("Eigenvalues 2x2") << inputMatrix << outputMatrix;

}

inline void EigenValuesChecker::testCase1()
{
    QFETCH(Eigen::MatrixXd, data);
    QFETCH(Eigen::MatrixXcd, expected);

    Eigen::EigenSolver<Eigen::MatrixXd> es(data,false);

    Eigen::MatrixXcd result;
    result = es.eigenvalues();

    QCOMPARE(expected,result);

}

inline void EigenValuesChecker::testCase2_data()
{
    QTest::addColumn<Eigen::MatrixXd>("data");
    QTest::addColumn<Eigen::MatrixXcd>("expected");

    Eigen::MatrixXd inputMatrix(3,3);
    inputMatrix=Eigen::MatrixXd::Random(3,3);

    Eigen::EigenSolver<Eigen::MatrixXd> es(inputMatrix,false);

    Eigen::MatrixXcd outputMatrix(3,1);
    outputMatrix = es.eigenvalues();

    QTest::newRow("Eigenvalues 3x3") << inputMatrix << outputMatrix;

}

inline void EigenValuesChecker::testCase2()
{
    QFETCH(Eigen::MatrixXd, data);
    QFETCH(Eigen::MatrixXcd, expected);

    Eigen::EigenSolver<Eigen::MatrixXd> es(data,false);

    Eigen::MatrixXcd result;
    result = es.eigenvalues();

    QCOMPARE(expected,result);

}

TEST_DECLARE(EigenValuesChecker)

