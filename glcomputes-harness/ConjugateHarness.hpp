#include<QTest>
#include<Eigen/Eigen>
#include<eigenHeader.hpp>
#include<QString>
#include"MultiTest.hpp"

class ConjugateTest : public QObject
{
	Q_OBJECT

public:
	ConjugateTest();
	 ~ConjugateTest();

private Q_SLOTS:

	void
	Complex2x2();
	void
	Complex2x2_data();

    void
	Complex3x4();
	void
	Complex3x4_data();

	void
	ComplexRowVector();
	void
	ComplexRowVector_data();

	void
	ComplexColVector();
	void
	ComplexColVector_data();

	void
	Real2x2();
	void
	Real2x2_data();

	void
	RealRowVector();
	void
	RealRowVector_data();

	void
	RealColVector();
	void
	RealColVector_data();


};

inline
ConjugateTest
::ConjugateTest()
{
}

inline
ConjugateTest
::~ConjugateTest()
{

}

inline
void
ConjugateTest
::Complex3x4_data()
{

	QTest::addColumn<Eigen::MatrixXcd>("TestData");
	QTest::addColumn<Eigen::MatrixXcd>("Expected");
	Eigen::MatrixXcd TestData(3,4);
	TestData = Eigen::MatrixXcd::Random(3,4);
	Eigen::MatrixXcd Expected(3,4);
	Expected = TestData.conjugate();
	QTest::newRow("Random 3x4 Complex") << TestData <<Expected;

}

inline
void
ConjugateTest::Complex3x4()
{

	QFETCH(Eigen::MatrixXcd,TestData);
	QFETCH(Eigen::MatrixXcd,Expected);
	Eigen::MatrixXcd Actual;
	Actual=TestData.conjugate();
	QCOMPARE(Actual,Expected);
	//Replace TestData.conjugate() with implemented function.
}

inline
void
ConjugateTest::ComplexRowVector_data(){

	QTest::addColumn<Eigen::MatrixXcd>("TestData");
	QTest::addColumn<Eigen::MatrixXcd>("Expected");
	Eigen::MatrixXcd TestData(1,4);
	TestData=Eigen::MatrixXcd::Random(1,4);
	Eigen::MatrixXcd Expected(1,4);
	Expected=TestData.conjugate();
	QTest::newRow("Random 4 element Row Vector Complex")<<TestData<<Expected;

}

inline
void
ConjugateTest::ComplexRowVector()
{

		QFETCH(Eigen::MatrixXcd,TestData);
		QFETCH(Eigen::MatrixXcd,Expected);
		Eigen::MatrixXcd Actual;
		Actual=TestData.conjugate();
		QCOMPARE(Actual,Expected);
		//Replace TestData.conjugate() with implemented function.


}

inline
void
ConjugateTest
::ComplexColVector_data()
{

	QTest::addColumn<Eigen::MatrixXcd>("TestData");
	QTest::addColumn<Eigen::MatrixXcd>("Expected");
	Eigen::MatrixXcd TestData(4,1);
	TestData = Eigen::MatrixXcd::Random(4,1);
	Eigen::MatrixXcd Expected(4,1);
	Expected = TestData.conjugate();
	QTest::newRow("Random 4 element Column Vector Complex")<<TestData<<Expected;

}

inline
void
ConjugateTest
::Real2x2()
{

}

inline
void
ConjugateTest
::ComplexColVector()
{

		QFETCH(Eigen::MatrixXcd,TestData);
		QFETCH(Eigen::MatrixXcd,Expected);
		Eigen::MatrixXcd Actual;
		Actual = TestData.conjugate();
		QCOMPARE(Actual, Expected);
		//Replace TestData.conjugate() with implemented function.

}


	inline
	void
	ConjugateTest
	::Real2x2_data()
	{

		QTest::addColumn<Eigen::MatrixXd>("TestData");
		QTest::addColumn<Eigen::MatrixXd>("Expected");
		Eigen::MatrixXd TestData(2,2);
		TestData = Eigen::MatrixXd::Random(2,2);
		Eigen::MatrixXd Expected(2,2);
		Expected = TestData.conjugate();
		QTest::newRow("Random 2x2 Real") << TestData << Expected;

	}

	inline
	void
	ConjugateTest
	::Complex2x2()
	{

        QFETCH(Eigen::MatrixXcd,TestData);
        QFETCH(Eigen::MatrixXcd,Expected);
        Eigen::MatrixXcd Actual;
		Actual = TestData.conjugate();
		QCOMPARE(Actual,Expected);
		//Replace TestData.conjugate() with implemented function.
	}

	inline
	void
	ConjugateTest
	::Complex2x2_data()
	{
        QTest::addColumn<Eigen::MatrixXcd>("TestData");
        QTest::addColumn<Eigen::MatrixXcd>("Expected");
        Eigen::MatrixXcd TestData(2,2);
        TestData = Eigen::MatrixXcd::Random(2,2);
        Eigen::MatrixXcd Expected(2,2);
        Expected = TestData.conjugate();
        QTest::newRow("Random 2x2 Complex") << TestData << Expected;
	}

	inline
	void
	ConjugateTest
	::RealRowVector_data()
	{

		QTest::addColumn<Eigen::MatrixXd>("TestData");
		QTest::addColumn<Eigen::MatrixXd>("Expected");
		Eigen::MatrixXd TestData(1,4);
		TestData=Eigen::MatrixXd::Random(1,4);
		Eigen::MatrixXd Expected(1,4);
		Expected=TestData.conjugate();
		QTest::newRow("Random 4 element Row Vector Real")<<TestData<<Expected;

	}

	inline
	void
	ConjugateTest::RealRowVector()
	{

			QFETCH(Eigen::MatrixXd,TestData);
			QFETCH(Eigen::MatrixXd,Expected);
			Eigen::MatrixXd Actual;
			Actual=TestData.conjugate();
			QCOMPARE(Actual,Expected);
			//Replace TestData.conjugate() with implemented function.


	}

	inline
	void
	ConjugateTest
	::RealColVector_data()
	{

		QTest::addColumn<Eigen::MatrixXd>("TestData");
		QTest::addColumn<Eigen::MatrixXd>("Expected");
		Eigen::MatrixXd TestData(7,1);
		TestData=Eigen::MatrixXd::Random(7,1);
		Eigen::MatrixXd Expected(7,1);
		Expected=TestData.conjugate();
		QTest::newRow("Random 7 element Column Vector Real")<<TestData<<Expected;

	}

	inline
	void
	ConjugateTest
	::RealColVector()
	{

			QFETCH(Eigen::MatrixXd,TestData);
			QFETCH(Eigen::MatrixXd,Expected);
			Eigen::MatrixXd Actual;
			Actual=TestData.conjugate();
			QCOMPARE(Actual,Expected);
			//Replace TestData.conjugate() with implemented function.

		}


TEST_DECLARE(ConjugateTest)
