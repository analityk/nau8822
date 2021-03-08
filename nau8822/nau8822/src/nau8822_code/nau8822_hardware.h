#ifndef nau8822_hardware_h__
#define nau8822_hardware_h__

#include <avr/io.h>
#include <i2c_soft.h>
#ifdef __cplusplus
extern "C"{
#endif

uint8_t nau8822_register_write(uint8_t reg_number, uint16_t reg_value);


#ifdef __cplusplus
}
#endif

#endif // nau8822_hardware_h__
