#include "stdint.h"
#include "tm4c123gh6pm.h"

void Led_Init (void){
    SYSCTL_RCGCGPIO_R |= 0x20; // enable portF clock
    while ((SYSCTL_PRGPIO_R & 0x20) == 0){}; // delay
    GPIO_PORTF_LOCK_R = 0x4C4F434B; // unlock commit register for portF
    GPIO_PORTF_CR_R |= 0x0E; // allow changes to PF123
    GPIO_PORTF_DIR_R |= 0X0E; // enable PF123 to be outputs
    GPIO_PORTF_DEN_R |= 0x0E; // enable PF123 to be digital
    GPIO_PORTF_AMSEL_R &= ~0x0E; // disable analog function
    GPIO_PORTF_AFSEL_R &=~0x0E; // no alternate function
    GPIO_PORTF_PCTL_R &= ~0x0000FFF0; // GPIO clear bit PCTL
    GPIO_PORTF_DATA_R &= ~0x0E; // initialize them to be off
}
#include <stdio.h>
#include <math.h> 
#define PI        3.14159265358979323846
// Function to convert degrees to radii
 double Radians(double degree)
{
	double onedeg = (PI) / 180;
	return (onedeg * degree);
}

  double distance(double new_lat, double new_long, double old_lat, double old_long)
{
	// Converting latitude and longitude from the degree system to the radial system
	new_lat = Radians(new_lat);
	new_long = Radians(new_long);
	old_lat = Radians(old_lat);
	old_long = Radians(old_long);

	// Haversine formula
	 double deltalong = new_long - old_long;
	 double deltalat = new_lat - old_lat;

	long double ans = pow(sin(deltalat / 2), 2) + cos(new_lat) * cos(old_lat) * pow(sin(deltalong / 2), 2);

	ans = 2 * asin(sqrt(ans));

	// Earth's radius in metres
	long double R = 6371000;

	// Calculate the result
	ans = ans * R;

	return ans;
}
