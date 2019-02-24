

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
//*****************************************************************************
//   preprocessor definition for leds
//*****************************************************************************

#define RED_LED   GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3
void Butt(void);
void Butt2(void);



//*****************************************************************************
// This guy has your back if anything goes wrong
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

volatile char r=' ';

int main(void) {
    int i=0;
    int lim=0;
    //clock configuration
 	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
 	//Peripheral configuration  for UART
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 9600,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    // Pin F4 setup
       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);        // Enable port F
       GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);  // Init PF4 as input
       GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4,
       GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);  // Enable weak pullup resistor for PF4
       // Pin D0 setup
       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);        // Enable port D
       GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_0);  // Init PD0 as input
       GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_0,
       GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);  // Enable weak pullup resistor for PD0
      //Moar ledes
       GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,RED_LED|BLUE_LED|GREEN_LED);
       // Interrupt setup PF4
       GPIOIntDisable(GPIO_PORTF_BASE, GPIO_PIN_4);        // Disable interrupt for PF4 (in case it was enabled)
       GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);      // Clear pending interrupts for PF4
       GPIOIntRegister(GPIO_PORTF_BASE, Butt);     // Register our handler function for port F
       GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4,
       GPIO_FALLING_EDGE);             // Configure PF4 for falling edge trigger
       GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4);     // Enable interrupt for PF4
       // Interrupt setup PD0
       GPIOIntDisable(GPIO_PORTD_BASE, GPIO_PIN_0);        // Disable interrupt for PD0 (in case it was enabled)
       GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_0);      // Clear pending interrupts for PD0
       GPIOIntRegister(GPIO_PORTD_BASE, Butt2);     // Register our handler function for port D
       GPIOIntTypeSet(GPIO_PORTD_BASE, GPIO_PIN_0,
       GPIO_FALLING_EDGE);             // Configure PD0 for falling edge trigger
       GPIOIntEnable(GPIO_PORTD_BASE, GPIO_PIN_0);     // Enable interrupt for PD0


    UARTCharPut(UART0_BASE, 'C');
    UARTCharPut(UART0_BASE, 'o');
    UARTCharPut(UART0_BASE, 'n');
    UARTCharPut(UART0_BASE, 'n');
    UARTCharPut(UART0_BASE, 'e');
    UARTCharPut(UART0_BASE, 'c');
    UARTCharPut(UART0_BASE, 't');
    UARTCharPut(UART0_BASE, 'e');
    UARTCharPut(UART0_BASE, 'd');

//infinite loop
    while (1)
    {
    	//check if we have a soda order
    	if (UARTCharsAvail(UART0_BASE)){
    		r=UARTCharGet(UART0_BASE);
    		//give change back
    	if(r=='C'){
    		r=UARTCharGet(UART0_BASE);
    		 lim= r - '0';
    		 for(i=0;i<lim;i++){
    			 GPIOPinWrite(GPIO_PORTF_BASE, RED_LED, RED_LED);
    			 SysCtlDelay(4000000);
    			 GPIOPinWrite(GPIO_PORTF_BASE, RED_LED, 0);
    			 SysCtlDelay(4000000);

    		 }

    	}
    	// dispatch soda
    	else if(r=='R'){
    		r=UARTCharGet(UART0_BASE);
		       lim= r - '0';
    						switch(lim){
    						case 0:
    							GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|GREEN_LED, RED_LED|GREEN_LED);
    							    		    			 SysCtlDelay(4000000);
    							    		    			 GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|GREEN_LED, 0);
    							    		    			 SysCtlDelay(4000000);
    							break;
    						case 1:
    							GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED, RED_LED|BLUE_LED);
    							    		    			 SysCtlDelay(4000000);
    							    		    			 GPIOPinWrite(GPIO_PORTF_BASE,RED_LED|BLUE_LED, 0);
    							    		    			 SysCtlDelay(4000000);
    							break;
    						case 2:
    							GPIOPinWrite(GPIO_PORTF_BASE, BLUE_LED, BLUE_LED);
    							SysCtlDelay(4000000);
    							GPIOPinWrite(GPIO_PORTF_BASE, BLUE_LED, 0);
    							SysCtlDelay(4000000);


    							break;
    						}

    					r=UARTCharGet(UART0_BASE);
    		    		 lim= r - '0';
    		    		 for(i=0;i<lim;i++){
    		    			 GPIOPinWrite(GPIO_PORTF_BASE, RED_LED, RED_LED);
    		    			 SysCtlDelay(4000000);
    		    			 GPIOPinWrite(GPIO_PORTF_BASE, RED_LED, 0);
    		    			 SysCtlDelay(4000000);

    		    		 }
    	}

    	}


    }

}
//Interruptions


void Timer0IntHandler(void)
{

}
//sensor for $1
void Butt(void)
{

	if (GPIOIntStatus(GPIO_PORTF_BASE, false) & GPIO_PIN_4) {
	UARTCharPut(UART0_BASE,'1');
	}

	GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
}
//sensor for $2
void Butt2(void)
{

	if (GPIOIntStatus(GPIO_PORTD_BASE, false) & GPIO_PIN_0) {
	UARTCharPut(UART0_BASE,'2');
	}

	GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_0);
}
