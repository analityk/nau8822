#ifndef serial_h__
#define serial_h__

#include <avr/io.h>
#include <avr/interrupt.h>

class serial{
	public:
	serial(void);

	void SetUbrr(uint16_t ubrr);
	void Enable(void);
	void Disable(void);
	void InterruptEnable_RX(void);
	void InterruptDisable_RX(void);
	void write(uint8_t* buff, uint8_t size);
	void write(const char* s, uint8_t size);
	void write(char* t);
	void write(const char* s);
	void write(uint8_t byte);
	//void write(array<uint8_t> &data);
	uint8_t readByte(void);
};

extern serial Serial;



#endif // serial_h__