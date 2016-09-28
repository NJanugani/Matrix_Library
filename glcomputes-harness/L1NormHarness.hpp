#include<QTest>
#include<Eigen/Eigen>
#include<eigenHeader.hpp>
#include<QString>
#include<stdio.h>
#include"MultiTest.hpp"

class L1NormChecker : public QObject
{
	Q_OBJECT

public:
	L1NormChecker();
  ~L1NormChecker();
private Q_SLOTS:

    void
		Complex2x2();
		void
		Complex2x2_data();

		void
		Complex4x4();
		void
		Complex4x4_data();

		void
		Real2x2();
		void
		Real2x2_data();

		void
		Real4x4();
		void
		Real4x4_data();

		void
		Negative3x3_data();
		void
		Negative3x3();

};
TEST_DECLARE(L1NormChecker)


inline
L1NormChecker::L1NormChecker()
{
}
inline
L1NormChecker::~L1NormChecker()
{

}

inline
void
L1NormChecker::Complex2x2_data(){
	QTest::addColumn<Eigen::MatrixXcd>("TestData");
	QTest::addColumn<double>("Expected");
	Eigen::MatrixXcd TestData(2,2);
	TestData=Eigen::MatrixXcd::Random(2,2);
	QTest::newRow("Random 2x2 Complex")<<TestData<<TestData.lpNorm<1>();

}

inline
void
L1NormChecker::Complex2x2(){
	QFETCH(Eigen::MatrixXcd,TestData);
	QFETCH(double,Expected);
	double Actual=TestData.lpNorm<1>();
	QCOMPARE(Actual,Expected);
	//Change lpNorm<1>() in above function call with implemented function
}


inline
void
L1NormChecker::Complex4x4_data(){
	QTest::addColumn<Eigen::MatrixXcd>("TestData");
	QTest::addColumn<double>("Expected");
	Eigen::MatrixXcd TestData(4,4);
	TestData=Eigen::MatrixXcd::Random(4,4);
	QTest::newRow("Random 4x4 Complex")<<TestData<<TestData.lpNorm<1>();

}

inline
void
L1NormChecker::Complex4x4(){
	QFETCH(Eigen::MatrixXcd,TestData);
	QFETCH(double,Expected);
	double Actual=TestData.lpNorm<1>();
	QCOMPARE(Actual,Expected);
	//Change lpNorm<1>() in above function call with implemented function
}

inline
void
L1NormChecker::Real2x2_data(){
	QTest::addColumn<Eigen::MatrixXd>("TestData");
	QTest::addColumn<double>("Expected");

	Eigen::MatrixXd TestData(2,2);
	TestData<<1,2,3,4;

	QTest::newRow("Basic 2x2 Real")<<TestData<<TestData.lpNorm<1>();
}

inline
void
L1NormChecker::Real2x2()
{
	QFETCH(Eigen::MatrixXd,TestData);
	QFETCH(double,Expected);
	double Actual = TestData.lpNorm<1>();
	QCOMPARE(Actual, Expected);
	//Change lpNorm<1>() in above function call with implemented function
}

inline
void
L1NormChecker
::Real4x4_data()
{
	QTest::addColumn<Eigen::MatrixXd>("TestData");
	QTest::addColumn<double>("Expected");
	Eigen::MatrixXd TestData(4,4);
	TestData=Eigen::MatrixXd::Random(4,4);
	QTest::newRow("Random 4x4 Real")<<TestData<<TestData.lpNorm<1>();
}

inline
void
L1NormChecker::Real4x4(){
	QFETCH(Eigen::MatrixXd,TestData);
	QFETCH(double,Expected);
	double Actual=TestData.lpNorm<1>();
	QCOMPARE(Actual,Expected);
	//Change lpNorm<1>() in above function call with implemented function
}

inline
void
L1NormChecker::Negative3x3_data(){
	QTest::addColumn<Eigen::MatrixXd>("TestData");
	QTest::addColumn<double>("Expected");
	Eigen::MatrixXd TestData(3,3);
	TestData<<-1,-2,-3,-4,-5,-34,-9,-1,-87;
	QTest::newRow("Negative 3x3 Real")<<TestData<<TestData.lpNorm<1>();
}

inline
void
L1NormChecker::Negative3x3(){
	QFETCH(Eigen::MatrixXd,TestData);
	QFETCH(double,Expected);
	double Actual=TestData.lpNorm<1>();
	QCOMPARE(Actual, Expected);
	//Change lpNorm<1>() in above function call with implemented function
}
