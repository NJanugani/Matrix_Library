
#include <QTest>
#include <Eigen/Eigen>
#include <eigenHeader.hpp>
#include <QString>
#include "MultiTest.hpp"

Q_DECLARE_METATYPE(Eigen::VectorXd)
Q_DECLARE_METATYPE(Eigen::VectorXcd)
Q_DECLARE_METATYPE(Eigen::RowVectorXd)
Q_DECLARE_METATYPE(Eigen::RowVectorXcd)

class OuterProductChecker
: public QObject
{
    Q_OBJECT

public:
    OuterProductChecker();
    ~OuterProductChecker();
private Q_SLOTS:

    void
    OuterProductReal();
    void
    OuterProductReal_data();
    void
    OuterProductComplex();
    void
    OuterProductComplex_data();
};

TEST_DECLARE(OuterProductChecker)
OuterProductChecker
::OuterProductChecker()
{
}

OuterProductChecker
::~OuterProductChecker()
{
}


inline
void 
OuterProductChecker
::OuterProductReal_data()
{
    QTest::addColumn<Eigen::VectorXd>("ColVector");
    QTest::addColumn<Eigen::RowVectorXd>("RowVector");
    QTest::addColumn<Eigen::MatrixXd>("Expected");
    Eigen::VectorXd ColVector(2);
    ColVector = Eigen::VectorXd::Random(2);
    Eigen::RowVectorXd RowVector(2);
    RowVector = Eigen::RowVectorXd::Random(2);
    Eigen::MatrixXd OuterProduct;
	OuterProduct = (ColVector * RowVector).eval();
	QTest::newRow("2x2 OuterProductMatrix") << ColVector << RowVector << OuterProduct;

    ColVector.resize(3);
    RowVector.resize(3);
    ColVector = Eigen::VectorXd::Random(3);
    RowVector = Eigen::RowVectorXd::Random(3);
	OuterProduct = (ColVector * RowVector).eval();
	QTest::newRow("3x3 OuterProductMatrix") << ColVector << RowVector << OuterProduct;

    ColVector.resize(8);
    RowVector.resize(4);
    ColVector = Eigen::VectorXd::Random(8);
    RowVector = Eigen::RowVectorXd::Random(4);
	OuterProduct = (ColVector * RowVector).eval();
	QTest::newRow("8x4 OuterProductMatrix") << ColVector << RowVector << OuterProduct;
}

inline
void 
OuterProductChecker
::OuterProductReal()
{
    QFETCH(Eigen::VectorXd,ColVector);
    QFETCH(Eigen::RowVectorXd,RowVector);
    QFETCH(Eigen::MatrixXd,Expected);
    Eigen::MatrixXd Actual;
	Actual = (ColVector * RowVector).eval();
    QCOMPARE(Actual, Expected);
    //Replace ColVector * RowVector with you implemented function
}

inline
void 
OuterProductChecker
::OuterProductComplex_data()
{
    QTest::addColumn<Eigen::VectorXcd>("ColVector");
    QTest::addColumn<Eigen::RowVectorXcd>("RowVector");
    QTest::addColumn<Eigen::MatrixXcd>("Expected");
    Eigen::VectorXcd ColVector(2);
    ColVector = Eigen::VectorXcd::Random(2);
    Eigen::RowVectorXcd RowVector(2);
    RowVector = Eigen::RowVectorXcd::Random(2);

	auto OuterProductOne = (ColVector * RowVector).eval();;
	QTest::newRow("2x2 ComplexOuterProductMatrix") << ColVector << RowVector << OuterProductOne;

    ColVector.resize(3);
    RowVector.resize(3);
    ColVector = Eigen::VectorXcd::Random(3);
    RowVector = Eigen::RowVectorXcd::Random(3);
	auto OuterProductTwo = (ColVector * RowVector).eval();;
	QTest::newRow("3x3 ComplexOuterProductMatrix") << ColVector << RowVector << OuterProductTwo;

    ColVector.resize(8);
    RowVector.resize(4);
    ColVector = Eigen::VectorXcd::Random(6);
    RowVector = Eigen::RowVectorXcd::Random(4);
	auto OuterProductThree = (ColVector * RowVector).eval();;
	QTest::newRow("6x4 ComplexOuterProductMatrix") << ColVector << RowVector << OuterProductThree;
}

inline
void 
OuterProductChecker
::OuterProductComplex()
{
    QFETCH(Eigen::VectorXcd,ColVector);
    QFETCH(Eigen::RowVectorXcd,RowVector);
    QFETCH(Eigen::MatrixXcd,Expected);
    Eigen::MatrixXcd Actual;
	Actual = (ColVector * RowVector).eval();;
    QCOMPARE(Actual, Expected);
    //Replace ColVector*RowVector with you implemented function
}
