
#include "sbusCall.h"

void SbusParse(uint8_t packet[25],float *header,float channelsOut1[],int size,float *endByte, int *failSafe,int *frameLost){
	//float channels[16];
	
	uint8_t payload[22];
	for (int i=0; i<22 ;i++){
		payload[i]= packet[(i+1)];
	}

	uint16_t ones11 = 2047; // this variable used to get 11 bit from combanation of two byte.
	
	* header = packet[0];
	//channelsOut1[0]  = 8;
	channelsOut1[0]  = (uint16_t) ((payload[0]    |payload[1] <<8)                     & ones11);
	channelsOut1[1]  = (uint16_t) ((payload[1]>>3 |payload[2] <<5)                     & ones11);
	channelsOut1[2]  = (uint16_t) ((payload[2]>>6 |payload[3] <<2 |payload[4]<<10)     & ones11);
	channelsOut1[3]  = (uint16_t) ((payload[4]>>1 |payload[5] <<7)                     & ones11);
	channelsOut1[4]  = (uint16_t) ((payload[5]>>4 |payload[6] <<4)                     & ones11);
	channelsOut1[5]  = (uint16_t) ((payload[6]>>7 |payload[7] <<1 |payload[8]<<9)      & ones11);
	channelsOut1[6]  = (uint16_t) ((payload[8]>>2 |payload[9] <<6)                     & ones11);
	channelsOut1[7]  = (uint16_t) ((payload[9]>>5 |payload[10]<<3)                     & ones11);
	channelsOut1[8]  = (uint16_t) ((payload[11]   |payload[12]<<8)                     & ones11);
	channelsOut1[9]  = (uint16_t) ((payload[12]>>3|payload[13]<<5)                     & ones11);
	channelsOut1[10] = (uint16_t) ((payload[13]>>6|payload[14]<<2 |payload[15]<<10)    & ones11);
	channelsOut1[11] = (uint16_t) ((payload[15]>>1|payload[16]<<7)                     & ones11);
	channelsOut1[12] = (uint16_t) ((payload[16]>>4|payload[17]<<4)                     & ones11);
	channelsOut1[13] = (uint16_t) ((payload[17]>>7|payload[18]<<1 |payload[19]<<9)     & ones11);
	channelsOut1[14] = (uint16_t) ((payload[19]>>2|payload[20]<<6)                     & ones11);
	channelsOut1[15] = (uint16_t) ((payload[20]>>5|payload[21]<<3)                     & ones11);
	
	* failSafe = (packet[23] & 8);
	//*failSafe = 1;
	*frameLost = (packet[23] & 4);
	* endByte = packet[24];
	//(*channelsOut1) = channels;
}
/*	

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
/*			
				float header =-999;
				float endByte = -999;
				int failSafe = -999;
				int frameLost =-999;
				float channelsOut[16];
				memset(&channelsOut, 0, sizeof channelsOut);
				
				
				SbusParse(Buffer1,&header,channelsOut,16,&endByte,&failSafe,&frameLost);
				
				printf("Header is: %f  \n",header);
				if(header!=15){
					Serial_obj.Close();
					Ret=Serial_obj.Open(DEVICE_PORT,100000,1,2,8,0); 
					cout << "ooooooooooooooooooooPPPPPPSSSSS \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n";
				}
				printf("endByte is: %f  \n",endByte);
				printf("frameLost is: %i  \n",frameLost);
				printf("failSafe is: %i  \n",failSafe);
				
				
				for(int i=0; i<4; i++){
					printf("CHANNELS%i : %f  ,",i,channelsOut[i]);
					if (i ==4) printf("\n");
				}
			}
			
			
			if (Ret==0) {
				printf("timed out \n");
			}
					
			
		}
	}
	else{
		cout << "failed to open the device \n" ;
	}		
	
	
	
	
	return 0;
}
*/
