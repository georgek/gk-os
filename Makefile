# gk-os

SRCS := $(wildcard *.c) $(wildcard */*.c)
ASM := start.s raspi/wait_cycles.s
OBJS := $(SRCS:.c=.o) $(ASM:.s=.o)
CFLAGS := -Wall -O0 -ffreestanding -nostdinc -nostdlib -nostartfiles
VPATH := raspi

all: clean kernel8.img

%.o: %.s
	aarch64-elf-gcc $(CFLAGS) -c $< -o $@

%.o: %.c
	aarch64-elf-gcc $(CFLAGS) -c $< -o $@

kernel8.elf: $(OBJS) link.ld
	aarch64-elf-ld -nostdlib -nostartfiles $(OBJS) -T link.ld -o $@

kernel8.img: kernel8.elf
	aarch64-elf-objcopy -O binary $< $@

clean:
	rm -f kernel8.img kernel8.elf $(OBJS) start.o
