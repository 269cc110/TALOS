/*	Copyright (c) 2016 condorcraft110
 *	
 *	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *	
 *	The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *	
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <internal/shell.h>
#include <drv/vga.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char text_buffer[VGA_LENGTH + 1];

void shell_init()
{
	text_buffer[VGA_LENGTH] = '\0';
}

void shell_putchar_internal(char c)
{
	size_t current_length = strlen(text_buffer);
	
	if(c == '\b')
	{
		text_buffer[current_length - 1] = '\0';
	}
	else if(strlen(text_buffer) < 2000)
	{
		text_buffer[current_length] = c;
		text_buffer[current_length + 1] = '\0';
	}
}

void shell_putchar(char c)
{
	shell_putchar_internal(c);
	vga_flush(text_buffer);
}

void shell_putstring_internal(const char *str)
{
	size_t len = strlen(str);
	
	for(size_t i = 0; i < len; i++)
	{
		shell_putchar_internal(str[i]);
	}
}

void shell_putstring(const char *str)
{
	shell_putstring_internal(str);
	vga_flush(text_buffer);
}

