#include<QTest>
#include <QString>
#include<QFile>
#include<Eigen/Eigen>
#include <eigenHeader.hpp>

//Q_DECLARE_METATYPE(Eigen::MatrixXd)

class SumChecker : public QObject
{
    Q_OBJECT
    
public:
    SumChecker();
    ~SumChecker();
private Q_SLOTS:
    void
    Basic2x2_data();
    void
    Basic2x2();
    void
    Random8x8_data();
    void
    Random8x8();
    void
    NonSquare_data();
    void
    NonSquare();
    void
    Identity_data();
    void
    Identity();
};


inline
SumChecker
::SumChecker()
{
}

inline
SumChecker
::~SumChecker()
{
}

inline
void
SumChecker::Basic2x2_data()
{
    QTest::addColumn<Eigen::MatrixXd>("TestData");
    QTest::addColumn<double>("Expected");

    Eigen::MatrixXd TestData(2,2);
    TestData<<1,1,1,1;
    QTest::newRow("Basic Ones 2x2")<<TestData<<TestData.sum();
}

inline
void
SumChecker::Basic2x2()
{
    QFETCH(Eigen::MatrixXd,TestData);
    QFETCH(double,Expected);
    QCOMPARE(TestData.sum(),Expected);
}

inline
void
SumChecker::NonSquare_data()
{

    QTest::addColumn<Eigen::MatrixXd>("TestData");
    QTest::addColumn<double>("Expected");

    Eigen::MatrixXd TestData(3,2);
    TestData<<1,2,3,4,5,6;
    QTest::newRow("Non Square 3x2")<<TestData<<TestData.sum();
}

inline
void
SumChecker::NonSquare()
{
    QFETCH(Eigen::MatrixXd,TestData);
    QFETCH(double,Expected);
    QCOMPARE(TestData.sum(),Expected);
}

inline
void
SumChecker::Random8x8_data()
{

    QTest::addColumn<Eigen::MatrixXd>("TestData");
    QTest::addColumn<double>("Expected");

    Eigen::MatrixXd TestData(8,8);
    TestData=Eigen::MatrixXd::Random(8,8);
    QTest::newRow("Random 8x8")<<TestData<<TestData.sum();

}

inline
void
SumChecker::Random8x8()
{
    QFETCH(Eigen::MatrixXd,TestData);
    QFETCH(double,Expected);
    QCOMPARE(TestData.sum(),Expected);
}

inline
void
SumChecker::Identity_data()
{

    QTest::addColumn<Eigen::MatrixXd>("TestData");
    QTest::addColumn<double>("Expected");

    Eigen::MatrixXd TestData(3,3);
            TestData<<
            1,0,0,
            0,1,0,
            0,0,1;
         QTest::newRow("Identity 3x3")<<TestData<<TestData.sum();

}

inline
void
SumChecker::Identity()
{

    QFETCH(Eigen::MatrixXd,TestData);
    QFETCH(double,Expected);
    QCOMPARE(TestData.sum(),Expected);
}
//TEST_DECLARE(SumChecker)

