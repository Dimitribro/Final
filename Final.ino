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



//STATE: Disabled

	//Turn yellow LED on
	//Turn motor off
	//No temp or water monitoring
	//Monitor start button using an ISR
	//If start button is pressed
		//Chnage state to Idle
//STATE: Idle

	//Turn green LED on
	//Turn motor off
	//Record time stamp of transition times
	//Continuously monitor water level
	//Display temperature and humidity on LCD
	//If Temperature > Threshold
		//Change state to Running
	//If water level < or = Threshold
		//Change state to Error

//STATE: Error

	//Turn on red LED
	//Turn Motor off regardless of temperature
	//Display message "Water level is too low"
	//If water level is above threshold and reset button pressed
		//Change state to Idle
	//If stop button is pressed
		//Change state to Disabled

//STATE: Running

	//Turn blue LED on
	//Turn motor on
	//Display temperature and humidity on LCD
	//If temperature < or = threshold
		//Change state to Idle
	//If water < Threshold
		//Transition to Error State
	//If stop button is pressed
		//Change state to Disabled




