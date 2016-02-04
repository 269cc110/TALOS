/*	Copyright (c) 2016 condorcraft110
 *	
 *	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *	
 *	The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *	
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <drv/vga.h>
#include <internal/kernel.h>
#include <internal/dt.h>
#include <internal/timer.h>

void kernel_init()
{
	gdt_init();
	idt_init();
	isr_init();
	irq_init();
	asm volatile("sti");
	timer_init();
	timer_phase(100);
	vga_init();
	vga_putstring("TALOS 0.1 loaded\n");
	//timer_wait(500);
	//asm volatile("int $0x3");
	while(1); // idle
}

void kfatal(const char *str)
{
	vga_set_colour(VGA_LIGHT_GREY, VGA_BLUE);
	vga_clear();
	vga_putstring("FATAL ERROR\n");
	vga_putstring(str);
	vga_putstring(" EXCEPTION\nSYSTEM HALTED\n");
	asm volatile("cli//hlt");
}

/*void kfatal_dumpreg(const char *str, registers_t *reg)
{
	vga_set_colour(VGA_MAGENTA, VGA_LIGHT_MAGENTA);
	vga_clear();
	vga_putstring("FATAL ERROR\n");
	vga_putstring(str);
	vga_putstring(" EXCEPTION\nSYSTEM HALTED\n\nINTERRUPT DETAILS:\n\t");
	asm volatile("hlt");
}*/

