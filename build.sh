#!/bin/bash

nasm -f elf32 desc_tables/gdt.s -o gdt.o
nasm -f elf32 desc_tables/interrupt.s -o interrupt.o
gcc -m32 -std=gnu99 -ffreestanding -O2 -g -c start.s -o start.o  &&
gcc -m32 -std=gnu99 -ffreestanding -O2 -g -c kernel.c -o kernel.o  &&
gcc -m32 -std=gnu99 -ffreestanding -O2 -g -c video/video.c -o video.o  &&
gcc -m32 -std=gnu99 -ffreestanding -O2 -g -c ports/ports.c -o ports.o  &&
gcc -m32 -std=gnu99 -ffreestanding -O2 -g -c desc_tables/descriptor_tables.c -o desc_tables.o  &&
gcc -m32 -std=gnu99 -ffreestanding -O2 -g -c desc_tables/isr.c -o isr.o  &&
gcc -m32 -std=gnu99 -ffreestanding -O2 -g -c libk/string.c -o string.o  &&
gcc -m32 -std=gnu99 -ffreestanding -O2 -g -c input/keyboard/keyboard.c -o keyboard.o  &&
gcc -m32 -std=gnu99 -ffreestanding -O2 -g -c heap/heap.c -o heap.o  &&
gcc -m32 -std=gnu99 -ffreestanding -O2 -g -c heap/heapManager.c -o heapManager.o  &&
ld -melf_i386 -T linker.ld start.o kernel.o video.o ports.o desc_tables.o gdt.o interrupt.o isr.o string.o keyboard.o heap.o heapManager.o -o length_os.elf -melf_i386
