/** @file ssd1306.h
*
* SSD1306 OLED - I2C driver
* 
* Derk Steggewentz, 3/2015 
* 
* This is a I2C driver for SSD1306 OLED displays including graphics library.
* 
*
* 
*/

#ifndef _SSD1306_H
#define _SSD1306_H
    
    
#include "stdio.h" 
#include <project.h>
    
    
//externally available defines and structures     
#define BLACK 0
#define WHITE 1
#define INVERSE 2   

#define LINE0 0
#define LINE1 8
#define LINE2 16
#define LINE3 24
#define LINE4 32
#define LINE5 40
#define LINE6 48
#define LINE7 56
    
typedef enum{
    SCROLL_RIGHT = 0x26,
    SCROLL_LEFT = 0x2A
}SCROLL_DIR;

typedef enum{
    SCROLL_SPEED_0 = 0x03,  // slowest
    SCROLL_SPEED_1 = 0x02,
    SCROLL_SPEED_2 = 0x01,
    SCROLL_SPEED_3 = 0x06,
    SCROLL_SPEED_4 = 0x00,
    SCROLL_SPEED_5 = 0x05,
    SCROLL_SPEED_6 = 0x04,
    SCROLL_SPEED_7 = 0x07   // fastest
}SCROLL_SPEED;

typedef enum{
    SCROLL_PAGE_0 = 0,
    SCROLL_PAGE_1,
    SCROLL_PAGE_2,
    SCROLL_PAGE_3,
    SCROLL_PAGE_4,
    SCROLL_PAGE_5,
    SCROLL_PAGE_6,
    SCROLL_PAGE_7   
}SCROLL_AREA;


//line number 0 to 7 for font size 1
//line number 0 to 3 for font size 2

void display_init(uint8_t textsize); //BC modified
void display_update(void);
void display_clear(void);
void display_stopscroll(void);
void display_scroll( SCROLL_AREA start, SCROLL_AREA end, SCROLL_DIR dir, SCROLL_SPEED speed );
void display_contrast( uint8_t contrast );
void display_invert( uint8_t invert );

void gfx_drawPixel(int16_t x, int16_t y, uint16_t color);
void gfx_drawLine( int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color );
void gfx_setCursor( int16_t x, int16_t y );
void gfx_setTextSize( uint8_t size );
void gfx_setTextColor( uint16_t color );
void gfx_setTextBg( uint16_t background );
void gfx_write( uint8_t ch );
int16_t gfx_width(void);
int16_t gfx_height(void);
void gfx_print( const char* s );
void gfx_println( const char* s );
void gfx_drawRect( int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color );
void gfx_fillRect( int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color );
void gfx_drawCircle( int16_t x0, int16_t y0, int16_t r,uint16_t color );
void gfx_drawTriangle( int16_t x0, int16_t y0,int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color );
void gfx_setRotation( uint8_t x );


void ssd_print_textline(const char* txt,uint8_t linenumber);
void ssd_print_int(int number, uint8_t x, uint8_t y);
void ssd_print_float(float number, uint8_t x, uint8_t y);
void lowerdisplay_clear(void);
void lowerdisplay_fill(void);
void ssd_print_text (const char*txt, uint8_t x, uint8_t y);


#endif	// _SSD1306_H



/* [] END OF FILE */
