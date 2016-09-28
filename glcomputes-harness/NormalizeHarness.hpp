#include <QString>
#include <QtTest>
#include <Eigen/Dense>
#include <eigenHeader.hpp>

#include"MultiTest.hpp"

class NormalizeChecker
: public QObject
{
    Q_OBJECT

public:
    NormalizeChecker();

private Q_SLOTS:
    void
    Vector1_data();
    void
    Vector1();
    void
    Vector2_data();
    void
    Vector2();
    void
    Vector3_data();
    void
    Vector3();
    void
    Vector4_data();
    void
    Vector4();
};

TEST_DECLARE(NormalizeChecker)

inline
NormalizeChecker
::NormalizeChecker()
{
}

inline
void NormalizeChecker
::Vector1_data()
{
    QTest::addColumn<Eigen::Vector3d>("data");

    Eigen::Vector3d actual(3,4,0);

    QTest::newRow("Vector1") << actual ;
}

inline
void NormalizeChecker
::Vector1()
{
    QFETCH(Eigen::Vector3d, data);
    QCOMPARE(data.normalized(),data.normalized());
}

inline
void NormalizeChecker
::Vector2_data()
{
    QTest::addColumn<Eigen::Vector3d>("data");

    Eigen::Vector3d actual(0.73815784,0.22424629,0.84450243);
    QTest::newRow("Vector2") << actual ;
}

inline
void NormalizeChecker
::Vector2()
{
    QFETCH(Eigen::Vector3d, data);
    QCOMPARE(data.normalized(),data.normalized());
}

inline
void NormalizeChecker
::Vector3_data()
{
    QTest::addColumn<Eigen::Vector3d>("data");

    Eigen::Vector3d actual(0,0,1);//replace by (0,0,0)
    QTest::newRow("Vector3") << actual ;
}

inline
void NormalizeChecker
::Vector3()
{
    QFETCH(Eigen::Vector3d, data);
    QCOMPARE(data.normalized(),data.normalized());
}

inline
void NormalizeChecker
::Vector4_data()
{
    QTest::addColumn<Eigen::Vector4d>("data");

    Eigen::Vector4d actual(3.126,-7.342,-4.563,0.936);
    QTest::newRow("Vector4") << actual ;
}

inline
void NormalizeChecker
::Vector4()
{
    QFETCH(Eigen::Vector4d, data);
    QCOMPARE(data.normalized(),data.normalized());
}
