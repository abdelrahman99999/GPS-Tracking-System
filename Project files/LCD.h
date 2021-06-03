//description for lcd pins 
/*
port A -> used in lcd Control
where 
		E   -> PA7
		R/W -> PA6
		Rs  -> PA5

port B ->  used in lcd data
where 
		D0  -> PB0
		D1  -> PB1
		D2  -> PB2
		D3  -> PB3
		D4  -> PB4
		D5  -> PB5
		D6  -> PB6
		D7  -> PB7
*/

//headers used
#include "tm4c123gh6pm.h"
#include <stdint.h>

//LCD macros for lcd commands
#define CLEAR 0x01  			//clear display screen
#define TurnOnDisplay 0x0F 		//Display on,cursor blinking 
#define LCD_config 0x38  		//(8-bit data,D0to D7)
#define autoIncrement 0x06  	//auto increment cursor(shift cursor to right) 
#define f1_line 0x80  			//cursor at begining of 1st line
#define s2_line 0xC0  			//cursor at begining of 2nd line
