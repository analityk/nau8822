#include <i2c_soft_gpio.h>
#include <serial.h>
#include <gpio.h>
#include <delay.h>


i2c_soft_gpio::i2c_soft_gpio(GPIO* gpio_sda, GPIO* gpio_scl, uint16_t wait):
	sda(gpio_sda),
	scl(gpio_scl),
	i2c_delay(wait)
{};

void i2c_soft_gpio::init(void)
{
	scl->i2c_set();
	sda->i2c_set();
	delay(i2c_delay);
};



void i2c_soft_gpio::start(void)
{
	sda->i2c_clr();
	delay(i2c_delay);
	scl->i2c_clr();
	delay(i2c_delay);
};

void i2c_soft_gpio::stop(void)
{
	sda->i2c_clr();
	delay(i2c_delay);
	scl->i2c_set();
	delay(i2c_delay);
	sda->i2c_set();
	delay(i2c_delay);
};

void i2c_soft_gpio::write(uint8_t b)
{

	uint8_t volatile i = 0x80;
	for(uint8_t volatile t = 0x80; t>0; t >>= 1)
	{
		if(b & t){
			sda->i2c_set();
		}else{
			sda->i2c_clr();
		};

		delay(i2c_delay);
		scl->i2c_set();
		delay(i2c_delay);
		scl->i2c_clr();
		delay(i2c_delay);
	};

	sda->i2c_set();
	delay(i2c_delay);
};

uint8_t i2c_soft_gpio::i2c_ack(void)
{
	uint8_t volatile t = 0;
	scl->i2c_set();
	delay(i2c_delay);
	if(get_sda() == 1){
		t = 1;
	};
	scl->i2c_clr();
	delay(i2c_delay);
	return t;
};

uint8_t i2c_soft_gpio::get_sda(void)
{
	sda->i2c_set();

	uint8_t volatile u = sda->readPullUp();

	if(u > 0){
		return 1;
	};

	return 0;
};