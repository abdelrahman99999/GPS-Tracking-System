//headers used
#include <stdint.h>
#include <stdio.h>
#include "LCD.h"
#include "Led.h"
#include "GPS.h"


void SystemInit(){}

//$GPRMC,200751.00,A,4147.320,N,02929.63031,E,9.879,105.80,301117,,,A*6C

char GPS_values[70];  //all GPS data chars

double latitude = 0, longitude = 0, seconds = 0, minutes = 0;

double current_distance = 0, new_lat = 0, new_long = 0, old_lat = 0, old_long = 0;

int degrees, T_distance = 0;

int main(){

        UART_Init();
        LCD_init();
        Led_Init();

        while (T_distance <= 100) {
                delay_milliseconds(1000);
                int i;

                for (i = 0; i < 70; i++) {
                        GPS_values[i] = UART_InChar();
                }

                 latitude = getCoordinate(GPS_values, LATITUDE);
                 longitude = getCoordinate(GPS_values, LONGITUDE);

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

                if (old_lat == 0 || old_long == 0) {    //for first time
                    old_lat = new_lat;
                    old_long = new_long;
                }
                else {
                    T_distance = Total_distance(new_lat, new_long, old_lat, old_long, current_distance);
                    old_lat = new_lat;
                    old_long = new_long;

                    //print total distance
                    LCD_Cmd(CLEAR);
                    delay_milliseconds(10);
                    LCD_Cmd(f1_line);
                    delay_milliseconds(10);
                    LCD_printS("distance = ");
                    delay_milliseconds(10);
                    LCD_Cmd(s2_line);
                    delay_milliseconds(10);
                    LCD_printInt(T_distance);
                }

            }
        
        // turn on the red led & view location on Maps
        turnOnReach100(T_distance,old_lat, old_long);

    return(0);
}
