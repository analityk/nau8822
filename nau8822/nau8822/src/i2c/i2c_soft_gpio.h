#ifndef i2c_soft_gpio_h__
#define i2c_soft_gpio_h__

#include <avr/io.h>
#include <gpio.h>
#include <serial.h>

class i2c_soft_gpio{
public:

	GPIO* sda;
	GPIO* scl;
	uint16_t i2c_delay;

	i2c_soft_gpio(GPIO* gpio_sda, GPIO* gpio_scl, uint16_t wait);

	void init(void);
	void start(void);
	void stop(void);
	void write(uint8_t b);

	uint8_t i2c_ack(void);

	uint8_t i2c_codec_write(uint8_t adr, uint16_t data);
	uint8_t get_sda(void);
};


#endif // i2c_soft_gpio_h__
