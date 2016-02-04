/*	Copyright (c) 2016 condorcraft110
 *	
 *	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *	
 *	The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *	
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <internal/dt.h>
#include <internal/kernel.h>
#include <stdint.h>

extern void __isr0();
extern void __isr1();
extern void __isr2();
extern void __isr3();
extern void __isr4();
extern void __isr5();
extern void __isr6();
extern void __isr7();
extern void __isr8();
extern void __isr9();
extern void __isr10();
extern void __isr11();
extern void __isr12();
extern void __isr13();
extern void __isr14();
extern void __isr15();
extern void __isr16();
extern void __isr17();
extern void __isr18();
extern void __isr19();
extern void __isr20();
extern void __isr21();
extern void __isr22();
extern void __isr23();
extern void __isr24();
extern void __isr25();
extern void __isr26();
extern void __isr27();
extern void __isr28();
extern void __isr29();
extern void __isr30();
extern void __isr31();

char *exception_messages[] =
{
	"Division by Zero",
	"Debug",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Into Detected Overflow",
	"Out of Bounds",
	"Invalid Opcode",
	"No Coprocessor",
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",
	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};

char *uc_exception_messages[] =
{
	"DIVISION BY ZERO",
	"DEBUG",
	"NON MASKABE INTERRUPT",
	"BREAKPOINT",
	"INTO DETECTED OVERFLOW",
	"OUT OF BOUNDS",
	"INVALID OPCODE",
	"NO COPROCESSOR",
	"DOUBLE FAULT",
	"COPROCESSOR SEGMENT OVERRUN",
	"BAD TSS",
	"SEGMENT NOT PRESENT",
	"STACK FAULT",
	"GENERAL PROTECTION FAULT",
	"PAGE FAULT",
	"UNKNOWN INTERRUPT",
	"COPROCESSOR FAULT",
	"ALIGNMENT CHECK",
	"MACHINE CHECK",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED"
};

void isr_init()
{
	idt_set_gate(0, (uint32_t)__isr0, 0x08, 0x8E);
	idt_set_gate(1, (uint32_t)__isr1, 0x08, 0x8E);
	idt_set_gate(2, (uint32_t)__isr2, 0x08, 0x8E);
	idt_set_gate(3, (uint32_t)__isr3, 0x08, 0x8E);
	idt_set_gate(4, (uint32_t)__isr4, 0x08, 0x8E);
	idt_set_gate(5, (uint32_t)__isr5, 0x08, 0x8E);
	idt_set_gate(6, (uint32_t)__isr6, 0x08, 0x8E);
	idt_set_gate(7, (uint32_t)__isr7, 0x08, 0x8E);
	idt_set_gate(8, (uint32_t)__isr8, 0x08, 0x8E);
	idt_set_gate(9, (uint32_t)__isr9, 0x08, 0x8E);
	idt_set_gate(10, (uint32_t)__isr10, 0x08, 0x8E);
	idt_set_gate(11, (uint32_t)__isr11, 0x08, 0x8E);
	idt_set_gate(12, (uint32_t)__isr12, 0x08, 0x8E);
	idt_set_gate(13, (uint32_t)__isr13, 0x08, 0x8E);
	idt_set_gate(14, (uint32_t)__isr14, 0x08, 0x8E);
	idt_set_gate(15, (uint32_t)__isr15, 0x08, 0x8E);
	idt_set_gate(16, (uint32_t)__isr16, 0x08, 0x8E);
	idt_set_gate(17, (uint32_t)__isr17, 0x08, 0x8E);
	idt_set_gate(18, (uint32_t)__isr18, 0x08, 0x8E);
	idt_set_gate(19, (uint32_t)__isr19, 0x08, 0x8E);
	idt_set_gate(20, (uint32_t)__isr20, 0x08, 0x8E);
	idt_set_gate(21, (uint32_t)__isr21, 0x08, 0x8E);
	idt_set_gate(22, (uint32_t)__isr22, 0x08, 0x8E);
	idt_set_gate(23, (uint32_t)__isr23, 0x08, 0x8E);
	idt_set_gate(24, (uint32_t)__isr24, 0x08, 0x8E);
	idt_set_gate(25, (uint32_t)__isr25, 0x08, 0x8E);
	idt_set_gate(26, (uint32_t)__isr26, 0x08, 0x8E);
	idt_set_gate(27, (uint32_t)__isr27, 0x08, 0x8E);
	idt_set_gate(28, (uint32_t)__isr28, 0x08, 0x8E);
	idt_set_gate(29, (uint32_t)__isr29, 0x08, 0x8E);
	idt_set_gate(30, (uint32_t)__isr30, 0x08, 0x8E);
	idt_set_gate(31, (uint32_t)__isr31, 0x08, 0x8E);
}

void _fault_handler(registers_t *reg)
{
	if(reg->interrupt < 32)
	{
		kfatal(uc_exception_messages[reg->interrupt]);
	}
}

