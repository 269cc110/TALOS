/*	Copyright (c) 2016 condorcraft110
 *	
 *	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *	
 *	The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *	
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <system.h>
//#include <drv/vga.h>
#include <internal/shell.h>
#include <internal/dt.h>

uint8_t kmap_us[128] = {0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0 /*ctrl*/, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0 /*left shift*/, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0 /*right shift*/, '*', 0 /*left alt*/, ' ', 0 /*caps lock*/, 0 /*f1*/, 0 /*f2*/, 0 /*f3*/, 0 /*f4*/, 0 /*f5*/, 0 /*f6*/, 0 /*f7*/, 0 /*f8*/, 0 /*f9*/, 0 /*f10*/, 0 /*num lock*/, 0 /*scroll lock*/, 0 /*home*/, 0 /*up arrow*/, 0 /*page up*/, '-', 0 /*left arrow*/, 0, 0 /*right arrow*/, '+', 0 /*end key*/, 0 /*down arrow*/, 0 /*page down*/, 0 /*insert*/, 0 /*delete*/, 0, 0, 0, 0 /*f11*/, 0 /*f12*/, 0};

uint8_t kmap_uk[128] = {0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0 /*ctrl*/, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0 /*left shift*/, '#', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0 /*right shift*/, '*', 0 /*left alt*/, ' ', 0 /*caps lock*/, 0 /*f1*/, 0 /*f2*/, 0 /*f3*/, 0 /*f4*/, 0 /*f5*/, 0 /*f6*/, 0 /*f7*/, 0 /*f8*/, 0 /*f9*/, 0 /*f10*/, 0 /*num lock*/, 0 /*scroll lock*/, 0 /*home*/, 0 /*up arrow*/, 0 /*page up*/, '-', 0 /*left arrow*/, 0, 0 /*right arrow*/, '+', 0 /*end key*/, 0 /*down arrow*/, 0 /*page down*/, 0 /*insert*/, 0 /*delete*/, 0, 0, 0, 0 /*f11*/, 0 /*f12*/, 0};

uint8_t kmap_uk_shift[128] = {0, 27, '!', '"', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 0 /*ctrl*/, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '@', '|', 0 /*left shift*/, '~', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '|', 0 /*right shift*/, '*', 0 /*left alt*/, ' ', 0 /*caps lock*/, 0 /*f1*/, 0 /*f2*/, 0 /*f3*/, 0 /*f4*/, 0 /*f5*/, 0 /*f6*/, 0 /*f7*/, 0 /*f8*/, 0 /*f9*/, 0 /*f10*/, 0 /*num lock*/, 0 /*scroll lock*/, 0 /*home*/, 0 /*up arrow*/, 0 /*page up*/, '-', 0 /*left arrow*/, 0, 0 /*right arrow*/, '+', 0 /*end key*/, 0 /*down arrow*/, 0 /*page down*/, 0 /*insert*/, 0 /*delete*/, 0, 0, 0, 0 /*f11*/, 0 /*f12*/, 0};

uint8_t lshifted = 0;
uint8_t rshifted = 0;

void _kb_handler(registers_t *regs)
{
	uint8_t scancode = inportb(0x60);
	
	if(scancode & 0x80)
	{
		uint8_t nscancode = scancode & ~0x80;
		
		if(nscancode == 42)
		{
			lshifted = 0;
		}
		else if(nscancode == 54)
		{
			rshifted = 0;
		}
	}
	else
	{
		if(scancode == 42)
		{
			lshifted = 1;
		}
		else if(scancode == 54)
		{
			rshifted = 1;
		}
		else
		{
			shell_putchar((lshifted || rshifted ? kmap_uk_shift : kmap_uk)[scancode]);
		}
	}
}

void kb_init()
{
	irq_install_handler(1, &_kb_handler);
}

