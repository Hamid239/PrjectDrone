#include "pwm.h"

int main(){
	float nanoS = 1000000;
	int perid = 20000000;
	pwm pwmObj;
	pwmObj.setupPwm("p9_14", perid);
	pwmObj.duty(nanoS,"p9_14",1)  ;
	
	for (int i=0; i<100 ; i++){
		cout << "enter your new value ";
		cin >> nanoS ;
		pwmObj.duty(nanoS,"p9_14",1)  ;
		
	}
	
	return(0);
}