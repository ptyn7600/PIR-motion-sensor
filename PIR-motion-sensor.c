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

// The senosr pin is PIN Digital 2 on arduino
#define SENSOR_PIN  PD2

/* C Prototypes of functions */
void turnOnLED(uint8_t led);
void my_delay_ms(uint32_t timeDelayed);
uint8_t motionDetect(uint32_t sensor);

int main (void) 
{
    // Set up DBC to catch error
	DBC_SETUP();
    
    // Set Port B5, the LED, to output
	DDRB |= _BV(DDB5);
 
	while(1) 
	{
		// Check if the sesonor detects motion
        if (motionDetect(SENSOR_PIN))
		{
            // Turn on LED
			turnOnLED(1);         
		} else {
            // Turn off the LED
            turnOnLED(0);
        } 
	}
    return 0;
}

/* 
 * motionDetect  this function checks if the sensor detects any motion
 * sensor        uint32_t - pin assigned to the sensor
 * return 0 if the sensor does not detect motion, and 1 if the sensor detects motion
 */
uint8_t motionDetect(uint32_t sensor)
{
     // Checking the pre condition which is sensor pin is non-negative
    PRE_CONDITION_DBC(sensor >=0, 6000);
	uint8_t isMotion = 0;
    // Check if the sensor detects motion
	if ((PIND & (1 << sensor)) != 0)
	{
        // set return value to 1 if the sensor detects motion
		isMotion = 1;
	}
	else
	{
        // set return value to 0 if the sensor does not detect motion
		isMotion = 0;
	}
    // Checking if the return value is valid, which is either 0 or 1
    POST_CONDITION_DBC(isMotion == 1 || isMotion == 0, 5000);
	return isMotion;
}

/* 
 * turnOnLED    a function to turn on specified LED
 * led     uint8_t - 1 if want to turn on the LED. Otherwise, set it to 0
 */
void turnOnLED(uint8_t led)
{
    // Checking the pre condition, which is led, is non-negative
    PRE_CONDITION_DBC(led == 1 || led == 0, 6000);
    
    // Turn on LED if input = 1
	if (led)
            // set port B5 - pin 13 on Arduino - to HIGH
        	PORTB |= _BV(PORTB5);
	else
            // set port B5 - pin 13 on Arduino - to LOW if input = 0
        	PORTB &= ~_BV(PORTB5);
}

/* 
 * Handles larger delays the _delay_ms can't do by itself (not sure how accurate)  
 * Note no DBC as this function is used in the DBC !!! 
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
