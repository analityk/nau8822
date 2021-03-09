#ifndef nau8822_types_h__
#define nau8822_types_h__

#include <avr/io.h>

enum e_left_pga_src{ e_left_pga_mic, e_left_pga_lin };
enum e_right_pga_src{ e_right_pga_mic, e_right_pga_lin };
enum e_left_in_mix_srcs{ e_lim_Left_PGA, e_lim_LeftLine, e_lim_LeftAux };
enum e_right_in_mix_srcs{ e_rim_RightMic, e_rim_RightLine, e_rim_RightAux };
enum e_left_main_mix_srcs{ e_lmm_LeftAux, e_lmm_LeftInputMixer, e_lmm_LeftDAC, e_lmm_RightDAC };
enum e_right_main_mix_srcs{ e_rmm_RightAux, e_rmm_RightInputMixer, e_rmm_RightDAC, e_rmm_LeftDAC };
enum e_aux_1_mix_srcs{ e_a1m_LeftMainMixer, e_a1m_RightDAC, e_a1m_LeftDAC, e_a1m_RightInputMixer };
// warning - aux2mixer is permanently connected to aux1mixer output
enum e_aux_2_mix_srcs{ e_a2m_LeftInputMixer, e_a2m_LeftDAC, e_a2m_LeftMainMixer };
enum e_submix_srcs{ e_rs_RightMainMixer, e_rs_RightAux };
enum e_mic_bias_levels{ e_mbl_off, e_mbl_85, e_mbl_70, e_mbl_60, e_mbl_50 }; // Vdda x _85 = 3.3V * 0.85 = 2.805V on mic bias pin
enum e_high_pass_filter{ e_hps_off, e_hps_113, e_hps_141, e_hpf_180, e_hpf_225, e_hpf_281, e_hpf_360, e_hpf_450, e_hpf_563 }; // cut-off freq for 44.1kHz operation
enum e_equ_band_1{ e_eb1_80, e_eb1_105, e_eb1_135, e_eb1_175 };
enum e_equ_band_2{ e_eb2_230, e_eb2_300, e_eb2_385, e_eb2_500 };
enum e_equ_band_3{ e_eb3_650, e_eb3_850, e_eb3_1100, e_eb3_1400 };
enum e_equ_band_4{ e_eb4_1800, e_eb4_2400, e_eb4_3200, e_eb4_4100 };
enum e_equ_band_5{ e_eb5_5300, e_eb5_6900, e_eb5_9000, e_eb5_11700 };
enum e_equ_src{ e_es_ADC, e_es_DAC };
enum e_alc_channels{ e_alc_off, e_alc_left, e_alc_right, e_alc_booth };

enum e_power_blocks{e_pb_dcbufen, e_pb_aux1mxen, e_pb_aux2mxen, e_pb_pllen, e_pb_micbiasen, e_pb_abiasen, e_pb_iobufen, e_pb_refimp_off, e_pb_refimp_3k,
					e_pb_refimp_80k, e_pb_refimp_300k, e_pb_rhpen, e_pb_lhpen, e_pb_sleep, e_pb_rbesten, e_pb_lbesten, e_pb_rpgaen, e_pb_lpgaen,
					e_pb_radcen, e_pb_ladcen, e_pb_auxout1en, e_pb_auxout2en, e_pb_lspken, e_pb_rspken, e_pb_rmixen, e_pb_lmixen, e_pb_rdacen, e_pb_ldacen };

typedef struct {
	uint8_t dcbufen		:	1;
	uint8_t aux1mxen	:	1;
	uint8_t aux2mxen	:	1;
	uint8_t pllen		:	1;
	uint8_t micbiasen	:	1;
	uint8_t abiasen		:	1;
	uint8_t iobufen		:	1;
	uint8_t refimp		:	2;
}s_power_1;

typedef struct {
	uint8_t rhpen	:	1;
	uint8_t lhpen	:	1;
	uint8_t sleep	:	1;
	uint8_t rbsten	:	1;
	uint8_t lbsten	:	1;
	uint8_t rpgaen	:	1;
	uint8_t lpgaen	:	1;
	uint8_t radcen	:	1;
	uint8_t ladcen	:	1;
}s_power_2;

typedef struct {
	uint8_t auxout1en	:	1;
	uint8_t auxout2en	:	1;
	uint8_t lspken		:	1;
	uint8_t rspken		:	1;
	uint8_t rmixen		:	1;
	uint8_t lmixen		:	1;
	uint8_t rdacen		:	1;
	uint8_t ldacen		:	1;
}s_power_3;

typedef struct {
	uint8_t bclkp	:	1;
	uint8_t lrp		:	1;
	uint8_t wlen	:	2;
	uint8_t aifmt	:	2;
	uint8_t dacphs	:	1;
	uint8_t adcphs	:	1;
	uint8_t mono	:	1;
}s_audio_interface;

typedef struct {
	uint8_t cmb8	:	1;
	uint8_t daccm	:	2;
	uint8_t adccm	:	2;
	uint8_t addap	:	1;
}s_companding;

typedef struct {
	uint8_t clkm	:	1;
	uint8_t mclksel	:	3;
	uint8_t bclksel	:	3;
	uint8_t clkioen	:	1;
}s_clock_control_1;

typedef struct {
	uint8_t wspien4	:	1;
	uint8_t smplr	:	3;
	uint8_t sclken	:	1;
}s_clock_control_2;

typedef struct {
	uint8_t gpio1pll:	2;
	uint8_t gpio1pl	:	1;
	uint8_t gpio1sel:	3;
}s_gpio;

typedef struct {
	uint8_t jckmiden : 2;
	uint8_t jacden	: 1;
	uint8_t jckdio	: 2;
}s_jack_detect_1;

typedef struct {
	uint8_t softmt	:	1;
	uint8_t dacos	:	1;
	uint8_t automt	:	1;
	uint8_t rdacpl	:	1;
	uint8_t ldacpl	:	1;
}s_dac_control;

typedef struct {
	uint8_t ldacvu	: 1;
	uint8_t ldacgain: 8;
}s_left_dac_volume;

typedef struct {
	uint8_t rdacvu	: 1;
	uint8_t rdacgain: 8;
}s_right_dac_volume;

typedef struct {
	uint8_t jckdoen1 : 4;
	uint8_t jckdoen0 : 4;
}s_jack_detect_2;

typedef struct {
	uint8_t hpfen	: 1;
	uint8_t hpfam	: 1;
	uint8_t hpf		: 3;
	uint8_t adcos	: 1;
	uint8_t radcpl	: 1;
	uint8_t ladcpl	: 1;
}s_adc_control;

typedef struct {
	uint8_t ladcvu	: 1;
	uint8_t ladcgain: 8;
}s_left_adc_volume;

typedef struct {
	uint8_t radcvu	: 1;
	uint8_t radcgain: 8;
}s_right_adc_volume;

typedef struct {
	uint8_t eqm		: 1;
	uint8_t eq1cf	: 2;
	uint8_t eq1gc	: 5;
}s_eq1;

typedef struct {
	uint8_t eq2bw	: 1;
	uint8_t eq2cf	: 2;
	uint8_t eq2gc	: 5;
}s_eq2;

typedef struct {
	uint8_t eq3bw	: 1;
	uint8_t eq3cf	: 2;
	uint8_t eq3gc	: 5;
}s_eq3;

typedef struct {
	uint8_t eq4bw	: 1;
	uint8_t eq4cf	: 2;
	uint8_t eq4gc	: 5;
}s_eq4;

typedef struct {
	uint8_t eq5cf	: 2;
	uint8_t eq5gc	: 5;
}s_eq5;

typedef struct {
	uint8_t daclimen : 1;
	uint8_t daclimdcy : 4;
	uint8_t daclimatk : 4;
}s_dac_limiter_1;

typedef struct {
	uint8_t daclimthl : 3;
	uint8_t daclimbst : 4;
}s_dac_limiter_2;

typedef struct {
	uint8_t nfcu1 : 1;
	uint8_t nfcen : 1;
	uint8_t nfca0h : 7;
}s_notch_filter_1;

typedef struct {
	uint8_t nfcu2 : 1;
	uint8_t nfca0l: 7;
}s_notch_filter_2;

typedef struct {
	uint8_t nfcu3 : 1;
	uint8_t nfca1h: 7;
}s_notch_filter_3;

typedef struct {
	uint8_t nfcu4 : 1;
	uint8_t nfca1l: 7;
}s_notch_filter_4;

typedef struct {
	uint8_t alcen : 2;
	uint8_t alcmxgain : 3;
	uint8_t alcmngain : 3;
}s_alc_control_1;

typedef struct {
	uint8_t alcht : 4;
	uint8_t alcsl : 4;
}s_alc_control_2;

typedef struct {
	uint8_t alcm : 1;
	uint8_t alcdcy : 4;
	uint8_t alcatk : 4;
}s_alc_control_3;

typedef struct {
	uint8_t alcnen : 1;
	uint8_t alcnth : 4;
}s_noise_gate;

typedef struct {
	uint8_t pllmclk : 1;
	uint8_t plln : 4;
}s_pll_n;

typedef struct {
	uint8_t pllk1 : 6;
}s_pll_k1;

typedef struct {
	uint16_t pllk2 : 9;
}s_pll_k2;

typedef struct {
	uint16_t pllk3 : 9;
}s_pll_k3;

typedef struct {
	uint8_t depth3d : 4;
}s_depth_3d;

typedef struct {
	uint8_t rmixmut : 1;
	uint8_t rsubbyp : 1;
	uint8_t rauxrsubg : 3;
	uint8_t rauxmut : 1;
}s_right_speaker_submixer;

typedef struct {
	uint8_t micbiasv : 2;
	uint8_t rlinrpga : 1;
	uint8_t rmicnrpga : 1;
	uint8_t rmicprpga : 1;
	uint8_t llinlpga : 1;
	uint8_t lmicnlpga : 1;
	uint8_t lmicplpga : 1;
}s_input_control;

typedef struct {
	uint8_t lpgau : 1;
	uint8_t lpgazc : 1;
	uint8_t lpgamt : 1;
	uint8_t lpgagain : 6;
}s_left_input_pga;

typedef struct {
	uint8_t rpgau : 1;
	uint8_t rpgazc : 1;
	uint8_t rpgamt : 1;
	uint8_t rpgagain : 6;
}s_right_input_pga;

typedef struct {
	uint8_t lpgabst : 1;
	uint8_t lpgabstgain : 3;
	uint8_t lauxbstgain : 3;
}s_left_adc_boost;

typedef struct {
	uint8_t rpgabst : 1;
	uint8_t rpgabstgain : 3;
	uint8_t rauxbstgain : 3;
}s_right_adc_boost;

typedef struct {
	uint8_t ldacrmx : 1;
	uint8_t rdaclmx : 1;
	uint8_t aux1bst : 1;
	uint8_t aux2bst : 1;
	uint8_t spkbst : 1;
	uint8_t tsen : 1;
	uint8_t aoutimp : 1;
}s_output_control;

typedef struct {
	uint8_t lauxmxgain : 3;
	uint8_t lauxlmx : 1;
	uint8_t lbypmxgain : 3;
	uint8_t lbyplmx : 1;
	uint8_t ldaclmx : 1;
}s_left_mixer;

typedef struct {
	uint8_t rauxmxgain : 3;
	uint8_t rauxrmx	: 1;
	uint8_t rbypmxgain : 3;
	uint8_t rbyprmx : 1;
	uint8_t rdacrmx : 1;
}s_right_mixer;

typedef struct {
	uint8_t lhpvu : 1;
	uint8_t lhpzc : 1;
	uint8_t lhpmute : 1;
	uint8_t lhpgain : 6;
}s_lhp_volume;

typedef struct {
	uint8_t rhpvu : 1;
	uint8_t rhpzc : 1;
	uint8_t rhpmute : 1;
	uint8_t rhpgain : 6;
}s_rhp_volume;

typedef struct {
	uint8_t lspkvu : 1;
	uint8_t lspkzc : 1;
	uint8_t lspkmute : 1;
	uint8_t lspkgain : 6;
}s_lspkput_volume;

typedef struct {
	uint8_t rspkvu : 1;
	uint8_t rspkzc : 1;
	uint8_t rspkmute : 1;
	uint8_t rspkgain : 6;
}s_rspkput_volume;

typedef struct {
	uint8_t auxout2mt : 1;
	uint8_t aux1mix2 : 1;
	uint8_t ladcaux2 : 1;
	uint8_t lmixaux2 : 1;
	uint8_t ldacaux2 : 1;
}s_aux_2_mixer;

typedef struct {
	uint8_t auxout1mt : 1;
	uint8_t aux1half : 1;
	uint8_t lmixaux1 : 1;
	uint8_t ldacaux1 : 1;
	uint8_t radcaux1 : 1;
	uint8_t rmixaux1 : 1;
	uint8_t rdacaux1 : 1;
}s_aux_1_mixer;

typedef struct{
	uint8_t lpdac : 1;
	uint8_t lpipbst : 1;
	uint8_t lpadc : 1;
	uint8_t lpspkd : 1;
	uint8_t micbiasm : 1;
	uint8_t regvolt : 2;
	uint8_t ibadj : 2;
}s_power_4;

typedef struct {
	uint16_t left_slot : 9;
}s_left_time_slot;

typedef struct {
	uint8_t pcmtsen : 1;
	uint8_t tri : 1;
	uint8_t pcm8bit : 1;
	uint8_t puden : 1;
	uint8_t pudpe : 1;
	uint8_t pudps : 1;
	uint8_t rtslot : 1;
	uint8_t ltslot : 1;
}s_misc;

typedef struct {
	uint16_t right_slot : 9;
}s_right_time_slot;

typedef	struct {
	uint8_t mod_dither : 4;
	uint8_t analog_dither : 4;
}s_dac_dither;

typedef struct {
	uint8_t alctblsel : 1;
	uint8_t alcpksel : 1;
	uint8_t alcngsel : 1;
	uint8_t alcgainl : 6; // ro
}s_alc_enhancement_1;

typedef struct {
	uint8_t pklimena : 1;
	uint8_t alcgainr : 6; // ro
}s_alc_enhancement_2;

typedef struct{
	uint8_t adcb_over : 1;
	uint8_t pll49mout : 1;
	uint8_t dac_osr32x : 1;
	uint8_t adc_osr32x : 1;
}s_sampling_192khz;

typedef struct {
	uint8_t spiena_4w : 1;
	uint8_t fserrval : 2;
	uint8_t fserflsh : 1;
	uint8_t fserrena : 1;
	uint8_t notchdly : 1;
	uint8_t dacinmute : 1;
	uint8_t plllockbp : 1;
	uint8_t dacosr256 : 1;
}s_misc_controls;

typedef struct {
	uint8_t maninena : 1;
	uint8_t manraux : 1;
	uint8_t manrlin : 1;
	uint8_t manrmicn : 1;
	uint8_t manrmicp : 1;
	uint8_t manlaux : 1;
	uint8_t manllin : 1;
	uint8_t manlmicn : 1;
	uint8_t manlmicp : 1;
}s_tieoff_1;

typedef struct {
	uint8_t ibthalfi : 1;
	uint8_t ibt500up : 1;
	uint8_t ibt250dn : 1;
	uint8_t maninbbp : 1;
	uint8_t maninpad : 1;
	uint8_t manvrefh : 1;
	uint8_t manvrefm : 1;
	uint8_t manvrefl : 1;
}s_tieoff_2;

typedef struct {
	uint8_t amutctrl : 1;
	uint8_t hvdet : 1;
	uint8_t nsgate : 1;
	uint8_t anamute : 1;
	uint8_t digmutel : 1;
	uint8_t digmuter : 1;
}s_automute_control;

typedef struct {
	uint8_t manouten : 1;
	uint8_t shrtbufh : 1;
	uint8_t shrtbufl : 1;
	uint8_t shrtlspk : 1;
	uint8_t shrtrspk : 1;
	uint8_t shrtaux1 : 1;
	uint8_t shrtaux2 : 1;
	uint8_t shrtlhp : 1;
	uint8_t shrtrhp : 1;
}s_tieoff_3;

typedef struct {
	uint16_t spi1 : 9;
}s_spi_1;

typedef struct {
	uint16_t spi2 : 9;
}s_spi_2;

typedef struct {
	uint16_t spi3 : 9;
}s_spi_3;

typedef struct {
	s_power_1	power_1;
	s_power_2	power_2;
	s_power_3	power_3;
	s_audio_interface audio_interface;
	s_companding companding;
	s_clock_control_1 clock_contorl_1;
	s_clock_control_2 clock_control_2;
	s_gpio gpio;
	s_jack_detect_1 jack_detect_1;
	s_dac_control dac_control;
	s_left_dac_volume left_dac_volume;
	s_right_dac_volume right_dac_volume;
	s_jack_detect_2 jack_detect_2;
	s_adc_control adc_control;
	s_left_adc_volume left_adc_volume;
	s_right_adc_volume right_adc_volume;
	s_eq1 eq1;
	s_eq2 eq2;
	s_eq3 eq3;
	s_eq4 eq4;
	s_eq5 eq5;
	s_dac_limiter_1 dac_limiter_1;
	s_dac_limiter_2 dac_limiter_2;
	s_notch_filter_1 notch_filter_1;
	s_notch_filter_2 notch_filter_2;
	s_notch_filter_3 notch_filter_3;
	s_notch_filter_4 notch_filter_4;
	s_alc_control_1 alc_control_1;
	s_alc_control_2 alc_control_2;
	s_alc_control_3 alc_control_3;
	s_noise_gate noise_gate;
	s_pll_n pll_n;
	s_pll_k1 pll_k1;
	s_pll_k2 pll_k2;
	s_pll_k3 pll_k3;
	s_depth_3d depth_3d;
	s_right_speaker_submixer right_speaker_submixer;
	s_input_control input_control;
	s_left_input_pga left_input_pga;
	s_right_input_pga right_input_pga;
	s_left_adc_boost left_adc_boost;
	s_right_adc_boost right_adc_boost;
	s_output_control output_control;
	s_left_mixer left_mixer;
	s_right_mixer right_mixer;
	s_lhp_volume lhp_volume;
	s_rhp_volume rhp_volume;
	s_lspkput_volume lspkput_volume;
	s_rspkput_volume rspkput_volume;
	s_aux_2_mixer aux_2_mixer;
	s_aux_1_mixer aux_1_mixer;
	s_power_4 power_4;
	s_left_time_slot left_time_slot;
	s_misc misc;
	s_right_time_slot right_time_slot;
	s_dac_dither dac_dither;
	s_alc_enhancement_1 alc_enhancement_1;
	s_alc_enhancement_2 alc_enhancement_2;
	s_sampling_192khz sampling_192khz;
	s_misc_controls misc_controls;
	s_tieoff_1 tie_of_1;
	s_tieoff_2 tie_of_2;
	s_automute_control automute_control;
	s_tieoff_3 tie_of_3;
	s_spi_1 spi_1;
	s_spi_2 spi_2;
	s_spi_3 spi_3;
}ts_nau8822;


#endif // nau8822_types_h__
