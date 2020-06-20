#include <iostream>
#include "../src/BNO055.h"
#include <unistd.h>
#include <fstream>
//#include <time.h> 
#include <sys/time.h> 


using namespace std;




double * Acc_bframe_to_acc_NEDframe(double qW, double qX, double qY, double qZ, double aX, double aY, double aZ ) {

   static double  acc_NEDframe[3]; //X, Y, Z

acc_NEDframe[0] = (qW*qW+qX*qX-qY*qY-qZ*qZ)*aX+2*(qX*qY-qW*qZ)*aY+2*(qW*qY+qX*qZ)*aZ;
acc_NEDframe[1] = 2*(qX*qY+qW*qZ)*aX+(qW*qW-qX*qX+qY*qY-qZ*qZ)*aY+2*(qY*qZ-qW*qX)*aZ;
acc_NEDframe[2] = 2*(qX*qZ+qW*qY)*aX+2*(qY*qZ+qW*qX)*aY+(qW*qW-qX*qX-qY*qY+qZ*qZ)*aZ;



   return acc_NEDframe;
}



int main()
{

double * acc_NEDframe;

BNO055 bno = BNO055(-1, BNO055_ADDRESS_A, 2);

 
//OPERATION_MODE_AMG
bno.begin(bno.OPERATION_MODE_NDOF);

usleep(1000000);

 int temp = bno.getTemp();
  std::cout << "Current Temperature: " << temp << " C" << std::endl;

  bno.setExtCrystalUse(true);

usleep(1000000);
//imu::Quaternion quat = bno.getQuat();
imu::Vector<3> acc_bframe = bno.getVector(BNO055::VECTOR_ACCELEROMETER);
imu::Vector<3> pqr = bno.getVector(BNO055::VECTOR_GYROSCOPE);
imu::Vector<3> mag = bno.getVector(BNO055::VECTOR_MAGNETOMETER);
usleep(1000000);
struct timeval t, initaltime;
double intT, finalT ,dum1, dum2;

uint8_t sys, gyro, accel, magcal;
int sysCalV,GyroCalV, accCalV, magCalV;

gettimeofday(&initaltime, NULL);
dum1 = initaltime.tv_usec ;
dum1 = dum1/1000000;
intT = (initaltime.tv_sec + dum1);


while(1)
{
	gettimeofday(&t, NULL);
	dum2 = t.tv_usec;
	dum2 = dum2/1000000;
	finalT = (t.tv_sec + dum2)- intT ;
	cout << "the t " << finalT << "\n";
	sys=0;
	gyro=0;
	accel=0; 
	magcal=0;
	bno.getCalibration(&sys, &gyro, &accel, &magcal);
	
	
	sysCalV  = sys;
	GyroCalV = gyro;
	accCalV  = accel;
	magCalV  = magcal;
	
	
	acc_bframe = bno.getVector(BNO055::VECTOR_ACCELEROMETER);
	pqr = bno.getVector(BNO055::VECTOR_GYROSCOPE);
	mag = bno.getVector(BNO055::VECTOR_MAGNETOMETER);
	std::ofstream fileObj("../../shared/readMe.txt");
	fileObj << finalT << ","<<acc_bframe[0] << "," << acc_bframe[1] << ","<< acc_bframe[2] << "," << pqr[0] << "," << pqr[1] <<","<< pqr[2] << "," << mag[0] << "," << mag[1] << ","<< mag[2] << "," << sysCalV << ","<< GyroCalV<< "," << accCalV<< "," << magCalV << "\n";
	fileObj.close();
	
	std::cout  << "sys: " << sysCalV << "  gyro cal: " << GyroCalV << "  accle cal: "<< accCalV << "  mag cal : " << magCalV << "\n" ;
	std::cout << "p: " << pqr[0] << " q: " << pqr[1] << " r: " << pqr[2]  << std::endl;
	
	std::cout << "aX: " << acc_bframe[0] << " aY: " << acc_bframe[1] << " aZ: " << acc_bframe[2]  << std::endl;
	
	std::cout << "magX: " << mag[0] << " magY: " << mag[1] << " magZ: " << mag[2]  << std::endl;
	
	usleep(100);

}
    
    return 0;
}
