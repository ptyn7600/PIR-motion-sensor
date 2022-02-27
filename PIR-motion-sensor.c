#include <avr/io.h>
#include <util/delay.h>

#define __DELAY_BACKWARD_COMPATIBLE__

/* This is the Design By Contract macros.*/
#define DBC // Can turn off these macros by commenting out this line
#ifdef DBC
/* needs to be at main since we are going to use Pin13 as our LED to warn us on assert fails */
#define DBC_SETUP() \
	/* turn on Pin 13 as we will use to indicate assertion/error failed */ \
	DDRB |= _BV(DDB5); 

#define PRE_CONDITION_DBC(eval_expression, time_blink_delay) \
	while (!(eval_expression))  \
	{ \
		PORTB |= _BV(PORTB5); \
		my_delay_ms(time_blink_delay); \
		PORTB &= ~_BV(PORTB5); \
		my_delay_ms(time_blink_delay); \
	}

#define POST_CONDITION_DBC(eval_expression, time_blink_delay) \
	while (!(eval_expression))  \
	{ \
		PORTB |= _BV(PORTB5); \
		my_delay_ms(time_blink_delay); \
		PORTB &= ~_BV(PORTB5); \
		/* half the delay off on post condition */ \
		my_delay_ms(time_blink_delay/2); \
	}
#elif
/* These are empty for when turned off */
#define DBC_SETUP() {}
#define PRE_CONDITION(eval_expression, time_blink_delay) {}
#define POST_CONDITION(eval_expression, time_blink_delay) {}
#endif

#define SENSOR_PIN  PD2

/* C Prototypes of functions */
void turnOnLED(uint8_t led);
void my_delay_ms(uint32_t timeDelayed);
uint8_t motionDetect(uint32_t sensor);

int main (void) 
{
    // Set up DBC to catch error
	DBC_SETUP();
    // Set Port B5, Green LED, to output
	DDRB |= _BV(DDB5);
 
	while(1) 
	{
		// Check if the button is pressed
        if (motionDetect(SENSOR_PIN))
		{
            // Turn on red LED back, others are off
			turnOnLED(1);
            // my_delay_ms(500);
            // turnOnLED(0);          
		} else {
            turnOnLED(0);
        }
            
	}
    return 0;
}

/* 
 * isButtonPressed  this function checks if the button is pressed
 * buttonPin        uint32_t - pin assigned to the button
 * return 0 if the button is not pressed, and 1 if the button is pressed
 */
uint8_t motionDetect(uint32_t sensor)
{
     // Checking the pre condition which is buttonPin is non-negative
    // PRE_CONDITION_DBC(buttonPin >=0, 6000);
	uint8_t isMotion = 0;
    // Check if the button is pressed    
	if ((PIND & (1 << sensor)) != 0)
	{
		/* software debounce */
		_delay_ms(15);
        // Chech if the buton is pressed after debounce is checked
		if ((PIND & (1 << sensor)) != 0)
		{
            // set return value to 1 if the button is pressed
			isMotion = 1;
		}
	}
	else
	{
        // set return value to 0 if the button is not pressed
		isMotion = 0;
	}
    // Checking if the return value is valid, which is either 0 or 1
    // POST_CONDITION_DBC(isPressed == 1 || isPressed == 0, 5000);
	return isMotion;
}

/* 
 * turnOnLED    a function to turn on specified LED
 * ledGreen     uint8_t - 1 if want to turn on the green LED. Otherwise, set it to 0
 * ledYellow    uint8_t - 1 if want to turn on the yellow LED. Otherwise, set it to 0
 * ledRed     uint8_t - 1 if want to turn on the red LED. Otherwise, set it to 0

 */
void turnOnLED(uint8_t led)
{
    // Checking the pre condition which is ledGreen, ledYellow, ledRed is non-negative
    PRE_CONDITION_DBC(led == 1 || led == 0, 6000);
    
    // Turn on green LED if input = 1
	if (led)
            // set port D5 to HIGH
        	PORTB |= _BV(PORTB5);
	else
            // set port D5 to LOW if input = 0
        	PORTB &= ~_BV(PORTB5);
}

/* 
 * Handles larger delays the _delay_ms can't do by itself (not sure how accurate)  
 * Note no DBC as this function is used in the DBC !!! 
 *
 * borrowed from : https://www.avrfreaks.net/forum/delayms-problem 
 * */
void my_delay_ms(uint32_t timeDelayed) 
{
	unsigned int i;

	for (i=0; i<(timeDelayed/10); i++) 
	{
		_delay_ms(10);
	}
	for (i=0; i < (timeDelayed % 10); i++) 
	{
		_delay_ms(1);
	}
}
