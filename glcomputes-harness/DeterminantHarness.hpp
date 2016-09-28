#include<QTest>
#include<Eigen/Eigen>
#include<eigenHeader.hpp>
#include<iostream>
#include<stdio.h>

#include <QString>
#include "MultiTest.hpp"

class DeterminantChecker
: public QObject
{
	Q_OBJECT

public:
	DeterminantChecker();
  ~DeterminantChecker();
private Q_SLOTS:

		void
		RandomComplex4x4();
		void
		RandomComplex4x4_data();
		void
		AllOnes2x2();
		void
		AllOnes2x2_data();
		void
		Random4x4();
		void
		Random4x4_data();
		void
		Identity3x3();
		void
		Identity3x3_data();
		//void
		//NonSquare();
		//void
		//NonSquare_data();
		//Uncomment once determinant function is implemented to return error

};
TEST_DECLARE(DeterminantChecker)

DeterminantChecker::DeterminantChecker()
{
}

DeterminantChecker::~DeterminantChecker()
{
}
//Uncomment once determinant function is implemented to return error


inline
void
DeterminantChecker
::AllOnes2x2_data()
{
	QTest::addColumn<Eigen::MatrixXd>("TestData");
	QTest::addColumn<double>("Expected");
	Eigen::MatrixXd TestData(2,2);
	TestData << 1,1,1,1;
	QTest::newRow("All Ones 2x2") << TestData << TestData.determinant();

}

inline
void
DeterminantChecker
::AllOnes2x2()
{
	QFETCH(Eigen::MatrixXd,TestData);
	QFETCH(double,Expected);
	QCOMPARE(TestData.determinant(), Expected);
	//Replace TestData.determinant() with implemented function result as actual

}

inline
void
DeterminantChecker
::Random4x4_data()
{
	QTest::addColumn<Eigen::MatrixXd>("TestData");
	QTest::addColumn<double>("Expected");
	Eigen::MatrixXd TestData(4,4);
	TestData.resize(4,4);
	TestData = Eigen::MatrixXd::Random(4,4);
	QTest::newRow("Random 4x4")<<TestData<<TestData.determinant();

}

inline
void
DeterminantChecker::Random4x4()
{
	QFETCH(Eigen::MatrixXd,TestData);
	QFETCH(double,Expected);
	QCOMPARE(TestData.determinant(),Expected);
	//Replace TestData.determinant() with implemented function result as actual
}

inline
void
DeterminantChecker
::Identity3x3_data()
{
	QTest::addColumn<Eigen::MatrixXd>("TestData");
	QTest::addColumn<double>("Expected");
	Eigen::MatrixXd TestData(3,3);
	TestData.resize(3,3);
	TestData <<
	1,0,0,
	0,1,0,
	0,0,1;
	QTest::newRow("Identity 3x3") << TestData << TestData.determinant();
}

inline
void
DeterminantChecker
::Identity3x3()
{
	QFETCH(Eigen::MatrixXd,TestData);
	QFETCH(double,Expected);
	QCOMPARE(TestData.determinant(),Expected);
	//Replace TestData.determinant() with implemented function result as actual
}

inline
void
DeterminantChecker
::RandomComplex4x4_data()
{
	  QTest::addColumn<Eigen::MatrixXcd>("TestData");
	  QTest::addColumn<std::complex<double> >("Expected");
	  Eigen::MatrixXcd TestData(4,4);
	  TestData=Eigen::MatrixXcd::Random(4,4);
	  QTest::newRow("Random 4x4 Complex")<<TestData<<TestData.determinant();
}

inline
void
DeterminantChecker
::RandomComplex4x4()
{
		QFETCH(Eigen::MatrixXcd, TestData);
		QFETCH(std::complex<double>, Expected);
		QCOMPARE(TestData.determinant(), Expected);
}
