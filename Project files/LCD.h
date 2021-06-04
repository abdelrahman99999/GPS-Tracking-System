//description for lcd pins used 
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
#include <string.h> 

//LCD macros for lcd commands
#define CLEAR 0x01  			//clear display screen
#define TurnOnDisplay 0x0F 		//Display on,cursor blinking 
#define LCD_config 0x38  		//(8-bit data,D0to D7)
#define autoIncrement 0x06  	//auto increment cursor(shift cursor to right) 
#define f1_line 0x80  			//cursor at begining of 1st line
#define s2_line 0xC0  			//cursor at begining of 2nd line

//functions 
//(1)function for delay milliseconds
void delay_milliseconds(int n){
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<3180;j++){}
}
//(2) function for delay microseconds
void delay_microseconds(int n){
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<3;j++){}
}

//(3)function for lcd commands
void LCD_Cmd(unsigned char command){
    GPIO_PORTA_DATA_R = 0x00; 		//RS =0, E=0, RW=0
    GPIO_PORTB_DATA_R = command;
    GPIO_PORTA_DATA_R |=0x80; 		//E=1
    delay_microseconds(0);
    GPIO_PORTA_DATA_R = 0x00; 		//E=0
    if(command < 4){    //as (clear display command) and (return cursor home command)
	      delay_milliseconds(2);} 
	else {delay_microseconds(37);}
}

//(4)function for lcd intitalization depending on specific pins 
void LCD_init(void) {

    SYSCTL_RCGCGPIO_R = 0x03; 		// Enable port A and port B clocks
    while ((SYSCTL_PRGPIO_R & 0x03) == 0) {};

    //we will use PA7,PA6,PA5 as digital output
    GPIO_PORTA_LOCK_R = 0x4C4F434B;
    GPIO_PORTA_CR_R = 0xE0;
    GPIO_PORTA_AFSEL_R = 0;
    GPIO_PORTA_PCTL_R = 0;
    GPIO_PORTA_AMSEL_R = 0;
    GPIO_PORTA_DIR_R |= 0xE0; 		//PORT A controls RS,E and R/W
    GPIO_PORTA_DEN_R |= 0xE0;

    //we will use all pins of portB as digital output 
    GPIO_PORTB_LOCK_R = 0x4C4F434B;
    GPIO_PORTB_CR_R = 0xFF;
    GPIO_PORTB_AFSEL_R = 0;
    GPIO_PORTB_PCTL_R = 0;
    GPIO_PORTB_AMSEL_R = 0;
    GPIO_PORTB_DIR_R |= 0xFF; 		//PORTB D0-D7
    GPIO_PORTB_DEN_R |= 0xFF; 		//PORTB D0-D7

    LCD_Cmd(LCD_config);
    LCD_Cmd(autoIncrement);
    LCD_Cmd(TurnOnDisplay);
    LCD_Cmd(CLEAR);
}

//(5)function for printing one character on lcd display 
void LCD_printC(unsigned char data) {
    GPIO_PORTA_DATA_R = 0x20; 		//RS=1, E=0,RW=0
    GPIO_PORTB_DATA_R = data;
    GPIO_PORTA_DATA_R |= 0x80;		//E=1
    delay_microseconds(0);
    GPIO_PORTA_DATA_R = 0x00;		//E=0
    delay_microseconds(0);
}

//(6)function for printing integer on lcd display 
//Integer must be between 0-255
void LCD_printInt(uint8_t num){
	uint8_t i=0,arr[20];
	uint8_t temp=num;
	for(i=0 ; num!=0 ; i++){
		arr[i]=temp%10;
		num=num/10;
		temp=num;
	}
	for(;i!=0;--i){
		LCD_printC(arr[i-1]+48);
		 delay_milliseconds(20);
	}	
};

//(7)function for printing one word on lcd display 
void LCD_printS(char *s){
    int i;
	int Size = strlen(s);
    for(i=0;i<Size;i++){
        LCD_printC(s[i]);
        delay_milliseconds(20);
    }
}
