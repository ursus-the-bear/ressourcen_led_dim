	#include <msp430.h>

#define TRUE 1==1

#define LEDS_OUT P1OUT
#define LEDS_DIR P1DIR
#define LED_RED (0x01 << 0)

#define MIN_SCALE 0
#define MAX_SCALE 500

#define GETTING_BRIGHTER 0
#define GETTING_DIMMER 1

int main(void) {

	// preamble

	// stop watchdog time
    WDTCTL = WDTPW | WDTHOLD;

    // set initial settings
    LEDS_OUT &= ~LED_RED; 	// initially off
    LEDS_DIR |= LED_RED; 	// switch to output direction

    // variables
	int curr_pos = 0;
	int status = GETTING_BRIGHTER;


    while (1) {
    	// counter
    	volatile int i = 0;

    	// first switch on for the amount of time
        LEDS_OUT 	= LED_RED;
    	for (i = MIN_SCALE; i <= curr_pos; i++)
    		;

    	// now switch off for the rest
    	LEDS_OUT ^= LED_RED;
    	for (i = curr_pos; i <= MAX_SCALE; i ++)
    		;

    	// now move your position
    	if (GETTING_BRIGHTER == status)
    		curr_pos++;
    	else
    		curr_pos--;

    	// change directions if needed
    	if (MAX_SCALE == curr_pos)
    		status = GETTING_DIMMER;
    	if (MIN_SCALE == curr_pos)
    		status = GETTING_BRIGHTER;
    } // while

    // NB: we can never get here
    return TRUE;
}
