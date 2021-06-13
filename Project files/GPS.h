#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//macros
#define PI   3.14159265358979323846
#define NMEA_RMC "$GPRMC"
#define LATITUDE 2
#define LONGITUDE 4




// Function to convert degrees to radii
double Radians(double degree) {
     double onedeg = (PI) / 180;
    return (onedeg * degree);
}




//  Function to calculate distance 
double Total_distance(double new_lat,double new_long,double old_lat,double old_long,double current_distance) {
    // Converting latitude and longitude from the degree system to the radial system
    new_lat = Radians(new_lat);
    new_long = Radians(new_long);
    old_lat = Radians(old_lat);
    old_long = Radians(old_long);
    // Haversine formula
    double deltalong = new_long - old_long;
    double deltalat = new_lat - old_lat;
    double ans = pow(sin(deltalat / 2), 2) + cos(new_lat) * cos(old_lat) * pow(sin(deltalong / 2), 2);
    ans = 2 * asin(sqrt(ans));
    // Earth's radius in metres
    double R = 6371000;
    // Calculate the result
    ans = ans * R;
    // updated distance
    current_distance = ans + current_distance;
    return (current_distance);
}






void UART_Init(void) {

    SYSCTL_RCGCUART_R |= 0x0004; // activate UART2       0 0 0 0 0 1 0 0  (8uart)
    SYSCTL_RCGCGPIO_R |= 0x0008; // activate port D          0 0 1 0 0 0   
    UART2_CTL_R &= ~0x0001; // disable UART
    UART2_IBRD_R = 104;
    UART2_FBRD_R = 11;
    UART2_LCRH_R = 0x0070;   //1 stop bit(stp2=0),fifo enable(fen=1),8 bit(wlen= 1 1 )    0 1 1 1 0 0 0 0 
    UART2_CTL_R = 0x0301;  // enable uart,hse=0,tx=1,rx=1
    GPIO_PORTD_LOCK_R = 0x4C4F434B;
    GPIO_PORTD_CR_R |= 0xC0;              //PD6,PD7
    GPIO_PORTD_AFSEL_R = 0xC0;             //enable alternative function for  PD6,PD7
    GPIO_PORTD_PCTL_R = 0x11000000;         
    GPIO_PORTD_DEN_R = 0xC0;
    GPIO_PORTD_AMSEL_R = 0x0;
}




// Wait for new input
// then return ASCII code
char UART_InChar(void) {
    while ((UART2_FR_R & 0x0010) != 0);
    // wait until RXFE is 0
    return((UART2_DR_R & 0xFF));

}



// A function to extract Latitude or Longitude coordinates of NMEA sentence from GPS
double getCoordinate(char data[], uint8_t coordinateIndex) {
    char* token = strtok(data, ",");
    float pos = 0;
    // check if NMEA is a GPRMC pattern
    if (strcmp(token, NMEA_RMC) == 0) {
        int i;
        for (i = 1; i <= coordinateIndex + 1; i++) {
            char* token = strtok(NULL, ",");
            pos = strtod(token, NULL);
        }
    }
    return pos;
}



//function that wait for 1s using SysTick timer
void Systick_delay_1s(void) {
    NVIC_ST_CTRL_R = 0; //disable Systick during setup
    NVIC_ST_RELOAD_R = 0x00F423FF // Reload value with 1 sec ((16*10^6) - 1 )
    NVIC_ST_CURRENT_R = 0 // Clear current value
    NVIC_ST_CTRL_R = 0x05 // enable Systick ad clk
}
