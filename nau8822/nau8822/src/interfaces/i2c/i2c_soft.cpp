#include <i2c_soft.h>

#ifdef __cplusplus
extern "C" {
#endif

uint8_t GET_SDA(void)
{
	SET_SDA; // hi-z

		uint8_t volatile t = I2C_SDA_PIN;
		uint8_t volatile u = t & (1<<I2C_SDA);

		if(u > 0){
			return 1;
		};

		return 0;

	//for(uint8_t n=0; n<127; n++){
		//SET_SCL;
		////if( (I2C_SDA_PIN & (1<<I2C_SDA)) == (1 << I2C_SDA)){
			////delay(0xFF);
			////return 1;
		////};
		////delay(0xFF);
	//};

	return 0;
};

void i2c_init(void){
	SET_SCL;
	SET_SDA;
	delay(I2C_DELAY);
};


void i2c_start(void)
{
	CLR_SDA;
	delay(I2C_DELAY);
	CLR_SCL;
	delay(I2C_DELAY);
};

void i2c_stop(void)
{
	CLR_SDA;
	delay(I2C_DELAY);
	SET_SCL;
	delay(I2C_DELAY);
	SET_SDA;
	delay(I2C_DELAY);
};

void i2c_write(uint8_t b)
{
	//SET_SDA; // hi-z state

	uint8_t i = 0x80;

	for(; i; i >>= 1)
	{
		if(b & i){ SET_SDA; } else { CLR_SDA; };

		delay(I2C_DELAY);
		SET_SCL;
		delay(I2C_DELAY);
		CLR_SCL;
		delay(I2C_DELAY);
	};

	SET_SDA;
	delay(I2C_DELAY);
};


uint8_t i2c_ack(void)
{
	uint8_t volatile t = 0;
	SET_SCL;
	delay(I2C_DELAY);
	if(GET_SDA() == 1){
		t = 1;
	};
	CLR_SCL;
	delay(I2C_DELAY);
	return t;
};

uint8_t i2c_codec_write(uint8_t adr, uint16_t data)
{
	uint8_t data_tx = data & 0xFF;

	uint8_t b8 = (data & 0x0100) >> 8;

	uint8_t cd =(uint8_t)((adr << 1) | b8);

	uint8_t acks = 0;



	uint8_t ar = 0;

	for(uint8_t i=0; i<255; i++){
		i2c_start();
		i2c_write(i);
		uint8_t volatile t = i2c_ack();
		if( t == 0){
			CLR_SCL;
			CLR_SDA;
			while(1);
		}
		i2c_stop();
		delay(0xFF);
	};

	i2c_write(cd);
	i2c_ack();
	i2c_write(data_tx);
	i2c_ack();
	i2c_stop();

return acks;
};

#ifdef __cplusplus
}
#endif