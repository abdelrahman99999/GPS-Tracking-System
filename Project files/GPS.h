#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//macros
#define PI   3.14159265358979323846
#define NMEA_RMC "$GPRMC"
#define LATITUDE 2
#define LONGITUDE 4

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
	return (current_distance);
}


// A function to extract Latitude or Longitude coordinates of NMEA sentence from GPS
float getCoordinate(char data[], uint8_t coordinateIndex) {

    char* token = strtok(data, ",");
    float pos = 0;
 
    // check if NMEA is a GPRMC pattern
    if (strcmp(token, NMEA_RMC) == 0){
        int i;
        for ( i = 1; i <= coordinateIndex +1; i++) {
            char* token = strtok(NULL, ",");
            pos = strtod(token, NULL);
        }
    }
    return pos;
}
