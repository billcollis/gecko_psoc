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
#include "project.h"
#include "menu.h"
#include "ssd1306.h"
#include "functiongen.h"
#include "keypad.h"

//putting these into ram significantly improves the range
//must be const to leave in flash, can add CYCODE as well - even through this appeared to do nothing beyong cocnst at a debug level of optimization
uint8 WaveDAC_wave1023[1023u] = { 128u,128u,129u,130u,131u,131u,132u,133u,134u,134u,135u,136u,137u,137u,138u,139u,140u,141u,141u,142u,143u,144u,144u,145u,146u,147u,147u,148u,149u,150u,150u,151u,152u,153u,153u,154u,155u,156u,156u,157u,158u,159u,159u,160u,161u,162u,162u,163u,164u,165u,165u,166u,167u,167u,168u,169u,170u,170u,171u,172u,173u,173u,174u,175u,175u,176u,177u,177u,178u,179u,180u,180u,181u,182u,182u,183u,184u,184u,185u,186u,186u,187u,188u,188u,189u,190u,190u,191u,192u,192u,193u,194u,194u,195u,196u,196u,197u,198u,198u,199u,200u,200u,201u,201u,202u,203u,203u,204u,204u,205u,206u,206u,207u,207u,208u,209u,209u,210u,210u,211u,212u,212u,213u,213u,214u,214u,215u,215u,216u,216u,217u,218u,218u,219u,219u,220u,220u,221u,221u,222u,222u,223u,223u,224u,224u,225u,225u,226u,226u,227u,227u,228u,228u,228u,229u,229u,230u,230u,231u,231u,232u,232u,232u,233u,233u,234u,234u,234u,235u,235u,236u,236u,236u,237u,237u,237u,238u,238u,239u,239u,239u,240u,240u,240u,241u,241u,241u,242u,242u,242u,242u,243u,243u,243u,244u,244u,244u,244u,245u,245u,245u,245u,246u,246u,246u,246u,247u,247u,247u,247u,248u,248u,248u,248u,248u,249u,249u,249u,249u,249u,249u,250u,250u,250u,250u,250u,250u,251u,251u,251u,251u,251u,251u,251u,251u,251u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,251u,251u,251u,251u,251u,251u,251u,251u,250u,250u,250u,250u,250u,250u,250u,249u,249u,249u,249u,249u,249u,248u,248u,248u,248u,247u,247u,247u,247u,247u,246u,246u,246u,246u,245u,245u,245u,245u,244u,244u,244u,243u,243u,243u,243u,242u,242u,242u,241u,241u,241u,240u,240u,240u,239u,239u,239u,238u,238u,238u,237u,237u,237u,236u,236u,235u,235u,235u,234u,234u,233u,233u,233u,232u,232u,231u,231u,230u,230u,230u,229u,229u,228u,228u,227u,227u,226u,226u,225u,225u,224u,224u,223u,223u,222u,222u,221u,221u,220u,220u,219u,219u,218u,218u,217u,217u,216u,216u,215u,215u,214u,213u,213u,212u,212u,211u,211u,210u,210u,209u,208u,208u,207u,207u,206u,205u,205u,204u,204u,203u,202u,202u,201u,200u,200u,199u,199u,198u,197u,197u,196u,195u,195u,194u,193u,193u,192u,191u,191u,190u,190u,189u,188u,187u,187u,186u,185u,185u,184u,183u,183u,182u,181u,181u,180u,179u,179u,178u,177u,176u,176u,175u,174u,174u,173u,172u,171u,171u,170u,169u,169u,168u,167u,166u,166u,165u,164u,163u,163u,162u,161u,161u,160u,159u,158u,158u,157u,156u,155u,155u,154u,153u,152u,152u,151u,150u,149u,149u,148u,147u,146u,145u,145u,144u,143u,142u,142u,141u,140u,139u,139u,138u,137u,136u,136u,135u,134u,133u,132u,132u,131u,130u,129u,129u,128u,127u,126u,126u,125u,124u,123u,123u,122u,121u,120u,119u,119u,118u,117u,116u,116u,115u,114u,113u,113u,112u,111u,110u,110u,109u,108u,107u,106u,106u,105u,104u,103u,103u,102u,101u,100u,100u,99u,98u,97u,97u,96u,95u,94u,94u,93u,92u,92u,91u,90u,89u,89u,88u,87u,86u,86u,85u,84u,84u,83u,82u,81u,81u,80u,79u,79u,78u,77u,76u,76u,75u,74u,74u,73u,72u,72u,71u,70u,70u,69u,68u,68u,67u,66u,65u,65u,64u,64u,63u,62u,62u,61u,60u,60u,59u,58u,58u,57u,56u,56u,55u,55u,54u,53u,53u,52u,51u,51u,50u,50u,49u,48u,48u,47u,47u,46u,45u,45u,44u,44u,43u,43u,42u,42u,41u,40u,40u,39u,39u,38u,38u,37u,37u,36u,36u,35u,35u,34u,34u,33u,33u,32u,32u,31u,31u,30u,30u,29u,29u,28u,28u,27u,27u,26u,26u,25u,25u,25u,24u,24u,23u,23u,22u,22u,22u,21u,21u,20u,20u,20u,19u,19u,18u,18u,18u,17u,17u,17u,16u,16u,16u,15u,15u,15u,14u,14u,14u,13u,13u,13u,12u,12u,12u,12u,11u,11u,11u,10u,10u,10u,10u,9u,9u,9u,9u,8u,8u,8u,8u,8u,7u,7u,7u,7u,6u,6u,6u,6u,6u,6u,5u,5u,5u,5u,5u,5u,5u,4u,4u,4u,4u,4u,4u,4u,4u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,4u,4u,4u,4u,4u,4u,4u,4u,4u,5u,5u,5u,5u,5u,5u,6u,6u,6u,6u,6u,6u,7u,7u,7u,7u,7u,8u,8u,8u,8u,9u,9u,9u,9u,10u,10u,10u,10u,11u,11u,11u,11u,12u,12u,12u,13u,13u,13u,13u,14u,14u,14u,15u,15u,15u,16u,16u,16u,17u,17u,18u,18u,18u,19u,19u,19u,20u,20u,21u,21u,21u,22u,22u,23u,23u,23u,24u,24u,25u,25u,26u,26u,27u,27u,27u,28u,28u,29u,29u,30u,30u,31u,31u,32u,32u,33u,33u,34u,34u,35u,35u,36u,36u,37u,37u,38u,39u,39u,40u,40u,41u,41u,42u,42u,43u,43u,44u,45u,45u,46u,46u,47u,48u,48u,49u,49u,50u,51u,51u,52u,52u,53u,54u,54u,55u,55u,56u,57u,57u,58u,59u,59u,60u,61u,61u,62u,63u,63u,64u,65u,65u,66u,67u,67u,68u,69u,69u,70u,71u,71u,72u,73u,73u,74u,75u,75u,76u,77u,78u,78u,79u,80u,80u,81u,82u,82u,83u,84u,85u,85u,86u,87u,88u,88u,89u,90u,90u,91u,92u,93u,93u,94u,95u,96u,96u,97u,98u,99u,99u,100u,101u,102u,102u,103u,104u,105u,105u,106u,107u,108u,108u,109u,110u,111u,111u,112u,113u,114u,114u,115u,116u,117u,118u,118u,119u,120u,121u,121u,122u,123u,124u,124u,125u,126u,127u };
uint8 WaveDAC_wave511[511u] = { 128u,129u,131u,132u,134u,135u,137u,138u,140u,141u,143u,144u,146u,147u,149u,150u,152u,153u,155u,156u,158u,159u,161u,162u,164u,165u,167u,168u,170u,171u,173u,174u,175u,177u,178u,180u,181u,182u,184u,185u,187u,188u,189u,191u,192u,193u,194u,196u,197u,198u,200u,201u,202u,203u,205u,206u,207u,208u,209u,210u,212u,213u,214u,215u,216u,217u,218u,219u,220u,221u,222u,223u,224u,225u,226u,227u,228u,229u,230u,231u,232u,232u,233u,234u,235u,236u,236u,237u,238u,239u,239u,240u,241u,241u,242u,243u,243u,244u,244u,245u,245u,246u,246u,247u,247u,248u,248u,248u,249u,249u,250u,250u,250u,250u,251u,251u,251u,251u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,251u,251u,251u,251u,250u,250u,250u,249u,249u,249u,248u,248u,247u,247u,247u,246u,246u,245u,245u,244u,243u,243u,242u,242u,241u,240u,240u,239u,238u,238u,237u,236u,235u,234u,234u,233u,232u,231u,230u,229u,228u,228u,227u,226u,225u,224u,223u,222u,221u,220u,219u,218u,217u,215u,214u,213u,212u,211u,210u,209u,208u,206u,205u,204u,203u,201u,200u,199u,198u,196u,195u,194u,193u,191u,190u,189u,187u,186u,184u,183u,182u,180u,179u,178u,176u,175u,173u,172u,170u,169u,168u,166u,165u,163u,162u,160u,159u,157u,156u,154u,153u,151u,150u,148u,147u,145u,144u,142u,141u,139u,137u,136u,134u,133u,131u,130u,128u,127u,125u,124u,122u,121u,119u,118u,116u,114u,113u,111u,110u,108u,107u,105u,104u,102u,101u,99u,98u,96u,95u,93u,92u,90u,89u,87u,86u,85u,83u,82u,80u,79u,77u,76u,75u,73u,72u,71u,69u,68u,66u,65u,64u,62u,61u,60u,59u,57u,56u,55u,54u,52u,51u,50u,49u,47u,46u,45u,44u,43u,42u,41u,40u,38u,37u,36u,35u,34u,33u,32u,31u,30u,29u,28u,27u,27u,26u,25u,24u,23u,22u,21u,21u,20u,19u,18u,17u,17u,16u,15u,15u,14u,13u,13u,12u,12u,11u,10u,10u,9u,9u,8u,8u,8u,7u,7u,6u,6u,6u,5u,5u,5u,4u,4u,4u,4u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,4u,4u,4u,4u,5u,5u,5u,5u,6u,6u,7u,7u,7u,8u,8u,9u,9u,10u,10u,11u,11u,12u,12u,13u,14u,14u,15u,16u,16u,17u,18u,19u,19u,20u,21u,22u,23u,23u,24u,25u,26u,27u,28u,29u,30u,31u,32u,33u,34u,35u,36u,37u,38u,39u,40u,41u,42u,43u,45u,46u,47u,48u,49u,50u,52u,53u,54u,55u,57u,58u,59u,61u,62u,63u,64u,66u,67u,68u,70u,71u,73u,74u,75u,77u,78u,80u,81u,82u,84u,85u,87u,88u,90u,91u,93u,94u,96u,97u,99u,100u,102u,103u,105u,106u,108u,109u,111u,112u,114u,115u,117u,118u,120u,121u,123u,124u,126u };
uint8 WaveDAC_wave255[255u] = { 128u,131u,134u,137u,140u,143u,146u,149u,152u,155u,158u,161u,164u,167u,170u,173u,176u,178u,181u,184u,187u,189u,192u,195u,197u,200u,202u,205u,207u,209u,212u,214u,216u,218u,220u,222u,224u,226u,228u,230u,232u,233u,235u,237u,238u,239u,241u,242u,243u,244u,245u,246u,247u,248u,249u,250u,250u,251u,251u,252u,252u,252u,252u,252u,252u,252u,252u,252u,252u,251u,251u,251u,250u,249u,249u,248u,247u,246u,245u,244u,243u,241u,240u,239u,237u,236u,234u,233u,231u,229u,227u,225u,223u,221u,219u,217u,215u,213u,211u,208u,206u,203u,201u,198u,196u,193u,191u,188u,185u,183u,180u,177u,174u,171u,168u,165u,162u,159u,156u,153u,150u,147u,144u,141u,138u,135u,132u,129u,126u,123u,120u,117u,114u,111u,108u,105u,102u,99u,96u,93u,90u,87u,84u,81u,78u,75u,72u,70u,67u,64u,62u,59u,57u,54u,52u,49u,47u,44u,42u,40u,38u,36u,34u,32u,30u,28u,26u,24u,22u,21u,19u,18u,16u,15u,14u,12u,11u,10u,9u,8u,7u,6u,6u,5u,4u,4u,4u,3u,3u,3u,3u,3u,3u,3u,3u,3u,3u,4u,4u,5u,5u,6u,7u,8u,9u,10u,11u,12u,13u,14u,16u,17u,18u,20u,22u,23u,25u,27u,29u,31u,33u,35u,37u,39u,41u,43u,46u,48u,50u,53u,55u,58u,60u,63u,66u,68u,71u,74u,77u,79u,82u,85u,88u,91u,94u,97u,100u,103u,106u,109u,112u,115u,118u,121u,124u };
uint8 WaveDAC_wave127[127u] = { 128u,134u,140u,146u,152u,158u,164u,170u,176u,181u,187u,192u,197u,202u,207u,212u,216u,221u,225u,228u,232u,235u,238u,241u,243u,246u,247u,249u,250u,251u,252u,252u,252u,252u,252u,251u,250u,248u,247u,245u,242u,240u,237u,234u,230u,227u,223u,219u,214u,210u,205u,200u,195u,190u,184u,179u,173u,167u,161u,155u,149u,143u,137u,131u,124u,118u,112u,106u,100u,94u,88u,82u,76u,71u,65u,60u,55u,50u,45u,41u,36u,32u,28u,25u,21u,18u,15u,13u,10u,8u,7u,5u,4u,3u,3u,3u,3u,3u,4u,5u,6u,8u,9u,12u,14u,17u,20u,23u,27u,30u,34u,39u,43u,48u,53u,58u,63u,68u,74u,79u,85u,91u,97u,103u,109u,115u,121u };
uint8 WaveDAC_wave63[63u] = { 128u,140u,152u,164u,176u,187u,198u,208u,217u,225u,233u,239u,244u,248u,251u,252u,252u,252u,249u,246u,241u,236u,229u,221u,213u,203u,193u,182u,170u,158u,146u,134u,121u,109u,97u,85u,73u,62u,52u,42u,34u,26u,19u,14u,9u,6u,3u,3u,3u,4u,7u,11u,16u,22u,30u,38u,47u,57u,68u,79u,91u,103u,115u };
uint8 WaveDAC_wave31[31u] = { 128u,153u,177u,199u,218u,234u,245u,251u,252u,249u,240u,226u,209u,188u,165u,140u,115u,90u,67u,46u,29u,15u,6u,3u,4u,10u,21u,37u,56u,78u,102u };


/* functiongen vars */
volatile FGen_Specifications_Struct fgen_specs;
volatile FGen_Enable_Struct fgen_enablestate;
volatile uint16 fgen_sample_size = FGEN_SAMPLE_SIZE_1023; //initialised for 1kHz 


/* keypad vars */
extern uint8_t button;
/* Menu vars */
extern uint8_t currentstate;
extern uint8_t newstate;
extern uint8 menu_nav_edit;
  
void fgen_init(){
    //load 1kHz into WaveDAC and DDS
    new_wavedac_setting(FGEN_SAMPLE_SIZE_1023, FGEN_INIT_FREQ);
    //DDS_Stop();
    //WaveDAC_Stop();
}


void fgen_setup_screen(){
    if (button == NONE){
        return;
    }
    lowerdisplay_clear();
    ssd_print_text(MT_ONOFF,MENU_X,FGEN_OUTPUT_Y);
    ssd_print_text(MT_SHAPE,MENU_X,FGEN_SHAPE_Y);
    ssd_print_text(MT_FREQ,MENU_X,FGEN_FREQ_Y);
    ssd_print_text(MT_PERIOD,MENU_X,FGEN_PERIOD_Y);
    ssd_print_text(MT_AMPL,MENU_X,FGEN_AMPLITUDE_Y);
    ssd_print_text(MT_OFFSET,MENU_X,FGEN_OFFSET_Y);
    display_update();
} 

//get the text to display upon the lcd
const char* get_shape_text_from_state(uint8_t var){
    switch(var){
        case ST_SINE:
            return MT_SINE;
        case ST_SQUARE:
            return MT_SQUARE;
        case ST_SAW:
            return MT_SAW;
        case ST_TRI:
            return MT_TRI;
        case ST_PWM:
            return MT_PWM;
    }
    return MT_EXIT;
}
//get the text to display upon the lcd
const char* get_shape_text_from_enum(uint8_t var){
    switch(var){
        case Sine:
            return MT_SINE;
        case Square:
            return MT_SQUARE;
        case Sawtooth:
            return MT_SAW;
        case Triangle:
            return MT_TRI;
        case PWM:
            return MT_PWM;
    }
    return MT_EXIT;
}

void fgen_show_values(void){
    char text[15];
    if (fgen_enablestate.enable == 0u){
        ssd_print_text("On",FGEN_CENTER_X,FGEN_OUTPUT_Y);
    }
    else{
        ssd_print_text("Off ",FGEN_CENTER_X,FGEN_OUTPUT_Y);
    }
    
    const char* shape_text = get_shape_text_from_enum(fgen_specs.shape);
    ssd_print_text(shape_text,FGEN_CENTER_X,FGEN_SHAPE_Y);
    
    sprintfcomma(fgen_specs.frequency,text,1,"Hz");
    ssd_print_text(text,FGEN_CENTER_X,FGEN_FREQ_Y);
    
    sprintfcomma(fgen_specs.period,text,1,"ms");
    ssd_print_text(text,FGEN_CENTER_X,FGEN_PERIOD_Y);
        
    sprintfcomma(fgen_specs.amplitude,text,1,"V");
    ssd_print_text(text,FGEN_CENTER_X,FGEN_AMPLITUDE_Y);
    
    sprintfcomma(fgen_specs.offset,text,1,"V");
    ssd_print_text(text,FGEN_CENTER_X,FGEN_OFFSET_Y);
    
    display_update();
}
   
void select_new_shape(uint8 var){
    switch(var){
        case ST_SQUARE:
            fgen_specs.shape = Square;
            break;
        case ST_SAW:
            fgen_specs.shape = Sawtooth;
            break;
        case ST_TRI:
            fgen_specs.shape = Triangle;
            break;
        case ST_PWM:
            fgen_specs.shape = PWM;
            break;
        default:
            fgen_specs.shape = Sine;
            break;
    }

}

void sprintfcomma (uint32 n, char *text, uint8 decimal, char *suffix) {
    uint16_t upper=0,middle=0;
    if (decimal == 0){ //no decimal places
        if (n > 999999){
            upper = n/1000000;
            n -= upper *1000000;
            middle = n/1000;
            n -= middle*1000;
            sprintf(text, "%3hu,%03hu,%03lu",upper,middle,n);
        }
        else if (n > 999){
            middle = n/1000;
            n-=middle*1000;
            sprintf(text, "    %3hu,%03lu",middle,n);

        }else{
            sprintf(text, "        %03lu",n);
        }
    }
    if (decimal == 1){ //3 decimal places
        if (n > 999999){
            upper = n/1000000;
            n -= upper *1000000;
            middle = n/1000;
            n -= middle*1000;
            sprintf(text, "%3hu,%03hu.%03lu",upper,middle,n);
        }
        else if (n > 999){
            middle = n/1000;
            n-=middle*1000;
            sprintf(text, "    %3hu.%03lu",middle,n);

        }else{
            sprintf(text, "      0.%03lu",n);
        }
    }
    strcat (text,suffix);
}

void longtotext(uint32_t number, char *text, char *suffix){
    uint32_t temp=number;
    uint16_t upper=0,middle=0,lower=0;
    char up[6];
    char mid[5];
    char low[5];
    text[0] = '\0';
    if (temp>999999){ // upper with ',' //get first three digits 
        upper = temp/1000000;
        temp -=(upper *1000000);
        sprintf (up, "%2d", upper);// 2digits needed - make sure it has leading spaces
        strcat(up,",");
        strcat(text,up);
    }else{
        strcpy(up, "   "); //insert 3 leading spaces to replace 'dd,'
        strcat(text,up);
    }
    
    if (temp>999){  //get middle 3 digits 
        middle = temp/1000;
        temp -=(middle *1000);
        if (upper == 0){
            sprintf(mid,"%3d",middle); //use leading spaces 
        }else{
            sprintf(mid,"%03d",middle); //fill in zeros
        }
        //add any 0 digits if needed
        if (upper !=0 && middle < 100)
            strcat(text,"0");
        if (upper !=0 && middle < 10)
            strcat(text,"0");
        strcat(text,mid);
        strcat(text,".");
    }else if (upper == 0 ){
        strcpy(up, "  0."); //format nicely for  
        strcat(text,up);
    }else {
        strcat(text,"000."); //format nicely 
    }
            
    if (temp > 0){
        lower = temp;
        sprintf(low, "%03d",lower);   
        strcat(text,low);
    }else{
        strcat(text, "000"); //format nicely for
    }

    strcat(text,suffix);
}

void fgen_open(){
    fgen_setup_screen();
    fgen_show_values();
    button=NONE;
}
void fgen_onoff(){
    fgen_remove_indicators();
    ssd_print_text("-", FGEN_LEFT_X, FGEN_OUTPUT_Y);
    //only process a select button if in the state  -stops selection when naigating
    if (button == SELECT && currentstate == ST_FG_ONOFF){ //changes the output
        if (fgen_enablestate.enable == 0u){ //off
            fgen_enablestate.enable=1;
            ssd_print_text("On ",FGEN_CENTER_X,FGEN_OUTPUT_Y);
            WaveDAC_Wakeup();
            DDS_Enable();
        }else{
            fgen_enablestate.enable=0;
            ssd_print_text("Off",FGEN_CENTER_X,FGEN_OUTPUT_Y);
            WaveDAC_Sleep();
            DDS_Stop();
        }
    }
    display_update();
}

void fgen_shape(){
    static uint8 modifying =0;
    fgen_remove_indicators();
    
    const char* shape_text;
    
    //no action on up/down/left/right buttons - just display the shape in use
    if (modifying == 0){
        if (button == SELECT){
            ssd_print_text("*", FGEN_LEFT_X, FGEN_SHAPE_Y);
            shape_text = get_shape_text_from_enum(fgen_specs.shape);
            ssd_print_text(shape_text, FGEN_CENTER_X, FGEN_SHAPE_Y);
            modifying = 1;
       }else{
            ssd_print_text("-", FGEN_LEFT_X, FGEN_SHAPE_Y);
       }
    }
    
    else if (modifying>0){
        if (button==LEFT || button == DOWN){
           ssd_print_text("*", FGEN_LEFT_X, FGEN_SHAPE_Y);
            shape_text = get_shape_text_from_state(newstate);
           ssd_print_text(shape_text, FGEN_CENTER_X, FGEN_SHAPE_Y);
        }
        else if (button==RIGHT || button == UP){
            ssd_print_text("*", FGEN_LEFT_X, FGEN_SHAPE_Y);
            shape_text = get_shape_text_from_state(newstate);
            ssd_print_text(shape_text, FGEN_CENTER_X, FGEN_SHAPE_Y);
        }
        else if(button==SELECT){ 
            ssd_print_text("-", FGEN_LEFT_X, FGEN_SHAPE_Y);
            shape_text = get_shape_text_from_state(newstate);
            select_new_shape(currentstate); 
            set_state(ST_SHAPE); //finished setting go back to FG menu 
            ssd_print_text(shape_text, FGEN_CENTER_X, FGEN_SHAPE_Y);
            modifying = 0;
        }
    }
    display_update(); //at the end to make sure any changes get shown
}
void fgen_freq(){
    char text[15];
    static int8 digit_x = FGEN_LEFT_DIGIT; //start at left hand side(0)
    fgen_remove_indicators();
    
    if (menu_nav_edit == navigate){
        if (button == SELECT && currentstate == ST_FREQ){
            ssd_print_text("*", FGEN_LEFT_X, FGEN_FREQ_Y);
            menu_nav_edit = edit;
        }
        else{
            ssd_print_text("-", FGEN_LEFT_X, FGEN_FREQ_Y);
        }
    }
    else {
        if (button == LEFT){ //navigate through digits
            remove_underline(FGEN_FREQ_Y + DIGIT_HEIGHT - 1);
            display_update();
            --digit_x;
            if (digit_x < FGEN_LEFT_DIGIT){ //gone past left digit, move to last digit
                digit_x = FGEN_RIGHT_DIGIT;
            }
            if (digit_x == COMMA){
                digit_x --;
            }
            if (digit_x == DECIMAL_POINT){
                digit_x --;
            }
        }
        else if (button == RIGHT){ //navigate through digits
            remove_underline(FGEN_FREQ_Y + DIGIT_HEIGHT - 1);
            display_update();
            digit_x ++;
            if (digit_x > FGEN_RIGHT_DIGIT){
                digit_x = FGEN_LEFT_DIGIT;
            }
            if (digit_x == COMMA){
                digit_x ++;
            }
            if (digit_x == DECIMAL_POINT){
                digit_x ++;
            }
        }
        else if (button == UP){ //increase current digit
            fgen_specs.frequency += get_freq_incr_decr(digit_x);
            if (fgen_specs.frequency > FGEN_MAX_FREQ){
                fgen_specs.frequency = FGEN_MAX_FREQ;
            }
            sprintfcomma(fgen_specs.frequency,text,1,"Hz");
            ssd_print_text(text,FGEN_CENTER_X,FGEN_FREQ_Y);
            sendFreqToDDS_WaveDAC(fgen_specs.frequency);
        }
        else if (button == DOWN){//decrease current digit
            fgen_specs.frequency -= get_freq_incr_decr(digit_x);
            if (fgen_specs.frequency > FGEN_MAX_FREQ){
                fgen_specs.frequency = 1u;
            }
            if (fgen_specs.frequency == 0){
                fgen_specs.frequency = 1u;
            }
            sendFreqToDDS_WaveDAC(fgen_specs.frequency);
            sprintfcomma(fgen_specs.frequency,text,1,"Hz");
            ssd_print_text(text,FGEN_CENTER_X,FGEN_FREQ_Y);
        }
        else{//button == SELECT
            menu_nav_edit = navigate; //back to 
            ssd_print_text("-", FGEN_LEFT_X, FGEN_FREQ_Y);
            set_state(ST_SHAPE); //finished setting go back to FG menu 
        }  
        underline(digit_x, FGEN_FREQ_Y + DIGIT_HEIGHT - 1);
    }
    //work out period in uS
    double period = fgen_specs.frequency;
    period = 1000000000 / period;
    if (period > 999999999){
        period = 999999999;
    }
    fgen_specs.period = (uint32) period;
    sprintfcomma(fgen_specs.period,text,1,"ms");
    ssd_print_text(text,FGEN_CENTER_X,FGEN_PERIOD_Y);
   
    display_update();
}
void sendFreqToDDS_WaveDAC(uint32 freq){
    //freq is in milli Hz
    uint16 samples = 0; //FGEN_SAMPLE_SIZE_1023; //default for 1kHz
    uint32 dds_freq = 1000000 * 2048 / 1000; //default: 1kHz and 2048 samples
    /*
    samples  |   freq range
    /32             75kHz
    /64             35kHz
    /128           18kHz
    /256            9kHz
    /512            4.5kHz
    /1024          2.2kHz
    /2048          1.1kHz
    /4000           500Hz
    */
    if (freq > FGEN_MAX_FREQ)
    {
        freq = FGEN_MAX_FREQ;
    }
    if (freq > FGEN_CUTOVER_1){ //up to 75kHz
        samples = FGEN_SAMPLE_SIZE_31;
    }else if (freq > FGEN_CUTOVER_2){ //up to 35kHz
        samples = FGEN_SAMPLE_SIZE_63;
    }else if (freq >  FGEN_CUTOVER_3){ //up to 18kHz
        samples = FGEN_SAMPLE_SIZE_127;
    }else if (freq >   FGEN_CUTOVER_4){ //up to 9kHz
        samples = FGEN_SAMPLE_SIZE_255;
    }else if (freq >   FGEN_CUTOVER_5){ //up to 4.5kHz
        samples =  FGEN_SAMPLE_SIZE_511;
    }else { //up to 2.2kHz
        samples =  FGEN_SAMPLE_SIZE_1023; 
    }

    dds_freq = freq * samples / 1000 ;
    
    //only change the wavdac if new range is required
    if (samples == fgen_sample_size){
        DDS_SetFrequency(dds_freq);
        return;
    }else {
        new_wavedac_setting(samples, dds_freq);
    }
    
}
void new_wavedac_setting(uint16 samples, uint32 dds_freq){
        WaveDAC_Stop();
    if (FGEN_SAMPLE_SIZE_31 == samples){ //up to 75kHz
        WaveDAC_Wave1Setup(WaveDAC_wave31, FGEN_SAMPLE_SIZE_31) ;
    }else if (FGEN_SAMPLE_SIZE_63 == samples){ //up to 35kHz
        WaveDAC_Wave1Setup(WaveDAC_wave63, FGEN_SAMPLE_SIZE_63) ;
    }else if (FGEN_SAMPLE_SIZE_127 == samples){ //up to 18kHz
        WaveDAC_Wave1Setup(WaveDAC_wave127, FGEN_SAMPLE_SIZE_127) ;
    }else if (FGEN_SAMPLE_SIZE_255 == samples){ //up to 9kHz
        WaveDAC_Wave1Setup(WaveDAC_wave255, FGEN_SAMPLE_SIZE_255) ;
    }else if (FGEN_SAMPLE_SIZE_511 == samples){ //up to 4.5kHz
        WaveDAC_Wave1Setup(WaveDAC_wave511, FGEN_SAMPLE_SIZE_511) ;
    }else { //up to 2.2kHz
        WaveDAC_Wave1Setup(WaveDAC_wave1023, FGEN_SAMPLE_SIZE_1023) ;
    }
    fgen_sample_size = samples; //save new sample size
    DDS_SetFrequency(dds_freq);// load new freq into DDS
    WaveDAC_Start();

}
uint32 get_freq_incr_decr (int8 digit){
    //note digits 3 and 7 are the ',' and '.' and are not used
    switch (digit){
        case 0:
         return 100000000u;
        case 1:
         return 10000000u;
        case 2:
         return 1000000u;
        case 4:
         return 100000u;
        case 5:
         return 10000u;
        case 6:
         return 1000u;
        case 8:
         return 100u;
        case 9:
         return 10u;
        default:
         return 1u;
    }
}

void underline(int8 digit, uint8 line){
    uint8 x =  FGEN_CENTER_X + digit * DIGIT_WIDTH; 
    gfx_drawLine (x , line, x + DIGIT_WIDTH , line, 1);
}
void remove_underline (uint8 line){
    gfx_drawLine (FGEN_CENTER_X , line, FGEN_CENTER_X + FGEN_RIGHT_DIGIT * DIGIT_WIDTH , line, 0);
}

void fgen_period(){
    fgen_remove_indicators();
    ssd_print_text("-", FGEN_LEFT_X, FGEN_PERIOD_Y);
    display_update();
}
void fgen_amplitude(){
    char text[15];
    static int8 digit_x = FGEN_LEFT_V_DIGIT; //start at digit 6
    fgen_remove_indicators();
    if (menu_nav_edit == navigate){
        if (button == SELECT && currentstate == ST_AMPL){
            ssd_print_text("*", FGEN_LEFT_X, FGEN_AMPLITUDE_Y);
            menu_nav_edit = edit;
        }
        else{
            ssd_print_text("-", FGEN_LEFT_X, FGEN_AMPLITUDE_Y);
        }
    }
    else {
        if (button == LEFT){ //navigate through digits
            remove_underline(FGEN_AMPLITUDE_Y + DIGIT_HEIGHT - 1);
            display_update();
            --digit_x;
            if (digit_x < FGEN_LEFT_V_DIGIT){ //gone past left digit, move to last digit
                digit_x = FGEN_RIGHT_DIGIT;
            }
            if (digit_x == DECIMAL_POINT){
                digit_x --;
            }
        }
        else if (button == RIGHT){ //navigate through digits
            remove_underline(FGEN_AMPLITUDE_Y + DIGIT_HEIGHT - 1);
            display_update();
            digit_x ++;
            if (digit_x > FGEN_RIGHT_DIGIT){
                digit_x = FGEN_LEFT_V_DIGIT;
            }
            if (digit_x == DECIMAL_POINT){
                digit_x ++;
            }
        }
        else if (button == UP){ //increase current digit
            fgen_specs.amplitude += get_freq_incr_decr(digit_x);
            if (fgen_specs.amplitude > FGEN_MAX_AMPL){
                fgen_specs.amplitude = FGEN_MAX_AMPL;
            }
            sprintfcomma(fgen_specs.frequency,text,1,"V");
            ssd_print_text(text,FGEN_CENTER_X,FGEN_AMPLITUDE_Y);
            //sendFreqToDDS_WaveDAC(fgen_specs.frequency);
        }
        else if (button == DOWN){//decrease current digit
            fgen_specs.amplitude -= get_freq_incr_decr(digit_x);
            if (fgen_specs.amplitude > FGEN_MAX_AMPL){
                fgen_specs.amplitude = 1u;
            }
            if (fgen_specs.amplitude == 0){
                fgen_specs.amplitude = 1u;
            }
            //sendFreqToDDS_WaveDAC(fgen_specs.amplitude);
            sprintfcomma(fgen_specs.amplitude,text,1,"V");
            ssd_print_text(text,FGEN_CENTER_X,FGEN_AMPLITUDE_Y);
        }
        else{//button == SELECT
            menu_nav_edit = navigate; //back to 
            ssd_print_text("-", FGEN_LEFT_X, FGEN_AMPLITUDE_Y);
            set_state(ST_SHAPE); //finished setting go back to FG menu 
        }  
        underline(digit_x, FGEN_AMPLITUDE_Y + DIGIT_HEIGHT - 1);
    }
    display_update();
}

void new_amplitude(uint16 millivolts){
    //the input value is 1 to 5000 mV
    //will need to change the range from 1.02 to 5.000
    //the amplitude is an 8 bit value
    
    uint8 newampl = millivolts/4;
}

void fgen_offset(){
    fgen_remove_indicators();
    ssd_print_text("-", FGEN_LEFT_X, FGEN_OFFSET_Y);
    display_update();
}
void fgen_back(){
    fgen_remove_indicators();
    display_update();
}

void fgen_remove_indicators(void){
    ssd_print_text(" ", FGEN_LEFT_X, FGEN_OUTPUT_Y);
    ssd_print_text(" ", FGEN_LEFT_X, FGEN_SHAPE_Y);
    ssd_print_text(" ", FGEN_LEFT_X, FGEN_FREQ_Y);
    ssd_print_text(" ", FGEN_LEFT_X, FGEN_PERIOD_Y);
    ssd_print_text(" ", FGEN_LEFT_X, FGEN_AMPLITUDE_Y);
    ssd_print_text(" ", FGEN_LEFT_X, FGEN_OFFSET_Y);
}


/* [] END OF FILE */
