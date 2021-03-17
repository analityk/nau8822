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

	nau8822_register_write(0,0);

	nau8822_power_up();

	//s_audio_interface i2s = { .bclkp=0, .lrp=0, .wlen=WLEN_16, .aifmt=I2S_STANDARD, .dacphs=0, .adcphs=0, .mono=0 };
	//nau8822_set_audio_interface(&i2s);

	nau8822_mic_bias_voltage(e_mbl_85);

	nau8822_left_pga_in_src(e_left_pga_mic, 20);
	nau8822_left_main_mix_src(e_lmm_LeftInputMixer, 1);

	//nau8822_equ_band_1(e_eb1_175, 0);
	//nau8822_equ_band_2(e_eb2_385, 0);
	//nau8822_equ_band_3(e_eb3_1400, 0);
	//nau8822_equ_band_4(e_eb4_2400, 0);
	//nau8822_equ_band_5(e_eb5_5300, 0);
//
	//// alc setup
	//// read carefull datasheet
	//// https://www.nuvoton.com/resource-files/NAU8822LDataSheetRev1.9.pdf
//
	s_alc_control_1 alcr1 = { .alcen=ALCEN_BOOTH_EN, .alcmxgain=7, .alcmngain=0 };
	s_alc_control_2 alcr2 = { .alcht=14, .alcsl=12 };
	s_alc_control_3 alcr3 = { .alcm=0, .alcdcy=8, .alcatk=2 };
	s_noise_gate noisegate= { .alcnen=0, .alcnth=4 };
//
	//// on avr i cant use non-trival list initializer
	//// and you can't make pointer to bitfield
	//// so you have to do this way or look at example with power_1
	snau8822.alc_control_1 = alcr1;
	snau8822.alc_control_2 = alcr2;
	snau8822.alc_control_3 = alcr3;
	snau8822.noise_gate = noisegate;
	nau8822_set_alc();

	nau8822_headphone_volume(11, 11);
//
	//uint8_t lsb = t;
	//uint8_t msb = t >> 8;



    /* Replace with your application code */
    while (1)
    {
		delay(0xFF);
    }
}

