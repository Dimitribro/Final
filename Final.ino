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
volatile unsigned char* port_e = (unsigned char*) 0x;
volatile unsigned char* ddr_e = (unsigned char*) 0x;
volatile unsigned char* pin_e = (unsigned char*) 0x;
//Yellow LED on Pin 3
volatile unsigned char* port_e = (unsigned char*) 0x;
volatile unsigned char* ddr_e = (unsigned char*) 0x;
volatile unsigned char* pin_e = (unsigned char*) 0x;
//Red LED on Pin 4
volatile unsigned char* port_g = (unsigned char*) 0x;
volatile unsigned char* ddr_g = (unsigned char*) 0x;
volatile unsigned char* pin_g = (unsigned char*) 0x;
//Blue LED on Pin 5
volatile unsigned char* port_e = (unsigned char*) 0x;
volatile unsigned char* ddr_e = (unsigned char*) 0x;
volatile unsigned char* pin_e = (unsigned char*) 0x;
//Fan Motor on Pin 6
volatile unsigned char* port_h = (unsigned char*) 0x;
volatile unsigned char* ddr_h = (unsigned char*) 0x;
volatile unsigned char* pin_h = (unsigned char*) 0x;
//Stepper Motor on Pin 7
	//Arduino Library
//LCD on ...
	//Arduino Library
//Water Level Sensor on Pin 8
	//Arduino Library
//Temperature/Humidity Sensor on Pin 9
	//Arduino Library



void setup(){

//Setting Inputs/Outputs
	//Green LED
	*ddr_ |= 0x80;
	//Yellow LED
	*ddr_ |= 0x80;
	//Red LED
	*ddr_ |= 0x80;
	//Blue LED
	*ddr_ |= 0x80;
	//Fan Motor
	*ddr_ |= 0x80;
	//Stepper Motor
	//LCD
	//Water Level Sensor
	//Temperature/Humidity Sensor
	
//Start Serial Communication (Library?)
	Serial.begin(9600);


}


void loop(){

//STATE: Disabled

	//Turn yellow LED on
	*port_ |= 0x80;
	//Turn all other LED's off
	*port_ &= 0x7F;
	*port_ &= 0x7F;
	*port_ &= 0x7F;
	//Turn motor off
	*port_ &= 0x7F;
	//Record time and date of when motor turns off
		//Arduino Real-time Clock Module
		//Display in serial monitor
		Serial.println("...");
	//No temp or water monitoring
	//Monitor start button using an ISR
	//If start button is pressed
	if(StartButton == 1){
		//Change state to Idle
	}
//STATE: Idle

	//Turn green LED on
	*port_ |= 0x80;
	//Turn all other LED's off
	*port_ &= 0x7F;
	*port_ &= 0x7F;
	*port_ &= 0x7F;
	//Turn motor off
	*port_ &= 0x7F;
	//Record time and date of when motor turns off
		//Arduino Real-time Clock Module
		//Display in serial monitor
		Serial.println("...");
	//Continuously monitor water level
		//Arduino Library
	//Display temperature and humidity on LCD
		//Arduino Library
	//If Temperature > Threshold
	if(){
		//Change state to Running
	}
	//If water level < or = Threshold
	if(){
		//Change state to Error
	}

//STATE: Error

	//Turn on red LED
	*port_ |= 0x80;
	//Turn all other LED's off
	*port_ &= 0x7F;
	*port_ &= 0x7F;
	*port_ &= 0x7F;
	//Turn Motor off regardless of temperature
	*port_ &= 0x7F;
	//Record time and date of when motor turns off
		//Arduino Real-time Clock Module
		//Display in serial monitor
		Serial.println("...");
	//Display "Water level is too low" on LCD and serial monitor
	Serial.println("Water level is too low");
		//Arduino LCD Library
	//If water level is above threshold and reset button pressed
	if(WaterLevel > WaterThreshold && ResetButton == 1){
		//Change state to Idle
	}
	//If stop button is pressed
	if(StopButton == 1){
		//Change state to Disabled
	}

//STATE: Running

	//Turn blue LED on
	*port_ |= 0x80;
	//Turn all other LED's off
	*port_ &= 0x7F;
	*port_ &= 0x7F;
	*port_ &= 0x7F;
	//Turn motor on
	*port_ |= 0x80;
	//Record time and date of when motor turns on
		//Arduino Real-time Clock Module
		//Display in serial monitor
		Serial.println("...");
	//Display temperature and humidity on LCD
		//Arduino LCD Library
	//If temperature < or = threshold
	if(Temperature <= TempThreshold){
		//Change state to Idle
	}
	//If water < Threshold
	if(WaterLevel < WaterThreshold){
		//Transition to Error State
	}
	//If stop button is pressed
	if(StopButton == 1){
		//Change state to Disabled
	}



//Globally

	//Depending on value of potentiometer
		//Adjust stepper motor for angle of vent
			//Arduino Library


}



