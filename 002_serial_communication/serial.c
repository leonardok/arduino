/*
 * Copyright (c) 2011, Leonardo Korndorfer
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
**/

#include <avr/io.h>

#include "serial.h"
#include "global.h"

void USART_flush_buffer(void)
{
	recv_buf.ready = FALSE;
	recv_buf.size  = 0;
}

void USART_init_serial( unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;

	/* Enable receiver and transmitter, and the interrupt for RX */
	UCSR0B = _BV(TXEN0)|_BV(RXEN0)|_BV(RXCIE0);

	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);

	/* setup buffers */
	*recv_buf.msg  = 0;
	recv_buf.size  = 0;
	recv_buf.ready = FALSE;
}


void USART_transmit_char(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while (!( UCSR0A & (1<<UDRE0))) ;

	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char USART_receive_char( void )
{
	/* Wait for data to be received */
	while (!(UCSR0A & (1<<RXC0)));

	/* Get and return received data from buffer */
	
	char char_readed = UDR0;
	if (char_readed != '\n')
	{
		recv_buf.msg[recv_buf.size++] = char_readed;
	}
	else
	{
		recv_buf.msg[recv_buf.size++] = '\0';
		recv_buf.ready = TRUE;
	}

	return char_readed;
}

void USART_transmit_buffer(char *data)
{
	int i;
	for (i = 0; data[i] != '\0'; i++)
		USART_transmit_char(data[i]);
}
