SERDEV=/dev/tty.PL2303-00001004
AVRPROG=avrisp2
AVRMMCU=m328p

PROJECT=main
SOURCES=main.c accelerometer.c compass.c gyro.c i2c.c uart.c
MMCU=atmega328p
CC=avr-gcc -D F_CPU=8000000

CFLAGS= -mmcu=$(MMCU) -Wall

default:
	@echo ""
	@echo "make clean......delete object & hex files"
	@echo "make hex........build the $(PROJECT).hex file"
	@echo "make flash......copy $(PROJECT).hex to 9DOF RAZOR flash"
	@echo ""

hex: $(PROJECT).elf
	avr-objcopy -j .text -O ihex $(PROJECT).elf $(PROJECT).hex

$(PROJECT).elf: $(SOURCES)
	$(CC) $(CFLAGS) -I./ -o $(PROJECT).elf $(SOURCES)

flash: $(PROJECT).hex
	avrdude -p $(AVRMMCU) -c $(AVRPROG) -P $(SERDEV) -U flash:w:$(PROJECT).hex

clean:
	rm $(PROJECT).elf $(PROJECT).hex
