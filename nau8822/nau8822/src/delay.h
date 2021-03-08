#ifndef delay_h__
#define delay_h__

#include <avr/io.h>

#ifdef __cplusplus
extern "C" {
#endif


void delay(uint32_t volatile t);

#ifdef __cplusplus
}
#endif

#endif // delay_h__
