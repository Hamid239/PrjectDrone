#include "gps.h"

#ifdef __linux__
#define         DEVICE_PORT             "/dev/ttyS3"                         // ttyS0 for linux
#endif

// Input: coma separated string
// Output: Vector with all the elements in input.
std::vector<std::string> splitStringByComma(std::string input){

    //std::cout <<"the input is=" << input << "\n";
    std::vector<std::string>  returnVector;
    std:: stringstream    ss(input);
    std:: string          element;
   // std:: string          dummy;

    while(getline(ss, element, ',')) {
	
	//std::cout <<"the element is=" << element << "\n";
        returnVector.push_back(element);
    }


    return returnVector;
}


string leftParse(string in,int shift){
	string leftOut;
    int inSize = in.length();
    int outSize= inSize - shift;
    leftOut = in.substr (0,outSize);
	return leftOut;
    }
	
string rightParse(string in,int shift){
	string rightOut;
    int inSize = in.length();   
    int outSize= inSize - shift;
    rightOut= in.substr(1+outSize,inSize);
	return rightOut;
    }
 
void detSen(string Buffer,int *caseId,vector<string> *GPSVecOut){
	
	vector<string> GPSVec=splitStringByComma(Buffer);
	*GPSVecOut=GPSVec;
	if (GPSVec.size()>3){
		
		if (GPSVec[0]=="$GPGGA"){
			*caseId=1;
		}
		else if (GPSVec[0]=="$GPRMC"){
			*caseId=2;
		}
		else if (GPSVec[0]=="$GPGSA")
			*caseId=3;
		else {
			cout << "not valid sentence" << endl;
			*caseId=4;			
		}
	}
	else {
		*caseId=4;
	}
} 

GPS_s GPS()
{
    GPS_s output;   // gps struct for the output result 
	static serialib Serial_obj; 	// Object of the serialib class 
	static bool openPortFlag=true ;  
    int Ret,caseId;    	// Used for return values
	int numChar0,numChar1,numChar2;
	int numCharArray[3];
    char Buffer0[500],Buffer1[500],Buffer2[500];
	string Buffer[3];
	vector<string> GPSVec;
    
    




    // Open serial port
	if(openPortFlag==1){
	
		Ret=Serial_obj.openDevice(DEVICE_PORT,115200);   	// Open serial link at 115200 bauds
	    if (Ret!=1) {                                                           // If an error occured...
        printf ("Error while opening port. Permission problem ?\n");        // ... display a message ...

        output.Ret=Ret;
        return output;                                                         // ... quit the application
		}
	printf ("Serial port opened successfully !\n");
	openPortFlag=false;
	}




    // Read a string from the serial device
    numChar0=Serial_obj.readString (Buffer0,'\n',500,1000); 	// Read a maximum of 128 characters with a timeout of 1 s
    cout << "the buff   "<< Buffer0 << endl; 

    numChar1=Serial_obj.readString(Buffer1,'\n',500,1000); 
	cout << "the buff1   "<< Buffer1 << endl;              // The final character of the string must be a line feed ('\n')
	
	
    numChar2=Serial_obj.readString(Buffer2,'\n',500,1000); 
	cout << "the buff1   "<< Buffer2 << endl;              // The final character of the string must be a line feed ('\n')

	sleep(1);

    //Serial_obj.Close();															//   only if it is last time Close the connection with the device

	Buffer[0]=Buffer0;
	Buffer[1]=Buffer1;
	Buffer[2]=Buffer2;
	numCharArray[0]=numChar0;
	numCharArray[1]=numChar1;
	numCharArray[2]=numChar2;
	
	output.validGGA=false;
	output.validGPRMC=false;
	output.validGPGSA=false;


	for (int i=0; i<3;i++){
		if(numCharArray[i]>0){
		GPSVec.clear();
		detSen(Buffer[i],&caseId,&GPSVec);	
		output.validator(GPSVec,caseId);
		}
	}
		
	cout << "gga " <<  output.validGGA << "  rmc  " <<  output.validGPRMC  << "  GSA  "<< output.validGPGSA << endl ;
}


int main()
{
int i=0;
for(i=1; i<100000; ++i){

GPS_s values;
values=GPS();

}
return 0;
}






