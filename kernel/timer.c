/*	Copyright (c) 2016 condorcraft110
 *	
 *	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *	
 *	The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *	
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <internal/timer.h>
#include <internal/dt.h>
#include <drv/vga.h>
#include <system.h>
#include <stdint.h>

volatile uint32_t timer_ticks;

void timer_phase(uint32_t hz)
{
	uint32_t divisor = 1193180 / hz;
	outportb(0x43, 0x36);
	outportb(0x40, divisor & 0xFF);
	outportb(0x40, divisor >> 8);
}

void timer_handler(registers_t *reg)
{
	timer_ticks++;
}

void timer_init()
{
	irq_install_handler(0, &timer_handler);
}

void timer_wait(uint32_t ticks)
{
	uint32_t eticks = timer_ticks + ticks;
	
	while(timer_ticks < eticks) asm volatile("sti//hlt//cli");
}

