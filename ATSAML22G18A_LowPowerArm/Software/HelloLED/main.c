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
	REG_PORT_OUTSET0 = (code<<8)&0xFF00;
	REG_PORT_OUTCLR0 = (~(code)<<8)&0xFF00;

}
int main()
{
	//    REG_PORT_DIR0 |= (1<<28);
	REG_PORT_DIR0 |= 0xFF00;
	while(1)
	{
		display(0xAA);
		for(uint8_t i = 0;i<20;i++)
		{
			REG_PORT_OUTTGL0 |= 0xFF00;
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
