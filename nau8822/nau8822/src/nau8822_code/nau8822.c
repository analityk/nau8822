#include <nau8822_code/nau8822.h>


#ifdef __cplusplus
extern "C" {
#endif

void nau8822_set_power_1(s_power_1* pw)
{
	uint16_t t = (pw->abiasen << ABIASEN) | (pw->aux1mxen << AUX1MXEN) | (pw->aux2mxen << AUX2MXEN) | (pw->dcbufen << DCBUFEN) |
				  (pw->iobufen << IOBUFEN) | (pw->micbiasen << MICBIASEN ) | (pw->pllen << PLLEN) | (pw->refimp << REFIMP);
	nau8822_register_write(POWER_MANAGMENT_1, t);
};

void nau8822_set_power_2(s_power_2* pw)
{
	uint16_t t = (pw->ladcen << LADCEN) | (pw->lbsten << LBSTEN) | (pw->lhpen << LHPEN) | (pw->lpgaen << LPGAEN) |
				 (pw->radcen << RADCEN) | (pw->rbsten << RBSTEN) | (pw->rhpen << RHPEN) | (pw->rpgaen << RPGAEN) | (pw->sleep << SLEEP);
	nau8822_register_write(POWER_MANAGMENT_2, t);
};

void nau8822_set_power_3(s_power_3* pw)
{
	uint16_t t = (pw->auxout1en << AUXOUT1EN) | (pw->auxout2en << AUXOUT2EN) | (pw->ldacen << LDACEN) | (pw->lmixen << LMIXEN) | (pw->lspken << LSPKEN) |
				 (pw->rdacen << RDACEN) | (pw->rmixen << RMIXEN) | (pw->rspken << RSPKEN);
	nau8822_register_write(POWER_MANAGMENT_3, t);
};

void nau8822_set_power_4(s_power_4* pw)
{
	uint16_t t = (pw->ibadj << IBADJ) | (pw->lpadc << LPADC) | (pw->lpipbst << LPIPBST) | (pw->lpspkd << LPSPKD) | (pw->micbiasm << MICBIASM) | (pw->regvolt << REGVOLT);
	nau8822_register_write(POWER_MANAGMENT_4, t);
};

void nau8822_set_audio_interface(s_audio_interface* ai)
{
	uint16_t t = (ai->bclkp << BCLKP) | (ai->lrp << LRP) | (ai->wlen << WLEN) | (ai->aifmt << AIFMT) | (ai->dacphs << DACPHS) | (ai->adcphs << ADCPHS) | (ai->mono << MONO);
	nau8822_register_write(AUDIO_INTERFACE, t);
};

void nau8822_set_companding(s_companding* c)
{
	uint16_t t = (c->adccm << ADCCM) | (c->addap << ADDAP) | (c->cmb8 << CMB8) | (c->daccm << DACCM);
	nau8822_register_write(COMPANDING, t);
};

void nau8822_set_clock_control_1(s_clock_control_1* c)
{
	uint16_t t = (c->bclksel << BCLKSEL) | (c->clkioen << CLKIOEN) | (c->clkm << CLKM) | (c->mclksel << MCLKSEL);
	nau8822_register_write(CLOCK_CONTROL_1, t);
};

void nau8822_set_clock_control_2(s_clock_control_2* c)
{
	uint16_t t = (c->sclken << SCLKEN) | (c->smplr << SMPLR) | (c->wspien4 << WSPIEN_4);
	nau8822_register_write(CLOCK_CONTROL_2, t);
};

void nau8822_set_gpio(s_gpio* g)
{
	uint16_t t = (g->gpio1pl << GPIO1PL) | (g->gpio1pll << GPIO1PLL) | (g->gpio1sel << GPIO1SEL);
	nau8822_register_write(NAU_GPIO, t);
};

void nau8822_set_jack_detect_1(s_jack_detect_1* j)
{
	uint16_t t = (j->jacden << JACDEN) | (j->jckdio << JCKDIO) | (j->jckmiden << JCKMIDEN);
	nau8822_register_write(JACK_DETECT_1, t);
};

void nau8822_set_dac_control(s_dac_control* d)
{
	uint16_t t = (d->automt << AUTOMT) | (d->dacos << DACOS) | (d->ldacpl << LDACPL) | (d->rdacpl << RDACPL) | (d->softmt << SOFTMT);
	nau8822_register_write(DAC_CONTROL, t);
};

void nau8822_set_left_dac_vol(s_left_dac_volume* d)
{
	uint16_t t = (d->ldacgain << LDACGAIN) | (d->ldacvu << LDACVU);
	nau8822_register_write(LEFT_DAC_VOLUME, t);
};

void nau8822_set_right_dac_vol(s_right_dac_volume* d)
{
	uint16_t t = (d->rdacgain << RDACGAIN) | (d->rdacvu << RDACVU);
	nau8822_register_write(RIGHT_DAC_VOLUME, t);
};

void nau8822_set_jack_detect_2(s_jack_detect_2* j)
{
	uint16_t t = (j->jckdoen0 << JCKDOEN0) | (j->jckdoen1 << JCKDOEN1);
	nau8822_register_write(JACK_DETECT_2, t);
};

void nau8822_set_adc_control(s_adc_control* c)
{
	uint16_t t = (c->adcos << ADCOS) | (c->hpf << HPF) | (c->hpfam << HPFAM) | (c->hpfen << HPFEN) | (c->ladcpl << LADCPL) | (c->radcpl << RADCPL);
	nau8822_register_write(ADC_CONTROL, t);
};

void nau8822_set_left_adc_vol(s_left_adc_volume* c)
{
	uint16_t t = (c->ladcgain << LADCGAIN) | (c->ladcvu << LADCVU);
	nau8822_register_write(LEFT_ADC_VOLUME, t);
};

void nau8822_set_right_adc_vol(s_right_adc_volume* c)
{
	uint16_t t = (c->radcgain << RADCGAIN) | (c->radcvu << RADCVU);
	nau8822_register_write(RIGHT_ADC_VOLUME, t);
};

void nau8822_set_eq1(s_eq1* e)
{
	uint16_t t = (e->eq1cf << EQ1CF) | (e->eq1gc << EQ1GC) | (e->eqm << EQM);
	nau8822_register_write(EQ_1_LOW_CUTOFF, t);
};

void nau8822_set_eq2(s_eq2* e)
{
	uint16_t t = (e->eq2bw << EQ2BW) | (e->eq2cf << EQ2CF) | (e->eq2gc << EQ2GC);
	nau8822_register_write(EQ_2_PEAK_1, t);
};

void nau8822_set_eq3(s_eq3* e)
{
	uint16_t t = (e->eq3bw << EQ3BW) | (e->eq3cf << EQ3CF) | (e->eq3gc << EQ3CF);
	nau8822_register_write(EQ_3_PEAK_2, t);
};

void nau8822_set_eq4(s_eq4* e)
{
	uint16_t t = (e->eq4bw << EQ4BW) | (e->eq4cf << EQ4CF) | (e->eq4gc << EQ4GC);
	nau8822_register_write(EQ_4_PEAK_3, t);
};

void nau8822_set_eq5(s_eq5* e)
{
	uint16_t t = (e->eq5cf << EQ5CF) | (e->eq5gc << EQ5GC);
	nau8822_register_write(EQ5_HIGH_CUTOFF, t);
};

void nau8822_set_dac_lim_1(s_dac_limiter_1* d)
{
	uint16_t t = (d->daclimatk << DACLIMATK) | (d->daclimdcy << DACLIMDCY) | (d->daclimen << DACLIMEN);
	nau8822_register_write(DAC_LIMITER_1, t);
};

void nau8822_set_dac_lim_2(s_dac_limiter_2* d)
{
	uint16_t t = (d->daclimbst << DACLIMBST) | (d->daclimthl << DACLIMTHL);
	nau8822_register_write(DAC_LIMITER_2, t);
};

void nau8822_set_notch_1(s_notch_filter_1* n)
{
	uint16_t t = (n->nfcu1 << NFCU1) | (n->nfcen << NFCEN) | (n->nfca0h << NFCA0H);
	nau8822_register_write(NOTCH_FILTER_1, t);
};

void nau8822_set_notch_2(s_notch_filter_2* n)
{
	uint16_t t = (n->nfca0l << NFCA0L) | (n->nfcu2 << NFCU2);
	nau8822_register_write(NOTCH_FILTER_2, t);
};

void nau8822_set_notch_3(s_notch_filter_3* n)
{
	uint16_t t = (n->nfca1h << NFCA1H) | (n->nfcu3 << NFCU3);
	nau8822_register_write(NOTCH_FILTER_3, t);
};

void nau8822_set_notch_4(s_notch_filter_4* n)
{
	uint16_t t = (n->nfca1l << NFCA1L) | (n->nfcu4 << NFCU4);
	nau8822_register_write(NOTCH_FILTER_4, t);
};

void nau8822_set_alc_1(s_alc_control_1* a)
{
	uint16_t t = (a->alcen << ALCEN) | (a->alcmngain << ALCMNGAIN) | (a->alcmxgain << ALCMXGAIN);
	nau8822_register_write(ALC_CONTROL_1, t);
};

void nau8822_set_alc_2(s_alc_control_2* a)
{
	uint16_t t = (a->alcht << ALCHT) | (a->alcsl << ALCSL);
	nau8822_register_write(ALC_CONTROL_2, t);
};

void nau8822_set_alc_3(s_alc_control_3* a)
{
	uint16_t t = (a->alcatk << ALCATK) | (a->alcdcy << ALCDCY) | (a->alcm << ALCM);
	nau8822_register_write(ALC_CONTROL_3, t);
};

void nau8822_set_noise_gate(s_noise_gate* n)
{
	uint16_t t = (n->alcnen << ALCNEN) | (n->alcnth << ALCNTH);
	nau8822_register_write(NOISE_GATE, t);
};

void nau8822_set_plln(s_pll_n* p)
{
	uint16_t t = (p->pllmclk << PLLMCLK) | (p->plln << PLLN);
	nau8822_register_write(PLLN_N, t);
}

void nau8822_set_pllk1(s_pll_k1* k)
{
	uint16_t t = (k->pllk1 << 0);
	nau8822_register_write(PLL_K_1, t);
};

void nau8822_set_pllk2(s_pll_k2* k)
{
	uint16_t t = (k->pllk2 << 0);
	nau8822_register_write(PLL_K_2, t);
};

void nau8822_set_pllk3(s_pll_k3* k)
{
	uint16_t t = (k->pllk3 << 0);
	nau8822_register_write(PLL_K_3, t);
};

void nau8822_set_3d_depth(s_depth_3d* k)
{
	uint16_t t = (k->depth3d << DEPTH_3D);
	nau8822_register_write(CONTROL_3D, t);
};

void nau8822_set_right_speaker_submixer(s_right_speaker_submixer* s)
{
	uint16_t t = (s->rauxmut << RAUXMUT) | (s->rauxrsubg << RAUXRSUBG) | (s->rmixmut << RMIXMUT) | (s->rsubbyp << RSUBBYP);
	nau8822_register_write(RIGHT_SPEAKER_SUBMIXER, t);
};

void nau8822_set_input_control(s_input_control* c)
{
	uint16_t t = (c->llinlpga << LLINLPGA) | (c->lmicnlpga << LMICNLPGA) | (c->lmicplpga << LMICPLPGA) | (c->micbiasv << MICBIASV) |
				 (c->rlinrpga << RLINRPGA) | (c->rmicnrpga << RMICNRPGA) | (c->rmicprpga << RMICPRPGA);
	nau8822_register_write(INPUT_CONTROL, t);
};

void nau8822_set_left_pga(s_left_input_pga* p)
{
	uint16_t t = (p->lpgagain << LPGAGAIN) | (p->lpgamt << LPGAMT) | (p->lpgau << LPGAU) | (p->lpgazc << LPGAZC);
	nau8822_register_write(LEFT_INPUT_PGA_GAIN, t);
};

void nau8822_set_right_pga(s_right_input_pga* p)
{
	uint16_t t = (p->rpgagain << RPGAGAIN) | (p->rpgamt << RPGAMT) | (p->rpgau << RPGAU) | (p->rpgazc << RPGAZC);
	nau8822_register_write(RIGHT_INPUT_PGA_GAIN, t);
};

void nau8822_set_left_adc_boost(s_left_adc_boost* b)
{
	uint16_t t = (b->lauxbstgain << LAUXBSTGAIN) | (b->lpgabst << LPGABST) | (b->lpgabstgain << LPGABSTGAIN);
	nau8822_register_write(LEFT_ADC_BOOST, t);
};

void nau8822_set_right_adc_boost(s_right_adc_boost* b)
{
	uint16_t t = (b->rauxbstgain << RAUXBSTGAIN) | (b->rpgabst << RPGABST) | (b->rpgabstgain << RPGABSTGAIN);
	nau8822_register_write(RIGHT_ADC_BOOST, t);
};

void nau8822_set_output_control(s_output_control* c)
{
	uint16_t t = (c->aoutimp << AOUTIMP) | (c->aux1bst << AUX1BST) | (c->aux2bst << AUX2BST) | (c->ldacrmx << LDACRMX) |
				 (c->rdaclmx << RDACLMX) | (c->spkbst << SPKBST) | (c->tsen << TSEN);
	nau8822_register_write(OUTPUT_CONTROL, t);
};

void nau8822_set_left_main_mixer(s_left_mixer* m)
{
	uint16_t t = (m->lauxlmx << LAUXLMX) | (m->lauxmxgain << LAUXMXGAIN) | (m->lbyplmx << LBYPLMX) |
				 (m->lbypmxgain << LBYPMXGAIN) | (m->ldaclmx << LDACLMX);
	nau8822_register_write(LEFT_MIXER, t);
};

void nau8822_set_right_main_mixer(s_right_mixer* m)
{
	uint16_t t = (m->rauxmxgain << RAUXMXGAIN) | (m->rauxrmx << RAUXRMX) | (m->rbypmxgain << RBYPMXGAIN) |
				 (m->rbyprmx << RBYPRMX) | (m->rdacrmx << RDACRMX);
	nau8822_register_write(RIGHT_MIXER, t);
};

void nau8822_set_lhp_vol(s_lhp_volume* v)
{
	uint16_t t = (v->lhpgain << LHPGAIN) | (v->lhpmute << LHPMUTE) | (v->lhpvu << LHPVU) | (v->lhpzc << LHPZC);
	nau8822_register_write(LHP_VOLUME, t);
};

void nau8822_set_rhp_vol(s_rhp_volume* v)
{
	uint16_t t = (v->rhpgain << RHPGAIN) | (v->rhpmute << RHPMUTE) | (v->rhpvu << RHPVU) | (v->rhpzc << RHPZC);
	nau8822_register_write(RHP_VOLUME, t);
};

void nau8822_set_lspkout_vol(s_lspkput_volume* v)
{
	uint16_t t = (v->lspkgain << LSPKGAIN) | (v->lspkmute << LSPKMUTE) | (v->lspkvu << LSPKVU) | (v->lspkzc << LSPKZC);
	nau8822_register_write(LSPKOUT_VOLUME, t);
};

void nau8822_set_rspkout_vol(s_rspkput_volume* v)
{
	uint16_t t = (v->rspkgain << RSPKGAIN) | (v->rspkmute << RSPKMUTE) | (v->rspkvu << RSPKVU) | (v->rspkzc << RSPKZC);
	nau8822_register_write(RSPKOUT_VOLUME, t);
};

void nau8822_set_aux_2_mix(s_aux_2_mixer* m)
{
	uint16_t t = (m->aux1mix2 << AUX1MIX2) | (m->auxout2mt << AUXOUT2MT) | (m->ladcaux2 << LADCAUX2) | (m->ldacaux2 << LDACAUX2) |
				 (m->lmixaux2 << LMIXAUX2);
	nau8822_register_write(AUX2MIXER, t);
};

void nau8822_set_aux_1_mix(s_aux_1_mixer* m)
{
	uint16_t t = (m->aux1half << AUX1HALF) | (m->auxout1mt << AUXOUT1MT) | (m->ldacaux1 << LDACAUX1) |
				 (m->lmixaux1 << LMIXAUX1) | (m->radcaux1 << RADCAUX1) | (m->rdacaux1 << RDACAUX1) | (m->rmixaux1 << RMIXAUX1);
	nau8822_register_write(AUX1MIXER, t);
};

void nau8822_set_left_time_slot(s_left_time_slot* t)
{
	uint16_t q = (t->left_slot << 0);
	nau8822_register_write(LEFT_TIME_SLOT, q);
};

void nau8822_set_right_time_slot(s_right_time_slot* t)
{
	uint16_t q = (t->right_slot << 0);
	nau8822_register_write(RIGHT_TIME_SLOT, q);
};

void nau8822_set_misc(s_misc* m)
{
	uint16_t t = (m->ltslot << LTSLOT) | (m->pcm8bit << PCM8BIT) | (m->pcmtsen << PCMTSEN) | (m->puden << PUDEN) |
				 (m->pudpe << PUDPE) | (m->pudps << PUDPS) | (m->rtslot << RTSLOT) | (m->tri << TRI);
	nau8822_register_write(MISC, t);
};

void nau8822_set_alc_enh_1(s_alc_enhancement_1* e)
{
	uint16_t t = (e->alcngsel << ALCNGSEL) | (e->alcpksel << ALCPKSEL) | (e->alctblsel << ALCTBLSEL);
	nau8822_register_write(ALC_ENHANCEMENT_1, t);
};

void nau8822_set_alc_enh_2(s_alc_enhancement_2* e)
{
	uint16_t t = (e->alcgainr << ALCGAINR) | (e->pklimena << PKLIMENA);
	nau8822_register_write(ALC_ENHANCEMENT_2, t);
};

void nau8822_set_oversampling(s_sampling_192khz* s)
{
	uint16_t t = (s->adc_osr32x << ADC_OSR32x) | (s->adcb_over << ADCB_OVER) | (s->dac_osr32x << DAC_OSR32x) | (s->pll49mout << PLL49MOUT);
	nau8822_register_write(SAMPLING_192KHZ, t);
};

void nau8822_set_misc_ctrl(s_misc_controls* m)
{
	uint16_t t = (m->dacinmute << DACINMUTE) | (m->dacosr256 << DACOSR256) | (m->fserflsh << FSERFLSH) | (m->fserrena << FSERRENA) |
				 (m->fserrval << FSERRVAL) | (m->notchdly << NOTCHDLY) | (m->plllockbp << PLLLOCKBP) | (m->spiena_4w << SPIENA_4W);
	nau8822_register_write(MISC_CONTROLS, t);
};

void nau8822_set_tieoff_1(s_tieoff_1* c)
{
	uint16_t t = (c->maninena << MANINENA) | (c->manlaux << MANLAUX) | (c->manllin << MANLLIN) | (c->manlmicn << MANLMICN) | ( c->manlmicp << MANLMICP) | ( c->manraux << MANRAUX) |
				 (c->manrlin << MANRLIN) | (c->manrmicn << MANRMICN) | (c->manrmicp << MANRMICP);
	nau8822_register_write(INPUT_TIE_OFF, t);
};

void nau8822_set_tieoff_2(s_tieoff_2* c)
{
	uint16_t t = (c->ibt250dn << IBT250DN) | (c->ibt500up << IBT500UP) | (c->ibthalfi << IBTHALFI) | (c->maninbbp << MANINBBP) |
				 (c->maninpad << MANINPAD) | (c->manvrefh << MANVREFH) | (c->manvrefl << MANVREFL) | (c->manvrefm << MANVREFM);
	nau8822_register_write(POWER_REDUCTION, t);
};

void nau8822_set_tieoff_3(s_tieoff_3* c)
{
	uint16_t t = (c->manouten << MANOUTEN) | (c->shrtaux1 << SHRTAUX1) | (c->shrtaux2 << SHRTAUX2) | (c->shrtbufh << SHRTBUFH) |
				 (c->shrtbufl << SHRTBUFL) | (c->shrtlhp << SHRTLHP) | (c->shrtlspk << SHRTLSPK) | (c->shrtrhp << SHRTRHP) |
				 (c->shrtrspk << SHRTRSPK);
	nau8822_register_write(OUTPUT_TIE_OFF, t);
};

void nau8822_set_automute(s_automute_control* m)
{
	uint16_t t = (m->amutctrl << AMUTCTRL) | (m->anamute << ANAMUTE) | (m->digmutel << DIGMUTEL) | (m->digmuter << DIGMUTER) |
				 (m->hvdet << HVDET) | (m->nsgate << NSGATE);
	nau8822_register_write(STATUS_READOUT, t);
};

#ifdef __cplusplus
};
#endif

