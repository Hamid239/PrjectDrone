
#include "./pwm/pwm.h"
#include "uart.h"
#include "sbusCall.h"


#ifdef __linux__
#define         DEVICE_PORT             "/dev/ttyS4"                         // ttyS0 for linux
#endif


int main(){
	
	int Ret;                                                               		 // Used to check succes or error 
	uint8_t  Buffer1[25];	
	uart Serial_obj; 	
	Ret=Serial_obj.Open(DEVICE_PORT,100000,1,2,8,0); 
	if (Ret > 0 ){
		printf ("Serial port opened successfully ! ret is %d \n",Ret);
	
		while(1) {
			
			memset(&Buffer1, 0, sizeof Buffer1);

			Ret=Serial_obj.Read(Buffer1,25,1000);
			if (Ret>0) {
				cout << "numbure of byte read " << Ret << "  \n" ;                                      // If a string has been read from, print the string
				/*
				for(int i=0; i<Ret; i++){
					printf("String read from serial port1 : %x  \n",Buffer1[i]);
				}	
			*/
				float header =-999;
				float endByte = -999;
				int failSafe = -999;
				int frameLost =-999;
				float channelsOut[16];
				memset(&channelsOut, 0, sizeof channelsOut);
				
				
				SbusParse(Buffer1,&header,channelsOut,16,&endByte,&failSafe,&frameLost);
				
				//printf("Header is: %f  \n",header);
				if(header!=15){
					Serial_obj.Close();
					Ret=Serial_obj.Open(DEVICE_PORT,100000,1,2,8,0); 
					//cout << "ooooooooooooooooooooPPPPPPSSSSS \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n";
				}
				
				
				
				if(header ==15 ) {
					//float nanoS = 1000000;
					float nanoS = ((channelsOut[2]-172)/16.39);
					cout << "nanoS value is " << nanoS << "\n";
					int perid = 20000000;
					pwm pwmObj;
					pwmObj.setupPwm("p9_14", perid);
					pwmObj.duty(nanoS,"p9_14",1)  ;
		
					}

				
				/*
				printf("endByte is: %f  \n",endByte);
				printf("frameLost is: %i  \n",frameLost);
				printf("failSafe is: %i  \n",failSafe);
				
				
				
				for(int i=0; i<4; i++){
					printf("CHANNELS%i : %f  ,",i,channelsOut[i]);
					if (i ==4) printf("\n");
				}
				*/
			}
			
			
			if (Ret==0) {
				printf("timed out \n");
			}
			
					
			
		}
	}
	else{
		cout << "failed to open the device \n" ;
	}		
	
	
	return(0);
}