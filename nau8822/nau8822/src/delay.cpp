#include <delay.h>

#ifdef __cplusplus
extern "C" {
#endif

void delay(uint32_t volatile t){
	while(t--){};
};

#ifdef __cplusplus
}

#endif
