#ifndef gpio_h__
#define gpio_h__

#include <avr/io.h>

class GPIO {
public:
	volatile uint8_t* port;
	volatile uint8_t pin;

	GPIO();
	GPIO(volatile uint8_t* port, uint8_t pin);

	void set(void);

	void i2c_set(void);
	void i2c_clr(void);

	void clear(void);

	void release(void);

	void flip(void);

	uint8_t read(void);

	uint8_t readOpenDrain(void);
	uint8_t readPullUp(void);
};


#endif // gpio_h__
