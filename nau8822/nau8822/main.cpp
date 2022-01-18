/*
 * nau8822.cpp
 *
 * Created: 2021-03-04 22:24:00
 * Author : Szymon
 */

#include <avr/io.h>
#include <nau8822_code/nau8822.h>
#include <delay.h>
#include <i2c_soft.h>
#include <serial.h>
#include <gpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <i2c_soft_gpio.h>

GPIO led1(&PORTC, PINC1);

GPIO msda(&PORTB, PINB4);
GPIO mscl(&PORTB, PINB3);

i2c_soft_gpio naui2c(&msda, &mscl, 100);

class NAU22{
public:
	NAU22(){};

	void i2c_codec_write(uint8_t adr, uint16_t data){

		uint8_t data_tx = data & 0xFF;

		uint8_t b8 = (data & 0x0100) >> 8;

		uint8_t cd =(uint8_t)((adr << 1) | b8);

		uint8_t acks = 0;

		naui2c.start();
		naui2c.write(0x34);
		naui2c.i2c_ack();
		naui2c.write(cd);
		naui2c.i2c_ack();
		naui2c.write(data_tx);
		naui2c.i2c_ack();
		naui2c.stop();
	};
};

int main(void)
{
	Serial.SetUbrr(103);

	NAU22 nau2;

	nau8822_register_write(0,0);

	i2c_codec_write(0,0);

	delay(0xFFFF);

	uint8_t vola = 5;
	uint8_t volb = 5;
	uint8_t volc = 5;

	nau8822_register_write(LHP_VOLUME, (1<<LHPVU)|(1<<LHPZC)|(vola<<LHPGAIN));
	nau8822_register_write(RHP_VOLUME, (1<<RHPVU)|(1<<RHPZC)|(volb<<RHPGAIN));

	nau2.i2c_codec_write(LHP_VOLUME, (1<<LHPVU)|(1<<LHPZC)|(vola<<LHPGAIN));
	nau2.i2c_codec_write(RHP_VOLUME, (1<<RHPVU)|(1<<RHPZC)|(volb<<RHPGAIN));

	nau8822_register_write(POWER_MANAGMENT_1, 0x01DD);
	nau8822_register_write(POWER_MANAGMENT_2, 0x01BF);
	nau8822_register_write(POWER_MANAGMENT_3, 0x000F);

	nau2.i2c_codec_write(POWER_MANAGMENT_1, 0x01DD);
	nau2.i2c_codec_write(POWER_MANAGMENT_2, 0x01BF);
	nau2.i2c_codec_write(POWER_MANAGMENT_3, 0x000F);

	nau8822_register_write(COMPANDING, (1 << ADDAP));
	nau8822_register_write(CLOCK_CONTROL_1, 0x0149); // sprawdzic

	nau8822_register_write(ADC_CONTROL, 0);
	nau8822_register_write(EQ_1_LOW_CUTOFF, 0x002C);

	nau2.i2c_codec_write(COMPANDING, (1 << ADDAP));
	nau2.i2c_codec_write(CLOCK_CONTROL_1, 0x0149); // sprawdzic

	nau2.i2c_codec_write(ADC_CONTROL, 0);
	nau2.i2c_codec_write(EQ_1_LOW_CUTOFF, 0x002C);



	nau8822_register_write(POWER_MANAGMENT_1, 0x01FD);
	nau8822_register_write(RIGHT_SPEAKER_SUBMIXER, 0x0020);
	nau8822_register_write(INPUT_CONTROL, 0);
	nau8822_register_write(LEFT_INPUT_PGA_GAIN, (1<<LPGAMT));
	nau8822_register_write(RIGHT_INPUT_PGA_GAIN, (1<<RPGAMT));
	nau8822_register_write(LEFT_ADC_BOOST, 1);
	nau8822_register_write(RIGHT_ADC_BOOST, 1);

	nau8822_register_write(LEFT_MIXER, (1<<LDACLMX));
	nau8822_register_write(RIGHT_MIXER, (1<<RDACRMX));


	nau2.i2c_codec_write(POWER_MANAGMENT_1, 0x01FD);
	nau2.i2c_codec_write(RIGHT_SPEAKER_SUBMIXER, 0x0020);
	nau2.i2c_codec_write(INPUT_CONTROL, 0);
	nau2.i2c_codec_write(LEFT_INPUT_PGA_GAIN, (1<<LPGAMT));
	nau2.i2c_codec_write(RIGHT_INPUT_PGA_GAIN, (1<<RPGAMT));
	nau2.i2c_codec_write(LEFT_ADC_BOOST, 1);
	nau2.i2c_codec_write(RIGHT_ADC_BOOST, 1);

	nau2.i2c_codec_write(LEFT_MIXER, (1<<LDACLMX));
	nau2.i2c_codec_write(RIGHT_MIXER, (1<<RDACRMX));

	//nau8822_set_input_control(0);
//
	//snau8822.companding.addap = 1;
	//nau8822_set_companding(&snau8822.companding);
//
	//nau8822_equ_src(e_es_ADC);
	//nau8822_mic_bias_voltage(e_mbl_85);
//
	//nau8822_left_in_mix_src(e_lim_LeftAux, 1);
	//nau8822_right_in_mix_src(e_rim_RightAux, 1);



	//nau8822_left_main_mix_src(e_lmm_LeftDAC, 211);
	//nau8822_right_main_mix_src(e_rmm_RightDAC, 211);


	//nau8822_equ_band_1(e_eb1_175, 12);
	//nau8822_equ_band_2(e_eb2_385, 12);
	//nau8822_equ_band_3(e_eb3_1400, 12);
	//nau8822_equ_band_4(e_eb4_2400, 12);
	//nau8822_equ_band_5(e_eb5_5300, 12);

	//// alc setup
	//// read carefull datasheet
	//// https://www.nuvoton.com/resource-files/nau8822ldatasheetrev1.9.pdf
//
	//s_alc_control_1 alcr1 = { .alcen=alcen_booth_en, .alcmxgain=7, .alcmngain=0 };
	//s_alc_control_2 alcr2 = { .alcht=14, .alcsl=12 };
	//s_alc_control_3 alcr3 = { .alcm=0, .alcdcy=8, .alcatk=2 };
	//s_noise_gate noisegate= { .alcnen=0, .alcnth=4 };
//
	//// on avr i cant use non-trival list initializer
	//// and you can't make pointer to bitfield
	//// so you have to do this way or look at example with power_1

	//snau8822.alc_control_1 = alcr1;
	//snau8822.alc_control_2 = alcr2;
	//snau8822.alc_control_3 = alcr3;
	//snau8822.noise_gate = noisegate;
	//nau8822_set_alc();




	//nau8822_headphone_volume(5, 5);


	while(1){
		uint8_t cr = Serial.readByte();

		switch(cr){
			case 'a':{
				if(vola < 63){
					vola += 1;
				};
				if(volb < 63){
					volb += 1;
				};
				if(volc < 63){
					volc += 1;
				};

				nau8822_register_write(LHP_VOLUME, (1<<LHPVU)|(1<<LHPZC)|(vola<<LHPGAIN));
				nau8822_register_write(RHP_VOLUME, (1<<RHPVU)|(1<<RHPZC)|(volb<<RHPGAIN));

				nau2.i2c_codec_write(LHP_VOLUME, (1<<LHPVU)|(1<<LHPZC)|(volc<<LHPGAIN));

				char spr[50];
				char num1[10];
				char num2[10];
				char num3[10];

				itoa(vola, num1, 10);
				itoa(volb, num2, 10);
				itoa(volc, num3, 10);

				sprintf(spr, "vol a: %s vol b: %s vol c: %s \r\n", num1, num2, num3);
				Serial.write(spr);

				break;
			};

			case 's':{
				if(volc < 62){
					volc += 1;
				};

				nau2.i2c_codec_write(LHP_VOLUME, (1<<LHPVU)|(1<<LHPZC)|(volc<<LHPGAIN));

				char spr[40];
				char num1[10];

				itoa(volc, num1, 10);

				sprintf(spr, "vol bas: %s \r\n", num1);
				Serial.write(spr);

				break;
			};

			case 'x':{
				if(volc >= 2){
					volc--;
				};

				nau2.i2c_codec_write(LHP_VOLUME, (1<<LHPVU)|(1<<LHPZC)|(volc<<LHPGAIN));

				char spr[40];
				char num1[10];

				itoa(volc, num1, 10);

				sprintf(spr, "vol bas: %s \r\n", num1);
				Serial.write(spr);

				break;
			};

			case 'z':{
				if(vola >= 2){
					vola--;
				};
				if(volb >= 2){
					volb--;
				};
				if(volc >= 2){
					volc--;
				};

				if(vola <= 1){
					vola = 0;
					nau8822_register_write(LHP_VOLUME, 1<<LHPMUTE);
				}else{
					nau8822_register_write(LHP_VOLUME, (1<<LHPVU)|(1<<LHPZC)|(vola<<LHPGAIN));
				};

				if(volb <= 1){
					volb = 0;
					nau8822_register_write(RHP_VOLUME, 1<<RHPMUTE);
 				}else{
					nau8822_register_write(RHP_VOLUME, (1<<RHPVU)|(1<<RHPZC)|(volb<<RHPGAIN));
				};

				if(volc <= 1){
					volc = 0;
					nau2.i2c_codec_write(LHP_VOLUME, 1<<LHPMUTE);
				}else{
					nau2.i2c_codec_write(LHP_VOLUME, (1<<LHPVU)|(1<<LHPZC)|(volc<<LHPGAIN));
				};

				char spr[50];
				char num1[10];
				char num2[10];
				char num3[10];

				itoa(vola, num1, 10);
				itoa(volb, num2, 10);
				itoa(volc, num3, 10);

				sprintf(spr, "vol a: %s vol b: %s vol c: %s \r\n", num1, num2, num3);
				Serial.write(spr);

				break;
			};

			default:break;

		};

		led1.flip();
	};
};

