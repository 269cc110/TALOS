; Copyright (c) 2016 condorcraft110
; 
; Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
; 
; The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
; 
; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

%macro ISR_NEC 1
global __isr%1
__isr%1:
	push byte 0
	push byte %1
	jmp isr_common_stub
%endmacro

%macro ISR_EC 1
global __isr%1
__isr%1:
	push byte 0
	jmp isr_common_stub
%endmacro

ISR_NEC 0
ISR_NEC 1
ISR_NEC 2
ISR_NEC 3
ISR_NEC 4
ISR_NEC 5
ISR_NEC 6
ISR_NEC 7
ISR_EC 8
ISR_NEC 9
ISR_EC 10
ISR_EC 11
ISR_EC 12
ISR_EC 13
ISR_EC 14
ISR_NEC 15
ISR_NEC 16
ISR_NEC 17
ISR_NEC 18
ISR_NEC 19
ISR_NEC 20
ISR_NEC 21
ISR_NEC 22
ISR_NEC 23
ISR_NEC 24
ISR_NEC 25
ISR_NEC 26
ISR_NEC 27
ISR_NEC 28
ISR_NEC 29
ISR_NEC 30
ISR_NEC 31

extern _fault_handler

isr_common_stub:
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, esp
	push eax
	mov eax, _fault_handler
	call eax
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret

