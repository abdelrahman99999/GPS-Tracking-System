//headers used
#include <stdint.h>
#include <stdio.h>
#include "LCD.h"
#include "Led.h"
#include "GPS.h"


void SystemInit(){}
int main(){
	long double total_distance  = 0;
	char data[100];
	
	Led_Init();
	LCD_init();
	// *UART init*
	
	while(1){
		
		// turn on red LED if distance measured is 100m.
		turnOnReach100(total_distance);
		
		// receive data from GPS
		for (int i=0;i<100;i++){
			c[i] = UART_inChar();
		}

		float latitude, longitude;
		latitude = getCoordinate(data, LATITUDE );
		longitude = getCoordinate(data, LONGITUDE );
		
		// update distance
		total_distance += Total_distance(latitude,longitude, , ,total_distance);

	}
}
