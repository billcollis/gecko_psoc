/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/


#include <project.h>
#include <stdlib.h>
#include "ssd1306.h" 
// clearing display

void scroll_psoc(void){
    gfx_setTextSize(1);
    gfx_setTextColor(WHITE);
    gfx_setCursor(0,0); //x,y

    gfx_println("PSOC");
    display_update(); 
    display_scroll(SCROLL_PAGE_0,SCROLL_PAGE_7,SCROLL_RIGHT,SCROLL_SPEED_7);
}

void display_test(void){
        

        CyDelay(1000);
        display_clear();    
        display_update();    
        int16_t i = 0;


        // drawing a pixel
        gfx_drawPixel(10, 10, 1);    //1= show 0 = black
        gfx_drawPixel(10, 15, 1);    
        gfx_drawPixel(15, 15, 1);    
        gfx_drawPixel(15, 10, 1);    
        display_update(); 
        CyDelay(3000);
//        display_clear();    
//        display_update();    

        
        // line drawing
        for( i = 0 ; i < gfx_width(); i+=4) {
            gfx_drawLine(0, 0, i, gfx_height()-1, WHITE);
            display_update();
        }
        for( i = 0 ; i < gfx_height() ; i += 4 ){
            gfx_drawLine(0, 0, gfx_width()-1, i, WHITE);
            display_update();
        }    
//     
        CyDelay(3000);
        display_clear();    
        display_update();    

        // text settings
        gfx_setTextSize(2); //2=large 1=small
        gfx_setTextColor(WHITE);
        gfx_setCursor(0,0);

         //text display
        for( i = 40 ; i < 80 ; i++){
            if( i == '\n' ) 
                continue;
            gfx_write(i);  //write ascii code
          }    
        display_update(); 
        
        CyDelay(3000);
        display_clear();    
        display_update();    
        
        // cursor
        gfx_setCursor( 0, 0 );
        
        // text sizes
        gfx_setTextSize(2);
        gfx_write( '8' );
        gfx_setTextSize(3);
        gfx_write( '8' );
        gfx_setTextSize(4);
        gfx_write( '8' );
        display_update(); 
        
        CyDelay(3000);
        display_clear();    
        display_update();    

        // line printing
        gfx_setTextSize(2);
        gfx_setTextColor(WHITE);
        gfx_setCursor(0,0);
        gfx_println("test line1");
        gfx_println("2nd line.. ");
        display_update();    

        CyDelay(3000);
        display_clear();    
        display_update();    

        
        // scrolling
        gfx_setTextSize(1);
        gfx_setTextColor(WHITE);
        gfx_setCursor(0,0);

        //print psoc 8 times ownthe display
        for( i = 1 ; i <= 8 ; i++ ){
            gfx_println("PSOC");
        }
        display_update();    
        
        
        
        display_scroll(SCROLL_PAGE_0,SCROLL_PAGE_7,SCROLL_RIGHT,SCROLL_SPEED_7);
        CyDelay(2750);
        display_stopscroll();
        display_scroll(SCROLL_PAGE_2,SCROLL_PAGE_7,SCROLL_LEFT,SCROLL_SPEED_3);
        CyDelay(5500);
        display_stopscroll();
        
        

        CyDelay(3000);
        display_clear();    
        display_update();    
        
        
        // rectangles
        for( i = 0 ; i < gfx_height()/2 ; i += 2 ){
            gfx_drawRect(i, i, gfx_width()-2*i, gfx_height()-2*i, WHITE);
            display_update();   
        }
        
        CyDelay(3000);
        display_clear();    
        display_update();    

        // filled rectangles
        uint8_t color = 1;
        for( i = 0 ; i < gfx_height()/2 ; i += 3 ){
            // alternate colors
            gfx_fillRect(i, i, gfx_width()-i*2, gfx_height()-i*2, color%2);
            display_update();    
            color++;
        }    

        CyDelay(3000);
        display_clear();    
        display_update();    
        
        // circles
        for( i = 0 ; i < gfx_height() ; i += 2 ){
            gfx_drawCircle( gfx_width()/2, gfx_height()/2, i, WHITE );
            display_update();    
        }    

        CyDelay(3000);
        display_clear();    
        display_update();    
        
        
        #define MIN(x, y) (((x) < (y)) ? (x) : (y))      
        // triangles
        for( i = 0 ; i < MIN(gfx_width(),gfx_height())/2; i+=5) {
            gfx_drawTriangle(gfx_width()/2, gfx_height()/2-i,
                             gfx_width()/2-i, gfx_height()/2+i,
                             gfx_width()/2+i, gfx_height()/2+i, WHITE);
            display_update();    
        }    
        CyDelay(3000);
        display_clear();    
        display_update();    
       
        // rotation
        int16_t j = 0;
        for( j = 0 ; j < 4 ; j++ ){
            gfx_setRotation(j);
            for( i = 0 ; i < MIN(gfx_width(),gfx_height())/2; i+=5) {
                gfx_drawTriangle(gfx_width()/2, gfx_height()/2-i,
                                 gfx_width()/2-i, gfx_height()/2+i,
                                 gfx_width()/2+i, gfx_height()/2+i, WHITE);
                display_update(); 
                CyDelay(200);
            }    
        }
        
        CyDelay(3000);
       
        // invert and dim
        display_invert(1);
        CyDelay(1000);
        
        for( i = 256 ; i >= 0 ; i-- ){
            display_contrast(i); 
            CyDelay(10);
        }
        
        
        
        display_invert(0);
        CyDelay(1000);
        for( i = 0 ; i < 256 ; i++ ){
            display_contrast(i); 
            CyDelay(10);
        }
        
    
        CyDelay(3000);
        
}



/* [] END OF FILE */