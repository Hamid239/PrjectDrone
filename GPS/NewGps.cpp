/*
New modified version of the gps code 
Written by Hamidreza Rezaei
Under Antevorta LLC 

*/

// initialization of the port for serial communication in Linux 
// TODO add the same for windows
// the return value contain the GPS code or the error code so check for error
// number corresponding to various error are as follow 
// 1: 
// 2: 
// 3:


#ifdef __linux__
#define         DEVICE_PORT             "/dev/ttyS5"                         // ttyS0 for linux 
#endif


void InitGps(int debug){
	serialib Serial_obj;				 								    // Object of the serialib class
	int Ret;							  						    	    // Used for return values
	char Buffer[500],Buffer1[500];
	Ret=Serial_obj.Open(DEVICE_PORT,4800);   						 		// Open serial link at specific bauds
	
	if (Ret!=1) {                                                           // If an error occurred...
        printf ("Error while opening port. Permission problem ?\n");        // ... display a message ...
        output.Ret=Ret;
        return output;                                                       // ... quit the application and return
    }

	printf ("Serial port opened successfully !\n");
	  // Read a string from the serial device
    
} 




Ret=Serial_obj.ReadString(Buffer,'\n',500,1000);    // Read a maximum of 128 characters with a timeout of 1 s