#include <Eigen/Dense>
#include <QTest>
#include <QtTest>
#include <eigenHeader.hpp>

#include"MultiTest.hpp"

using namespace QTest;
using namespace Eigen;

class RankChecker
: public QObject
{
    Q_OBJECT

public:
        RankChecker();

private Q_SLOTS:
    void
    matrix3x3_data();
    void
    matrix3x3();
    void
    matrix2x6_data();
    void
    matrix2x6();
    void
    matrix8x6_data();
    void
    matrix8x6();

};

inline
RankChecker
::RankChecker()
{
}

inline
void
RankChecker
::matrix3x3_data()
{
    addColumn<Eigen::Matrix3d>("data1");
        Eigen::Matrix3d expected;
        expected <<
        2, 3, 1,
        1 ,2, 2,
        3 ,1 ,2;
        newRow("3x3 matrix") <<expected;
}

inline
void
RankChecker
::matrix3x3()
{
    QFETCH(Eigen::Matrix3d,data1);
    FullPivLU<MatrixXd> lu_decomp(data1);
    QCOMPARE(lu_decomp.rank(),lu_decomp.rank());
}

inline
void
RankChecker
::matrix2x6_data()
{
    addColumn<Eigen::MatrixXd>("data2");
        Eigen::MatrixXd expected(2,6);
        expected <<
        -0.2612, 0.3919, -0.9480, -0.5078, 0.0125, -0.4570,
        0.4434, -1.2507, -0.7411, -0.3206, -3.0292, 1.2424;
        newRow("2x6 matrix") <<expected;
}

inline
void
RankChecker
::matrix2x6()
{
    QFETCH(Eigen::MatrixXd,data2);
    FullPivLU<MatrixXd> lu_decomp(data2);
    QCOMPARE(lu_decomp.rank(),lu_decomp.rank());
}

inline
void
RankChecker
::matrix8x6_data()
{
    addColumn<Eigen::MatrixXd>("data3");
    Eigen::MatrixXd expected(8,2);
    expected <<
    -1.0667, 0.0983,
     0.9337, 0.0414,
     0.3503, -0.7342,
    -0.0290, -0.0308,
     0.1825, 0.2323,
    -1.5651, 0.4264,
    -0.0845, -0.3728,
     1.6039, -0.2365;
    newRow("8x2 matrix") << expected;
}

inline
void
RankChecker
::matrix8x6()
{
    QFETCH(Eigen::MatrixXd,data3);
    FullPivLU<MatrixXd> lu_decomp(data3);
    QCOMPARE(lu_decomp.rank(),lu_decomp.rank());
}

TEST_DECLARE(RankChecker)
