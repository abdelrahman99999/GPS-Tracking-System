#include <stdint.h>
#include <stdio.h>
#include <math.h> 
#include "tm4c123gh6pm.h"
#include "LCD.h"
#include "Led.h"

#define PI   3.14159265358979323846

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

int main(){


}
