mkdir atstart
unzip *.atzip -d atstart/
mkdir atresources
cp atstart/gcc/Makefile atresources/Makefile_suggestion
cp atstart/atmel_start_config.atstart atresources
sed -i "s/hpl\//atstart\/hpl\//" atresources/Makefile_suggestion
sed -i "s/hal\//atstart\/hal\//" atresources/Makefile_suggestion
sed -i "s/gcc\//atstart\/gcc\//" atresources/Makefile_suggestion
sed -i "s/CMSIS\//atstart\/CMSIS\//" atresources/Makefile_suggestion
sed -i "s/gcc /atstart\/gcc /" atresources/Makefile_suggestion
sed -i "s/examples/atstart\/examples/" atresources/Makefile_suggestion
sed -i "s/atmel_start.o/atstart\/atmel_start.o/" atresources/Makefile_suggestion
sed -i "s/atmel_start.d/atstart\/atmel_start.d/" atresources/Makefile_suggestion
sed -i "s/driver_init.o/atstart\/driver_init.o/" atresources/Makefile_suggestion
sed -i "s/driver_init.d/atstart\/driver_init.d/" atresources/Makefile_suggestion
sed -i "s/\.\.\/config/atstart\/config/" atresources/Makefile_suggestion
sed -i "s/\.\.\/include/atstart\/include/" atresources/Makefile_suggestion
sed -i "s/\.\.\/hri/atstart\/hri/" atresources/Makefile_suggestion
sed -i "s/\.\.\/atstart/atstart/" atresources/Makefile_suggestion
sed -i "s/DIR_INCLUDES +=/DIR_INCLUDES += -I atstart /" atresources/Makefile_suggestion
sed -i "s/AtmelStart/main/" atresources/Makefile_suggestion

if [ ! -f Makefile ]; then
    cp atresources/Makefile_suggestion Makefile
fi
if [ ! -f main.c ]; then
    cp atstart/main.c main.c
fi
