# Options for Arduino NANO
DEV_NANO       = /dev/ttyUSB0
BAUD_NANO       = 115200

# Options for Arduino UNO
DEV_UNO        = /dev/ttyACM0
BAUD_UNO       = 115200

# Commom
AVRDUDE_BOTH   = -p atmega328p -c arduino

PRG            = blinkled
OBJ            = main.o
MCU_TARGET     = atmega328p
OPTIMIZE       = -Os

DEFS           =
LIBS           =

# You should not have to change anything below here.

CC             = avr-gcc
AVRDUDE        = avrdude

CFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS)
LDFLAGS       = -Wl,-Map,$(PRG).map

OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump

all: $(PRG).elf lst text eeprom

$(PRG).elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o $(PRG).elf *.eps *.png *.pdf *.bak
	rm -rf *.lst *.map $(EXTRA_CLEAN_FILES)

install_nano:
	sudo $(AVRDUDE) $(AVRDUDE_BOTH) -b $(BAUD_NANO) -P $(DEV_NANO) -U flash:w:${PRG}.hex

install_uno:
	sudo $(AVRDUDE) -F -V $(AVRDUDE_BOTH) -b $(BAUD_UNO) -P $(DEV_UNO) -U flash:w:${PRG}.hex


lst:  $(PRG).lst

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

# Rules for building the .text rom images

text: hex bin srec

hex:  $(PRG).hex
bin:  $(PRG).bin
srec: $(PRG).srec

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.srec: %.elf
	$(OBJCOPY) -j .text -j .data -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@

# Rules for building the .eeprom rom images

eeprom: ehex ebin esrec

ehex:  $(PRG)_eeprom.hex
ebin:  $(PRG)_eeprom.bin
esrec: $(PRG)_eeprom.srec

%_eeprom.hex: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@

%_eeprom.srec: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O srec $< $@

%_eeprom.bin: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O binary $< $@
