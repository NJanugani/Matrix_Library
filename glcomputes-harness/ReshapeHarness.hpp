#include<QTest>
#include<Eigen/Eigen>
#include<eigenHeader.hpp>
#include<QString>
#include"MultiTest.hpp"

class ReshapeChecker : public QObject
{
	Q_OBJECT

public:
	ReshapeChecker();
  ~ReshapeChecker();
private Q_SLOTS:

    void
		ReshapeEigen();
    void
		ReshapeEigen_data();
};
TEST_DECLARE(ReshapeChecker)

ReshapeChecker::ReshapeChecker()
{
}
ReshapeChecker::~ReshapeChecker()
{

}

void ReshapeChecker::ReshapeEigen_data(){

    QTest::addColumn<Eigen::MatrixXd>("Original");
    QTest::addColumn<int>("New_Int");
    QTest::addColumn<int>("New_Column");

    Eigen::MatrixXd a(4,1);
    a<< 1,2,3,4;
    QTest::newRow("4x1 to 2x2 Matrix")<<a<<2<<2;

    a.resize(2,2);
    QTest::newRow("2x2 to a 4x1 Matrix")<<a<<4<<1;

    a.resize(4,5);
    a<<1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20;
    QTest::newRow("4x5 to 6x6 , Append Zeros")<<a<<6<<6;

    a.resize(6,6);
    a<<1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16;
    QTest::newRow("6x6 to 4x5 , should Return Error")<<a<<4<<5;

}

void ReshapeChecker::ReshapeEigen(){
    QFETCH(Eigen::MatrixXd,Original);
   	QFETCH(int,New_Int);
   	QFETCH(int,New_Column);

  	Eigen::MatrixXd a=Original;
  	a.resize(New_Int,New_Column);
  	Original.resize(New_Int,New_Column);

   	QCOMPARE(a,Original);
   	//Replace a.resize() with implemented function

}
