

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


#include "RTClib.h"
RTC_DS1307 rtc;
#include <Stepper.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 7, 8, 10, 9);
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 13
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
RTC_DS1307 rtc;
//Stepper motor
Stepper myStepper = Stepper(stepsPerRevolution, 38, 36, 34, 32);

int buttonState = 0;
char state = 'I';
int Temperature, Humidity;
int TemperatureThreshold = 20;
int HuidityThreshold = 10;

void setup(){

//Setting Inputs/Outputs
  //LED's and button
  DDRE |= 0b00111000;
  DDRG |= 0b00100000;
  DDRH |= 0b00001000;
  //Fan Motor
  DDRB |= 0b10000000;
  //Stepper Motor
  myStepper.setSpeed(5);
  //Start Serial Communication
  Serial.begin(9600);
  //LCD
  lcd.begin(16, 2);
  lcd.print("Temp: ");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");  
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
	rtc.adjust(DateTime(2022,12,10,16,19,0);
}


void loop(){


  switch(state){
    case 'D':{

	state = I;
      	PORTE |= 0b00100000;
    	//Turn all other LED's off
      	PORTE &= 0b00100000;
        PORTG &= 0b00100000;

    	//Turn motor off
    	PORTB &= 0b00000000;
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

    	//Monitor start button using an ISR
		state = I;



        break;
    }
    case 'I':{

    //Turn green LED on
      PORTE = 0b00010000;
    //Turn all other LED's off
      PORTG = 0b0010000;
    //Turn motor off
      PORTB &= 0b00000000;
    	//Record time and date of when motor turns off
      Serial.print("Date & Time: ");
      Serial.print(now.month(), DEC);
      Serial.print('/');
      Serial.println(now.day(), DEC);      
      Serial.print(now.hour(), DEC);
      Serial.print(':');
      Serial.print(now.minute(), DEC);
      Serial.println(now.second(), DEC); 
      Serial.println("Fan turned on");
    		
    	//Continuously monitor water level
        lcd.setCursor(0, 0);
        lcd.print("Water Level: ");
        lcd.print(analogRead(A0));
        lcd.print(" ");
        lcd.setCursor(0, 1);
        lcd.print("Water Level: ");
        lcd.print(analogRead(A1));
        lcd.print(" ");
        delay(1000);
    	//Display temperature and humidity on LCD
          delay(2000);
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
    	if(Temperature > Temperature Threshold){
	       state = R;
    	}
    	if(WaterLevel <= WaterThreshold){
	       state = R;
    	}

	//ISR
		state = D;


        break;
    }
    case 'E':{
    	//Turn on red LED
    	PORTG |= 0b00100000;
      //Turn all other LED's off
    	PORTE &= 0b00000000;
    	//Turn Motor off regardless of temperature
    	PORTB &= 0b00000000;
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
      if (analogRead(A1) < 30) {
        Serial.println("Water Level is too low");
    		//Arduino LCD Library
    	if(WaterLevel > WaterThreshold && ResetButton == 1){
	        state = I;
    	}


	//ISR
	        state = D;



      break;
    }
    case 'R':{

    	//Turn blue LED on
    	PORTE |= 0b00001000;
    	//Turn all other LED's off
    	PORTE &= 0b00001000;
      PORTG &= 0b00000000;
    	//Turn motor on
      PORTB |= 0b10000000;
    	//Record time and date of when motor turns on
	Serial.print("Date & Time: ");
        Serial.print(now.month(), DEC);
        Serial.print('/');
        Serial.println(now.day(), DEC);      
        Serial.print(now.hour(), DEC);
        Serial.print(':');
        Serial.print(now.minute(), DEC);
        Serial.println(now.second(), DEC); 
    	//Display temperature and humidity on LCD
    		//Arduino LCD Library
        lcd.setCursor(0, 0);
        lcd.print("Water Level: ");
        lcd.print(analogRead(A0));
        lcd.print(" ");
        lcd.setCursor(0, 1);
        lcd.print("Water Level: ");
        lcd.print(analogRead(A1));
        lcd.print(" ");
        delay(1000);
    	//Display temperature and humidity on LCD
          delay(2000);
        float h = dht.readHumidity();
        float t = dht.readTemperature();
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
    	if(Temperature <= TempThreshold){
	        state = Idle;
    	}
     	if (analogRead(A0) > 100) {
        Serial.println("Water Level is too high");
        } 
      	if (analogRead(A1) < 30) {
        Serial.println("Water Level is too low");
        }

    	if(WaterLevel < WaterThreshold){
	       state = E;
    	}


	//ISR
	        state = D;



      break;
    }
  }    
  }
}

//Globally

	//Depending on value of potentiometer
		//Adjust stepper motor for angle of vent
			//Arduino Library
     myStepper.step(stepsPerRevolution);
