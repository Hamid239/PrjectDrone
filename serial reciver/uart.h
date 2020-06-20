// Used for TimeOut operations
#ifndef UART_H
#define UART_H



#ifdef __linux__
    #include <stdlib.h>
    #include <sys/types.h>
    #include <sys/shm.h>
   // #include <termios.h>
  // 	#include <asm/termios.h>
  
	#include <asm/ioctls.h>
	#include <asm/termbits.h>
	#include <sys/ioctl.h>
	
	
    #include <string.h>
    #include <iostream>
	#include <sys/time.h>// Include for Linux
    // File control definitions
    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/ioctl.h>

#endif



/*!  \class uart
     \brief     This class can manage a serial port. The class allows basic operations (opening the connection, reading, writing data and closing the connection).
     \example   Example1.cpp
   */


class uart
{
public:
    // Constructor of the class
    uart    ();

    // Destructor
    ~uart   ();
	
     //________________________________________
    // ::: Configuration and initialization :::


    // Open a device
    int    Open        (const char *Device,const unsigned int Bauds,bool parity,int stopBitNum,int numBits,bool flowControl);

    // Close the current device
    void    Close();



    //___________________________________________
    // ::: Read/Write operation on characters :::


    // Write a char
    char    WriteChar   (char);

    // Read a char (with timeout)
    char    ReadChar    (char *pByte,const unsigned int TimeOut_ms=NULL);



    //________________________________________
    // ::: Read/Write operation on strings :::


    // Write a string
    char    WriteString (const char *String);
    // Read a string (with timeout)
    int     ReadString  (   char *String,
                            char FinalChar,
                            unsigned int MaxNbBytes,
                            const unsigned int TimeOut_ms=NULL);



    // _____________________________________
    // ::: Read/Write operation on bytes :::


    // Write an array of bytes
    char    Write       (const void *Buffer, const unsigned int NbBytes);

    // Read an array of byte (with timeout)
    int     Read        (void *Buffer,unsigned int MaxNbBytes,const unsigned int TimeOut_ms=NULL);


    // _________________________
    // ::: Special operation :::

    // Return the number of bytes in the received buffer
    int     Peek();

private:
    // Read a string (no timeout)
    int     ReadStringNoTimeOut  (char *String,char FinalChar,unsigned int MaxNbBytes);

#ifdef __linux__
    int             fd;
#endif

};


/*!  \class     TimeOut
     \brief     This class can manage a timer which is used as a timeout.
   */
   
// Class TimeOut
class TimeOut
{
public:

    // Constructor
    TimeOut();

    // Init the timer
    void                InitTimer();

    // Return the elapsed time since initialization
    unsigned long int   ElapsedTime_ms();

private:    
    struct timeval      PreviousTime;
};





#endif // uart_H