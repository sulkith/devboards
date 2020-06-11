#include <atmel_start.h>
#include <SSD1306.h>

SSD1306 oled;

void twi_write(unsigned char a, unsigned char* b, unsigned char c, void (*d)(unsigned char, unsigned char*))
{}

uint8_t twi_wait(){return 0;}
uint8_t twi_init(){return 0;}

void delay(int n)
{
	int i;

	for (;n >0; n--)
	{
		for (i=0;i<100;i++)
			__asm("nop");
	}
}
void display(uint8_t code)
{
	PORT->Group[0].OUTSET.reg = (code<<8)&0xFF00;
	PORT->Group[0].OUTCLR.reg = (~(code)<<8)&0xFF00;

}
int main(void)
{
	atmel_start_init();
	oled.init();
//	PORT->Group[0].DIR.reg = 0xFF00;
	while(1)
	{
		display(0xAA);
		display(0x0F);
		for(uint8_t i = 0;i<20;i++)
		{
			PORT->Group[0].OUTTGL.reg |= 0xFF00;
			delay(500);
		}
		for(uint8_t i = 0;i<100;i++)
		{
			display(i);
			delay(1000);
		}
		for(uint16_t i = 0;i<1000;i++)
		{
			display(255);
			delay(10);
			display(0);
			delay(40);
		}

	}
}
