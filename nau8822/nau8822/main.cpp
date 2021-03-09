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

int main(void)
{

	Serial.SetUbrr(103);
	Serial.SetUbrr(103); // 9600

	s_audio_interface i2s = { .bclkp=0, .lrp=0, .wlen=WLEN_16, .aifmt=I2S_STANDARD, .dacphs=0, .adcphs=0, .mono=0 };
	nau8822_set_audio_interface(&i2s);

	s_power_1 power_1 = { .dcbufen=1,.aux1mxen=1,.aux2mxen=1,.pllen=0,.micbiasen=1,.abiasen=1,.iobufen=1,.refimp=REFIMP_3k };
	uint16_t t = nau8822_set_power_1(&power_1);

	s_power_2 power_2 = { .rhpen=1,.lhpen=1,.sleep=0,.rbsten=1,.lbsten=1,.rpgaen=1,.lpgaen=1,.radcen=1,.ladcen=1 };
	nau8822_set_power_2(&power_2);

	s_power_3 power_3 = { .auxout1en=1,.auxout2en=1,.lspken=1,.rspken=1,.rmixen=1,.lmixen=1,.rdacen=1,.ldacen=1 };
	nau8822_set_power_3(&power_3);

	power_1.dcbufen = 1;
	power_1.iobufen = 0;
	t = nau8822_set_power_1(&power_1);

	nau8822_equ_band_1(e_eb1_175, 0);
	nau8822_equ_band_2(e_eb2_385, 0);
	nau8822_equ_band_3(e_eb3_1400, 0);
	nau8822_equ_band_4(e_eb4_2400, 0);
	nau8822_equ_band_5(e_eb5_5300, 0);

	// alc setup
	// read carefull datasheet
	// https://www.nuvoton.com/resource-files/NAU8822LDataSheetRev1.9.pdf

	s_alc_control_1 alcr1 = { .alcen=ALCEN_BOOTH_EN, .alcmxgain=7, .alcmngain=0 };
	s_alc_control_2 alcr2 = { .alcht=10, .alcsl=5 };
	s_alc_control_3 alcr3 = { .alcm=0, .alcdcy=5, .alcatk=10 };
	s_noise_gate noisegate= { .alcnen=0, .alcnth=4 };

	// on avr i cant use non-trival list initializer
	// and you can't make pointer to bitfield
	// so you have to do this way or look at example with power_1
	snau8822.alc_control_1 = alcr1;
	snau8822.alc_control_2 = alcr2;
	snau8822.alc_control_3 = alcr3;
	snau8822.noise_gate = noisegate;

	nau8822_set_alc();


	uint8_t lsb = t;
	uint8_t msb = t >> 8;

    /* Replace with your application code */
    while (1)
    {
		delay(0xFFFFF);
		Serial.write( (uint8_t)(msb) );
		Serial.write( (uint8_t)(lsb) );
    }
}

