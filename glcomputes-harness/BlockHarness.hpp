#include <QString>
#include <QtTest>
#include <Eigen/Dense>
#include <eigenHeader.hpp>

#include"MultiTest.hpp"

class BlockChecker
: public QObject
{
    Q_OBJECT

public:
        BlockChecker();
		~BlockChecker();
		void
		initTestCase();
		void
		cleanupTestCase();

private Q_SLOTS:
    void
    Matrix3x3_data();
    void
    Matrix3x3();
    void
    Centre_data();
    void
    Centre();
    void
    Complete_data();
    void
    Complete();
    void
    Null_data();
    void
    Null();
};

inline
BlockChecker
::BlockChecker()
{
}

inline
BlockChecker
::~BlockChecker()
{
}

inline
void
BlockChecker
::initTestCase()

{
}

inline
void
BlockChecker
::cleanupTestCase()
{
}



void BlockChecker
::Matrix3x3_data()

{
    QTest::addColumn<Eigen::Matrix3d>("data");
    QTest::addColumn<int>("indexX");
    QTest::addColumn<int>("indexY");
    QTest::addColumn<int>("sizeX");
    QTest::addColumn<int>("sizeY");

    Eigen::Matrix3d actual;
    actual <<
    2, 3, 4,
    2, 5, 6,
    3, 4, 2;

    QTest::newRow("Matrix3x3") << actual << 1 << 1<< 2<< 2;
}


inline
void BlockChecker
::Matrix3x3()
{
    QFETCH(Eigen::Matrix3d, data);
    QCOMPARE(data.block(1,1,2,2),data.block(1,1,2,2));
}

inline
void BlockChecker
::Centre_data()
{
    QTest::addColumn<Eigen::Matrix3d>("data");
    QTest::addColumn<int>("indexX");
    QTest::addColumn<int>("indexY");
    QTest::addColumn<int>("sizeX");
    QTest::addColumn<int>("sizeY");
    Eigen::Matrix3d data;
    data <<
    2, 3, 4,
    2, 5, 6,
    3, 4, 2;

    QTest::newRow("1") << data << 1 << 1 << 4 << 4;
}



inline
void BlockChecker
::Centre()
{
    QFETCH(Eigen::Matrix3d, data);
	QCOMPARE(data.block(1,1,1,1), data.block(1,1,1,1));
}


inline
void BlockChecker
::Complete_data()
{
    QTest::addColumn<Eigen::Matrix3d>("data");
    QTest::addColumn<int>("indexX");
    QTest::addColumn<int>("indexY");
    QTest::addColumn<int>("sizeX");
    QTest::addColumn<int>("sizeY");

    Eigen::Matrix3d actual;
    actual <<
    4, 1, 5,
    6, 2, 8,
    6, 2, 7;

    QTest::newRow("Complete") << actual << 0<<0<<2<<2;
}


inline
void BlockChecker
::Complete()
{
    QFETCH(Eigen::Matrix3d, data);
    QCOMPARE(data.block(0,0,2,2),data.block(0,0,2,2));
}


inline
void BlockChecker
::Null_data()
{
    QTest::addColumn<Eigen::Matrix3d>("data");
    QTest::addColumn<int>("indexX");
    QTest::addColumn<int>("indexY");
    QTest::addColumn<int>("sizeX");
    QTest::addColumn<int>("sizeY");
    Eigen::Matrix3d actual;
    actual <<
    1, 2, 3,
    4, 5, 6,
    7, 8, 9;

	QTest::newRow("Null") << actual << 0 << 0 << 0 << 0;
}

inline
void BlockChecker
::Null()
{
    QFETCH(Eigen::Matrix3d, data);
    QCOMPARE(data.block(0,0,0,0),data.block(0,0,0,0));
}

TEST_DECLARE(BlockChecker)

