#include <gpio.h>

GPIO::GPIO(volatile uint8_t* port, uint8_t pin)
{
	this->port = port;
	this->pin = pin;
};

 GPIO::GPIO()
 {
	this->port = 0;
	this->pin = 0;
 };

void GPIO::set(void)
{
	*this->port |= (1<<pin);		// port_n
	*(this->port-1) |= (1<<pin);	// ddr_n
};

void GPIO::i2c_set(void)
{
	*(this->port-1) &=~ (1<<pin);
	*this->port |= (1<<pin);
};

void GPIO::i2c_clr(void)
{
	*(this->port-1) |= (1<<pin);
	*this->port &=~ (1<<pin);
};

void GPIO::clear(void)
{
	*this->port &=~(1<<pin);		// port_n
	*(this->port-1) |= (1<<pin);	// ddr_n
};

void GPIO::release(void)
{
	*this->port &=~ (1<<pin);		// port_n
	*(this->port-1) &=~ (1<<pin);	// ddr_n
};

void GPIO::flip(void)
{
	*this->port ^= (1<<pin);		// port_n
	*(this->port-1) |= (1<<pin);	// ddr_n
}

uint8_t GPIO::read(void)
{
	volatile uint8_t r = *(this->port-2) & (1<<pin);	//pin_n
	if(r == (1<<pin)){
		return 1;
	};
	return 0;
};

uint8_t GPIO::readOpenDrain(void)
{
	*this->port &=~(1<<pin);							// port_n
	*(this->port-1) &=~ (1<<pin);						// ddr_n
	volatile uint8_t r = *(this->port-2) & (1<<pin);	//pin_n
	if(r & (1<<pin)){
		return 1;
	};
	return 0;
};

uint8_t GPIO::readPullUp(void)
{
	*this->port |= (1<<pin);		// port_n
	*(this->port-1) &=~(1<<pin);	// ddr_n clr
	volatile uint8_t r = *(this->port-2) & (1<<pin);	//pin_n
	if(r & (1<<pin)){
		return 1;
	};
	return 0;
};

