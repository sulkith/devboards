ASF_PATH = ~/lib/xdk-asf-3.48.0
CPU_FAM = sam0
CPU_TYPE = saml22
CPU_NAME = saml22g18a
MCUTYPE=__SAML22G18A__

LDSCRIPT = xdk_asf/$(CPU_NAME)_flash.ld
BOOTUP = xdk_asf/startup_$(CPU_TYPE).o xdk_asf/system_$(CPU_TYPE).o

OBJS=$(BOOTUP) main.o

# Tools
CC=arm-none-eabi-gcc
CPP=arm-none-eabi-g++
LD=arm-none-eabi-gcc
AR=arm-none-eabi-ar
AS=arm-none-eabi-as

ELF=main.elf
HEX=main.hex

LDFLAGS+= -T$(LDSCRIPT) -mthumb -mcpu=cortex-m0 -Wl,--gc-sections
CFLAGS+= -mcpu=cortex-m0 -mthumb -g
CFLAGS+= -I xdk_asf -I xdk_asf/include -I xdk_asf/cmsis -I .
CFLAGS+= -D$(MCUTYPE)

$(HEX): $(ELF)
	rm -f $(HEX) 
	arm-none-eabi-objcopy -j .text -j .data -j .init -j .fini -j .rodata -j .ARM.exidx -j.eh_frame -O ihex $(ELF) $(HEX)
	arm-none-eabi-size main.elf -A --totals -x

$(ELF):$(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

# compile and generate dependency info
.c.o:
	$(CC) -c $(CFLAGS) $< -o $@
	$(CC) -MM $(CFLAGS) $< > $*.d

.cpp.o:
	$(CPP) -c $(CFLAGS) $< -o $@
	$(CPP) -MM $(CFLAGS) $< > $*.d

.s.o:
	$(AS) $< -o $@

clean:
	rm -f $(OBJS) $(OBJS:.o=.d) $(ELF) $(CLEANOTHER)

debug:  $(ELF)
	arm-none-eabi-gdb -iex "target extended-remote localhost:3333" $(ELF)

upload:  $(ELF)
	arm-none-eabi-gdb --batch -x gdb_upload $(ELF)

# pull in dependencies
-include        $(OBJS:.o=.d)

links:
	mkdir xdk_asf
	ln -s $(ASF_PATH)/thirdparty/CMSIS/Include xdk_asf/cmsis
	ln -s $(ASF_PATH)/$(CPU_FAM)/utils/cmsis/$(CPU_TYPE)/include xdk_asf
	ln -s $(ASF_PATH)/$(CPU_FAM)/utils/cmsis/$(CPU_TYPE)/source/gcc/startup_$(CPU_TYPE).c xdk_asf
	ln -s $(ASF_PATH)/$(CPU_FAM)/utils/cmsis/$(CPU_TYPE)/source/system_$(CPU_TYPE).c xdk_asf
	ln -s $(ASF_PATH)/$(CPU_FAM)/utils/cmsis/$(CPU_TYPE)/source/system_$(CPU_TYPE).h xdk_asf
	ln -s $(ASF_PATH)/$(CPU_FAM)/utils/linker_scripts/$(CPU_TYPE)/gcc/$(CPU_NAME)_flash.ld xdk_asf

openocd:
	openocd &
