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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "serial.h"
#include "command.h"
#include "global.h"

void COMMAND_help(void)
{
	char *message = malloc(80);
	strcpy(message, "This is the help.\n\0");
	USART_transmit_buffer(message);
	strcpy(message, "\th\t Dsiplay this help.\n\n");

	free(message);
}

void COMMAND_invalid(void)
{
	USART_transmit_buffer("Invalid command. Try \"help\" for more information.\n\n");
}

void COMMAND_flush_cmd_buffer(void)
{
	command.size    = 0;
	command.args[0] = '\0';
	command.cmd_id  = CMD_INVALID;
}

int COMMAND_identify(char *cmd)
{
	if(!strcmp(cmd, "help"))
	{
		command.cmd_id = CMD_HELP;
	}

	return command.cmd_id;;
}

int COMMAND_execute(void)
{
	switch(command.cmd_id)
	{
		case CMD_HELP: COMMAND_help(); break;
		default: COMMAND_invalid(); return FALSE;
	}
	
	return TRUE;
}

