# BadUSB firmware build for Linux
# Using sdcc and makebin
# based on build.bat
# Sep 9, 2016
# daveti

CC=sdcc-sdcc
LINK=sdcc-sdcc
MAKEBIN=sdcc-makebin
CFLAGS=--model-small -mmcs51 -pdefcpu
LINKFLAGS=--xram-loc 0x6000
MAKEBINFLAGS=-p

SRCS=main.c timers.c usb.c control.c scsi.c
RELS=$(SRCS:.c=.rel)
ASSS=$(SRCS:.c=.s)

all: firmware.bin

firmware.bin: firmware.hex
	$(MAKEBIN) $(MAKEBINFLAGS) $< $@

firmware.hex: $(RELS)
	$(LINK) $(LINKFLAGS) $(RELS) -o $@

firmware.s: $(ASSS)

%.rel: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.s: %.c
	$(CC) $(CFLAGS) -S $< -o $@

clean:
	rm -rf firmware.* $(RELS) $(ASSS) *.asm *.rst *.lst *.sym
