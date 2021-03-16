#ifndef nau8822_h__
#define nau8822_h__

#include <avr/io.h>
#include <nau8822_code/nau8822_map_reg.h>
#include <nau8822_code/nau8822_hardware.h>
#include <nau8822_code/nau8822_types.h>

extern ts_nau8822 snau8822;

#ifdef __cplusplus
extern "C" {
#endif

uint16_t nau8822_gain(enum e_gains g);

uint16_t nau8822_mic_bias_voltage(enum e_mic_bias_levels mbl);		// voltage is equal to vdda times setting factor
uint16_t nau8822_3d_enhancement(uint8_t level);						// 0 - off, 15 - max;

uint16_t nau8822_equ_src(enum e_equ_src es);						// adc or dac
uint16_t nau8822_equ_band_1(enum e_equ_band_1 eb1, int8_t level);	// level <-12 .. 11>
uint16_t nau8822_equ_band_2(enum e_equ_band_2 eb2, int8_t level);	// level <-12 .. 11>
uint16_t nau8822_equ_band_3(enum e_equ_band_3 eb3, int8_t level);	// level <-12 .. 11>
uint16_t nau8822_equ_band_4(enum e_equ_band_4 eb4, int8_t level);	// level <-12 .. 11>
uint16_t nau8822_equ_band_5(enum e_equ_band_5 eb5, int8_t level);	// level <-12 .. 11>

// outputs volumes
uint16_t nau8822_headphone_volume(uint8_t left, uint8_t right);		// level <0 .. 63>
uint16_t nau8822_speaker_volume(uint8_t left, uint8_t right);		// leve; <0 .. 63>

// analog inputs
uint16_t nau8822_left_in_mix_src(enum e_left_in_mix_srcs ms, uint8_t gain);			// pga, lin or aux
uint16_t nau8822_left_pga_in_src(enum e_left_pga_src ms, uint8_t gain);				// mic or lin - can be gained by alc
uint16_t nau8822_right_in_mix_src(enum e_right_in_mix_srcs ms, uint8_t gain);		// pga, lin or aux
uint16_t nau8822_right_pga_in_src(enum e_right_pga_src ms, uint8_t gain);			// mix or lin - can be gained by alc

// internal mixers
uint16_t nau8822_left_main_mix_src(enum e_left_main_mix_srcs ms, uint8_t gain);		// ldac, rdac, aux, in_mix stage
uint16_t nau8822_right_main_mix_src(enum e_right_main_mix_srcs ms, uint8_t gain);	// rdac, ldac, aux, in_mix stage
uint16_t nau8822_aux_1_mix_src(enum e_aux_1_mix_srcs ms);							// rinmix, ldac, rdac, lmix, rmix
uint16_t nau8822_aux_2_mix_src(enum e_aux_2_mix_srcs ms);							// aux1(!), linmix, ldac, lmix
uint16_t nau8822_rspk_submix_src(enum e_submix_srcs ms);							// rauxin or rmix

// alc - automatic level control
// this stuff can automatic set up gain on mic input (pga) or lin pga input
// and hold the output stage signal on ~constant level (if sound source is resonably loud).
// but it is a bit hard to proper setup, even if you work with datasheet, you propably will spent
// here a more time. Anyway it is worth, output signal can be free of distorion and dynamic range
// is wider than you think. I tested this future with signal gen and oscilloscope.
// With input signal in range 15mV - 500mV output signal was constant on goal level about ~1Vp-p with
// small deviation about 50mV WITHOUT distorion - just dynamic change of input gain
// https://www.youtube.com/watch?v=RilggJd1_LY - this guy use alc in his mic. He is loud but never too
// in 3 word: cool awsome nice future that you have to buy now...
// lets back on ground
// because you have to know how it work and how to setup it in your enviroment
// i don't write here any high level api
// lets look at example

// but this function get your 4 register param and set it to proper register
// however you may do it yourself
void nau8822_set_alc(void);

uint16_t nau8822_set_power_1(s_power_1* pw);	// ok
uint16_t nau8822_set_power_2(s_power_2* pw);	// ok
uint16_t nau8822_set_power_3(s_power_3* pw);
uint16_t nau8822_set_power_4(s_power_4* pw);
uint16_t nau8822_set_audio_interface(s_audio_interface* ai);
uint16_t nau8822_set_companding(s_companding* c);
uint16_t nau8822_set_clock_control_1(s_clock_control_1* c);
uint16_t nau8822_set_clock_control_2(s_clock_control_2* c);
uint16_t nau8822_set_gpio(s_gpio* g);
uint16_t nau8822_set_jack_detect_1(s_jack_detect_1* j);
uint16_t nau8822_set_dac_control(s_dac_control* d);
uint16_t nau8822_set_left_dac_vol(s_left_dac_volume* d);
uint16_t nau8822_set_right_dac_vol(s_right_dac_volume* d);
uint16_t nau8822_set_jack_detect_2(s_jack_detect_2* j);
uint16_t nau8822_set_adc_control(s_adc_control* c);
uint16_t nau8822_set_left_adc_vol(s_left_adc_volume* c);
uint16_t nau8822_set_right_adc_vol(s_right_adc_volume* c);
uint16_t nau8822_set_eq1(s_eq1* e);
uint16_t nau8822_set_eq2(s_eq2* e);
uint16_t nau8822_set_eq3(s_eq3* e);
uint16_t nau8822_set_eq4(s_eq4* e);
uint16_t nau8822_set_eq5(s_eq5* e);
uint16_t nau8822_set_dac_lim_1(s_dac_limiter_1* d);
uint16_t nau8822_set_dac_lim_2(s_dac_limiter_2* d);
uint16_t nau8822_set_notch_1(s_notch_filter_1* n);
uint16_t nau8822_set_notch_2(s_notch_filter_2* n);
uint16_t nau8822_set_notch_3(s_notch_filter_3* n);
uint16_t nau8822_set_notch_4(s_notch_filter_4* n);
uint16_t nau8822_set_alc_1(s_alc_control_1* a);
uint16_t nau8822_set_alc_2(s_alc_control_2* a);
uint16_t nau8822_set_alc_3(s_alc_control_3* a);
uint16_t nau8822_set_noise_gate(s_noise_gate* n);
uint16_t nau8822_set_plln(s_pll_n* p);
uint16_t nau8822_set_pllk1(s_pll_k1* k);
uint16_t nau8822_set_pllk2(s_pll_k2* k);
uint16_t nau8822_set_pllk3(s_pll_k3* k);
uint16_t nau8822_set_3d_depth(s_depth_3d* k);
uint16_t nau8822_set_right_speaker_submixer(s_right_speaker_submixer* s);
uint16_t nau8822_set_input_control(s_input_control* c);
uint16_t nau8822_set_left_pga(s_left_input_pga* p);
uint16_t nau8822_set_right_pga(s_right_input_pga* p);
uint16_t nau8822_set_left_adc_boost(s_left_adc_boost* b);
uint16_t nau8822_set_right_adc_boost(s_right_adc_boost* b);
uint16_t nau8822_set_output_control(s_output_control* c);
uint16_t nau8822_set_left_main_mixer(s_left_mixer* m);
uint16_t nau8822_set_right_main_mixer(s_right_mixer* m);
uint16_t nau8822_set_lhp_vol(s_lhp_volume* v);
uint16_t nau8822_set_rhp_vol(s_rhp_volume* v);
uint16_t nau8822_set_lspkout_vol(s_lspkput_volume* v);
uint16_t nau8822_set_rspkout_vol(s_rspkput_volume* v);
uint16_t nau8822_set_aux_2_mix(s_aux_2_mixer* m);
uint16_t nau8822_set_aux_1_mix(s_aux_1_mixer* m);
uint16_t nau8822_set_left_time_slot(s_left_time_slot* t);
uint16_t nau8822_set_right_time_slot(s_right_time_slot* t);
uint16_t nau8822_set_misc(s_misc* m);
uint16_t nau8822_set_alc_enh_1(s_alc_enhancement_1* e);
uint16_t nau8822_set_alc_enh_2(s_alc_enhancement_2* e);
uint16_t nau8822_set_oversampling(s_sampling_192khz* s);
uint16_t nau8822_set_misc_ctrl(s_misc_controls* m);
uint16_t nau8822_set_tieoff_1(s_tieoff_1* c);
uint16_t nau8822_set_tieoff_2(s_tieoff_2* c);
uint16_t nau8822_set_tieoff_3(s_tieoff_3* c);
uint16_t nau8822_set_automute(s_automute_control* m);


#ifdef __cplusplus
};
#endif

#endif // nau8822_h__
