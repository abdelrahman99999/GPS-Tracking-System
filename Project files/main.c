#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "tm4c123gh6pm.h"
#include "LCD.h"
#include "Led.h"
#include "Functions.h"


//macros
#define PI   3.14159265358979323846
#define NMEA_RMC "$GPRMC"
#define LATITUDE 2
#define LONGITUDE 4

void SystemInit() {}
//testing
// $GPRMC,200751.00,A,4047.32510,N,02929.63031,E,9.879,105.80,301117,,,A*6C

int main() {

    UART_Init();
    UART_InChar();
    LCD_init();
    Led_Init();

    char GPS_values[70];
    double latitude = 0, longitude = 0, seconds = 0, minutes = 0;
    double current_distance = 0, new_lat = 0, new_long = 0, old_lat = 0, old_long = 0;
    int degrees, T_distance = 0;

    //storing data in an array
begin:while (T_distance <= 100) {
    Systick_delay_1s();
    int i;
    for (i = 0; i < 70; i++) {
        while ((UART2_FR_R & 0x0010) != 0) {
            GPS_values[i] = (UART2_DR_R & 0xFF);
        }
    }
    //Data valid if GPS_values[1] = A is valid - not valid if =V
    if (strcmp(GPS_values[2], "A") == 0) {
        latitude = getCoordinate(GPS_values, LATITUDE);
        longitude = getCoordinate(GPS_values, LONGITUDE);
    }

    //latitude calculation
    degrees = latitude / 100;
    minutes = latitude - (double)(degrees * 100);
    seconds = minutes / 60.00;
    new_lat = degrees + seconds;

    //longitude calculation
    degrees = longitude / 100;
    minutes = longitude - (double)(degrees * 100);
    seconds = minutes / 60.00;
    new_long = degrees + seconds;

    // calculate distance and update values 
    if (old_lat == 0 | old_long == 0) {
        old_lat = new_lat;
        old_long = new_long;
    }
    else {
        T_distance = Total_distance(new_lat, new_long, old_lat, old_long, current_distance);
        old_lat = new_lat;
        old_long = new_long;

        //print total distance
        LCD_Cmd(CLEAR);
        LCD_Cmd(f1_line);
        LCD_printS("distance = ");
        LCD_Cmd(s2_line);
        delay_milliseconds(20);
        LCD_printInt(T_distance);
        delay_milliseconds(1000);
    }
    {goto begin;}
}
void turnOnReach100(T_distance);
return(0);
}
