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
#include "project.h"
#include "menu.h"
#include "ssd1306.h"
#include "keypad.h"
#include "sinewavegen.h"

const char MT_MENU[] =      "MENU         "; 
const char MT_SINEGEN[] =   "Sinewave Gen."; 
const char MT_SCOPE[] =     "SCOPE        "; 
const char MT_DVM[] =       "DVM          "; 

const char MTON[] =         "ON ";
const char MTOFF[] =        "OFF";
const char MT_EXIT[] =      "Exit"; 

//SinewaveGen parameters
const char MT_ONOFF[] =    "O/P ";
const char MT_FREQ[] =     "Freq"; //
const char MT_PERIOD[] =   "Per "; //
const char MT_AMPL[] =     "Ampl"; //
const char MT_OFFSET[] =   "Offs"; //



//globals
//a few globals are used as these are used extensively though out the program
volatile uint8 currentstate = ST_INSTR;    //declared and initialised here as this is where it is written to 
volatile uint8 newstate = ST_INSTR;  
//the manu has two main modes for navigation and for editing
//while navigating the menu needs to look up in the table new states to go to
//while editting the button presses are passed through to the function

volatile uint8 menu_mode = navigate; //
uint8 menu_item=0;

/* keypad */
extern uint8_t button; 

MenuEntry menu [] =
{
  //{currstate,   mainmenutext,   down,           up,           selectstate,    fn called - every button press }
    {ST_INSTR,      MT_MENU,    ST_SINEGEN,     ST_DVM,         ST_INSTR,       display_instructions},
    {ST_SINEGEN,    MT_SINEGEN, ST_SCOPE,       ST_INSTR,       ST_SI_ENTER,    sinegen_display}, 
    {ST_SCOPE,      MT_SCOPE,   ST_DVM,         ST_SINEGEN,     ST_SCOPE,       clear_lowerdisplay}, 
    {ST_DVM,        MT_DVM,     ST_INSTR,       ST_SCOPE,       ST_DVM,         clear_lowerdisplay}, 
     
    //function gen sub menu 
    {ST_SI_ENTER,   MT_SINEGEN, ST_SI_ONOFF,    ST_SI_BACK,     ST_SI_ONOFF,    sinegen_enter}, // 
    {ST_SI_ONOFF,   MT_SINEGEN, ST_SI_FREQ,     ST_SI_BACK,     ST_SI_ONOFF,    sinegen_onoff}, // 
    {ST_SI_FREQ,    MT_SINEGEN, ST_SI_PERIOD,   ST_SI_ONOFF,    ST_SI_FQ_EDIT,  sinegen_freq}, 
    {ST_SI_PERIOD,  MT_SINEGEN, ST_SI_AMPL,     ST_SI_FREQ,     ST_SI_PERIOD,   sinegen_period}, 
    {ST_SI_AMPL,    MT_SINEGEN, ST_SI_OFFSET,   ST_SI_PERIOD,   ST_SI_AMPL,     sinegen_amplitude},
    {ST_SI_OFFSET,  MT_SINEGEN, ST_SI_BACK,     ST_SI_AMPL,     ST_SI_OFFSET,   sinegen_offset}, 
    {ST_SI_BACK,    MT_SINEGEN, ST_SI_ONOFF,    ST_SI_OFFSET,   ST_SINEGEN,     sinegen_back},
    
    {ST_SI_FQ_EDIT, MT_SINEGEN, ST_SI_FQ_EDIT, ST_SI_FQ_EDIT,   ST_SI_FREQ,     sinegen_freq_edit}, 


};


void navigate_menu(){
    newstate = currentstate;
    //loop through all the states looking for the current state
    //  then lookup what the next state will be
    for (volatile uint8 i=0; menu[i].state; i++){
        if (menu[i].state == currentstate && button == SELECT){
            newstate = menu[i].select;  
            break;
        }
        //navigating main or submenu action the buttons as navigation control
        if (menu[i].state == currentstate && button == UP){
            if (menu_mode != edit) 
                newstate = menu[i].up;
            break;
        }
        if (menu[i].state == currentstate && button == DOWN){
            if (menu_mode != edit)
                newstate = menu[i].down;
            break;
        }
        if (menu[i].state == currentstate && button == LEFT){
            if (menu_mode != edit)
                newstate = menu[i].up;  
            break;
        }
        if (menu[i].state == currentstate && button == RIGHT){
            if (menu_mode != edit)
                newstate = menu[i].down;  
            break;
        }
    }    
    menu_item = set_state(newstate);
    if (menu[menu_item].fp != 0){
         menu[menu_item].fp();
    }
}


//a display of where we are in the menu
//loop through the menus again looking for the nextstate
//   then displaying its text
//   and call its function
uint8 set_state (uint8 newstate){
    currentstate = newstate;
    for (int i=0; menu[i].state; i++){
        if (newstate == menu[i].state){ 
            if (newstate < ST_SI_ENTER){
                ssd_print_text("-", MENU_LEFT, MAIN_MENU_Y);
            }
            else{
               ssd_print_text("*", MENU_LEFT, MAIN_MENU_Y);
            }
            ssd_print_text(menu[i].text, MENU_X, MAIN_MENU_Y);
            display_update();
            return i;//look no further
        }
    }
    return 0;
}



void welcome_screen(){
    lowerdisplay_clear();
    gfx_setTextSize(2);

    //display_update();
    ssd_print_textline("GECKO",2);
    ssd_print_textline(" by Bill",4);
    gfx_setTextSize(1);
    CyDelay(1000);
    //gfx_setTextSize(1); //2=large 1=small
    //gfx_setTextColor(WHITE);
    //gfx_setCursor(0,0); //x,y
    ssd_print_textline("GECKO",0); 
    display_instructions();
}

void display_instructions(){
    ssd_print_text("Instructions",MENU_X,MAIN_MENU_Y);
    lowerdisplay_clear();
    ssd_print_textline("Up/down buttons to",2);
    ssd_print_textline("  scroll menu/value",3);
    ssd_print_textline("Center button to",4);
    ssd_print_textline("  select option",5);
    ssd_print_textline("Left/right button to",6);
    ssd_print_textline("  select place value",7);
}

void clear_lowerdisplay(){
    lowerdisplay_clear();
    display_update();
}

//the modes for menus
//navigating main menu, navigating submenu or editing submenu
//- these makes sure the up/down buttons do not change the menu but the item being editted
// - this determines where and whether the * or - are shown when changing between modes and editting
/*
void set_menumode_submenu_edit(){
    menu_mode = submenu_edit;
}
void set_menumode_mainmenu_navigate(){
    ssd_print_text("-", MENU_LEFT, MAIN_MENU_Y);
    menu_mode = mainmenu_navigate;
}
void set_menumode_submenu_navigate(){
    menu_mode = submenu_navigate;
    ssd_print_text("*", MENU_LEFT, MAIN_MENU_Y);
}

uint8 is_mainmenu_navigatemode(){
    if (menu_mode == mainmenu_navigate)
        return true;
    else
        return false;
}
uint8 is_submenu_navigatemode(){
    if (menu_mode == submenu_navigate)
        return true;
    else
        return false;
}
uint8 is_submenu_editmode(){
    if (menu_mode == submenu_edit)
        return true;
    else
        return false;
}
*/


/* [] END OF FILE */
