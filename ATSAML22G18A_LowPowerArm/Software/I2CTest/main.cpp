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
void callbackI2C(uint8_t len, uint8_t *data)
{

}
void read_AM2315()
{
	twi_read(0x5C,20,&callbackI2C);

}
int main(void)
{
	atmel_start_init();
	char helloWorld0[] = "Hello World0!";
	helloWorld0[11] = 0x32;
	oled.init();
	oled.clear();
	oled.drawString(helloWorld0,0,0);
	oled.drawString("Hello World1!!!",0,8);
	oled.drawString("Hello World2!!!",0,16);
	oled.drawString("Hello World3!!!",0,24);
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
			helloWorld0[11] = 0x30 + i%10;
			oled.drawString(helloWorld0,0,0);
			oled.show();
		}
		for(uint8_t i = 0;i<100;i++)
		{
			display(i);
			delay_ms(100);
			helloWorld0[11] = 0x30 + i%10;
			oled.drawString(helloWorld0,0,0);
			oled.show();
		}
		for(uint16_t i = 0;i<1000;i++)
		{
			display(255);
			delay_ms(1);
			display(0);
			delay_ms(4);
			helloWorld0[11] = 0x30 + i%10;
			oled.drawString(helloWorld0,0,0);
			oled.show();
		}

	}
}
