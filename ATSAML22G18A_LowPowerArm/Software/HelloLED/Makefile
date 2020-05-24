
DEVICE      = cortex-m0plus
PROGRAMMER = -c buspirate
OBJECTS    = main.o 
HEADERS    = 
PORT = /dev/ttyUSB0

# Tune the lines below only if you know what you are doing:
#AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE) -P $(PORT)

#COMPILE = arm-none-eabi-gcc -mcpu=$(DEVICE) --specs=nosys.specs 
COMPILE = arm-none-eabi-g++ -mcpu=$(DEVICE) --specs=nosys.specs 

# symbolic targets:
all:	main.hex

clean:
	rm -f main.hex main.elf $(OBJECTS)

.c.o:
	$(COMPILE) -c $< -o $@

.cpp.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(COMPILE) -S $< -o $@

# file targets:
main.elf: $(OBJECTS) $(HEADERS)
	$(COMPILE) -o main.elf $(OBJECTS)
main.hex: main.elf
	rm -f main.hex
	arm-none-eabi-objcopy -j .text -j .data -O ihex main.elf main.hex

