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

# all: $(PRG).elf lst text eeprom
all: $(PRG).elf lst eeprom

$(PRG).elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	\rm -rf $(PRG).elf $(PRG).o
	rm -rf *.lst *.map *.hex

install_nano:
	sudo $(AVRDUDE) $(AVRDUDE_BOTH) -b $(BAUD_NANO) -P $(DEV_NANO) -U flash:w:${PRG}.hex

install_uno:
	sudo $(AVRDUDE) -F -V $(AVRDUDE_BOTH) -b $(BAUD_UNO) -P $(DEV_UNO) -U flash:w:${PRG}.hex


lst:  $(PRG).lst

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@


hex:  $(PRG).hex

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@


# Rules for building the .eeprom rom images

eeprom: ehex

ehex:  $(PRG).hex

%_eeprom.hex: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@
