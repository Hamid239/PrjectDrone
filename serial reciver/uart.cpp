//Written by hamidreza Rezaei (rezae018@umn.edu)

// Thank to () for awesome guide in his/her blog: https://blog.mbedded.ninja/
// thank to   Philippe Lucidarme for his libary seriallib this libary is slightly modified version of his.

#include "uart.h"

/*!
    \brief      Constructor of the class uart.
*/
// Class constructor
uart::uart()
{}


/*!
    \brief      Destructor of the class uart. It close the connection
*/
// Class desctructor
uart::~uart()
{
    Close();
}





// Error handling :
// 

int uart::Open(const char *Device,const unsigned int Bauds,bool parity,int stopBitNum,int numBits,bool flowControl){

	fd = open(Device, O_RDWR | O_NOCTTY | O_NDELAY);
	struct termios2 tty;		// Create new termios struc, we call it 'tty' for convention

	if (fd < 0) {
		printf("Error %i from open: %s\n", errno, strerror(errno));
		return -1;
	};
	  
	    fcntl(fd, F_SETFL, FNDELAY);          // Open the Device in non blocking mode ,i think this is redundant not sure. 


	memset(&tty, 0, sizeof tty);  // flushing tty setting everything to 0 


	// Read in existing settings, and handle any error

	if(ioctl(fd, TCGETS2, &tty) != 0) {
		printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
		return -1;
	};


	/// parity check 

	if (parity == 1) {
		tty.c_cflag |= PARENB;  // Set parity bit, enabling parity
	} else {
		tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
	};

	// number of stop bit (1 or 2 )
	switch(stopBitNum){
		case 1:
			tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
			break;
		case 2:
			tty.c_cflag |= CSTOPB;  // Set stop field, two stop bits used in communication
			break;
	};

	// number of bit transmitted by each byte only valid options are 5 , 6 ,7 ,8;
	switch(numBits){
		case 5:	
			tty.c_cflag |= CS5; // 5 bits per byte
			break;
		case 6:	
			tty.c_cflag |= CS6; // 6 bits per byte
			break;
		case 7:	
			tty.c_cflag |= CS7; // 7 bits per byte
			break;
		case 8:	
			tty.c_cflag |= CS8; // 8 bits per byte
			break;
	};


	// Flow Control

	if (flowControl==0){
		tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
	} else {
		tty.c_cflag |= CRTSCTS;  // Enable RTS/CTS hardware flow control
	};


	tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (from modem).

	tty.c_iflag |= IGNBRK;   // just ignore the break check what will happen if it is not set

	tty.c_cc[VTIME]=0;          // Timer unused
	tty.c_cc[VMIN]=0;           // At least on character before satisfy reading



	// Specifying a custom baud rate when using GNU C

	//cfsetispeed(&tty,Bauds);   // note this is if you are not using BOTHER and using CBAUD then uses the look up table 
	//cfsetospeed(&tty,Bauds);	 // note this is if you are not using BOTHER and using CBAUD then uses the look up table 
	tty.c_cflag &= ~CBAUD;
	tty.c_cflag |= BOTHER;
    tty.c_ispeed = Bauds;
    tty.c_ospeed = Bauds;
	

	tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
	tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

	tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

	// Save tty settings, also checking for error
	if (ioctl(fd, TCSETS2, &tty) != 0) {
		printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
		return -1;
	};
	
	return 1;

}

void uart::Close()
{
    close (fd);
};




/*!
     \brief Write a char on the current serial port
     \param Byte : char to send on the port (must be terminated by '\0')
     \return 1 success
     \return -1 error while writting data
  */
char uart::WriteChar(const char Byte)
{
#ifdef __linux__
    if (write(fd,&Byte,1)!=1)                                           // Write the char
        return -1;                                                      // Error while writting
    return 1;                                                           // Write operation successfull
#endif
};



//________________________________________
// ::: Read/Write operation on strings :::


/*!
     \brief Write a string on the current serial port
     \param String : string to send on the port (must be terminated by '\0')
     \return 1 success
     \return -1 error while writting data
  */
char uart::WriteString(const char *String)
{
#ifdef __linux__
    int Lenght=strlen(String);                                          // Lenght of the string
    if (write(fd,String,Lenght)!=Lenght)                                // Write the string
        return -1;                                                      // error while writing
    return 1;                                                           // Write operation successfull
#endif
}

// _____________________________________
// ::: Read/Write operation on bytes :::



/*!
     \brief Write an array of data on the current serial port
     \param Buffer : array of bytes to send on the port
     \param NbBytes : number of byte to send
     \return 1 success
     \return -1 error while writting data
  */
char uart::Write(const void *Buffer, const unsigned int NbBytes)
{

#ifdef __linux__
    if (write (fd,Buffer,NbBytes)!=(ssize_t)NbBytes)                    // Write data
        return -1;                                                      // Error while writing
    return 1;                                                           // Write operation successfull
#endif
}



/*!
     \brief Wait for a byte from the serial Device and return the data read
     \param pByte : data read on the serial Device
     \param TimeOut_ms : delay of timeout before giving up the reading
            If set to zero, timeout is disable (Optional)
     \return 1 success
     \return 0 Timeout reached
     \return -1 error while setting the Timeout
     \return -2 error while reading the byte
  */
char uart::ReadChar(char *pByte,unsigned int TimeOut_ms)
{
#ifdef __linux__

    TimeOut         Timer;                                              // Timer used for timeout
    Timer.InitTimer();                                                  // Initialise the timer
    while (Timer.ElapsedTime_ms()<TimeOut_ms || TimeOut_ms==0)          // While Timeout is not reached
    {

        switch (read(fd,pByte,1)) {                                     // Try to read a byte on the Device
        case 1  : return 1;                                            	// Read successfull
        case -1 : return -2;                                            // Error while reading
        }

    }
    return 0;
#endif
}



/*!
     \brief Read a string from the serial Device (without TimeOut)
     \param String : string read on the serial Device
     \param FinalChar : final char of the string
     \param MaxNbBytes : maximum allowed number of bytes read
     \return >0 success, return the number of bytes read
     \return -1 error while setting the Timeout
     \return -2 error while reading the byte
     \return -3 MaxNbBytes is reached
  */
int uart::ReadStringNoTimeOut(char *String,char FinalChar,unsigned int MaxNbBytes)
{
    unsigned int    NbBytes=0;                                          // Number of bytes read
    char            ret;                                                // Returned value from Read
	//memset(String, '\0', sizeof(String));
    while (NbBytes<MaxNbBytes)                                          // While the buffer is not full
    {                                                                   // Read a byte with the restant time
        ret=ReadChar(&String[NbBytes]);
        if (ret==1)                                                     // If a byte has been read
        {
            if (String[NbBytes]==FinalChar)                             // Check if it is the final char
            {
                String  [++NbBytes]=0;                                  // Yes : add the end character 0
                return NbBytes;                                         // Return the number of bytes read
            }
            NbBytes++;                                                  // If not, just increase the number of bytes read
        }
        if (ret<0) return ret;                                          // Error while reading : return the error number
    }
    return -3;                                                          // Buffer is full : return -3
}

/*!
     \brief Read a string from the serial Device (with timeout)
     \param String : string read on the serial Device
     \param FinalChar : final char of the string
     \param MaxNbBytes : maximum allowed number of bytes read
     \param TimeOut_ms : delay of timeout before giving up the reading (optional)
     \return  >0 success, return the number of bytes read
     \return  0 timeout is reached
     \return -1 error while setting the Timeout
     \return -2 error while reading the byte
     \return -3 MaxNbBytes is reached
  */
int uart::ReadString(char *String,char FinalChar,unsigned int MaxNbBytes,unsigned int TimeOut_ms)
{
    if (TimeOut_ms==0)
        return ReadStringNoTimeOut(String,FinalChar,MaxNbBytes);

	//memset(String, '\0', sizeof(String));
    unsigned int    NbBytes=0;                                          // Number of bytes read
    char            ret;                                                // Returned value from Read
    TimeOut         Timer;                                              // Timer used for timeout
    long int        TimeOutParam;
    Timer.InitTimer();                                                  // Initialize the timer

    while (NbBytes<MaxNbBytes)                                          // While the buffer is not full
    {                                                                   // Read a byte with the restant time
        TimeOutParam=TimeOut_ms-Timer.ElapsedTime_ms();                 // Compute the TimeOut for the call of ReadChar
        if (TimeOutParam>0)                                             // If the parameter is higher than zero
        {
            ret=ReadChar(&String[NbBytes],TimeOutParam);                // Wait for a byte on the serial link            
            if (ret==1)                                                 // If a byte has been read
            {

                if (String[NbBytes]==FinalChar)                         // Check if it is the final char
                {
                    String  [++NbBytes]=0;                              // Yes : add the end character 0
                    return NbBytes;                                     // Return the number of bytes read
                }
                NbBytes++;                                              // If not, just increase the number of bytes read
            }
            if (ret<0) return ret;                                      // Error while reading : return the error number
        }
        if (Timer.ElapsedTime_ms()>TimeOut_ms) {                        // Timeout is reached
            String[NbBytes]=0;                                          // Add the end caracter
            return 0;                                                   // Return 0
        }
    }
    return -3;                                                          // Buffer is full : return -3
}


/*!
     \brief Read an array of bytes from the serial Device (with timeout)
     \param Buffer : array of bytes read from the serial Device
     \param MaxNbBytes : maximum allowed number of bytes read
     \param TimeOut_ms : delay of timeout before giving up the reading
     \return 1 success, return the number of bytes read
     \return 0 Timeout reached
     \return -1 error while setting the Timeout
     \return -2 error while reading the byte
  */
int uart::Read (void *Buffer,unsigned int MaxNbBytes,unsigned int TimeOut_ms)
{
#ifdef __linux__
    TimeOut          Timer;                                             // Timer used for timeout
    Timer.InitTimer();                                                  // Initialise the timer
    unsigned int     NbByteRead=0;
    while (Timer.ElapsedTime_ms()<TimeOut_ms || TimeOut_ms==0)          // While Timeout is not reached
    {
        unsigned char* Ptr=(unsigned char*)Buffer+NbByteRead;           // Compute the position of the current byte
        int Ret=read(fd,(void*)Ptr,MaxNbBytes-NbByteRead);              // Try to read a byte on the Device
        if (Ret==-1) return -2;                                         // Error while reading
        if (Ret>0) {                                                    // One or several byte(s) has been read on the Device
            NbByteRead+=Ret;                                            // Increase the number of read bytes
            if (NbByteRead>=MaxNbBytes)                                 // Success : bytes has been read
                return NbByteRead;
        }
    }
    return 0;                                                           // Timeout reached, return 0
#endif
}




// _________________________
// ::: Special operation :::



/*!
    \brief  Return the number of bytes in the received buffer (UNIX only)
    \return The number of bytes in the received buffer
*/
int uart::Peek()
{
    int Nbytes=0;
#ifdef __linux__
    ioctl(fd, FIONREAD, &Nbytes);
#endif
    return Nbytes;
}

// ******************************************
//  Class TimeOut
// ******************************************


/*!
    \brief      Constructor of the class TimeOut.
*/
// Constructor
TimeOut::TimeOut()
{}

/*!
    \brief      Initialise the timer. It writes the current time of the day in the structure PreviousTime.
*/
//Initialize the timer
void TimeOut::InitTimer()
{
    gettimeofday(&PreviousTime, NULL);
}

/*!
    \brief      Returns the time elapsed since initialization.  It write the current time of the day in the structure CurrentTime.
                Then it returns the difference between CurrentTime and PreviousTime.
    \return     The number of microseconds elapsed since the functions InitTimer was called.
  */
//Return the elapsed time since initialization
unsigned long int TimeOut::ElapsedTime_ms()
{
    struct timeval CurrentTime;
    int sec,usec;
    gettimeofday(&CurrentTime, NULL);                                   // Get current time
    sec=CurrentTime.tv_sec-PreviousTime.tv_sec;                         // Compute the number of second elapsed since last call
    usec=CurrentTime.tv_usec-PreviousTime.tv_usec;                      // Compute
    if (usec<0) {                                                       // If the previous usec is higher than the current one
        usec=1000000-PreviousTime.tv_usec+CurrentTime.tv_usec;          // Recompute the microseonds
        sec--;                                                          // Substract one second
    }
    return sec*1000+usec/1000;
}









