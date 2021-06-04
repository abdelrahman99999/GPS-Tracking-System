#include "stdint.h"
#include "tm4c123gh6pm.h"

// function(1) to initialze PortF Leds:
void Led_Init (void)
{
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
