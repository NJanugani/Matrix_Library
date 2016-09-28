#include<QTest>
#include<Eigen/Eigen>
#include<eigenHeader.hpp>
#include<QString>
#include<stdio.h>
#include"MultiTest.hpp"

class MinChecker : public QObject
{
	Q_OBJECT

public:
	MinChecker();
  ~MinChecker();
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

TEST_DECLARE(MinChecker)

inline
MinChecker::MinChecker()
{
}

inline
MinChecker::~MinChecker()
{

}

inline
void
MinChecker::RowWise3x3_data(){
	QTest::addColumn<Eigen::MatrixXd>("TestData");
	QTest::addColumn<Eigen::MatrixXd>("Expected");

	Eigen::MatrixXd TestData(3,3);
	TestData<<1,2,3,4,5,6,7,8,9;
	Eigen::MatrixXd Expected=TestData.rowwise().minCoeff();
	QTest::newRow("3x3 RowWise")<<TestData<<Expected;

}

inline
void
MinChecker::RowWise3x3(){

	QFETCH(Eigen::MatrixXd,TestData);
	QFETCH(Eigen::MatrixXd,Expected);
	Eigen::MatrixXd Actual = TestData.rowwise().minCoeff();
	QCOMPARE(Actual,Expected);
	//Replace Initialization of Actual with the rowWise function call that is implemented

}


inline
void
MinChecker::RowWise4x3_data(){
	QTest::addColumn<Eigen::MatrixXd>("TestData");
	QTest::addColumn<Eigen::MatrixXd>("Expected");

	Eigen::MatrixXd TestData(4,3);
	TestData=Eigen::MatrixXd::Random(4,3);
	Eigen::MatrixXd Expected=TestData.rowwise().minCoeff();
	QTest::newRow("4x3 RowWise")<<TestData<<Expected;

}

inline
void
MinChecker::RowWise4x3(){

	QFETCH(Eigen::MatrixXd,TestData);
	QFETCH(Eigen::MatrixXd,Expected);
	Eigen::MatrixXd Actual = TestData.rowwise().minCoeff();
	QCOMPARE(Actual,Expected);
	//Replace Initialization of Actual with the rowWise function call that is implemented

}


inline
void
MinChecker::ColWise3x3_data(){
	QTest::addColumn<Eigen::MatrixXd>("TestData");
	QTest::addColumn<Eigen::MatrixXd>("Expected");

	Eigen::MatrixXd TestData(3,3);
	TestData<<1,2,3,4,5,6,7,8,9;
	Eigen::MatrixXd Expected=TestData.colwise().minCoeff();
	QTest::newRow("3x3 Column Wise")<<TestData<<Expected;

}

inline
void
MinChecker::ColWise3x3(){

	QFETCH(Eigen::MatrixXd,TestData);
	QFETCH(Eigen::MatrixXd,Expected);
	Eigen::MatrixXd Actual = TestData.colwise().minCoeff();
	QCOMPARE(Actual,Expected);
	//Replace Initialization of Actual with the rowWise function call that is implemented

}


inline
void
MinChecker
::ColWise4x3_data()
{
	QTest::addColumn<Eigen::MatrixXd>("TestData");
	QTest::addColumn<Eigen::MatrixXd>("Expected");

	Eigen::MatrixXd TestData(4,3);
	TestData=Eigen::MatrixXd::Random(4,3);
	Eigen::MatrixXd Expected=TestData.colwise().minCoeff();
	QTest::newRow("4x3 ColWise")<<TestData<<Expected;

}

inline
void
MinChecker::ColWise4x3(){

	QFETCH(Eigen::MatrixXd,TestData);
	QFETCH(Eigen::MatrixXd,Expected);
	Eigen::MatrixXd Actual = TestData.colwise().minCoeff();
	QCOMPARE(Actual,Expected);
	//Replace Initialization of Actual with the rowWise function call that is implemented

}
