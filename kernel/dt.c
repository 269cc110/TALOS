/*	Copyright (c) 2016 condorcraft110
 *	
 *	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *	
 *	The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *	
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdint.h>
#include <internal/dt.h>
#include <string.h>

struct gdt_entry
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __attribute__((packed));

struct idt_entry
{
	uint16_t base_low;
	uint16_t sel;
	uint8_t null;
	uint8_t flags;
	uint16_t base_high;
} __attribute__((packed));

struct dt_ptr
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

struct gdt_entry gdt[3];
struct dt_ptr gdtp;

struct idt_entry idt[256];
struct dt_ptr idtp;

extern void __gdt_flush();
extern void __idt_load();

void gdt_set_gate(int32_t index, uint64_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
	gdt[index].base_low = base & 0xFFFF;
	gdt[index].base_middle = (base >> 16) & 0xFF;
	gdt[index].base_high = (base >> 24) & 0xFF;
	
	gdt[index].limit_low = limit & 0xFFFF;
	gdt[index].granularity = (limit >> 16) & 0x0F;
	gdt[index].granularity |= granularity & 0xF0;
	
	gdt[index].access = access;
}

void idt_set_gate(uint8_t index, uint32_t base, uint16_t sel, uint8_t flags)
{
	idt[index].base_low = base & 0xFFFF;
	idt[index].base_high = (base >> 16) & 0xFFFF;
	
	idt[index].sel = sel;
	
	idt[index].null = 0;
	
	idt[index].flags = flags;
}

void gdt_init()
{
	gdtp.limit = (sizeof(struct gdt_entry) * 3) - 1;
	gdtp.base = (uint32_t)&gdt;
	// 0x2000000
	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	
	__gdt_flush();
}

void idt_init()
{
	idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
	idtp.base = (uint32_t)&idt;
	
	memset(&idt, 0, sizeof(struct idt_entry) * 256);
	
	__idt_load();
}

