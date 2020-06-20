#include <stdio.h>
#include "serialib.h"
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>     /* atof */
using namespace std;
struct GPS_s
{
int     Ret;    // Used for return values
int     latD;
int		latMin;
float	latS;
char 	latLet;
int     lonD;
int		lonMin;
float	lonS;
char 	lonLet;
float 	alt;	   	// in meter
float  speed;
float  heading;
int     numberSatellites;
int     date;
int 	fix;
int 	time[3]; // IN UTC
int		numSat;
bool    validGGA,validGPRMC,validGPGSA;



void validator(vector<string> BufferVector,int id){
	string latDegStr,latMinStr,latSecStr,intermidiateStr;  // just used for parsing 
	string lonDegStr,lonMinStr,lonSecStr;
	int intermidiateSize;								  // just used for parsing
	
	switch(id){
		case 1:			
			validGGA=true;			
			for(int i=0;i<10;i++){
				int size=BufferVector[i].size();
				
				if(size!=0){
					switch(i){

						case 1:						
							time[0] = atoi((BufferVector[i].substr(0,2)).c_str()); // hour in utc
							time[1] = atoi((BufferVector[i].substr(2,2)).c_str()); // min in utc
							time[2] = atoi((BufferVector[i].substr(4,2)).c_str()); // sec in utc
							break;
						case 2:

							latDegStr = BufferVector[i].substr(0,size-8);
							latD = atoi(latDegStr.c_str());
							
							
							intermidiateStr = BufferVector[i].substr(latDegStr.size(),size-latDegStr.size());
							intermidiateSize=intermidiateStr.size();
							
							latMinStr = intermidiateStr.substr(0,intermidiateSize-6);
							latMin = atoi(latMinStr.c_str());
													
							latSecStr = intermidiateStr.substr(latMinStr.size(),intermidiateSize-latMinStr.size());
							latS = atof(latSecStr.c_str());
							
							printf("this is parsed  hour %d min %d sec %d latd %d latmin %d latMinStr %s latStr %s  latS %f  \n",time[0],time[1],time[2],latD,latMin,latMinStr.c_str(),latSecStr.c_str(),latS);
	
							break;
						case 3:
							
							if(BufferVector[i]== "N"){
								latLet ='N';
							}
							else  latLet ='S';
							break;
							
						case 4:
							lonDegStr = BufferVector[i].substr(0,size-8);
							lonD = atoi(lonDegStr.c_str());
							
							
							intermidiateStr = BufferVector[i].substr(lonDegStr.size(),size-lonDegStr.size());
							intermidiateSize=intermidiateStr.size();
							
							lonMinStr = intermidiateStr.substr(0,intermidiateSize-6);
							lonMin = atoi(lonMinStr.c_str());
													
							lonSecStr = intermidiateStr.substr(lonMinStr.size(),intermidiateSize-latMinStr.size());
							lonS = atof(lonSecStr.c_str());
														
							break;
						case 5:
						
							if(BufferVector[i]== "W"){
								lonLet ='W';
							}
							else  lonLet ='E';

							break;
						case 6:
							fix = atoi(BufferVector[i].c_str());
							break;
							
						case 7:
							numSat = atoi(BufferVector[i].c_str());
							break;
							
						case 8:
							//Horizontal dilution of position
							break;
							
						case 9:
							alt =	atof(BufferVector[i].c_str());
							cout << "altitude in meter "<< alt << endl;
							break;

					}	
				}
			}
			
			break;
			
		case 2:
			validGPRMC=true;
			for(int i=0;i<10;i++){
				int size=BufferVector[i].size();
				
				if(size!=0){
					switch(i){
						case 7:
							speed = atof(BufferVector[i].c_str());
							cout << "speed "<< speed << endl;
							break;
						case 8:
							heading = atof(BufferVector[i].c_str());
							cout << "heading "<< heading << endl;
							break;
					}
				}
			}
			break;
		case 3:
			validGPGSA=true;
			cout << "this is the checking what is in " << BufferVector[4] << " size  "  <<BufferVector[4].size() << endl;
			break;
		case 4:
			break;
	}
	
}

};
void parse(string in, string *leftOut, string *rightOut, int position_char,int shift ,int *flagHaveValue);
GPS_s GPS();
std::vector<std::string> splitStringByComma(std::string input);
void detSen(string Buffer,int *caseId,vector<string> *GPSVec);

string leftParse(string in,int shift);
string rightParse(string in,int shift);