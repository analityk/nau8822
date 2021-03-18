#include <nau8822_code/nau8822.h>

ts_nau8822 snau8822;



void nau8822_mute_all(void)
{
	s_input_control ic = { .micbiasv=0,.rlinrpga=0,.rmicnrpga=0,.rmicprpga=0,.llinlpga=0,.lmicnlpga=0,.lmicplpga=0 };
	snau8822.input_control = ic;
	nau8822_set_input_control(&snau8822.input_control);

	snau8822.right_speaker_submixer.rauxmut = 1;
	snau8822.right_speaker_submixer.rmixmut = 1;
	nau8822_set_right_speaker_submixer(&snau8822.right_speaker_submixer);

	snau8822.lhp_volume.lhpmute = 1;
	nau8822_set_lhp_vol(&snau8822.lhp_volume);

	snau8822.rhp_volume.rhpmute = 1;
	nau8822_set_rhp_vol(&snau8822.rhp_volume);

	snau8822.lspkput_volume.lspkmute = 1;
	nau8822_set_lspkout_vol(&snau8822.lspkput_volume);

	snau8822.rspkput_volume.rspkmute = 1;
	nau8822_set_rspkout_vol(&snau8822.rspkput_volume);

	snau8822.aux_1_mixer.auxout1mt = 1;
	nau8822_set_aux_1_mix(&snau8822.aux_1_mixer);

	snau8822.aux_2_mixer.auxout2mt = 1;
	nau8822_set_aux_2_mix(&snau8822.aux_2_mixer);
};

#ifdef __cplusplus
extern "C" {
#endif

void nau8822_power_up(void)
{
	nau8822_mute_all();
	snau8822.clock_contorl_1.bclksel = 2;
	snau8822.clock_contorl_1.clkioen = 1;
	snau8822.clock_contorl_1.mclksel = 2;
	snau8822.clock_contorl_1.clkm = 1;
	nau8822_set_clock_control_1(&snau8822.clock_contorl_1);

	s_power_1 power_1 = { .dcbufen=1, .aux1mxen=1, .aux2mxen=1, .pllen=0, .micbiasen=1, .abiasen=1, .iobufen=1, .refimp=REFIMP_3k };
	nau8822_set_power_1(&power_1);

	s_power_2 power_2 = { .rhpen=1, .lhpen=1, .sleep=0, .rbsten=1, .lbsten=1, .rpgaen=1, .lpgaen=1, .radcen=1, .ladcen=1 };
	nau8822_set_power_2(&power_2);

	s_power_3 power_3 = { .auxout1en=1, .auxout2en=1, .lspken=1, .rspken=1, .rmixen=1, .lmixen=1, .rdacen=1, .ldacen=1 };
	nau8822_set_power_3(&power_3);

	//uint32_t naupllcfg = 0x86c226;
//
	//uint16_t a =  naupllcfg;
	//uint16_t b = (naupllcfg >> 9);
	//uint16_t c = (naupllcfg >> 18);
//
	//snau8822.pll_n.plln = 8;
	//nau8822_set_plln(&snau8822.pll_n);
//
	//snau8822.pll_k1.pllk1 = a;
	//nau8822_set_pllk1(&snau8822.pll_k1);
//
	//snau8822.pll_k2.pllk2 = b;
	//nau8822_set_pllk2(&snau8822.pll_k2);
//
	//snau8822.pll_k3.pllk3 = c;
	//nau8822_set_pllk3(&snau8822.pll_k3);

	nau8822_register_write(36, 0x007);
	nau8822_register_write(37, 0x0a1); // im wiêksza wartoœæ tym szybciej odtwarza
	nau8822_register_write(38, 0x15f);
	nau8822_register_write(39, 0x126);

	power_1.pllen = 1;
	nau8822_set_power_1(&power_1);

};

uint16_t nau8822_mic_bias_voltage(enum e_mic_bias_levels mbl)
{
	switch(mbl){
		case e_mbl_50:{
			snau8822.input_control.micbiasv = 3;
			break;
		};
		case e_mbl_60:{
			snau8822.input_control.micbiasv = 1;
			break;
		};
		case e_mbl_70:{
			snau8822.input_control.micbiasv = 2;
			break;
		};
		case e_mbl_85:{
			snau8822.input_control.micbiasv = 0;
			break;
		};
		default:break;
	};
	return nau8822_set_input_control(&snau8822.input_control);
};

uint16_t nau8822_3d_enhancement(uint8_t level)
{
	if(level < 16){
		snau8822.depth_3d.depth3d = level;
	};
	return nau8822_set_3d_depth(&snau8822.depth_3d);
};

uint16_t nau8822_equ_src(enum e_equ_src es)
{
	switch(es){
		case e_es_ADC:{
			snau8822.eq1.eqm = 0;
			break;
		};
		case e_es_DAC:{
			snau8822.eq1.eqm = 1;
			break;
		};
		default:break;
	};
	return nau8822_set_eq1(&snau8822.eq1);
};

uint16_t nau8822_equ_band_1(enum e_equ_band_1 eb1, int8_t level)
{
	switch(eb1){
		case e_eb1_80:{
			snau8822.eq1.eq1cf = 0;
			break;
		};
		case e_eb1_105:{
			snau8822.eq1.eq1cf = 0;
			break;
		};
		case e_eb1_135:{
			snau8822.eq1.eq1cf = 0;
			break;
		};
		case e_eb1_175:{
			snau8822.eq1.eq1cf = 0;
			break;
		};
		default:break;
	};
	if( level >= -12 && level < 12){
		uint8_t gain = (uint8_t)(level + 12);
		snau8822.eq1.eq1gc = gain;
	};
	return nau8822_set_eq1(&snau8822.eq1);
};

uint16_t nau8822_equ_band_2(enum e_equ_band_2 eb2, int8_t level)
{
	switch(eb2){
		case e_eb2_230:{
			snau8822.eq2.eq2cf = 0;
			break;
		};
		case e_eb2_300:{
			snau8822.eq2.eq2cf = 1;
			break;
		};
		case e_eb2_385:{
			snau8822.eq2.eq2cf = 2;
			break;
		};
		case e_eb2_500:{
			snau8822.eq2.eq2cf = 3;
			break;
		};
		default:break;
	};
	if( level >= -12 && level < 12){
		uint8_t gain = (uint8_t)(level + 12);
		snau8822.eq2.eq2gc = gain;
	};
	return nau8822_set_eq2(&snau8822.eq2);
};

uint16_t nau8822_equ_band_3(enum e_equ_band_3 eb3, int8_t level)
{
	switch(eb3){
		case e_eb3_650:{
			snau8822.eq3.eq3cf = 0;
			break;
		};
		case e_eb3_850:{
			snau8822.eq3.eq3cf = 1;
			break;
		};
		case e_eb3_1100:{
			snau8822.eq3.eq3cf = 2;
			break;
		};
		case e_eb3_1400:{
			snau8822.eq3.eq3cf = 3;
			break;
		};
		default:break;
	};
	if( level >= -12 && level < 12){
		uint8_t gain = (uint8_t)(level + 12);
		snau8822.eq3.eq3gc = gain;
	};
	return nau8822_set_eq3(&snau8822.eq3);
};

uint16_t nau8822_equ_band_4(enum e_equ_band_4 eb4, int8_t level)
{
	switch(eb4){
		case e_eb4_1800:{
			snau8822.eq4.eq4cf = 0;
			break;
		};
		case e_eb4_2400:{
			snau8822.eq4.eq4cf = 1;
			break;
		};
		case e_eb4_3200:{
			snau8822.eq4.eq4cf = 2;
			break;
		};
		case e_eb4_4100:{
			snau8822.eq4.eq4cf = 3;
			break;
		};
		default:break;
	};
	if( level >= -12 && level < 12){
		uint8_t gain = (uint8_t)(level + 12);
		snau8822.eq4.eq4gc = gain;
	};
	return nau8822_set_eq4(&snau8822.eq4);
};

uint16_t nau8822_equ_band_5(enum e_equ_band_5 eb5, int8_t level)
{
	switch(eb5){
		case e_eb5_5300:{
			snau8822.eq5.eq5cf = 0;
			break;
		};
		case e_eb5_6900:{
			snau8822.eq5.eq5cf = 1;
			break;
		};
		case e_eb5_9000:{
			snau8822.eq5.eq5cf = 2;
			break;
		};
		case e_eb5_11700:{
			snau8822.eq5.eq5cf = 3;
			break;
		};
		default:break;
	};
	if( level >= -12 && level < 12){
		uint8_t gain = (uint8_t)(level + 12);
		snau8822.eq5.eq5gc = gain;
	};
	return nau8822_set_eq5(&snau8822.eq5);
};

uint16_t nau8822_headphone_volume(uint8_t left, uint8_t right)
{
	if( (left < 64) && (right < 64) ){
		snau8822.lhp_volume.lhpgain = left;
		snau8822.rhp_volume.rhpgain = right;
	};

	snau8822.lhp_volume.lhpmute = 0;
	snau8822.rhp_volume.rhpmute = 0;

	nau8822_set_rhp_vol(&snau8822.rhp_volume);
	nau8822_set_lhp_vol(&snau8822.lhp_volume);
	return 0;
};

uint16_t nau8822_speaker_volume(uint8_t left, uint8_t right)
{
	if( (left < 64) && (right < 64) ){
		snau8822.rspkput_volume.rspkgain = right;
		snau8822.lspkput_volume.lspkgain = left;
	};
	uint16_t t = nau8822_set_rspkout_vol(&snau8822.rspkput_volume) << 8;
	t = nau8822_set_lspkout_vol(&snau8822.lspkput_volume);
	return t;
};

uint16_t nau8822_left_in_mix_src(enum e_left_in_mix_srcs ms, uint8_t gain)
{
	switch(ms){
		case e_lim_LeftAux:{
			break;
		};
		case e_lim_LeftLine:{
			break;
		};
		case e_lim_Left_PGA:{
			break;
		};
		default:break;
	};
	return 0;
};

uint16_t nau8822_left_pga_in_src(enum e_left_pga_src ms, uint8_t gain)
{
	switch(ms){
		case e_left_pga_mic:{
			snau8822.input_control.llinlpga = 0;
			snau8822.input_control.lmicnlpga = 1;
			snau8822.input_control.lmicplpga = 1;
			nau8822_set_input_control(&snau8822.input_control);

			if( (gain >= 0) && (gain <= 0x3F) ){
				snau8822.left_input_pga.lpgagain = gain;
			};

			snau8822.left_input_pga.lpgau = 1;
			snau8822.left_input_pga.lpgazc = 1;
			snau8822.left_input_pga.lpgamt = 0;
			nau8822_set_left_pga(&snau8822.left_input_pga);

			break;
		};
		case e_left_pga_lin:{
			snau8822.input_control.llinlpga = 1;
			snau8822.input_control.lmicnlpga = 0;
			snau8822.input_control.lmicplpga = 0;

			if( (gain >= 0) && (gain <= 0x3F) ){
				snau8822.left_input_pga.lpgagain = gain;
			};

			snau8822.left_input_pga.lpgau = 1;
			snau8822.left_input_pga.lpgazc = 1;
			snau8822.left_input_pga.lpgamt = 0;
			nau8822_set_left_pga(&snau8822.left_input_pga);
			break;
		};
		default:break;
	};
	return 0;
};

uint16_t nau8822_right_pga_in_src(enum e_right_pga_src ms, uint8_t gain)
{
	switch(ms){
		case e_left_pga_mic:{
			snau8822.input_control.rlinrpga = 0;
			snau8822.input_control.rmicnrpga = 1;
			snau8822.input_control.rmicprpga = 1;
			nau8822_set_input_control(&snau8822.input_control);

			if( (gain >= 0) && (gain <= 0x3F) ){
				snau8822.right_input_pga.rpgagain = gain;
			};

			snau8822.right_input_pga.rpgau = 1;
			snau8822.right_input_pga.rpgazc = 1;
			snau8822.right_input_pga.rpgamt = 0;
			nau8822_set_right_pga(&snau8822.right_input_pga);

			break;
		};
		case e_left_pga_lin:{
			snau8822.input_control.rlinrpga = 1;
			snau8822.input_control.rmicnrpga = 0;
			snau8822.input_control.rmicprpga = 0;

			if( (gain >= 0) && (gain <= 0x3F) ){
				snau8822.right_input_pga.rpgagain = gain;
			};

			snau8822.right_input_pga.rpgau = 1;
			snau8822.right_input_pga.rpgazc = 1;
			snau8822.right_input_pga.rpgamt = 0;
			nau8822_set_right_pga(&snau8822.right_input_pga);
			break;
		};
		default:break;
	};
	return 0;
}

uint16_t nau8822_left_main_mix_src(enum e_left_main_mix_srcs ms, uint8_t gain)
{
	switch(ms){
		case e_lmm_LeftAux:{
			if(gain > 7){
				gain = 7;
			};
			snau8822.left_mixer.lauxlmx = 1;
			snau8822.left_mixer.lauxmxgain = gain;
			nau8822_set_left_main_mixer(&snau8822.left_mixer);
			break;
		};

		case e_lmm_LeftDAC:{
			if(gain > 255){
				gain = 255;
			};
			snau8822.left_dac_volume.ldacvu = 1;
			snau8822.left_dac_volume.ldacgain = gain;
			nau8822_set_left_dac_vol(&snau8822.left_dac_volume);

			snau8822.left_mixer.ldaclmx = 1;
			nau8822_set_left_main_mixer(&snau8822.left_mixer);
			break;
		};

		case e_lmm_RightDAC:{
			snau8822.right_mixer.rdacrmx = 0;
			nau8822_set_right_main_mixer(&snau8822.right_mixer);

			snau8822.output_control.rdaclmx = 1;
			nau8822_set_output_control(&snau8822.output_control);
			break;
		};

		case e_lmm_LeftInputMixer:{
			if(gain > 7){
				gain = 7;
			};
			snau8822.left_mixer.lbyplmx = 1;
			snau8822.left_mixer.lbypmxgain = gain;
			nau8822_set_left_main_mixer(&snau8822.left_mixer);
			break;
		};
		default:break;
	};
	return 0;
};

uint16_t nau8822_right_main_mix_src(enum e_right_main_mix_srcs ms, uint8_t gain)
{
	switch(ms){
		case e_rmm_RightAux:{
			if(gain > 7){
				gain = 7;
			};
			snau8822.right_mixer.rauxrmx = 1;
			snau8822.right_mixer.rbypmxgain = gain;
			nau8822_set_right_main_mixer(&snau8822.right_mixer);
			break;
		};

		case e_rmm_RightDAC:{
			if(gain > 255){
				gain = 255;
			};
			snau8822.right_dac_volume.rdacvu = 1;
			snau8822.right_dac_volume.rdacgain = gain;
			nau8822_set_right_dac_vol(&snau8822.right_dac_volume);

			snau8822.right_mixer.rdacrmx = 1;
			nau8822_set_right_main_mixer(&snau8822.right_mixer);
			break;
		};

		case e_rmm_LeftDAC:{
			snau8822.left_mixer.ldaclmx = 0;
			nau8822_set_left_main_mixer(&snau8822.left_mixer);

			snau8822.output_control.ldacrmx = 1;
			nau8822_set_output_control(&snau8822.output_control);
			break;
		};

		case e_rmm_RightInputMixer:{
			if(gain > 7){
				gain = 7;
			};
			snau8822.right_mixer.rbyprmx = 1;
			snau8822.right_mixer.rbypmxgain = gain;
			nau8822_set_right_main_mixer(&snau8822.right_mixer);
			break;
		};
		default:break;
	};
	return 0;
}

void nau8822_set_alc(void)
{
	nau8822_set_alc_1(&snau8822.alc_control_1);
	nau8822_set_alc_2(&snau8822.alc_control_2);
	nau8822_set_alc_3(&snau8822.alc_control_3);
	nau8822_set_noise_gate(&snau8822.noise_gate);
};

uint16_t nau8822_set_power_1(s_power_1* pw)
{
	uint16_t t = (pw->abiasen << ABIASEN) | (pw->aux1mxen << AUX1MXEN) | (pw->aux2mxen << AUX2MXEN) | (pw->dcbufen << DCBUFEN) |
				  (pw->iobufen << IOBUFEN) | (pw->micbiasen << MICBIASEN ) | (pw->pllen << PLLEN) | (pw->refimp << REFIMP);
	nau8822_register_write(POWER_MANAGMENT_1, t);
	return t;
};

uint16_t nau8822_set_power_2(s_power_2* pw)
{
	uint16_t t = (pw->ladcen << LADCEN) | (pw->lbsten << LBSTEN) | (pw->lhpen << LHPEN) | (pw->lpgaen << LPGAEN) |
				 (pw->radcen << RADCEN) | (pw->rbsten << RBSTEN) | (pw->rhpen << RHPEN) | (pw->rpgaen << RPGAEN) | (pw->sleep << SLEEP);
	nau8822_register_write(POWER_MANAGMENT_2, t);
	return t;
};

uint16_t nau8822_set_power_3(s_power_3* pw)
{
	uint16_t t = (pw->auxout1en << AUXOUT1EN) | (pw->auxout2en << AUXOUT2EN) | (pw->ldacen << LDACEN) | (pw->lmixen << LMIXEN) | (pw->lspken << LSPKEN) |
				 (pw->rdacen << RDACEN) | (pw->rmixen << RMIXEN) | (pw->rspken << RSPKEN);
	nau8822_register_write(POWER_MANAGMENT_3, t);
	return t;
};

uint16_t nau8822_set_power_4(s_power_4* pw)
{
	uint16_t t = (pw->ibadj << IBADJ) | (pw->lpadc << LPADC) | (pw->lpipbst << LPIPBST) | (pw->lpspkd << LPSPKD) | (pw->micbiasm << MICBIASM) | (pw->regvolt << REGVOLT);
	nau8822_register_write(POWER_MANAGMENT_4, t);
	return t;
};

uint16_t nau8822_set_audio_interface(s_audio_interface* ai)
{
	uint16_t t = (ai->bclkp << BCLKP) | (ai->lrp << LRP) | (ai->wlen << WLEN) | (ai->aifmt << AIFMT) | (ai->dacphs << DACPHS) | (ai->adcphs << ADCPHS) | (ai->mono << MONO);
	nau8822_register_write(AUDIO_INTERFACE, t);
	return t;
};

uint16_t nau8822_set_companding(s_companding* c)
{
	uint16_t t = (c->adccm << ADCCM) | (c->addap << ADDAP) | (c->cmb8 << CMB8) | (c->daccm << DACCM);
	nau8822_register_write(COMPANDING, t);
	return t;
};

uint16_t nau8822_set_clock_control_1(s_clock_control_1* c)
{
	uint16_t t = (c->bclksel << BCLKSEL) | (c->clkioen << CLKIOEN) | (c->clkm << CLKM) | (c->mclksel << MCLKSEL);
	nau8822_register_write(CLOCK_CONTROL_1, t);
	return t;
};

uint16_t nau8822_set_clock_control_2(s_clock_control_2* c)
{
	uint16_t t = (c->sclken << SCLKEN) | (c->smplr << SMPLR) | (c->wspien4 << WSPIEN_4);
	nau8822_register_write(CLOCK_CONTROL_2, t);
	return t;
};

uint16_t nau8822_set_gpio(s_gpio* g)
{
	uint16_t t = (g->gpio1pl << GPIO1PL) | (g->gpio1pll << GPIO1PLL) | (g->gpio1sel << GPIO1SEL);
	nau8822_register_write(NAU_GPIO, t);
	return t;
};

uint16_t nau8822_set_jack_detect_1(s_jack_detect_1* j)
{
	uint16_t t = (j->jacden << JACDEN) | (j->jckdio << JCKDIO) | (j->jckmiden << JCKMIDEN);
	nau8822_register_write(JACK_DETECT_1, t);
	return t;
};

uint16_t nau8822_set_dac_control(s_dac_control* d)
{
	uint16_t t = (d->automt << AUTOMT) | (d->dacos << DACOS) | (d->ldacpl << LDACPL) | (d->rdacpl << RDACPL) | (d->softmt << SOFTMT);
	nau8822_register_write(DAC_CONTROL, t);
	return t;
};

uint16_t nau8822_set_left_dac_vol(s_left_dac_volume* d)
{
	uint16_t t = (d->ldacgain << LDACGAIN) | (d->ldacvu << LDACVU);
	nau8822_register_write(LEFT_DAC_VOLUME, t);
	return t;
};

uint16_t nau8822_set_right_dac_vol(s_right_dac_volume* d)
{
	uint16_t t = (d->rdacgain << RDACGAIN) | (d->rdacvu << RDACVU);
	nau8822_register_write(RIGHT_DAC_VOLUME, t);
	return t;
};

uint16_t nau8822_set_jack_detect_2(s_jack_detect_2* j)
{
	uint16_t t = (j->jckdoen0 << JCKDOEN0) | (j->jckdoen1 << JCKDOEN1);
	nau8822_register_write(JACK_DETECT_2, t);
	return t;
};

uint16_t nau8822_set_adc_control(s_adc_control* c)
{
	uint16_t t = (c->adcos << ADCOS) | (c->hpf << HPF) | (c->hpfam << HPFAM) | (c->hpfen << HPFEN) | (c->ladcpl << LADCPL) | (c->radcpl << RADCPL);
	nau8822_register_write(ADC_CONTROL, t);
	return t;
};

uint16_t nau8822_set_left_adc_vol(s_left_adc_volume* c)
{
	uint16_t t = (c->ladcgain << LADCGAIN) | (c->ladcvu << LADCVU);
	nau8822_register_write(LEFT_ADC_VOLUME, t);
	return t;
};

uint16_t nau8822_set_right_adc_vol(s_right_adc_volume* c)
{
	uint16_t t = (c->radcgain << RADCGAIN) | (c->radcvu << RADCVU);
	nau8822_register_write(RIGHT_ADC_VOLUME, t);
	return t;
};

uint16_t nau8822_set_eq1(s_eq1* e)
{
	uint16_t t = (e->eq1cf << EQ1CF) | (e->eq1gc << EQ1GC) | (e->eqm << EQM);
	nau8822_register_write(EQ_1_LOW_CUTOFF, t);
	return t;
};

uint16_t nau8822_set_eq2(s_eq2* e)
{
	uint16_t t = (e->eq2bw << EQ2BW) | (e->eq2cf << EQ2CF) | (e->eq2gc << EQ2GC);
	nau8822_register_write(EQ_2_PEAK_1, t);
	return t;
};

uint16_t nau8822_set_eq3(s_eq3* e)
{
	uint16_t t = (e->eq3bw << EQ3BW) | (e->eq3cf << EQ3CF) | (e->eq3gc << EQ3CF);
	nau8822_register_write(EQ_3_PEAK_2, t);
	return t;
};

uint16_t nau8822_set_eq4(s_eq4* e)
{
	uint16_t t = (e->eq4bw << EQ4BW) | (e->eq4cf << EQ4CF) | (e->eq4gc << EQ4GC);
	nau8822_register_write(EQ_4_PEAK_3, t);
	return t;
};

uint16_t nau8822_set_eq5(s_eq5* e)
{
	uint16_t t = (e->eq5cf << EQ5CF) | (e->eq5gc << EQ5GC);
	nau8822_register_write(EQ5_HIGH_CUTOFF, t);
	return t;
};

uint16_t nau8822_set_dac_lim_1(s_dac_limiter_1* d)
{
	uint16_t t = (d->daclimatk << DACLIMATK) | (d->daclimdcy << DACLIMDCY) | (d->daclimen << DACLIMEN);
	nau8822_register_write(DAC_LIMITER_1, t);
	return t;
};

uint16_t nau8822_set_dac_lim_2(s_dac_limiter_2* d)
{
	uint16_t t = (d->daclimbst << DACLIMBST) | (d->daclimthl << DACLIMTHL);
	nau8822_register_write(DAC_LIMITER_2, t);
	return t;
};

uint16_t nau8822_set_notch_1(s_notch_filter_1* n)
{
	uint16_t t = (n->nfcu1 << NFCU1) | (n->nfcen << NFCEN) | (n->nfca0h << NFCA0H);
	nau8822_register_write(NOTCH_FILTER_1, t);
	return t;
};

uint16_t nau8822_set_notch_2(s_notch_filter_2* n)
{
	uint16_t t = (n->nfca0l << NFCA0L) | (n->nfcu2 << NFCU2);
	nau8822_register_write(NOTCH_FILTER_2, t);return t;
};

uint16_t nau8822_set_notch_3(s_notch_filter_3* n)
{
	uint16_t t = (n->nfca1h << NFCA1H) | (n->nfcu3 << NFCU3);
	nau8822_register_write(NOTCH_FILTER_3, t);return t;
};

uint16_t nau8822_set_notch_4(s_notch_filter_4* n)
{
	uint16_t t = (n->nfca1l << NFCA1L) | (n->nfcu4 << NFCU4);
	nau8822_register_write(NOTCH_FILTER_4, t);return t;
};

uint16_t nau8822_set_alc_1(s_alc_control_1* a)
{
	uint16_t t = (a->alcen << ALCEN) | (a->alcmngain << ALCMNGAIN) | (a->alcmxgain << ALCMXGAIN);
	nau8822_register_write(ALC_CONTROL_1, t);return t;
};

uint16_t nau8822_set_alc_2(s_alc_control_2* a)
{
	uint16_t t = (a->alcht << ALCHT) | (a->alcsl << ALCSL);
	nau8822_register_write(ALC_CONTROL_2, t);return t;
};

uint16_t nau8822_set_alc_3(s_alc_control_3* a)
{
	uint16_t t = (a->alcatk << ALCATK) | (a->alcdcy << ALCDCY) | (a->alcm << ALCM);
	nau8822_register_write(ALC_CONTROL_3, t);return t;
};

uint16_t nau8822_set_noise_gate(s_noise_gate* n)
{
	uint16_t t = (n->alcnen << ALCNEN) | (n->alcnth << ALCNTH);
	nau8822_register_write(NOISE_GATE, t);return t;
};

uint16_t nau8822_set_plln(s_pll_n* p)
{
	uint16_t t = (p->pllmclk << PLLMCLK) | (p->plln << PLLN);
	nau8822_register_write(PLLN_N, t);return t;
}

uint16_t nau8822_set_pllk1(s_pll_k1* k)
{
	uint16_t t = (k->pllk1 << 0);
	nau8822_register_write(PLL_K_1, t);return t;
};

uint16_t nau8822_set_pllk2(s_pll_k2* k)
{
	uint16_t t = (k->pllk2 << 0);
	nau8822_register_write(PLL_K_2, t);return t;
};

uint16_t nau8822_set_pllk3(s_pll_k3* k)
{
	uint16_t t = (k->pllk3 << 0);
	nau8822_register_write(PLL_K_3, t);return t;
};

uint16_t nau8822_set_3d_depth(s_depth_3d* k)
{
	uint16_t t = (k->depth3d << DEPTH_3D);
	nau8822_register_write(CONTROL_3D, t);
	return t;
};

uint16_t nau8822_set_right_speaker_submixer(s_right_speaker_submixer* s)
{
	uint16_t t = (s->rauxmut << RAUXMUT) | (s->rauxrsubg << RAUXRSUBG) | (s->rmixmut << RMIXMUT) | (s->rsubbyp << RSUBBYP);
	nau8822_register_write(RIGHT_SPEAKER_SUBMIXER, t);
	return t;
};

uint16_t nau8822_set_input_control(s_input_control* c)
{
	uint16_t t = (c->llinlpga << LLINLPGA) | (c->lmicnlpga << LMICNLPGA) | (c->lmicplpga << LMICPLPGA) | (c->micbiasv << MICBIASV) |
				 (c->rlinrpga << RLINRPGA) | (c->rmicnrpga << RMICNRPGA) | (c->rmicprpga << RMICPRPGA);
	nau8822_register_write(INPUT_CONTROL, t);
	return t;
};

uint16_t nau8822_set_left_pga(s_left_input_pga* p)
{
	uint16_t t = (p->lpgagain << LPGAGAIN) | (p->lpgamt << LPGAMT) | (p->lpgau << LPGAU) | (p->lpgazc << LPGAZC);
	nau8822_register_write(LEFT_INPUT_PGA_GAIN, t);
	return t;
};

uint16_t nau8822_set_right_pga(s_right_input_pga* p)
{
	uint16_t t = (p->rpgagain << RPGAGAIN) | (p->rpgamt << RPGAMT) | (p->rpgau << RPGAU) | (p->rpgazc << RPGAZC);
	nau8822_register_write(RIGHT_INPUT_PGA_GAIN, t);
	return t;
};

uint16_t nau8822_set_left_adc_boost(s_left_adc_boost* b)
{
	uint16_t t = (b->lauxbstgain << LAUXBSTGAIN) | (b->lpgabst << LPGABST) | (b->lpgabstgain << LPGABSTGAIN);
	nau8822_register_write(LEFT_ADC_BOOST, t);
	return t;
};

uint16_t nau8822_set_right_adc_boost(s_right_adc_boost* b)
{
	uint16_t t = (b->rauxbstgain << RAUXBSTGAIN) | (b->rpgabst << RPGABST) | (b->rpgabstgain << RPGABSTGAIN);
	nau8822_register_write(RIGHT_ADC_BOOST, t);
	return t;
};

uint16_t nau8822_set_output_control(s_output_control* c)
{
	uint16_t t = (c->aoutimp << AOUTIMP) | (c->aux1bst << AUX1BST) | (c->aux2bst << AUX2BST) | (c->ldacrmx << LDACRMX) |
				 (c->rdaclmx << RDACLMX) | (c->spkbst << SPKBST) | (c->tsen << TSEN);
	nau8822_register_write(OUTPUT_CONTROL, t);
	return t;
};

uint16_t nau8822_set_left_main_mixer(s_left_mixer* m)
{
	uint16_t t = (m->lauxlmx << LAUXLMX) | (m->lauxmxgain << LAUXMXGAIN) | (m->lbyplmx << LBYPLMX) |
				 (m->lbypmxgain << LBYPMXGAIN) | (m->ldaclmx << LDACLMX);
	nau8822_register_write(LEFT_MIXER, t);
	return t;
};

uint16_t nau8822_set_right_main_mixer(s_right_mixer* m)
{
	uint16_t t = (m->rauxmxgain << RAUXMXGAIN) | (m->rauxrmx << RAUXRMX) | (m->rbypmxgain << RBYPMXGAIN) |
				 (m->rbyprmx << RBYPRMX) | (m->rdacrmx << RDACRMX);
	nau8822_register_write(RIGHT_MIXER, t);
	return t;
};

uint16_t nau8822_set_lhp_vol(s_lhp_volume* v)
{
	uint16_t t = (v->lhpgain << LHPGAIN) | (v->lhpmute << LHPMUTE) | (v->lhpvu << LHPVU) | (v->lhpzc << LHPZC);
	nau8822_register_write(LHP_VOLUME, t);
	return t;
};

uint16_t nau8822_set_rhp_vol(s_rhp_volume* v)
{
	uint16_t t = (v->rhpgain << RHPGAIN) | (v->rhpmute << RHPMUTE) | (v->rhpvu << RHPVU) | (v->rhpzc << RHPZC);
	nau8822_register_write(RHP_VOLUME, t);
	return t;
};

uint16_t nau8822_set_lspkout_vol(s_lspkput_volume* v)
{
	uint16_t t = (v->lspkgain << LSPKGAIN) | (v->lspkmute << LSPKMUTE) | (v->lspkvu << LSPKVU) | (v->lspkzc << LSPKZC);
	nau8822_register_write(LSPKOUT_VOLUME, t);
	return t;
};

uint16_t nau8822_set_rspkout_vol(s_rspkput_volume* v)
{
	uint16_t t = (v->rspkgain << RSPKGAIN) | (v->rspkmute << RSPKMUTE) | (v->rspkvu << RSPKVU) | (v->rspkzc << RSPKZC);
	nau8822_register_write(RSPKOUT_VOLUME, t);
	return t;
};

uint16_t nau8822_set_aux_2_mix(s_aux_2_mixer* m)
{
	uint16_t t = (m->aux1mix2 << AUX1MIX2) | (m->auxout2mt << AUXOUT2MT) | (m->ladcaux2 << LADCAUX2) | (m->ldacaux2 << LDACAUX2) |
				 (m->lmixaux2 << LMIXAUX2);
	nau8822_register_write(AUX2MIXER, t);
	return t;
};

uint16_t nau8822_set_aux_1_mix(s_aux_1_mixer* m)
{
	uint16_t t = (m->aux1half << AUX1HALF) | (m->auxout1mt << AUXOUT1MT) | (m->ldacaux1 << LDACAUX1) |
				 (m->lmixaux1 << LMIXAUX1) | (m->radcaux1 << RADCAUX1) | (m->rdacaux1 << RDACAUX1) | (m->rmixaux1 << RMIXAUX1);
	nau8822_register_write(AUX1MIXER, t);
	return t;
};

uint16_t nau8822_set_left_time_slot(s_left_time_slot* t)
{
	uint16_t q = (t->left_slot << 0);
	nau8822_register_write(LEFT_TIME_SLOT, q);
	return q;
};

uint16_t nau8822_set_right_time_slot(s_right_time_slot* t)
{
	uint16_t q = (t->right_slot << 0);
	nau8822_register_write(RIGHT_TIME_SLOT, q);
	return q;
};

uint16_t nau8822_set_misc(s_misc* m)
{
	uint16_t t = (m->ltslot << LTSLOT) | (m->pcm8bit << PCM8BIT) | (m->pcmtsen << PCMTSEN) | (m->puden << PUDEN) |
				 (m->pudpe << PUDPE) | (m->pudps << PUDPS) | (m->rtslot << RTSLOT) | (m->tri << TRI);
	nau8822_register_write(MISC, t);
	return t;
};

uint16_t nau8822_set_alc_enh_1(s_alc_enhancement_1* e)
{
	uint16_t t = (e->alcngsel << ALCNGSEL) | (e->alcpksel << ALCPKSEL) | (e->alctblsel << ALCTBLSEL);
	nau8822_register_write(ALC_ENHANCEMENT_1, t);
	return t;
};

uint16_t nau8822_set_alc_enh_2(s_alc_enhancement_2* e)
{
	uint16_t t = (e->alcgainr << ALCGAINR) | (e->pklimena << PKLIMENA);
	nau8822_register_write(ALC_ENHANCEMENT_2, t);
	return t;
};

uint16_t nau8822_set_oversampling(s_sampling_192khz* s)
{
	uint16_t t = (s->adc_osr32x << ADC_OSR32x) | (s->adcb_over << ADCB_OVER) | (s->dac_osr32x << DAC_OSR32x) | (s->pll49mout << PLL49MOUT);
	nau8822_register_write(SAMPLING_192KHZ, t);
	return t;
};

uint16_t nau8822_set_misc_ctrl(s_misc_controls* m)
{
	uint16_t t = (m->dacinmute << DACINMUTE) | (m->dacosr256 << DACOSR256) | (m->fserflsh << FSERFLSH) | (m->fserrena << FSERRENA) |
				 (m->fserrval << FSERRVAL) | (m->notchdly << NOTCHDLY) | (m->plllockbp << PLLLOCKBP) | (m->spiena_4w << SPIENA_4W);
	nau8822_register_write(MISC_CONTROLS, t);
	return t;
};

uint16_t nau8822_set_tieoff_1(s_tieoff_1* c)
{
	uint16_t t = (c->maninena << MANINENA) | (c->manlaux << MANLAUX) | (c->manllin << MANLLIN) | (c->manlmicn << MANLMICN) | ( c->manlmicp << MANLMICP) | ( c->manraux << MANRAUX) |
				 (c->manrlin << MANRLIN) | (c->manrmicn << MANRMICN) | (c->manrmicp << MANRMICP);
	nau8822_register_write(INPUT_TIE_OFF, t);
	return t;
};

uint16_t nau8822_set_tieoff_2(s_tieoff_2* c)
{
	uint16_t t = (c->ibt250dn << IBT250DN) | (c->ibt500up << IBT500UP) | (c->ibthalfi << IBTHALFI) | (c->maninbbp << MANINBBP) |
				 (c->maninpad << MANINPAD) | (c->manvrefh << MANVREFH) | (c->manvrefl << MANVREFL) | (c->manvrefm << MANVREFM);
	nau8822_register_write(POWER_REDUCTION, t);
	return t;
};

uint16_t nau8822_set_tieoff_3(s_tieoff_3* c)
{
	uint16_t t = (c->manouten << MANOUTEN) | (c->shrtaux1 << SHRTAUX1) | (c->shrtaux2 << SHRTAUX2) | (c->shrtbufh << SHRTBUFH) |
				 (c->shrtbufl << SHRTBUFL) | (c->shrtlhp << SHRTLHP) | (c->shrtlspk << SHRTLSPK) | (c->shrtrhp << SHRTRHP) |
				 (c->shrtrspk << SHRTRSPK);
	nau8822_register_write(OUTPUT_TIE_OFF, t);
	return t;
};

uint16_t nau8822_set_automute(s_automute_control* m)
{
	uint16_t t = (m->amutctrl << AMUTCTRL) | (m->anamute << ANAMUTE) | (m->digmutel << DIGMUTEL) | (m->digmuter << DIGMUTER) |
				 (m->hvdet << HVDET) | (m->nsgate << NSGATE);
	nau8822_register_write(STATUS_READOUT, t);
	return t;
};

#ifdef __cplusplus
};
#endif

