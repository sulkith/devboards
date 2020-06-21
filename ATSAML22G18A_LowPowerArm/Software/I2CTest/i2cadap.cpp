#include <atmel_start.h>
#include <std_twi.h>
struct io_descriptor *I2C_0_io;

void twi_write_internal(uint8_t address, uint8_t* data, uint8_t length, void (*callback)(uint8_t, uint8_t *), uint8_t stop);

void twi_init()
{
	i2c_m_sync_get_io_descriptor(&I2C_0, &I2C_0_io);
	i2c_m_sync_enable(&I2C_0);
}
uint8_t * twi_wait(){return 0;}

void twi_write(uint8_t address, uint8_t* data, uint8_t length, void (*callback)(uint8_t, uint8_t *))
{
	twi_write_internal(address,data,length,callback,1);
}
void twi_write_internal(uint8_t address, uint8_t* data, uint8_t length, void (*callback)(uint8_t, uint8_t *), uint8_t stop)
{
	i2c_m_sync_set_slaveaddr(&I2C_0, address, I2C_M_SEVEN);

	struct _i2c_m_msg msg;
	msg.addr = I2C_0.slave_addr;
	msg.buffer = data;
	msg.len = length;

	if(stop == 1)
		msg.flags = I2C_M_STOP;
	else
		msg.flags = 0;

	_i2c_m_sync_transfer(&I2C_0.device, &msg);

	return;
}

void twi_read(uint8_t address, uint8_t length, void (*callback)(uint8_t, uint8_t *))
{
	uint8_t data[64];
	i2c_m_sync_set_slaveaddr(&I2C_0, address, I2C_M_SEVEN);

	struct _i2c_m_msg;
	msg.addr = I2C_0.slave_addr;
	msg.buffer = data;
	msg.len = length;
	msg.flags = I2C_M_STOP | I2C_M_RD;

	_i2c_m_sync_transfer(&I2C_0.device, &msg);

	callback(length,data);
}
