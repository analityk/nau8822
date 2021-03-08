#ifndef nau8822_h__
#define nau8822_h__

#include <avr/io.h>
#include <nau8822_code/nau8822_map_reg.h>
#include <nau8822_code/nau8822_hardware.h>
#include <nau8822_code/nau8822_types.h>


#ifdef __cplusplus
extern "C" {
#endif

//void nau8822_mic_bias_voltage(enum e_mic_bias_levels mbl);
//void nau8822_3d_enhancement(uint8_t level); // 0 - off,
//void nau8822_equ_src(enum e_equ_src es); // off, adc or dac
//void nau8822_equ_band_1(enum e_equ_band_1 eb1, int8_t level);	// level <-12 .. 11>
//void nau8822_equ_band_2(enum e_equ_band_2 eb2, int8_t level);	// level <-12 .. 11>
//void nau8822_equ_band_3(enum e_equ_band_3 eb3, int8_t level);	// level <-12 .. 11>
//void nau8822_equ_band_4(enum e_equ_band_4 eb4, int8_t level);	// level <-12 .. 11>
//void nau8822_equ_band_5(enum e_equ_band_5 eb5, int8_t level);	// level <-12 .. 11>
//
//void nau8822_headphone_volume(uint8_t left, uint8_t right);		// level <0 .. 63>
//void nau8822_speaker_volume(uint8_t left, uint8_t right);		// leve; <0 .. 63>
//void nau8822_aux1_volume(uint8_t aux1);
//void nau8822_aux2_volume(uint8_t aux2);
//
//#ifdef LEVEL_HIGH_API
//void nau8822_power_block_on(enum e_power_blocks pb);
//void nau8822_power_block_off(enum e_power_blocks pb);
//#elif LEVEL_REGISTER_API
//void nau8822_power_reg_1(uint16_t mask);
//void nau8822_power_reg_2(uint16_t mask);
//void nau8822_power_reg_3(uint16_t mask);
//#endif


void nau8822_set_power_1(s_power_1* pw);	// ok
void nau8822_set_power_2(s_power_2* pw);	// ok
void nau8822_set_power_3(s_power_3* pw);
void nau8822_set_power_4(s_power_4* pw);
void nau8822_set_audio_interface(s_audio_interface* ai);
void nau8822_set_companding(s_companding* c);
void nau8822_set_clock_control_1(s_clock_control_1* c);
void nau8822_set_clock_control_2(s_clock_control_2* c);
void nau8822_set_gpio(s_gpio* g);
void nau8822_set_jack_detect_1(s_jack_detect_1* j);
void nau8822_set_dac_control(s_dac_control* d);
void nau8822_set_left_dac_vol(s_left_dac_volume* d);
void nau8822_set_right_dac_vol(s_right_dac_volume* d);
void nau8822_set_jack_detect_2(s_jack_detect_2* j);
void nau8822_set_adc_control(s_adc_control* c);
void nau8822_set_left_adc_vol(s_left_adc_volume* c);
void nau8822_set_right_adc_vol(s_right_adc_volume* c);
void nau8822_set_eq1(s_eq1* e);
void nau8822_set_eq2(s_eq2* e);
void nau8822_set_eq3(s_eq3* e);
void nau8822_set_eq4(s_eq4* e);
void nau8822_set_eq5(s_eq5* e);
void nau8822_set_dac_lim_1(s_dac_limiter_1* d);
void nau8822_set_dac_lim_2(s_dac_limiter_2* d);
void nau8822_set_notch_1(s_notch_filter_1* n);
void nau8822_set_notch_2(s_notch_filter_2* n);
void nau8822_set_notch_3(s_notch_filter_3* n);
void nau8822_set_notch_4(s_notch_filter_4* n);
void nau8822_set_alc_1(s_alc_control_1* a);
void nau8822_set_alc_2(s_alc_control_2* a);
void nau8822_set_alc_3(s_alc_control_3* a);
void nau8822_set_noise_gate(s_noise_gate* n);
void nau8822_set_plln(s_pll_n* p);
void nau8822_set_pllk1(s_pll_k1* k);
void nau8822_set_pllk2(s_pll_k2* k);
void nau8822_set_pllk3(s_pll_k3* k);
void nau8822_set_3d_depth(s_depth_3d* k);
void nau8822_set_right_speaker_submixer(s_right_speaker_submixer* s);
void nau8822_set_input_control(s_input_control* c);
void nau8822_set_left_pga(s_left_input_pga* p);
void nau8822_set_right_pga(s_right_input_pga* p);
void nau8822_set_left_adc_boost(s_left_adc_boost* b);
void nau8822_set_right_adc_boost(s_right_adc_boost* b);
void nau8822_set_output_control(s_output_control* c);
void nau8822_set_left_main_mixer(s_left_mixer* m);
void nau8822_set_right_main_mixer(s_right_mixer* m);
void nau8822_set_lhp_vol(s_lhp_volume* v);
void nau8822_set_rhp_vol(s_rhp_volume* v);
void nau8822_set_lspkout_vol(s_lspkput_volume* v);
void nau8822_set_rspkout_vol(s_rspkput_volume* v);
void nau8822_set_aux_2_mix(s_aux_2_mixer* m);
void nau8822_set_aux_1_mix(s_aux_1_mixer* m);
void nau8822_set_left_time_slot(s_left_time_slot* t);
void nau8822_set_right_time_slot(s_right_time_slot* t);
void nau8822_set_misc(s_misc* m);
void nau8822_set_alc_enh_1(s_alc_enhancement_1* e);
void nau8822_set_alc_enh_2(s_alc_enhancement_2* e);
void nau8822_set_oversampling(s_sampling_192khz* s);
void nau8822_set_misc_ctrl(s_misc_controls* m);
void nau8822_set_tieoff_1(s_tieoff_1* c);
void nau8822_set_tieoff_2(s_tieoff_2* c);
void nau8822_set_tieoff_3(s_tieoff_3* c);
void nau8822_set_automute(s_automute_control* m);


#ifdef __cplusplus
};
#endif

#endif // nau8822_h__
