#include <saml22.h>

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
int main()
{
	PORT->Group[0].DIR.reg = 0xFF00;
	while(1)
	{
		display(0xAA);
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
