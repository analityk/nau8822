/*
 * nau8822.cpp
 *
 * Created: 2021-03-04 22:24:00
 * Author : Szymon
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include <nau8822_code/nau8822.h>
#include <delay.h>
#include <i2c_soft.h>
#include <serial.h>
#include <gpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <i2c_soft_gpio.h>

#define REG_ESV0		(uint8_t *)0
#define REG_ESV1		(uint8_t *)1
#define REG_ESV2		(uint8_t *)2
#define REG_ESV3		(uint8_t *)3
#define REG_ESV4		(uint8_t *)4

#define REG_ESF0		(uint8_t *)5
#define REG_ESF1		(uint8_t *)6
#define REG_ESF2		(uint8_t *)7
#define REG_ESF3		(uint8_t *)8
#define REG_ESF4		(uint8_t *)9

#define REG_EBV0		(uint8_t *)10
#define REG_EBV1		(uint8_t *)11
#define REG_EBV2		(uint8_t *)12
#define REG_EBV3		(uint8_t *)13
#define REG_EBV4		(uint8_t *)14

#define REG_EBF0		(uint8_t *)15
#define REG_EBF1		(uint8_t *)16
#define REG_EBF2		(uint8_t *)17
#define REG_EBF3		(uint8_t *)18
#define REG_EBF4		(uint8_t *)19

#define REG_GVA			(uint8_t *)20
#define REG_GVB			(uint8_t *)21
#define REG_GVC			(uint8_t *)22

GPIO led1(&PORTC, PINC1);

GPIO msda(&PORTB, PINB4);
GPIO mscl(&PORTB, PINB3);

i2c_soft_gpio naui2c(&msda, &mscl, 100);

class NAU22{
public:
	NAU22(){};

	void write(uint8_t adr, uint16_t data){

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

NAU22 nau2;

void setup(uint8_t kodek, uint8_t nau_reg, uint16_t nau_val, uint8_t nau_part_val, uint8_t* eepreg, char* info);

int main(void)
{
	Serial.SetUbrr(103);

	nau8822_register_write(0,0);

	nau2.write(0,0);

	delay(0xFFFF);

	uint8_t vola = 5;
	uint8_t volb = 5;
	uint8_t volc = 5;

	nau8822_register_write(LHP_VOLUME, (1<<LHPVU)|(1<<LHPZC)|(vola<<LHPGAIN));
	nau8822_register_write(RHP_VOLUME, (1<<RHPVU)|(1<<RHPZC)|(volb<<RHPGAIN));

	nau2.write(LHP_VOLUME, (1<<LHPVU)|(1<<LHPZC)|(vola<<LHPGAIN));
	nau2.write(RHP_VOLUME, (1<<RHPVU)|(1<<RHPZC)|(volb<<RHPGAIN));

	nau8822_register_write(POWER_MANAGMENT_1, 0x01DD);
	nau8822_register_write(POWER_MANAGMENT_2, 0x01BF);
	nau8822_register_write(POWER_MANAGMENT_3, 0x000F);

	nau2.write(POWER_MANAGMENT_1, 0x01DD);
	nau2.write(POWER_MANAGMENT_2, 0x01BF);
	nau2.write(POWER_MANAGMENT_3, 0x000F);

	nau8822_register_write(COMPANDING, (1 << ADDAP));
	nau8822_register_write(CLOCK_CONTROL_1, 0x0149); // sprawdzic

	nau8822_register_write(ADC_CONTROL, 0);
	nau8822_register_write(EQ_1_LOW_CUTOFF, 0x002C);

	nau2.write(COMPANDING, (1 << ADDAP));
	nau2.write(CLOCK_CONTROL_1, 0x0149); // sprawdzic

	nau2.write(ADC_CONTROL, 0);
	nau2.write(EQ_1_LOW_CUTOFF, 0x002C);



	nau8822_register_write(POWER_MANAGMENT_1, 0x01FD);
	nau8822_register_write(RIGHT_SPEAKER_SUBMIXER, 0x0020);
	nau8822_register_write(INPUT_CONTROL, 0);
	nau8822_register_write(LEFT_INPUT_PGA_GAIN, (1<<LPGAMT));
	nau8822_register_write(RIGHT_INPUT_PGA_GAIN, (1<<RPGAMT));
	nau8822_register_write(LEFT_ADC_BOOST, 1);
	nau8822_register_write(RIGHT_ADC_BOOST, 1);

	nau8822_register_write(LEFT_MIXER, (1<<LDACLMX));
	nau8822_register_write(RIGHT_MIXER, (1<<RDACRMX));


	nau2.write(POWER_MANAGMENT_1, 0x01FD);
	nau2.write(RIGHT_SPEAKER_SUBMIXER, 0x0020);
	nau2.write(INPUT_CONTROL, 0);
	nau2.write(LEFT_INPUT_PGA_GAIN, (1<<LPGAMT));
	nau2.write(RIGHT_INPUT_PGA_GAIN, (1<<RPGAMT));
	nau2.write(LEFT_ADC_BOOST, 1);
	nau2.write(RIGHT_ADC_BOOST, 1);

	nau2.write(LEFT_MIXER, (1<<LDACLMX));
	nau2.write(RIGHT_MIXER, (1<<RDACRMX));

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

	uint8_t equ_sat_vol[5];	// 0 - 23
	uint8_t equ_sat_freq[5];
	uint8_t equ_bas_vol[5];	// 0 - 23
	uint8_t equ_bas_freq[5];

//
	//// before first use set eeprom mem to 0, then comment this section
	//for(uint8_t i=0; i<100; i++){
		//eeprom_write_byte((uint8_t*)(i), 0);
	//};
	//while(1);

	for(uint8_t i = 0; i<5; i++){
		equ_sat_vol[i] = eeprom_read_byte((uint8_t*)i);
	};

	for(uint8_t i = 5; i<10; i++){
		equ_sat_freq[i-5] = eeprom_read_byte((uint8_t*)i);
	};

	for(uint8_t i = 10; i<15; i++){
		equ_bas_vol[i-10] = eeprom_read_byte((uint8_t*)i);
	};

	for(uint8_t i = 15; i<20; i++){
		equ_bas_freq[i-15] = eeprom_read_byte((uint8_t*)i);
	};

	vola = eeprom_read_byte(REG_GVA);
	volb = eeprom_read_byte(REG_GVB);
	volc = eeprom_read_byte(REG_GVC);

	nau8822_register_write(LHP_VOLUME, (1<<LHPVU)|(1<<LHPZC)|(vola<<LHPGAIN));
	nau8822_register_write(RHP_VOLUME, (1<<RHPVU)|(1<<RHPZC)|(volb<<RHPGAIN));

	nau2.write(LHP_VOLUME, (1<<LHPVU)|(1<<LHPZC)|(volc<<LHPGAIN));


	nau8822_register_write(EQ_1_LOW_CUTOFF, (equ_sat_vol[0]) | (equ_sat_freq[0] << EQ1CF) );
	nau8822_register_write(EQ_2_PEAK_1,		(equ_sat_vol[1]) | (equ_sat_freq[1] << EQ2CF) );
	nau8822_register_write(EQ_3_PEAK_2,		(equ_sat_vol[2]) | (equ_sat_freq[2] << EQ3CF) );
	nau8822_register_write(EQ_4_PEAK_3,		(equ_sat_vol[3]) | (equ_sat_freq[3] << EQ4CF) );
	nau8822_register_write(EQ5_HIGH_CUTOFF, (equ_sat_vol[4]) | (equ_sat_freq[4] << EQ5CF) );

	nau2.write(EQ_1_LOW_CUTOFF, (equ_bas_vol[0]) | (equ_bas_freq[0] << EQ1CF) );
	nau2.write(EQ_2_PEAK_1,		(equ_bas_vol[1]) | (equ_bas_freq[1] << EQ2CF) );
	nau2.write(EQ_3_PEAK_2,		(equ_bas_vol[2]) | (equ_bas_freq[2] << EQ3CF) );
	nau2.write(EQ_4_PEAK_3,		(equ_bas_vol[3]) | (equ_bas_freq[3] << EQ4CF) );
	nau2.write(EQ5_HIGH_CUTOFF, (equ_bas_vol[4]) | (equ_bas_freq[4] << EQ5CF) );


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

				nau2.write(LHP_VOLUME, (1<<LHPVU)|(1<<LHPZC)|(volc<<LHPGAIN));

				char spr[50];
				char num1[10];
				char num2[10];
				char num3[10];

				itoa(vola, num1, 10);
				itoa(volb, num2, 10);
				itoa(volc, num3, 10);

				sprintf(spr, "vol a: %s vol b: %s vol c: %s \r\n", num1, num2, num3);
				Serial.write(spr);

				eeprom_write_byte(REG_GVA, vola);
				delay(0xffff);
				eeprom_write_byte(REG_GVB, volb);
				delay(0xffff);
				eeprom_write_byte(REG_GVC, volc);

				break;
			};

			case 's':{
				if(volc < 62){
					volc += 1;
				};

				nau2.write(LHP_VOLUME, (1<<LHPVU)|(1<<LHPZC)|(volc<<LHPGAIN));

				char spr[40];
				char num1[10];

				itoa(volc, num1, 10);

				sprintf(spr, "vol bas: %s \r\n", num1);
				Serial.write(spr);

				eeprom_write_byte(REG_GVC, volc);

				break;
			};

			case 'x':{
				if(volc >= 2){
					volc--;
				};

				nau2.write(LHP_VOLUME, (1<<LHPVU)|(1<<LHPZC)|(volc<<LHPGAIN));

				char spr[40];
				char num1[10];

				itoa(volc, num1, 10);

				sprintf(spr, "vol bas: %s \r\n", num1);
				Serial.write(spr);

				eeprom_write_byte(REG_GVC, volc);

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
					nau2.write(LHP_VOLUME, 1<<LHPMUTE);
				}else{
					nau2.write(LHP_VOLUME, (1<<LHPVU)|(1<<LHPZC)|(volc<<LHPGAIN));
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

				eeprom_write_byte(REG_GVA, vola);
				delay(0xffff);
				eeprom_write_byte(REG_GVB, volb);
				delay(0xffff);
				eeprom_write_byte(REG_GVC, volc);

				break;
			};


			case '1':{
				if(equ_sat_vol[0]>1){
					equ_sat_vol[0] -= 1;
					setup(0, EQ_1_LOW_CUTOFF, (equ_sat_vol[0]) | (equ_sat_freq[0] << EQ1CF), equ_sat_vol[0], REG_ESV0, "equ sat vol 1: ");
				};
				break;
			};

			case '2':{
				if(equ_sat_vol[1]>1){
					equ_sat_vol[1] -= 1;
					setup(0, EQ_2_PEAK_1, (equ_sat_vol[1]) | (equ_sat_freq[1] << EQ2CF), equ_sat_vol[1], REG_ESV1, "equ sat vol 2: ");
				};
				break;
			};

			case '3':{
				if(equ_sat_vol[2]>1){
					equ_sat_vol[2] -= 1;
					setup(0, EQ_3_PEAK_2, (equ_sat_vol[2]) | (equ_sat_freq[2] << EQ3CF), equ_sat_vol[2], REG_ESV2, "equ sat vol 3: ");
				};
				break;
			};

			case '4':{
				if(equ_sat_vol[3]>1){
					equ_sat_vol[3] -= 1;
					setup(0, EQ_4_PEAK_3, (equ_sat_vol[3]) | (equ_sat_freq[3] << EQ4CF), equ_sat_vol[3], REG_ESV3, "equ sat vol 4: ");
				};
				break;
			};

			case '5':{
				if(equ_sat_vol[4]>1){
					equ_sat_vol[4] -= 1;
					setup(0, EQ5_HIGH_CUTOFF, (equ_sat_vol[4]) | (equ_sat_freq[4] << EQ5CF), equ_sat_vol[4], REG_ESV4, "equ sat vol 5: ");
				};
				break;
			};




			case 'q':{
				if(equ_sat_vol[0]<23){
					equ_sat_vol[0] += 1;
					setup(0, EQ_1_LOW_CUTOFF, (equ_sat_vol[0]) | (equ_sat_freq[0] << EQ1CF), equ_sat_vol[0], REG_ESV0, "equ sat vol 1: ");
				};
				break;
			};

			case 'w':{
				if(equ_sat_vol[1]<23){
					equ_sat_vol[1] += 1;
					setup(0, EQ_2_PEAK_1, (equ_sat_vol[1]) | (equ_sat_freq[1] << EQ2CF), equ_sat_vol[1], REG_ESV1, "equ sat vol 2: ");
				};
				break;
			};

			case 'e':{
				if(equ_sat_vol[2]<23){
					equ_sat_vol[2] += 1;
					setup(0, EQ_3_PEAK_2, (equ_sat_vol[2]) | (equ_sat_freq[2] << EQ3CF), equ_sat_vol[2], REG_ESV2, "equ sat vol 3: ");
				};
				break;
			};

			case 'r':{
				if(equ_sat_vol[3]<23){
					equ_sat_vol[3] += 1;
					setup(0, EQ_4_PEAK_3, (equ_sat_vol[3]) | (equ_sat_freq[3] << EQ4CF), equ_sat_vol[3], REG_ESV3, "equ sat vol 4: ");
				};
				break;
			};

			case 't':{
				if(equ_sat_vol[4]<23){
					equ_sat_vol[4] += 1;
					setup(0, EQ5_HIGH_CUTOFF, (equ_sat_vol[4]) | (equ_sat_freq[4] << EQ5CF), equ_sat_vol[4], REG_ESV4, "equ sat vol 5: ");
				};
				break;
			};

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

			case '6':{
				if(equ_bas_vol[0]>1){
					equ_bas_vol[0] -= 1;
					setup(1, EQ_1_LOW_CUTOFF, (equ_bas_vol[0]) | (equ_sat_freq[0] << EQ1CF), equ_bas_vol[0], REG_EBV0, "equ bas vol 1: ");
				};
				break;
			};

			case '7':{
				if(equ_bas_vol[1]>1){
					equ_bas_vol[1] -= 1;
					setup(1, EQ_2_PEAK_1, (equ_bas_vol[1]) | (equ_sat_freq[1] << EQ2CF), equ_bas_vol[1], REG_EBV1, "equ bas vol 2: ");
				};
				break;
			};

			case '8':{
				if(equ_bas_vol[2]>1){
					equ_bas_vol[2] -= 1;
					setup(1, EQ_3_PEAK_2, (equ_bas_vol[2]) | (equ_sat_freq[2] << EQ3CF), equ_bas_vol[2], REG_EBV2, "equ bas vol 3: ");
				};
				break;
			};

			case '9':{
				if(equ_bas_vol[3]>1){
					equ_bas_vol[3] -= 1;
					setup(1, EQ_4_PEAK_3, (equ_bas_vol[3]) | (equ_sat_freq[3] << EQ4CF), equ_bas_vol[3], REG_EBV3, "equ bas vol 4: ");
				};
				break;
			};

			case '0':{
				if(equ_bas_vol[4]>1){
					equ_bas_vol[4] -= 1;
					setup(1, EQ5_HIGH_CUTOFF, (equ_bas_vol[4]) | (equ_sat_freq[4] << EQ5CF), equ_bas_vol[4], REG_EBV4, "equ bas vol 5: ");
				};
				break;
			};




			case 'y':{
				if(equ_bas_vol[0]<23){
					equ_bas_vol[0] += 1;
					setup(1, EQ_1_LOW_CUTOFF, (equ_bas_vol[0]) | (equ_sat_freq[0] << EQ1CF), equ_bas_vol[0], REG_EBV0, "equ bas vol 1: ");
				};
				break;
			};

			case 'u':{
				if(equ_bas_vol[1]<23){
					equ_bas_vol[1] += 1;
					setup(1, EQ_2_PEAK_1, (equ_bas_vol[1]) | (equ_sat_freq[1] << EQ2CF), equ_bas_vol[1], REG_EBV1, "equ bas vol 2: ");
				};
				break;
			};

			case 'i':{
				if(equ_bas_vol[2]<23){
					equ_bas_vol[2] += 1;
					setup(1, EQ_3_PEAK_2, (equ_bas_vol[2]) | (equ_sat_freq[2] << EQ3CF), equ_bas_vol[2], REG_EBV2, "equ bas vol 3: ");
				};
				break;
			};

			case 'o':{
				if(equ_bas_vol[3]<23){
					equ_bas_vol[3] += 1;
					setup(1, EQ_4_PEAK_3, (equ_bas_vol[3]) | (equ_sat_freq[3] << EQ4CF), equ_bas_vol[3], REG_EBV3, "equ bas vol 4: ");
				};
				break;
			};

			case 'p':{
				if(equ_bas_vol[4]<23){
					equ_bas_vol[4] += 1;
					setup(1, EQ5_HIGH_CUTOFF, (equ_bas_vol[4]) | (equ_sat_freq[4] << EQ5CF), equ_bas_vol[4], REG_EBV4, "equ bas vol 5: ");
				};
				break;
			};


//////////////////////////////////////////////////////////////////////////
// freq setting
//////////////////////////////////////////////////////////////////////////


			case '!':{
				if(equ_sat_freq[0] < 4){
					equ_sat_freq[0] += 1;
					setup(0, EQ_1_LOW_CUTOFF, (equ_sat_vol[0]) | (equ_sat_freq[0] << EQ1CF), equ_sat_freq[0], REG_ESF0, "equ sat 1 freq band: ");
				};
				break;
			};

			case 'Q':{
				if(equ_sat_freq[0] > 1){
					equ_sat_freq[0] -= 1;
					setup(0, EQ_1_LOW_CUTOFF, (equ_sat_vol[0]) | (equ_sat_freq[0] << EQ1CF), equ_sat_freq[0], REG_ESF0, "equ sat 1 freq band: ");
				};
				break;
			};

			case '@':{
				if(equ_sat_freq[1] < 4){
					equ_sat_freq[1] += 1;
					setup(0, EQ_2_PEAK_1, (equ_sat_vol[1]) | (equ_sat_freq[1] << EQ2CF), equ_sat_freq[1], REG_ESF1, "equ sat 2 freq band: ");
				};
				break;
			};

			case 'W':{
				if(equ_sat_freq[1] > 1){
					equ_sat_freq[1] -= 1;
					setup(0, EQ_2_PEAK_1, (equ_sat_vol[1]) | (equ_sat_freq[1] << EQ2CF), equ_sat_freq[1], REG_ESF1, "equ sat 2 freq band: ");
				};
				break;
			};



			case '#':{
				if(equ_sat_freq[2] < 4){
					equ_sat_freq[2] += 1;
					setup(0, EQ_3_PEAK_2, (equ_sat_vol[2]) | (equ_sat_freq[2] << EQ3CF), equ_sat_freq[2], REG_ESF2, "equ sat 3 freq band: ");
				};
				break;
			};

			case 'E':{
				if(equ_sat_freq[2] > 1){
					equ_sat_freq[2] -= 1;
					setup(0, EQ_3_PEAK_2, (equ_sat_vol[2]) | (equ_sat_freq[2] << EQ3CF), equ_sat_freq[2], REG_ESF2, "equ sat 3 freq band: ");
				};
				break;
			};


			case '$':{
				if(equ_sat_freq[3] < 4){
					equ_sat_freq[3] += 1;
					setup(0, EQ_4_PEAK_3, (equ_sat_vol[3]) | (equ_sat_freq[3] << EQ4CF), equ_sat_freq[3], REG_ESF3, "equ sat 4 freq band: ");
				};
				break;
			};

			case 'R':{
				if(equ_sat_freq[3] > 1){
					equ_sat_freq[3] -= 1;
					setup(0, EQ_4_PEAK_3, (equ_sat_vol[3]) | (equ_sat_freq[3] << EQ4CF), equ_sat_freq[3], REG_ESF3, "equ sat 4 freq band: ");
				};
				break;
			};


			case '%':{
				if(equ_sat_freq[4] < 4){
					equ_sat_freq[4] += 1;
					setup(0, EQ5_HIGH_CUTOFF, (equ_sat_vol[4]) | (equ_sat_freq[4] << EQ5CF), equ_sat_freq[4], REG_ESF4, "equ sat 5 freq band: ");
				};
				break;
			};

			case 'T':{
				if(equ_sat_freq[4] > 1){
					equ_sat_freq[4] -= 1;
					setup(0, EQ5_HIGH_CUTOFF, (equ_sat_vol[4]) | (equ_sat_freq[4] << EQ5CF), equ_sat_freq[4], REG_ESF4, "equ sat 5 freq band: ");
				};
				break;
			};

			//////////////////////////////////////////////////////////////////////////

			//////////////////////////////////////////////////////////////////////////

			case '^':{
				if(equ_bas_freq[0] < 4){
					equ_bas_freq[0] += 1;
					setup(1, EQ_1_LOW_CUTOFF, (equ_bas_vol[0]) | (equ_bas_freq[0] << EQ1CF), equ_bas_freq[0], REG_EBF0, "equ bas 1 freq band: ");
				};
				break;
			};

			case 'Y':{
				if(equ_bas_freq[0] > 1){
					equ_bas_freq[0] -= 1;
					setup(1, EQ_1_LOW_CUTOFF, (equ_bas_vol[0]) | (equ_bas_freq[0] << EQ1CF), equ_bas_freq[0], REG_EBF0, "equ bas 1 freq band: ");
				};
				break;
			};

			//////////////////////////////////////////////////////////////////////////

			case '&':{
				if(equ_bas_freq[1] < 4){
					equ_bas_freq[1] += 1;
					setup(1, EQ_2_PEAK_1, (equ_bas_vol[1]) | (equ_bas_freq[1] << EQ2CF), equ_bas_freq[1], REG_EBF1, "equ bas 2 freq band: ");
				};
				break;
			};

			case 'U':{
				if(equ_bas_freq[1] > 1){
					equ_bas_freq[1] -= 1;
					setup(1, EQ_2_PEAK_1, (equ_bas_vol[1]) | (equ_bas_freq[1] << EQ2CF), equ_bas_freq[1], REG_EBF1, "equ bas 2 freq band: ");
				};
				break;
			};

			//////////////////////////////////////////////////////////////////////////

			case '*':{
				if(equ_bas_freq[2] < 4){
					equ_bas_freq[2] += 1;
					setup(1, EQ_3_PEAK_2, (equ_bas_vol[2]) | (equ_bas_freq[2] << EQ3CF), equ_bas_freq[2], REG_EBF2, "equ bas 3 freq band: ");
				};
				break;
			};

			case 'I':{
				if(equ_bas_freq[2] > 1){
					equ_bas_freq[2] -= 1;
					setup(1, EQ_3_PEAK_2, (equ_bas_vol[2]) | (equ_bas_freq[2] << EQ3CF), equ_bas_freq[2], REG_EBF2, "equ bas 3 freq band: ");
				};
				break;
			};

			//////////////////////////////////////////////////////////////////////////


			case '(':{
				if(equ_bas_freq[3] < 4){
					equ_bas_freq[3] += 1;
					setup(1, EQ_4_PEAK_3, (equ_bas_vol[3]) | (equ_bas_freq[3] << EQ4CF), equ_bas_freq[3], REG_EBF3, "equ bas 4 freq band: ");
				};
				break;
			};

			case 'O':{
				if(equ_bas_freq[3] > 1){
					equ_bas_freq[3] -= 1;
					setup(1, EQ_4_PEAK_3, (equ_bas_vol[3]) | (equ_bas_freq[3] << EQ4CF), equ_bas_freq[3], REG_EBF3, "equ bas 4 freq band: ");
				};
				break;
			};

			//////////////////////////////////////////////////////////////////////////

			case ')':{
				if(equ_bas_freq[4] < 4){
					equ_bas_freq[4] += 1;
					setup(1, EQ5_HIGH_CUTOFF, (equ_bas_vol[4]) | (equ_bas_freq[4] << EQ5CF), equ_bas_freq[4], REG_EBF4, "equ bas 5 freq band: ");
				};
				break;
			};

			case 'P':{
				if(equ_bas_freq[4] > 1){
					equ_bas_freq[4] -= 1;
					setup(1, EQ5_HIGH_CUTOFF, (equ_bas_vol[4]) | (equ_bas_freq[4] << EQ5CF), equ_bas_freq[4], REG_EBF4, "equ bas 5 freq band: ");
				};
				break;
			};
			default:break;
		};

		led1.flip();
	};
};


// kodek, rejestr, wartoœæ, eeprom reg i napis
void setup(uint8_t kodek, uint8_t nau_reg, uint16_t nau_val, uint8_t nau_part_val, uint8_t* eepreg, char* info){
	if(kodek == 0){
		// nau8822_register_write
		nau8822_register_write(nau_reg, nau_val);
	};
	if(kodek == 1){
		//nau2.write
		nau2.write(nau_reg, nau_val);
	};

	eeprom_write_byte(eepreg, nau_part_val);

	char r[50];
	char num1[10];
	itoa(nau_part_val, num1, 10);
	sprintf(r, "%s %s \r\n", info, num1);
	Serial.write(r);
};

