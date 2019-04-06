# gk-os

SRCS = $(wildcard *.c) $(wildcard */*.c)
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -O0 -ffreestanding -nostdinc -nostdlib -nostartfiles
VPATH = raspi

all: clean kernel8.img

start.o: start.s
	aarch64-elf-gcc $(CFLAGS) -c $< -o $@

%.o: %.c
	aarch64-elf-gcc $(CFLAGS) -c $< -o $@

kernel8.img: start.o $(OBJS)
	aarch64-elf-ld -nostdlib -nostartfiles start.o $(OBJS) -T link.ld -o kernel8.elf
	aarch64-elf-objcopy -O binary kernel8.elf $@

clean:
	rm -f kernel8.img kernel8.elf $(OBJS)
