# NAU8822
8 analog inputs; I2S/PCM/a/b/time slot; 32b 48kHz ADC and DAC; digital high pass filter; automatic gain control for left and right differential (mic)/line input; notch filter; 5 band equalizer; 3D enchancement; DAC Dither; 6 analog mixers + 1 for differential output (power up to 1W); PLL - clock input from 8MHz to 33MHz; low noise bias current for electret mic; controlled by simple I2C interface;

https://www.nuvoton.com/resource-files/NAU8822LDataSheetRev1.9.pdf

Here you have simple piece of code for use this chip with, i believe, can be used for any uC architecture. Currently i test it on avr - on arduino nano.

What you can build with this chip? If you will use simple uC - without i2s - this chip may be used as audio preamplifier with excellent sound quality. Moreover you are able to use sound equalizer - add a few rotary encoder to uC and drive codec in real time. You may to change sound source, volume on each source, you can mix it together or swap sound in left and right channel. You may choose active output - you have two, two-channels outputs (speakers and headphones) plus additional two auxiliary (single chanler or better - nonchannel) output from aux mixers. You may use simple and cheap ecm mic and if you connect it to differential input you can use ALC - automatic level (loudness) control features.

I think all this features can be used with near any arduino.

But here we have I2S. I've built with this chip ethernet audio streamer. I used this chip and Atmel SAM E70 Xplained board. Data from pc was sended in UDP packets into SAM E70 uC and from here into codec by I2S. This chip is cheap and awesome and if you want to try it without build own pcb - you can use (in near future, currently is under tests) my board and my drivers.

Have a nice day!
