

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



//Green LED on Pin 2
//Yellow LED on Pin 3
//Red LED on Pin 4
//Blue LED on Pin 5
//Fan Motor on Pin 6
//Stepper Motor on Pins 38-32 Even #'s
//LCD on Pins 12, 11, 7, 8, 10, 9
//Water Level Sensor on Pin A 0
//Temperature/Humidity Sensor on Pins 13
//Button on Pin 52
//Real-Time Clock Module on Pins SDA, SCL

//Libraries and Definitions
#include "RTClib.h"
#include <Stepper.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 7);
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 13
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
RTC_DS1307 rtc;
//Stepper motor
const int stepsPerRevolution = 2048;
Stepper myStepper = Stepper(stepsPerRevolution, 38, 36, 34, 32);

int buttonState = 0;
volatile char state = 'R';
int Temperature, Humidity;
int TemperatureThreshold = 26;
int HuidityThreshold = 10;
volatile bool restart_loop;
volatile unsigned char *myTCCR1A = (unsigned char *) 0x80;
volatile unsigned char *myTCCR1B = (unsigned char *) 0x81;
volatile unsigned char *myTCCR1C = (unsigned char *) 0x82;
volatile unsigned char *myTIMSK1 = (unsigned char *) 0x6F;
volatile unsigned int  *myTCNT1  = (unsigned  int *) 0x84;
volatile unsigned char *myTIFR1 =  (unsigned char *) 0x36;
unsinged int Current_freq = 0;


void setup(){

//Setting Inputs/Outputs
  //LED's
	DDRA |= 0b01010101;
  //Fan Motor
	DDRH |= 0b00001000;
  //Stepper Motor
	myStepper.setSpeed(5);
  //Start Serial Communication
	Serial.begin(9600);
  //ISR Button
 	 DDRE |= 0b00000000;
  	PORTE |= 0b00010000;
  	attachInterrupt(0, pin_ISR, CHANGE);
  //LCD
  	lcd.begin(16, 2);
  	lcd.print("Temp: ");
  	lcd.setCursor(0, 1);
  	lcd.print("Humidity: ");  
  //Timer Registers
  	*myTCCR1A = 0b00000000;
  	*myTCCR1B = 0b00000000;
  	*myTCCR1C = 0b00000000;
  //Water Level Sensor
  //Temperature/Humidity Sensor
  	dht.begin();  
  //Real time clock
  	if (! rtc.begin()) {
  	Serial.println("Couldn't find RTC");
  	while (1);
	}	

#ifndef ESP8266
	while(!Serial);
#endif

	if(! rtc.begin()) {
		Serial.println("Couldn't find RTC");
	}
	rtc.adjust(DateTime(2022,12,12,17,45,0));
}


void loop(){
restart_loop = false;

DateTime now = rtc.now();

while(!restart_loop){

  switch(state){

    case 'D':{

	//LED's
        PORTA = 0b00010000;

    	//Turn motor off
    	PORTH &= 0b00000000;

    	//Record time and date of when motor turns off
          DateTime now = rtc.now();
          Serial.print("Date & Time: ");
          Serial.print(now.month(), DEC);
	  Serial.print('/');
          Serial.println(now.day(), DEC);      
          Serial.print(now.hour(), DEC);
          Serial.print(':');
          Serial.print(now.minute(), DEC);
	  Serial.println(now.second(), DEC);

        break;
    }

    case 'I':{
	
	//LED's
        PORTA = 0b00000100;

        //Turn motor off
        PORTH &= 0b0000000;

    	//Record time and date of when motor turns off
        Serial.print("Date & Time: ");
        Serial.print(now.month(), DEC);
        Serial.print('/');
        Serial.println(now.day(), DEC);      
        Serial.print(now.hour(), DEC);
        Serial.print(':');
        Serial.print(now.minute(), DEC);
        Serial.println(now.second(), DEC); 
    		
    	//Display temperature and humidity on LCD
       	my_delay(1);
	float h = dht.readHumidity();
        float t = dht.readTemperature();
       	Temperature = t;
	Humidity = h;

	lcd.setCursor(6, 0);
        lcd.print(t);
        lcd.print((char)223);
        lcd.print("C");
        lcd.setCursor(10, 1);
        lcd.print(h);
        lcd.print("%");

        Serial.print("Humidity: ");
        Serial.print(h);
        Serial.print(" %\t");
        Serial.print("Temperature: ");
        Serial.print(t);
        Serial.print((char)223);
        Serial.println(" C");

    	if(Temperature > TemperatureThreshold){
	       state = 'R';
    	}

	but  = PINE & 0b00010000;

    	if(analogRead(A0) <= 300 && but &= 0b00010000;){
	       state = 'R';
    	}
		
        break;
    }

    case 'E':{

	//LED's
    	PORTA = 0b01000000;
    	
	//Turn Motor off regardless of temperature
    	PORTH &= 0b00000000;
    	
	//Record time and date of when motor turns off
	Serial.print("Date & Time: ");
        Serial.print(now.month(), DEC);
        Serial.print('/');
        Serial.println(now.day(), DEC);      
        Serial.print(now.hour(), DEC);
        Serial.print(':');
        Serial.print(now.minute(), DEC);
        Serial.println(now.second(), DEC); 
    	
	//Display "Water level is too low" on LCD and serial monitor
        if (analogRead(A0) < 80) {
        Serial.println("Water Level is too low");
	}    	
	
	but = PINE & 0b00010000;
    
	if(analogRead(A0) > 300 && but &= 0b00010000;){
	        state = 'I';
    	}


      break;
    }

    case 'R':{

	//LED's
    	PORTA = 0b00000001;
    	
	//Turn motor on
        PORTH |= 0b00001000;
    	
	//Record time and date of when motor turns on
        Serial.println("Fan turned on");
	Serial.print("Date & Time: ");
        Serial.print(now.month(), DEC);
        Serial.print('/');
        Serial.println(now.day(), DEC);      
        Serial.print(now.hour(), DEC);
        Serial.print(':');
        Serial.print(now.minute(), DEC);
        Serial.println(now.second(), DEC); 

    	//Display temperature and humidity on LCD
        my_delay(0.5);
	float h = dht.readHumidity();
        float t = dht.readTemperature();
        Temperature = t;

	lcd.setCursor(6, 0);
        lcd.print(t);
        lcd.print((char)223);
        lcd.print("C");
        lcd.setCursor(10, 1);
        lcd.print(h);
        lcd.print("%");

        Serial.print("Humidity: ");
        Serial.print(h);
        Serial.print(" %\t");
        Serial.print("Temperature: ");
        Serial.print(t);
        Serial.print((char)223);
        Serial.println(" C");

    	if(Temperature <= 24){
	        state = 'I';
    	}

     	if (analogRead(A0) > 300) {
        Serial.println("Water Level is too high");
        } 

      	if (analogRead(A0) < 80) {
        Serial.println("Water Level is too low");
          state = 'E';
        }


      break;
    }

  }    

  }


//Globally

	//Adjust stepper motor for angle of vent
     myStepper.step(stepsPerRevolution);
}

}

void pin_ISR(){
  if(state == 'D'){
    state = 'I';
    restart_loop = true;
  }
  else{
    state = 'D';
    restart_loop = true;
  }
 
}

void my_delay(unsigned int freq)
{
  // calc period
  double period = 1.0/double(freq);
  // 50% duty cycle
  double half_period = period/ 2.0f;
  // clock period def
  double clk_period = 0.0000000625;
  // calc ticks
  unsigned int ticks = half_period / clk_period;
  // stop the timer
  *myTCCR1B &= 0xF8;
  // set the counts
  *myTCNT1 = (unsigned int) (65536 - ticks);
  // start the timer
  * myTCCR1B |= 0b00000001;
  // wait for overflow
  while((*myTIFR1 & 0x01)==0); // 0b 0000 0000
  // stop the timer
  *myTCCR1B &= 0xF8;   // 0b 0000 0000
  // reset TOV           
  *myTIFR1 |= 0x01;
}

