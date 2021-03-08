#ifndef i2c_soft_h__
#define i2c_soft_h__

#include <delay.h>

#ifdef __cplusplus
extern "C" {
#endif

#define I2C_SDA_DDR		(DDRB)
#define I2C_SDA_PORT	(PORTB)
#define I2C_SDA_PIN		(PINB)

#define I2C_SCL_DDR		(DDRB)
#define I2C_SCL_PORT	(PORTB)

#define I2C_SDA		(PINB1)
#define I2C_SCL		(PINB2)

#define I2C_DELAY	100


#ifdef SAM_UC
#define CLR_SDA	{ pio_clear(I2C_SDA_PIO, I2C_SDA); }
#define SET_SDA	{ pio_set(I2C_SDA_PIO, I2C_SDA);   }
#define CLR_SCL { pio_clear(I2C_SCL_PIO, I2C_SCL); }
#define SET_SCL { pio_set(I2C_SCL_PIO, I2C_SCL);   }
#elif AVR_UC
#define CLR_SDA { I2C_SDA_DDR |= (1<<I2C_SDA); I2C_SDA_PORT &=~(1<<I2C_SDA); }
#define SET_SDA { I2C_SDA_DDR |= (0<<I2C_SDA); I2C_SDA_PORT |=(1<<I2C_SDA);	 } // input in hi-z but pull-up'ed
#define CLR_SCL { I2C_SCL_DDR |= (1<<I2C_SCL); I2C_SCL_PORT &=~(1<<I2C_SDA); }
#define SET_SCL { I2C_SCL_DDR |= (1<<I2C_SCL); I2C_SCL_PORT |=(1<<I2C_SCL);	 } // input in hi-z but pull-up'ed
#else
#error "make your own scl and sda macros"
#endif


uint8_t GET_SDA(void);

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_write(uint8_t b);

uint8_t i2c_ack(void);

uint8_t i2c_codec_write(uint8_t adr, uint16_t data);

#ifdef __cplusplus
}
#endif

#endif // i2c_soft_h__
