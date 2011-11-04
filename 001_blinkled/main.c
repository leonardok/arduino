#include <avr/io.h>
#include <avr/delay.h>

int main(void)
{
	/* Define PINB5 as output and turn it on */
	DDRB  = 1 << 5;
	for(;;)
	{
		/* turn led on */
		PORTB = 1 << 5;
		_delay_ms(10000);

		/* turn led off */
		PORTB = 0 << 5;
		_delay_ms(10000);
	}
}
