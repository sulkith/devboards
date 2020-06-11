#include <atmel_start.h>
#include <std_twi.h>
struct io_descriptor *I2C_0_io;

void twi_init()
{
	i2c_m_sync_get_io_descriptor(&I2C_0, &I2C_0_io);
	i2c_m_sync_enable(&I2C_0);
}
uint8_t * twi_wait(){return 0;}
void twi_write(uint8_t address, uint8_t* data, uint8_t length, void (*callback)(uint8_t, uint8_t *)) {
	i2c_m_sync_set_slaveaddr(&I2C_0, address, I2C_M_SEVEN);
	io_write(I2C_0_io, data,length);
	uint8_t data_in[128] = {};
	uint8_t length_in = 0;
	length_in = io_read(I2C_0_io, data_in,sizeof(data_in));
	if(callback!=0)
		(callback)(length_in,data_in);
}
