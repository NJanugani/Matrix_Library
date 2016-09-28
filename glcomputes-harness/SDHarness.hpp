#include<QTest>
#include<Eigen/Eigen>
#include<eigenHeader.hpp>
#include<QString>
#include<stdio.h>
#include"MultiTest.hpp"

class SDChecker : public QObject
{
	Q_OBJECT

public:
		SDChecker();
    ~SDChecker();
private Q_SLOTS:
	void
	RowWise3x3_data();
	void
	RowWise3x3();

	void
	RowWise4x3_data();
	void
	RowWise4x3();

	void
	ColWise3x3_data();
	void
	ColWise3x3();

	void
	ColWise4x3_data();
	void
	ColWise4x3();

};
TEST_DECLARE(SDChecker)

SDChecker
::SDChecker()
{
}

SDChecker
::~SDChecker()
{

}

inline
void
SDChecker
::RowWise3x3_data()
{
	QTest::addColumn<Eigen::MatrixXd>("TestData");
	QTest::addColumn<Eigen::MatrixXd>("Expected");

	Eigen::MatrixXd TestData(3,3);
	TestData<< 1,2,3,4,5,6,7,8,9;
	Eigen::MatrixXd Expected(3,1);
	Expected<< 1,1,1;
	QTest::newRow("3x3 RowWise")<<TestData<<Expected;

}

inline
void
SDChecker
::RowWise3x3()
{

	QFETCH(Eigen::MatrixXd,TestData);
	QFETCH(Eigen::MatrixXd,Expected);
	Eigen::MatrixXd Actual(Expected.rows(),Expected.cols());
	Actual = Eigen::MatrixXd::Random(Expected.rows(),Expected.cols());

	QCOMPARE(Actual,Expected);


}


inline
void
SDChecker
::RowWise4x3_data()
{
	QTest::addColumn<Eigen::MatrixXd>("TestData");
	QTest::addColumn<Eigen::MatrixXd>("Expected");

	Eigen::MatrixXd TestData(4,3);
	TestData <<
	1,5,3,
	2,4,76,
	34,22,11,
	12,14,143;

	Eigen::MatrixXd Expected(4,1);
	Expected << 2.00,42.16,11.50,75.06;
	QTest::newRow("4x3 RowWise") << TestData << Expected;

}

inline
void
SDChecker
::RowWise4x3()
{

	QFETCH(Eigen::MatrixXd,TestData);
	QFETCH(Eigen::MatrixXd,Expected);
	Eigen::MatrixXd Actual(Expected.rows(),Expected.cols());
	Actual=Eigen::MatrixXd::Random(Expected.rows(),Expected.cols());

	QCOMPARE(Actual,Expected);
	//Replace the Initialization of Actual with rowwise standard deviation computation on TestData.
	//Answer rounded to 2 decimal places
}


inline
void
SDChecker
::ColWise3x3_data()
{
	QTest::addColumn<Eigen::MatrixXd>("TestData");
	QTest::addColumn<Eigen::MatrixXd>("Expected");

	Eigen::MatrixXd TestData(3,3);
	TestData << 1,2,3,4,5,6,7,8,9;
	Eigen::MatrixXd Expected(1,3);
	Expected << 3,3,3;
	QTest::newRow("3x3 ColWise")<<TestData<<Expected;

}

inline
void
SDChecker
::ColWise3x3()
{

}

inline
void
SDChecker
::ColWise4x3_data()
{

}

inline
void
SDChecker
::ColWise4x3()
{

}


