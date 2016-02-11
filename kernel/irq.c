/*	Copyright (c) 2016 condorcraft110
 *	
 *	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *	
 *	The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *	
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <system.h>
#include <internal/dt.h>

extern void __irq0();
extern void __irq1();
extern void __irq2();
extern void __irq3();
extern void __irq4();
extern void __irq5();
extern void __irq6();
extern void __irq7();
extern void __irq8();
extern void __irq9();
extern void __irq10();
extern void __irq11();
extern void __irq12();
extern void __irq13();
extern void __irq14();
extern void __irq15();

void *irq_handlers[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void irq_install_handler(uint32_t irq, void (*handler)(registers_t *))
{
	irq_handlers[irq] = handler;
}

void irq_uninstall_handler(uint32_t irq)
{
	irq_handlers[irq] = 0;
}

void irq_remap()
{
	outportb(0x20, 0x11);
	outportb(0xA0, 0x11);
	outportb(0x21, 0x20);
	outportb(0xA1, 0x28);
	outportb(0x21, 0x04);
	outportb(0xA1, 0x02);
	outportb(0x21, 0x01);
	outportb(0xA1, 0x01);
	outportb(0x21, 0x0);
	outportb(0xA1, 0x0);
}

void irq_init()
{
	irq_remap();
	
	idt_set_gate(32, (uint32_t)__irq0, 0x08, 0x8E);
	idt_set_gate(33, (uint32_t)__irq1, 0x08, 0x8E);
	idt_set_gate(34, (uint32_t)__irq2, 0x08, 0x8E);
	idt_set_gate(35, (uint32_t)__irq3, 0x08, 0x8E);
	idt_set_gate(36, (uint32_t)__irq4, 0x08, 0x8E);
	idt_set_gate(37, (uint32_t)__irq5, 0x08, 0x8E);
	idt_set_gate(38, (uint32_t)__irq6, 0x08, 0x8E);
	idt_set_gate(39, (uint32_t)__irq7, 0x08, 0x8E);
	idt_set_gate(40, (uint32_t)__irq8, 0x08, 0x8E);
	idt_set_gate(41, (uint32_t)__irq9, 0x08, 0x8E);
	idt_set_gate(42, (uint32_t)__irq10, 0x08, 0x8E);
	idt_set_gate(43, (uint32_t)__irq11, 0x08, 0x8E);
	idt_set_gate(44, (uint32_t)__irq12, 0x08, 0x8E);
	idt_set_gate(45, (uint32_t)__irq13, 0x08, 0x8E);
	idt_set_gate(46, (uint32_t)__irq14, 0x08, 0x8E);
	idt_set_gate(47, (uint32_t)__irq15, 0x08, 0x8E);
}

void _irq_handler(registers_t *reg)
{
	void (*handler)(registers_t *reg);
	
	handler = irq_handlers[reg->interrupt - 32];
	if(handler)
	{
		handler(reg);
	}
	
	if(reg->interrupt >= 40)
	{
		outportb(0xA0, 0x20);
	}
	
	outportb(0x20, 0x20);
}

