#ifndef PWM_H
#define PWM_H

#include <iostream>
#include <sstream>
#include <stdio.h>  
#include <unistd.h>
#include <string>
//#include <bits/stdc++.h> 
#include <cstring>
using namespace std;

class pwm
{
public:

    // Constructor of the class
    pwm ();

    // Destructor
    ~pwm ();
	
	void setupPwm(std::string pin, int period) ;
	
	
	void duty(float nanoS,std::string pin,bool flagServo)  ;
	
	std::string pinSelect(std::string pin);
	



};

#endif // uart_H