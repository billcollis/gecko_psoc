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



#ifndef _MENU_H
#define _MENU_H
    
    
#include "project.h"
    
    
    
/***************************************
*           Constants
***************************************/    
#define MENU_LEFT 0
#define MENU_X 8 //8 pixels in
#define MAIN_MENU_Y 8 //8 pixels down
#define MAIN_MENU_LINE LINE1 // 1= second line

//menu items
#define ST_INSTR 1
#define ST_SINEGEN 2
#define ST_SCOPE 3
#define ST_DVM 4 

#define ST_SI_ENTER     0x10
#define ST_SI_ONOFF     0x11    
#define ST_SI_FREQ      0x12
#define ST_SI_FQ_EDIT   0x13
#define ST_SI_AMPL      0x14
#define ST_SI_PERIOD    0x15
#define ST_SI_OFFSET    0x16
#define ST_SI_BACK      0x17
 

  
typedef const struct
{
    int state;
    const char *text; 
    int down;
    int up;
    int select; 
    void ( *fp ) (); //function to call 
}MenuEntry;

enum uint8 { navigate, edit};

/***************************************
*        Function Prototypes
***************************************/
void navigate_menu();
void edit_menu();
uint8 set_state (uint8 nextstate); //allow some other function to set the state
void welcome_screen();
void display_instructions();
void clear_lowerdisplay();
void set_menumode_submenu_edit();
void set_menumode_mainmenu_navigate();
void set_menumode_submenu_navigate();
uint8 is_mainmenu_navigatemode();
uint8 is_submenu_navigatemode();
uint8 is_submenu_editmode();

#endif
    
    




/* [] END OF FILE */
