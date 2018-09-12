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
#include <project.h>
#include <keypad.h>

#ifndef _KEYPAD_H
#define _KEYPAD_H

volatile uint8_t button = NONE; //declared and initialised here as this is where it is written to
    
uint8 check_for_key(void){
    //uint8_t btn = NONE;
    if (Input_Up_Read() == 0){
        button = UP;
    }
    else if (Input_Down_Read() == 0){
        button = DOWN;
    }
    else if (Input_Select_Read() == 0 ){
        button = SELECT;
    }
    else if (Input_Left_Read() == 0){
         button = LEFT;
    }
    else if (Input_Right_Read() == 0){
         button = RIGHT;
    }
    else {
         button = NONE;
    }
    return button;
}


//https://www.embeddedrelated.com/showarticle/519.php
void read_key(){
    static uint8 state = K_IDLE;
    static uint8 count;                  // debounce filter count
    static uint8 key_count;
    static uint8 last_val = 0;           // 0 means no buttons pushed
    uint8 val;                           // raw val this time
    uint8 filtered_val = 0;              // our filtered return val
  
    val = check_for_key();              // get raw keypad value
        
    switch (state)
    {
        case K_IDLE:                      // 1 = waiting for a key
            if (val != 0)                   // have a new key
            {
              count = FILTER_COUNT;         // start filtering this key
              state = K_FILTERING;
            }
        break;

        case K_FILTERING:                 // 2= filtering a key
            if (val == last_val)            // keep filtering this key
            {
              if ((count != 0) && (--count == 0))  // filter count just went to 0
              {
                filtered_val = val;         // output this filtered key val once
                count = DELAY_COUNT;
                state = K_1ST_KEY_EVENT;
              }
            }
            else
              state = K_IDLE;               // new key found, catch it next time thru
        break;

        case K_1ST_KEY_EVENT:             // 3 = already returned a key, wait for key up
            if (val == last_val)
            {
              if (--count == 0)
              {
                filtered_val = val;         // first repeat key
                count = RPT1_COUNT;
                key_count = RPT_KEYS;
                state = K_RPT1_EVENT;
              }
            }
            else
              state = K_IDLE;               // anything else, back to idle
        break;

        case K_RPT1_EVENT:                // 4 = already returned a key, wait for key up
            if (val == last_val)
            {
              if (--count == 0)
              {
                filtered_val = val;         // another slow repeat key
                if (--key_count == 0)
                {
                  state = K_RPT2_EVENT;     // start repeating faster
                  count = RPT2_COUNT;
                }
                else
                  count = RPT1_COUNT;       // continue slow repeats
              }
            }
            else
              state = K_IDLE;               // anything else, back to idle
        break;

        case K_RPT2_EVENT:                // 5 = already returned a key, wait for key up
            if (val == last_val)
            {
              if (--count == 0)
              {
                filtered_val = val;         // another fast repeat key
                count = RPT2_COUNT;
              }
            }
            else
              state = K_IDLE;               // anything else, back to idle
        break;

        default:
            state = K_IDLE;                 // safety valve
            break;
    }
    last_val = val;                   // always remember the last val
    button = filtered_val;
}

#endif //_KEYPAD_H
/* [] END OF FILE */
