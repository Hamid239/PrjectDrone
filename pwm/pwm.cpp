

#include "pwm.h"



// limitation:  period of pin with two chanel have to be same.
// pin : get the coresponded pin number for the desired pwm pin example P9_14.
// input period is in nano second;


// Class constructor
pwm::pwm()
{}


// Class desctructor
pwm::~pwm()
{
    cout << "Object is being deleted" << endl;
}

std::string pwm::pinSelect(std::string pin){
	
	if(pin =="p9_14"){
		pin="ehrpwm1a";
	}
	
	else if(pin == "p9_16"){
		pin= "ehrpwm1b";
	}
	
	else if(pin == "P9_22"){
		pin= "ehrpwm0a";
	}
	
	else if(pin == "P9_21"){
		pin= "ehrpwm0b";
	}
	
	else if(pin == "P9_14"){
		pin= "ehrpwm1a";
	}
	
	else if(pin == "P8_19"){
		pin= "ehrpwm2a";
	}
	
	else if(pin == "P8_13"){
		pin= "ehrpwm2b";
	}
	
	return pin;
}




 
void pwm::setupPwm(std::string pin, int period) {
	
	pin = pinSelect(pin);
	

    FILE *periodF, *pwmF;
	stringstream ss;
	

	ss << "/dev/pwm/" << pin <<"/period" ; 
	string loc = ss.str();
	cout << " the string for period is : " << loc << "\n" ;
	int n = loc.length(); 
	char loc_array[n + 1]; 
	strcpy(loc_array, loc.c_str());

	
    periodF = fopen(loc_array, "w");  
    fseek(periodF,0,SEEK_SET);  
    fprintf(periodF,"%d",period);  
    //fprintf(periodF,"%f",100011*10); 
    fflush(periodF);  
    fclose(periodF);  
    
	ss.str("");
	ss << "/dev/pwm/" << pin <<"/enable" ; 
	loc = ss.str();
	n = loc.length(); 
	char new_array[n + 1]; 
	strcpy(new_array, loc.c_str());
	
    pwmF = fopen(new_array, "w");  
    fseek(pwmF,0,SEEK_SET);  
    fprintf(pwmF,"%d",1);  
    fflush(pwmF);  
    fclose(pwmF);  
}; 

void pwm::duty(float nanoS,std::string pin,bool flagServo)  
{  
	// if flag servo is tru instead of duty cycle it will recive percentage values must be between 0 to 100
    stringstream ss;
	pin = pinSelect( pin);
	FILE *dutyF;  
	
	
	
	ss << "/dev/pwm/" << pin <<"/duty_cycle";
	

	string loc = ss.str();
	int n = loc.length(); 
	char loc_array[n + 1]; 
	strcpy(loc_array, loc.c_str());
	
	if (flagServo ==1){
		nanoS = (10000*nanoS)+ 1000000;

}
    dutyF = fopen(loc_array, "w");  
    fseek(dutyF,0,SEEK_SET);  
    fprintf(dutyF,"%d",static_cast<int>(nanoS));  
    fflush(dutyF);  
    fclose(dutyF);  
}  








