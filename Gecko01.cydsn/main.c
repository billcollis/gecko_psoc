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
//to make defines and type defines visible
//   copy these into every header file
#include "project.h"
#include <stdio.h>
#include <stdlib.h>

#include "ssd1306.h"
#include "keypad.h"
#include "display_test.h"
#include "menu.h"
#include "sinewavegen.h"



void disp_btn(uint8 btn){
    static uint8 up_count=0;
    static uint8 down_count=0;
    static uint8 select_count=0;
    static uint8 left_count=0;
    static uint8 right_count=0;
    gfx_setCursor(60,0); //x,y
    if (btn == NONE){
        gfx_println("------");
        display_update(); 
    }
    else if (btn == UP){
        gfx_println("up    ");
        display_update(); 
        up_count++;
    }
    else if (btn==DOWN){
        gfx_println("down  ");
        display_update();
        down_count++;
    }
    else if (btn==SELECT){
        gfx_println("select");
        display_update();
        select_count++;
    }
    else if (btn==LEFT){
        gfx_println("left  ");
        display_update();
        left_count++;
    }
    else if (btn==RIGHT){
        gfx_println("right ");
        display_update();
        right_count++;
    }
    ssd_print_int(up_count,0,LINE3);
    ssd_print_int(down_count,0,LINE4);
    ssd_print_int(select_count,0,LINE5);
    ssd_print_int(left_count,0,LINE6);
    ssd_print_int(right_count,0,LINE7);
    display_update();        
}


/* Timer Globals */
volatile uint8 tcount=0;
volatile uint8 tick_flag=0;

CY_ISR_PROTO(tick_timer_intr);
CY_ISR(tick_timer_intr){
    Timer_5ms_tick_ReadStatusRegister();//this resets the timer and makes it start again
    tick_flag=1;
    tcount++;
    if (tcount > 250){
        PCB_LED_Write(1); 
    }  
    if (tcount > 254){
        PCB_LED_Write(0); 
        tcount=0;
    }
}


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Initialization/startup code  */

    /* KEYPAD */
    Timer_5ms_tick_Start();
    isr_5ms_tick_StartEx(tick_timer_intr);
    
    
    /* DDS */
    //DDS_Start();
    
    /* WaveDAC */
    WaveDAC_Start();
    
    /* SINEGEN set to 1kHz and OFF*/
    sinegen_init();
    
    
    /* DISPLAY */
    display_init(1); //pass text size
    display_clear();         
    welcome_screen();
    
   
    /* keypad */
    extern uint8_t button;
    
    /* Sinewave Generator */
    extern volatile FGen_Specifications_Struct sinegen_specs;
    extern volatile FGen_Enable_Struct sinegen_enablestate;
    
    sinegen_off();
    sinegen_enablestate.enable = 0; //off
    sinegen_specs.frequency = 1000000;//1kHz
    sinegen_specs.period =    1000u; //1ms=1000us
    sinegen_specs.amplitude = 1000u; //1V
    sinegen_specs.offset =    0u; //0.001V


    
    for(;;){                
        if (tick_flag){ //do this every tick (5ms)
            read_key();
            if (button != NONE ){
                navigate_menu();                
                //disp_btn(btn);
            }
            tick_flag=0;
        }
    }
}

/* [] END OF FILE */
