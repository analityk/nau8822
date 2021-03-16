#include <nau8822_hardware.h>

#ifdef __cplusplus
extern "C" {
#endif

uint8_t nau8822_register_write(uint8_t reg_number, uint16_t reg_value)
{
#ifdef NAU8822_INTERFACE_I2C
	return i2c_codec_write(reg_number, reg_value);
#elif NAU8822_INTERFACE_SPI
#else
#error "you should choos interface to communicate with your codec"
#endif

}

#ifdef __cplusplus
}
#endif

