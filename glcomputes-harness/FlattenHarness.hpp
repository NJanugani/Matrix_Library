#include <QString>
#include <QtTest>
#include <Eigen/Dense>
#include <eigenHeader.hpp>

#include<MultiTest.hpp>

class FlattenChecker
: public QObject
{
    Q_OBJECT

public:
    FlattenChecker();

private Q_SLOTS:
    void
    Matrix3x3_data();
    void
    Matrix3x3();
    void
    Matrix2x2_data();
    void
    Matrix2x2();
    void
    Matrix3x3b_data();
    void
    Matrix3x3b();
};

TEST_DECLARE(FlattenChecker)

inline
FlattenChecker
::FlattenChecker()
{
}

inline
void FlattenChecker
::Matrix3x3_data()
{
    QTest::addColumn<Eigen::Matrix3d>("data");
    Eigen::Matrix3d actual;

    actual <<
    3, 4, 0,
    6, 3, 7,
    4, 5, 3;

    QTest::newRow("Matrix3x3") << actual;
}

inline
void FlattenChecker
::Matrix3x3()
{
    QFETCH(Eigen::Matrix3d, data);
    Eigen::MatrixXd expected1(1,9),expected2(1,9);

    expected1 <<
    3, 4, 0, 6, 3, 7, 4, 5, 3;

    expected2 <<
    3, 6, 4, 4, 3, 5, 0, 7, 3;

    QCOMPARE(expected1,expected1);
    QCOMPARE(expected2,expected2);
}

inline
void FlattenChecker
::Matrix2x2_data()
{
    QTest::addColumn<Eigen::Matrix2d>("data");
    Eigen::Matrix2d actual;

    actual <<
    45, 21,
    22, 11;

    QTest::newRow("Matrix2x2") << actual;
}

inline
void FlattenChecker
::Matrix2x2()
{
    QFETCH(Eigen::Matrix2d, data);
    Eigen::MatrixXd expected1(1,4),expected2(1,4);

    expected1 <<
    45, 21, 22, 11;

    expected2 <<
    45, 22, 21, 11;

    QCOMPARE(expected1,expected1);
    QCOMPARE(expected2,expected2);
}

inline
void FlattenChecker
::Matrix3x3b_data()
{
    QTest::addColumn<Eigen::Matrix3d>("data");
    Eigen::Matrix3d actual;

    actual <<
    1, 2, 3,
    4, 5, 6,
    7, 8, 9;

    QTest::newRow("Matrix3x3b") << actual;
}

inline
void FlattenChecker
::Matrix3x3b()
{
    QFETCH(Eigen::Matrix3d, data);
    Eigen::MatrixXd expected1(1,9),expected2(1,9);

    expected1 <<
    1, 2, 3, 4, 5, 6, 7, 8, 9;

    expected2 <<
    1, 4, 7,
    2, 5, 8,
    3, 6, 9;

    QCOMPARE(expected1,expected1);
    QCOMPARE(expected2,expected2);
}
