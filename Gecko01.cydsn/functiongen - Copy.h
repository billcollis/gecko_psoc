/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Bill Collis.
 *
 * ========================================
*/

#ifndef _FUNCTIONGEN_H
#define _FUNCTIONGEN_H  
    
#include "project.h"


#define FGEN_OUTPUT_Y 16
#define FGEN_SHAPE_Y 24
#define FGEN_FREQ_Y 32
#define FGEN_PERIOD_Y 40
#define FGEN_AMPLITUDE_Y 48
#define FGEN_OFFSET_Y 56
    
#define FGEN_INIT_FREQ 1000000 //1kHz
    // if wave data stored in flash then use the commented out values
#define FGEN_CUTOVER_1 50000001 // 35000001
#define FGEN_CUTOVER_2 22000001 // 1800001
#define FGEN_CUTOVER_3 12000000 //  9000001 
#define FGEN_CUTOVER_4  6000001  //  4500001 4.5kHz
#define FGEN_CUTOVER_5  3000001  //  2200001 2.2kHz
#define FGEN_MAX_FREQ 100000000  // 75000001 75kHz  
#define FGEN_MAX_AMPL 5000 //mV    
    
#define FGEN_SAMPLE_SIZE_1023 1023
#define FGEN_SAMPLE_SIZE_511 511
#define FGEN_SAMPLE_SIZE_255 255
#define FGEN_SAMPLE_SIZE_127 127
#define FGEN_SAMPLE_SIZE_63 63
#define FGEN_SAMPLE_SIZE_31 31
    
#define FGEN_LEFT_X 0
#define FGEN_DESCRIPTION_X 8
#define FGEN_CENTER_X 48

#define FGEN_LEFT_DIGIT 0
#define FGEN_LEFT_V_DIGIT 6
#define FGEN_RIGHT_DIGIT 10
#define COMMA 3 //need to skip
#define DECIMAL_POINT 7 //need to skip

#define DIGIT_WIDTH 6
#define DIGIT_HEIGHT 8

enum fgen_waveshapes {Sine=1,Square,Triangle,Sawtooth,PWM};

typedef struct {
    uint8_t  enable;
} FGen_Enable_Struct;

typedef struct {  
    enum fgen_waveshapes shape;  
    uint32_t frequency; //in mHz 1mHz to 75kHz(75,000,000mHz) 
    uint32_t period; //in uS 1mHz = 1000,000,000 uS to 1MHz = 13.33uS 
    uint16_t amplitude; //in mV 0 to 1000mV
    uint16_t offset; //in mV
} FGen_Specifications_Struct;
    

/* Menu */
extern const char MT_ONOFF[];
extern const char MT_SHAPE[];
extern const char MT_FREQ[];
extern const char MT_PERIOD[];
extern const char MT_AMPL[];
extern const char MT_OFFSET[];
extern const char MT_SINE[]; 
extern const char MT_SQUARE[];
extern const char MT_TRI[]; 
extern const char MT_SAW[]; 
extern const char MT_PWM[]; 
extern const char MT_EXIT[]; 


void fgen_init();
void fgen_open();
void fgen_setup_screen();

void fgen_onoff();
void fgen_shape();
void fgen_freq();
void fgen_period();
void fgen_amplitude();
void fgen_offset();
void fgen_back();
void sprintfcomma (uint32 n, char *text, uint8 decimal, char *suffix);
void longtotext(uint32_t number, char *text, char *suffix);
void fgen_remove_indicators(void);
void fgen_show_values(void);
void underline(int8 digit, uint8 line);
void remove_underline (uint8 line);
void sendFreqToDDS_WaveDAC(uint32 freq);
uint32 get_freq_incr_decr (int8 digit);
void new_wavedac_setting(uint16 samples, uint32 dds_freq);

#endif // _FUNCTIONGEN_H

/* [] END OF FILE */
