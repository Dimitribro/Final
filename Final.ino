/* NEED:

[Lib] - Can use Arduino Library
[None] - Can't use Arduino Library

- [None] Fan motor with fan blade
	- Use with separate power supply board
- [Lib] Vent motor (Stepper motor)
	- Button or Potentiometer
- [None] Red, Blue, Yellow, and Green LED's
- [Lib] LCD
- [Lib/None] Water level sensor
	- Use either an interrupt from the comparator
	- Or Sample using the ADC (No ADC library)
- [Lib] Temperature/humidity sensor DHT11
- [Lib] Real-time clock module

*/



//Define Pointers
//Green LED on Pin 2
//Yellow LED on Pin 3
//Red LED on Pin 4
//Blue LED on Pin 5



//Fan Motor on Pin 6
//Stepper Motor on Pins 38-32 Even #'s
	//Arduino Library
//LCD on Pins 53 - 23 Odd #'s
	//Arduino Library
//Water Level Sensor on Pins 8, 9, 10
	//Arduino Library
//Temperature/Humidity Sensor on Pins 12, 13, 7
	//Arduino Library
//Button on Pin 11
//Real-Time Clock Module on Pins 22, 24, 26 (A,L,W)
#include "RTClib.h"
RTC_DS1307 rtc;

char state = 'I';


void setup(){

//Setting Inputs/Outputs
  //LED's
  DDRE |= 0b00111000;
  DDRG |= 0b00100000;
  DDRH |= 0b00001000;
	//Fan Motor
	//*ddr_h |= 0x80;
	//Stepper Motor
	//LCD
	//Water Level Sensor
	//Temperature/Humidity Sensor
  //Real time clock
  if (! rtc.begin()) {
  Serial.println("Couldn't find RTC");
  while (1);
}

rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

	
//Start Serial Communication (Library?)
	Serial.begin(9600);


}



void loop(){


  switch(state){
    case 'D':{

    	//Turn yellow LED on
      	PORTE |= 0b00100000;
    	//Turn all other LED's off
      	PORTE &= 0b00100000;
        PORTG &= 0b00100000;

    	//Turn motor off
    	PORTH &= 0b00000000;
//    	//Record time and date of when motor turns off
          DateTime now = rtc.now();
          Serial.print("Date & Time: ");
         
          Serial.print(now.day(), DEC);
          Serial.print(" (");
          
          Serial.print(now.hour(), DEC);
          Serial.print(':');
          Serial.print(now.minute(), DEC);

//    		//Arduino Real-time Clock Module
//    		//Display in serial monitor
//    		Serial.println("...");
//    	//No temp or water monitoring
//    	//Monitor start button using an ISR
//    	//If start button is pressed
//    	if(StartButton == 1){
//    		//Change state to Idle
//    	}
        break;
    }
    case 'I':{

    //Turn green LED on
      PORTE = 0b00010000;
    //Turn all other LED's off
      PORTG = 0b0010000;
    //Turn motor off
      PORTH &= 0b00000000;
    	//Record time and date of when motor turns off
    		//Arduino Real-time Clock Module
    		//Display in serial monitor
    		//Serial.println("...");
    	//Continuously monitor water level
    		//Arduino Library
    	//Display temperature and humidity on LCD
    		//Arduino Library
//    	//If Temperature > Threshold
//    	if(){
//    		//Change state to Running
//       state = Running;
//    	}
//    	//If water level < or = Threshold
//    	if(){
//    		//Change state to Error
//       state = Error;
//    	}
        break;
    }
    case 'E':{
    	//Turn on red LED
    	PORTG |= 0b00100000;
      //Turn all other LED's off
    	PORTE &= 0b00000000;
    	//Turn Motor off regardless of temperature
    	PORTH &= 0b00000000;
//    	//Record time and date of when motor turns off
//    		//Arduino Real-time Clock Module
//    		//Display in serial monitor
//    		Serial.println("...");
//    	//Display "Water level is too low" on LCD and serial monitor
//    	Serial.println("Water level is too low");
//    		//Arduino LCD Library
//    	//If water level is above threshold and reset button pressed
//    	if(WaterLevel > WaterThreshold && ResetButton == 1){
//    		//Change state to Idle
//        state = Idle;
//    	}
//    	//If stop button is pressed
//    	if(StopButton == 1){
//    		//Change state to Disabled
//        state = Disabled;
//    	}
      break;
    }
    case 'R':{

    	//Turn blue LED on
    	PORTE |= 0b00001000;
    	//Turn all other LED's off
    	PORTE &= 0b00001000;
      PORTG &= 0b00000000;
    	//Turn motor on
      PORTH |= 0b00001000;
//    	//Record time and date of when motor turns on
//    		//Arduino Real-time Clock Module
//    		//Display in serial monitor
//    		Serial.println("...");
//    	//Display temperature and humidity on LCD
//    		//Arduino LCD Library
//    	//If temperature < or = threshold
//    	if(Temperature <= TempThreshold){
//    		//Change state to Idle
//        state = Idle;
//    	}
//    	//If water < Threshold
//    	if(WaterLevel < WaterThreshold){
//    		//Transition to Error State
//       state = Error;
//    	}
//    	//If stop button is pressed
//    	if(StopButton == 1){
//    		//Change state to Disabled
//        state = Disabled;
//    	}
      break;
    }
  }    
}

//Globally

	//Depending on value of potentiometer
		//Adjust stepper motor for angle of vent
			//Arduino Library
