CC=avr-gcc
CFLAGS=-Wall -O3 -DF_CPU=$(F_CPU) -mmcu=$(MCU)
MCU=atmega328p
F_CPU=16000000L

OBJCOPY=avr-objcopy
BIN_FORMAT=ihex

PORT=/dev/ttyUSB0
BAUD=57600
PROTOCOL=arduino
#PART=$(MCU)
PART=m328p
#AVRDUDE=avrdude -F -V
AVRDUDE=avrdude
AVRSIZE=avr-size -A

RM=rm -f

.PHONY: all
all: size

serprog.hex: serprog.elf

serprog.elf: serprog.s

serprog.s: serprog.c

.PHONY: clean
clean:
	$(RM) serprog.elf serprog.hex serprog.s

.PHONY: upload
upload: serprog.hex
	$(AVRDUDE) -c $(PROTOCOL) -p $(PART) -P $(PORT) -b $(BAUD) -U flash:w:$<

.PHONY: size
size: serprog.elf
	$(AVRSIZE) $<

%.elf: %.s ; $(CC) $(CFLAGS) -s -o $@ $<

%.s: %.c ; $(CC) $(CFLAGS) -S -o $@ $<

%.hex: %.elf ; $(OBJCOPY) -O $(BIN_FORMAT) -R .eeprom $< $@
