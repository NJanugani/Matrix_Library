#include<QTest>
#include <QString>
#include<QFile>
#include<Eigen/Eigen>
#include"MultiTest.hpp"

Q_DECLARE_METATYPE(Eigen::MatrixXd)
Q_DECLARE_METATYPE(Eigen::MatrixXcd)

class EigenvectorChecker
: public QObject
{
    Q_OBJECT

public:
    EigenvectorChecker();
       ~EigenvectorChecker();
private Q_SLOTS:
    void
    testCase1_data();
    void
    testCase1();
    void
    testCase2_data();
    void
    testCase2();


};
TEST_DECLARE(EigenvectorChecker)

inline
EigenvectorChecker
::EigenvectorChecker()
{
}

inline
EigenvectorChecker
::~EigenvectorChecker()
{
}

inline
void
EigenvectorChecker
::testCase1_data()
{
    QTest::addColumn<Eigen::MatrixXcd>("TestData");
    QTest::addColumn<std::complex<double> >("Expected");

    Eigen::MatrixXd Random2x2;


    Random2x2=Eigen::MatrixXd::Random(2,2);

    Eigen::EigenSolver<Eigen::MatrixXd> es1(Random2x2);
    QTest::newRow("Basic Ones 2x2")<<Random2x2<<es1.eigenvectors();

}

inline
void
EigenvectorChecker
::testCase1()
{
    QFETCH(Eigen::MatrixXd,TestData);
    QFETCH(double,Expected);
    Eigen::EigenSolver<Eigen::MatrixXd> es(TestData);
    QCOMPARE(es.eigenvectors(),Expected);
}

inline
void
EigenvectorChecker
::testCase2_data()
{

    QTest::addColumn<Eigen::MatrixXcd>("TestData");
    QTest::addColumn<std::complex<double> >("Expected");



    Eigen::MatrixXd Identity3x3;
    Identity3x3<<
        1,0,0,
        0,1,0,
        0,0,1;

    Eigen::EigenSolver<Eigen::MatrixXd> es2(Identity3x3);
    QTest::newRow("Identity 3x3")<<Identity3x3<<es2.eigenvectors();

}


inline
void
EigenvectorChecker
::testCase2()
{
    QFETCH(Eigen::MatrixXd,TestData);
    QFETCH(double,Expected);
    Eigen::EigenSolver<Eigen::MatrixXd> es(TestData);
    QCOMPARE(es.eigenvectors(),Expected);
}
