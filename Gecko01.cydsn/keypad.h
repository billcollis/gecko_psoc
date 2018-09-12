/* ========================================
 *
 * Copyright Bill Collis, 2018
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Bill Collis.
 *
 * ========================================
*/

#ifndef KEYPAD_H
#define KEYPAD_H

#include "project.h"
    
enum uint8_t {NONE=0,UP,DOWN,SELECT,RIGHT,LEFT};
enum {K_IDLE=1, K_FILTERING, K_1ST_KEY_EVENT, K_RPT1_EVENT, K_RPT2_EVENT};
#define TICK_MS 5 
#define FILTER_COUNT  (30/TICK_MS)
#define DELAY_COUNT   (800/TICK_MS)
#define RPT1_COUNT    (400/TICK_MS)
#define RPT_KEYS      5
#define RPT2_COUNT    (100/TICK_MS) 


void read_key(); //read one of the 5 keys
uint8 check_for_key(void); //debounce and handle repeats


#endif

/* [] END OF FILE */
