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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "serial.h"
#include "command.h"
#include "global.h"


ISR(USART_RX_vect)
{
	/* for each received char, echo it back */
	USART_transmit_char(USART_receive_char());
}


int SYSTEM_wait_for_command(void)
{
	if (recv_buf.ready == TRUE)
	{
		if (COMMAND_identify(recv_buf.msg) != CMD_INVALID)
		{
			COMMAND_execute();
			COMMAND_flush_cmd_buffer();
		}
		/* If got here is because we received stuff, but it is
		 * not valid */
		else
		{
			COMMAND_execute();
		}

		USART_flush_buffer();
		return TRUE;
	}

	return FALSE;
}

void SYSTEM_init(void)
{
	COMMAND_flush_cmd_buffer();
	USART_init_serial(103);

	sei();
}

int main(int argc, char **argv)
{
	SYSTEM_init();

	USART_transmit_buffer("Welcome to the serial port!\n");
	for(;;) 
	{
		SYSTEM_wait_for_command();
	}

	return 0;
}

