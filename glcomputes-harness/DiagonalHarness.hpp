#include <QString>
#include <QtTest>
#include <QTest>
#include <eigenHeader.hpp>
#include"MultiTest.hpp"
using namespace QTest;


class DiagonalChecker
: public QObject
{
    Q_OBJECT

public:
    DiagonalChecker();

private Q_SLOTS:
    void
    Matrix4x4_data();
    void
    Matrix4x4();
    void
    Matrix3x3_data();
    void
    Matrix3x3();
};

DiagonalChecker
::DiagonalChecker()
{
}

inline
void
DiagonalChecker
::Matrix4x4_data()
{
    addColumn<Eigen::Matrix4f>("data1");
    Eigen::Matrix4f expected;
    expected <<
    1.0, 0.3, 0.1, 0.1,
    0.6, 1.3, 0.0, 0.1,
    0.3, 0.0, 1.0, 0.0,
    0.3, 0.1, 0.3, 1.0;
    newRow("real 4x4 matrix") << expected;
}

inline
void
DiagonalChecker
::Matrix4x4()
{
	QFETCH(Eigen::Matrix4f, data1);
	QCOMPARE(data1.diagonal(),data1.diagonal());
}


inline
void
DiagonalChecker
::Matrix3x3_data()
{
    addColumn<Eigen::Matrix3f>("data2");
    Eigen::Matrix3f expected;
    expected <<
    1.3, 2.1, 3.3,
    4.1, 5.3, 6.3,
    7.3, 8.3, 9.1;
    newRow("real 3x3 matrix") << expected;
}

inline
void
DiagonalChecker
::Matrix3x3()
{
    QFETCH(Eigen::Matrix3f,data2);
    QCOMPARE(data2.diagonal(),data2.diagonal());
}

TEST_DECLARE(DiagonalChecker)
