#include<QTest>
#include<Eigen/Eigen>
#include<eigenHeader.hpp>
#include<QString>
#include"MultiTest.hpp"

class PosDefChecker : public QObject
{
	Q_OBJECT

public:
	PosDefChecker();
    ~PosDefChecker();
private Q_SLOTS:

    void
		isPosDefReal();
    void
		isPosDefReal_data();



};

PosDefChecker::PosDefChecker()
{
}
PosDefChecker::~PosDefChecker()
{
}


inline
void 
PosDefChecker::isPosDefReal_data(){
    QTest::addColumn<Eigen::MatrixXd>("TestMatrix");
    QTest::addColumn<bool>("Result");

    Eigen::MatrixXd Testdata(3,3);
    Testdata<<2,-1,0,-1,2,-1,0,-1,2;
    QTest::newRow("3x3 Positive Definite Matrix")<<Testdata<<true;

    Testdata.resize(2,2);
    Testdata<<2,-1,2,-1;
    QTest::newRow("Positive Definite 2x2 Matrix")<<Testdata<<true;

    Testdata.resize(3,3);
    Testdata<<1,2,3,4,5,6,7,8,9;
    QTest::newRow("Non Positive Definite 3x3")<<Testdata<<false;


}

void PosDefChecker::isPosDefReal(){
    QFETCH(Eigen::MatrixXd,TestMatrix);
    QFETCH(bool,Result);
    QCOMPARE(true,Result);
    //Replace true with an implemented function call on Matrix fetched
}
TEST_DECLARE(PosDefChecker)
