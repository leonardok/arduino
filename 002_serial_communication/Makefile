PRG            = sercial_c
OBJ            = main.o command.o serial.o
MCU_TARGET     = atmega328p
OPTIMIZE       = -Os

DEFS           = -DF_CPU=16000000
LIBS           =

# You should not have to change anything below here.

CC             = avr-gcc

CFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS)
LDFLAGS       = -Wl,-Map,$(PRG).map

OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump

all: $(PRG).elf lst text

$(PRG).elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o $(PRG).elf *.eps *.png *.pdf *.bak
	rm -rf *.lst *.map $(EXTRA_CLEAN_FILES)

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

# Every thing below here is used by avr-libc's build system and can be ignored
# by the casual user.

JPEGFILES               = stdiodemo-setup.jpg

JPEG2PNM                = jpegtopnm
PNM2EPS                 = pnmtops
JPEGRESOLUTION          = 180
EXTRA_CLEAN_FILES       = *.hex *.bin *.srec *.eps

dox: ${JPEGFILES:.jpg=.eps}

%.eps: %.jpg
	$(JPEG2PNM) $< |\
	$(PNM2EPS) -noturn -dpi $(JPEGRESOLUTION) -equalpixels \
	> $@
