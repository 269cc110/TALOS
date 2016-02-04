#!/bin/bash

# Copyright (c) 2016 condorcraft110
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

IFS=$'\n'; for asmsource in $(find . -name '*.s'); do nasm -f elf32 -o ${asmsource::-1}o $asmsource; done

IFS=$'\n'; for csource in $(find . -name '*.c'); do i686-elf-gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -ffreestanding -I ./include -c -o ${csource::-1}o -D__is_talos $csource; done

find . -name '*.o' -exec i686-elf-ld -T linker.ld -o kernel.bin '{}' +

find . -name '*.o' -delete

mkdir -p iso/boot/grub/

cp kernel.bin iso/boot/
cp grub.cfg iso/boot/grub/

grub-mkrescue -o talos.iso iso

rm -r iso

