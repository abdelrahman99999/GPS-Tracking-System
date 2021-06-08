//headers used
#include <stdint.h>
#include <stdio.h>
#include <math.h> 
#include <string.h>
#include <stdlib.h>
#include "tm4c123gh6pm.h"
#include "LCD.h"
#include "Led.h"

//macros
#define PI   3.14159265358979323846

void SystemInit(){}
	
char GPSValues[100], *parseValue[20], *token;
long double latitude, longitude;
int index = 0;
const char comma[2] = ",";
// Wait for new input
// then return ASCII code
//Then test if the incoming data $GPRMC?
	uint8_t UART_InChar(void); {
		while ((UART2_FR_R & 0x0010) != 0);
		return((uint8_t)(UART2_DR_R & 0xFF));
		char c0;
		c0 = UART2_DR_R;
		if (c0 == '$'); {
			while ((UART2_FR_R & 0x0010) != 0);
			return((uint8_t)(UART2_DR_R & 0xFF));
			char c1;
			c0 = UART2_DR_R;
			if (c1 == 'G'); {
				while ((UART2_FR_R & 0x0010) != 0);
				return((uint8_t)(UART2_DR_R & 0xFF));
				char c2;
				c2 = UART2_DR_R;
				if (c2 == 'P'); {
					while ((UART2_FR_R & 0x0010) != 0);
					return((uint8_t)(UART2_DR_R & 0xFF));
					char c3;
					c3 = UART2_DR_R;
					if (c3 == 'R'); {
						while ((UART2_FR_R & 0x0010) != 0);
						return((uint8_t)(UART2_DR_R & 0xFF));
						char c4;
						c4 = UART2_DR_R;
						if (c4 == 'M'); {
							while ((UART2_FR_R & 0x0010) != 0);
							return((uint8_t)(UART2_DR_R & 0xFF));
							char c5;
							c5 = UART2_DR_R;
							if (c5 == 'C'); {
								while ((UART2_FR_R & 0x0010) != 0);
								return((uint8_t)(UART2_DR_R & 0xFF));
								char c6;
								c6 = UART2_DR_R;
								if (c6 == ','); {
									while ((UART2_FR_R & 0x0010) != 0);
									return((uint8_t)(UART2_DR_R & 0xFF));
									char c7;
									c7 = UART2_DR_R;
									//Assigning data to GPSValues array
									while (c7 != '*') {
										GPSValues[index] = c7;
										while ((UART2_FR_R & 0x0010) != 0);
										return((uint8_t)(UART2_DR_R & 0xFF));
										index++;
									}
									//Separating data in GPSValues array by comma
									index = 0;
									token = strtok(GPSValues, comma);
									while (token != NULL) {
										strcpy(parseValue[index], token);
										token = strtok(NULL, comma);
										index++;
									}
									//Data is valid if parseValue[1] = A / not valid if V
									if (strcmp(parseValue[1], "A") == 0) {
										latitude = atof(parseValue[2]);
										longitude = atof(parseValue[4]);
									}}}}}}}}}

// Function to convert degrees to radii
 long double Radians(long double degree){
     long double onedeg = (PI) / 180;
     return (onedeg * degree);
}

//  Function to calculate distance 
long double Total_distance(long double new_lat,long double new_long,long double old_lat,long double old_long,long double current_distance){
// Converting latitude and longitude from the degree system to the radial system
     new_lat = Radians(new_lat);
     new_long = Radians(new_long);
     old_lat = Radians(old_lat);
     old_long = Radians(old_long);
// Haversine formula
     long double deltalong = new_long - old_long;
     long double deltalat = new_lat - old_lat;
     long double ans = pow(sin(deltalat / 2), 2) + cos(new_lat) * cos(old_lat) * pow(sin(deltalong / 2), 2);
     ans = 2 * asin(sqrt(ans));
// Earth's radius in metres
     long double R = 6371000;
// Calculate the result
	ans = ans * R;
// updated distance
        current_distance = ans + current_distance;
	return current_distance;
}
int main(){
// testing distance and led 	
old_lat =  new_lat;
old_long = new_long;
new_lat = latitude;
new_long = longitude;
int x ;
	x = Total_distance(new_lat,new_long,old_lat,old_long,current_distance);
//testing led

  LCD_init();
  Led_Init();
  LCD_Cmd(CLEAR);

  int distance = x;
	
  turnOnReach100(distance);

  LCD_Cmd(f1_line);
  LCD_printS("distance :");
  delay_milliseconds(15);
  LCD_Cmd(s2_line);
  delay_milliseconds(15);
  LCD_printInt(distance);
}
	//Then LOOP
