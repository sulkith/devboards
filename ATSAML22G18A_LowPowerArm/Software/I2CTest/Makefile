
#atstart/hal/utils/src/utils_syscalls.o \

# List the object files
OBJS +=  \
atstart/hal/src/hal_io.o \
atstart/hpl/systick/hpl_systick.o \
atstart/hal/src/hal_calendar.o \
atstart/hal/src/hal_spi_m_sync.o \
atstart/hal/src/hal_timer.o \
atstart/hal/src/hal_i2c_m_sync.o \
atstart/hal/src/hal_delay.o \
atstart/hpl/oscctrl/hpl_oscctrl.o \
atstart/hpl/core/hpl_init.o \
atstart/hal/utils/src/utils_list.o \
atstart/hpl/core/hpl_core_m0plus_base.o \
atstart/hal/utils/src/utils_assert.o \
atstart/hpl/dmac/hpl_dmac.o \
atstart/hpl/pm/hpl_pm.o \
atstart/hpl/mclk/hpl_mclk.o \
atstart/hpl/gclk/hpl_gclk.o \
atstart/hal/src/hal_init.o \
main.o \
i2cadap.o \
atstart/hpl/osc32kctrl/hpl_osc32kctrl.o \
atstart/hpl/rtc/hpl_rtc.o \
atstart/examples/driver_examples.o \
atstart/driver_init.o \
atstart/hal/src/hal_adc_sync.o \
atstart/hpl/sercom/hpl_sercom.o \
atstart/gcc/system_saml22.o \
atstart/hal/src/hal_gpio.o \
atstart/hal/utils/src/utils_event.o \
atstart/hal/src/hal_sleep.o \
atstart/atmel_start.o \
atstart/hpl/tc/hpl_tc.o \
atstart/hal/src/hal_atomic.o \
atstart/gcc/gcc/startup_saml22.o \
atstart/hpl/adc/hpl_adc.o \
lib/SSD1306-AVR/Framebuffer.o \
lib/SSD1306-AVR/SSD1306.o \

OBJS_AS_ARGS = $(OBJS)

# List the directories containing header files
DIR_INCLUDES += -I atstart   \
-I"../" \
-I"atstart/config" \
-I"atstart/examples" \
-I"atstart/hal/include" \
-I"atstart/hal/utils/include" \
-I"atstart/hpl/adc" \
-I"atstart/hpl/core" \
-I"atstart/hpl/dmac" \
-I"atstart/hpl/gclk" \
-I"atstart/hpl/i2c" \
-I"atstart/hpl/mclk" \
-I"atstart/hpl/osc32kctrl" \
-I"atstart/hpl/oscctrl" \
-I"atstart/hpl/pm" \
-I"atstart/hpl/port" \
-I"atstart/hpl/rtc" \
-I"atstart/hpl/sercom" \
-I"atstart/hpl/tc" \
-I"atstart/hri" \
-I"atstart/include" \
-I"lib/SSD1306-AVR/" \
-I"atstart/CMSIS/Core/Include" \
-I"atstart/include"

# List the dependency files
DEPS := $(OBJS:%.o=%.d)

DEPS_AS_ARGS = $(DEPS)

OUTPUT_FILE_NAME :=main
QUOTE := "
OUTPUT_FILE_PATH +=$(OUTPUT_FILE_NAME).elf
OUTPUT_FILE_PATH_AS_ARGS +=$(OUTPUT_FILE_NAME).elf
ELF = $(OUTPUT_FILE_PATH)

# All Target
all: $(SUB_DIRS) $(OUTPUT_FILE_PATH)

# Linker target

#-T"atstart/gcc/gcc/saml22g18a_flash.ld" \

$(OUTPUT_FILE_PATH): $(OBJS)
	@echo Building target: $@
	@echo Invoking: ARM/GNU Linker
	$(QUOTE)arm-none-eabi-g++$(QUOTE) -o $(OUTPUT_FILE_NAME).elf $(OBJS_AS_ARGS) -Wl,--start-group -lm -Wl,--end-group -mthumb \
-Wl,-Map="$(OUTPUT_FILE_NAME).map" --specs=rdimon.specs -lrdimon -Wl,--gc-sections -mcpu=cortex-m0plus \
 \
-T"project.ld" \
-L"atstart/gcc/gcc"
	@echo Finished building target: $@

	"arm-none-eabi-objcopy" -O binary "$(OUTPUT_FILE_NAME).elf" "$(OUTPUT_FILE_NAME).bin"
	"arm-none-eabi-objcopy" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  \
        "$(OUTPUT_FILE_NAME).elf" "$(OUTPUT_FILE_NAME).hex"
	"arm-none-eabi-objcopy" -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma \
        .eeprom=0 --no-change-warnings -O binary "$(OUTPUT_FILE_NAME).elf" \
        "$(OUTPUT_FILE_NAME).eep" || exit 0
	"arm-none-eabi-objdump" -h -S "$(OUTPUT_FILE_NAME).elf" > "$(OUTPUT_FILE_NAME).lss"
	"arm-none-eabi-size" "$(OUTPUT_FILE_NAME).elf"

	

# Compiler targets


%.o: %.cpp
	@echo Building file: $<
	@echo ARM/GNU C Compiler
	$(QUOTE)arm-none-eabi-g++$(QUOTE) -mthumb -DDEBUG -Os -ffunction-sections -mlong-calls -g3 -Wall -c \
-D__SAML22G18A__ -mcpu=cortex-m0plus  \
$(DIR_INCLUDES) \
-MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -o "$@" "$<"
	@echo Finished building: $<

%.o: %.c
	@echo Building file: $<
	@echo ARM/GNU C Compiler
	$(QUOTE)arm-none-eabi-gcc$(QUOTE) -x c -mthumb -DDEBUG -Os -ffunction-sections -mlong-calls -g3 -Wall -c -std=gnu99 \
-D__SAML22G18A__ -mcpu=cortex-m0plus  \
$(DIR_INCLUDES) \
-MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -o "$@" "$<"
	@echo Finished building: $<

%.o: %.s
	@echo Building file: $<
	@echo ARM/GNU Assembler
	$(QUOTE)arm-none-eabi-as$(QUOTE) -x c -mthumb -DDEBUG -Os -ffunction-sections -mlong-calls -g3 -Wall -c -std=gnu99 \
-D__SAML22G18A__ -mcpu=cortex-m0plus  \
$(DIR_INCLUDES) \
-MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -o "$@" "$<"
	@echo Finished building: $<

%.o: %.S
	@echo Building file: $<
	@echo ARM/GNU Preprocessing Assembler
	$(QUOTE)arm-none-eabi-gcc$(QUOTE) -x c -mthumb -DDEBUG -Os -ffunction-sections -mlong-calls -g3 -Wall -c -std=gnu99 \
-D__SAML22G18A__ -mcpu=cortex-m0plus  \
$(DIR_INCLUDES) \
-MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -o "$@" "$<"
	@echo Finished building: $<

# Detect changes in the dependent files and recompile the respective object files.
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(DEPS)),)
-include $(DEPS)
endif
endif

clean:
	rm -f $(OBJS_AS_ARGS)
	rm -f $(OUTPUT_FILE_PATH)
	rm -f $(DEPS_AS_ARGS)
	rm -f $(OUTPUT_FILE_NAME).a $(OUTPUT_FILE_NAME).hex $(OUTPUT_FILE_NAME).bin \
        $(OUTPUT_FILE_NAME).lss $(OUTPUT_FILE_NAME).eep $(OUTPUT_FILE_NAME).map \
        $(OUTPUT_FILE_NAME).srec

debug:  $(ELF)
	arm-none-eabi-gdb -iex "target extended-remote localhost:3333" $(ELF)

upload:  $(ELF)
	arm-none-eabi-gdb --batch -x gdb_upload $(ELF)

openocd:
	openocd &
