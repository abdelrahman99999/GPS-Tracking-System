#include "stdint.h"
#include <stdio.h>
#include <math.h> 
#include "tm4c123gh6pm.h"
#include "LCD.h"

#define PI   3.14159265358979323846
#define RED       0x02
#define BLUE      0x04
#define GREEN     0x08



void led_on(unsigned char color){
if(color==0x02){GPIO_PORTF_DATA_R=RED;}  
else if(color==0x04){GPIO_PORTF_DATA_R=BLUE;}
else if(color==0x08){GPIO_PORTF_DATA_R=GREEN;} 
else{GPIO_PORTF_DATA_R = 0;}
}

// Function to convert degrees to radii
 long double Radians(long double degree)
{
     long double onedeg = (PI) / 180;
     return (onedeg * degree);
}
  long double distance(long double new_lat,long double new_long,long double old_lat,long double old_long)
{
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
        return ans;
}
