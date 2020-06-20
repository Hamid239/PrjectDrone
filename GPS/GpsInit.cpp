/*
GPS Initialization
Written by Hamidreza Rezaei
Under Antevorta LLC 

*/

// initialization of the port for serial communication in Linux 
// TODO add the same for windows
// the return value is either 0 or 1
// 1: opened successfully 
// 2:  fail to open 

#include "GpsInit.h"
using namespace std;

#ifdef __linux__
#define         DEVICE_PORT             "/dev/ttyS3"                         // ttyS0 for linux 
#endif


int InitGps(){
	serialib Serial_obj;				 								    // Object of the serialib class
	int Ret;							  						    	    // Used for return values
	char Buffer[500],Buffer1[500],Buffer2[500];
	Ret=Serial_obj.openDevice(DEVICE_PORT,115200);   						 		// Open serial link at specific bauds
	
	if (Ret!=1) {                                                           // If an error occurred...
        printf ("Error while opening port. Permission problem ?\n");        // ... display a message ...
        return Ret;                                                         // ... quit the application and return
    }

	printf ("Serial port opened successfully !\n");
	
	

	
	while(1){
		int i=0;
		cout << "here " << endl;
		//Ret=Serial_obj.openDevice(DEVICE_PORT,115200);  
		 for(int i=0; i< 1000; i++){
			 
			 Ret=Serial_obj.readString(Buffer,'\n',500,10000);    // Read a maximum of 128 characters with a timeout of 1 s
			 cout << "the buff   "<< Buffer << "   ret   "<< Ret << endl; 
			 //cout << "this is what is stored in buffer:  " << Buffer  << endl ; 
			 
			 int Ret1;
			 Ret1=Serial_obj.readString(Buffer1,'\n',500,100000); 
			 //cout << "this is what is stored in buffer1:  " << Buffer1  << endl ; 
			 cout << "the buff1   "<< Buffer1 << "   ret1   "<< Ret1 << endl;

			 usleep(100000);
			 
			
		 }
		 //Serial_obj.closeDevice();	


	}
    
}


int main(){
	while(1){
		InitGps();	
	}
return 0;
	 
}