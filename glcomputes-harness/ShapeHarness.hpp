#include <QTest>
#include <QtTest>
#include <Eigen/Eigen>
#include <eigenHeader.hpp>

#include"MultiTest.hpp"

using namespace QTest;

class ShapeChecker
: public QObject
{
    Q_OBJECT

public:
    ShapeChecker();

private Q_SLOTS:
    void
    matrix2x8_data();
    void
    matrix2x8();
    void
    matrix5x6_data();
    void
    matrix5x6();
    void
    matrix2x1_data();
    void
    matrix2x1();
};

inline
ShapeChecker
::ShapeChecker()
{
}

inline
void
ShapeChecker
::matrix2x8_data()
{
    addColumn<Eigen::MatrixXd>("data1");
        Eigen::MatrixXd expected(2,8);
        expected <<
        4, 8, 8, 7, 5, 6, 4, 4,
        7, 8, 9, 6, 2, 4, 4, 5;
    newRow("Matrix 2x8 ") << expected;
}

inline
void
ShapeChecker
::matrix2x8()
{
    QFETCH(Eigen::MatrixXd,data1);
    QCOMPARE(data1.size(),data1.size());
}

inline
void
ShapeChecker
::matrix5x6_data()
{
    addColumn<Eigen::MatrixXd>("data2");
    Eigen::MatrixXd expected(5,6);
    expected <<
    4, 8, 8, 7, 5,
    6, 4, 4, 7, 8,
    9, 6, 2, 4, 5,
    5, 4, 5, 7, 6,
    7, 8, 9, 5, 4,
    8, 1, 3, 6, 5;
    newRow("matrix 5x6 ") << expected;
}

inline
void
ShapeChecker
::matrix5x6()
{
    QFETCH(Eigen::MatrixXd,data2);
    QCOMPARE(data2.size(),data2.size());
}

inline
void
ShapeChecker
::matrix2x1_data()
{
    addColumn<Eigen::MatrixXd>("data3");
    Eigen::MatrixXd expected(2,1);
    expected <<
    1,
    2;
    newRow("Matrix 2x1") << expected;
}

inline
void
ShapeChecker
::matrix2x1()
{
    QFETCH(Eigen::MatrixXd,data3);
    QCOMPARE(data3.size(),data3.size());
}

TEST_DECLARE(ShapeChecker)
