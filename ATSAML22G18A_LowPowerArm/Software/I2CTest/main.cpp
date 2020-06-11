#include <atmel_start.h>
#include <Framebuffer.h>
#include <std_twi.h>

extern struct io_descriptor *I2C_0_io;
Framebuffer oled;

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
	oled.clear();
	oled.drawString("Hello World!!!",0,0);
	oled.drawString("Hello World!!!",0,8);
	oled.show();
//	PORT->Group[0].DIR.reg = 0xFF00;
//	i2c_m_sync_get_io_descriptor(&I2C_0, &I2C_0_io);
	while(1)
	{
		display(0xAA);
		display(0x0F);
		for(uint8_t i = 0;i<20;i++)
		{
			PORT->Group[0].OUTTGL.reg |= 0xFF00;
			delay_ms(100);
	oled.drawString("Hello World!",0,0);
	oled.show();
		}
		for(uint8_t i = 0;i<100;i++)
		{
			display(i);
			delay_ms(100);
	oled.drawString("Hello World!",0,0);
	oled.show();
		}
		for(uint16_t i = 0;i<1000;i++)
		{
			display(255);
			delay_ms(1);
			display(0);
			delay_ms(4);
	oled.drawString("Hello World!",0,0);
	oled.show();
		}

	}
}
