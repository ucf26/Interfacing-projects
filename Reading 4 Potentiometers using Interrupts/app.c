/* 
 * File:   appplication.c
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 5:48 AM
 */


#include "application.h"
#include "MCAL_Layer/EEPROM/eeprom.h"
#include "MCAL_Layer/ADC/hal_adc.h"

uint16 adc_res1, adc_res2, adc_res3, adc_res4;
uint8 adc1_txt[6],  adc2_txt[6], adc3_txt[6],  adc4_txt[6];
uint8 adc_fl =0;

void adc_defaulthandler(void);

adc_cfg_t adc_1={
    .ADC_InterruptHandler = adc_defaulthandler,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .acuisition_time = ADC_12_TAD,
    .adc_channel = ADC_CHANNEL_AN0,
    .conversion_clock = ADC_CONVERSION_CLOCK_DIV_16,
    .result_format = ADC_RESULT_RIGHT,
    .voltage_reference = ADC_VOLTAGE_REFERENCE_DISABLED
};


lcd_4bit_t lcd_1={
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN1,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    .lcd_data[0].port = PORTC_INDEX,
    .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[1].port = PORTC_INDEX,
    .lcd_data[1].pin = GPIO_PIN3,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[2].port = PORTC_INDEX,
    .lcd_data[2].pin = GPIO_PIN4,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[3].port = PORTC_INDEX,
    .lcd_data[3].pin = GPIO_PIN5,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOW
};



int main() {
    Std_ReturnType ret = E_NOT_OK;
    
    ret = ADC_Init(&adc_1);
    ret = lcd_4bit_initialize(&lcd_1);
    ret = lcd_4bit_send_string_pos(&lcd_1, 1 , 5, "ADC Is Done !!");
    __delay_ms(1000);
    ret = lcd_4bit_send_string_pos(&lcd_1, 1 , 5, "              ");
    
    ret = lcd_4bit_send_string_pos(&lcd_1, 1 , 1, "PoT1: ");
    ret = lcd_4bit_send_string_pos(&lcd_1, 2 , 1, "PoT1: ");
    ret = lcd_4bit_send_string_pos(&lcd_1, 3 , 1, "PoT1: ");
    ret = lcd_4bit_send_string_pos(&lcd_1, 4 , 1, "PoT1: ");

    
    while(1)
    {
        if(adc_fl == 0){
            ret = ADC_StartConversion_Interrupt(&adc_1, ADC_CHANNEL_AN0);
        }
        else if(adc_fl == 1){
            ret = ADC_StartConversion_Interrupt(&adc_1, ADC_CHANNEL_AN1);
        }
        else if(adc_fl == 2){
            ret = ADC_StartConversion_Interrupt(&adc_1, ADC_CHANNEL_AN2);
        }
        else if(adc_fl == 3){
            ret = ADC_StartConversion_Interrupt(&adc_1, ADC_CHANNEL_AN3);
        }
        else {/*nothing*/}
        
        ret = convert_uint16_to_string(adc_res1, adc1_txt);
        ret = convert_uint16_to_string(adc_res2, adc2_txt);
        ret = convert_uint16_to_string(adc_res3, adc3_txt);
        ret = convert_uint16_to_string(adc_res4, adc4_txt);
        
        
        ret = lcd_4bit_send_string_pos(&lcd_1, 1 , 8, adc1_txt);
        ret = lcd_4bit_send_string_pos(&lcd_1, 2 , 8, adc2_txt);
        ret = lcd_4bit_send_string_pos(&lcd_1, 3 , 8, adc3_txt);
        ret = lcd_4bit_send_string_pos(&lcd_1, 4 , 8, adc4_txt);
       
    }
    return (EXIT_SUCCESS);
}


void adc_defaulthandler(void){
    Std_ReturnType ret = E_NOT_OK;
    if(adc_fl == 0){
        ret = ADC_GetConversionResult(&adc_1, &adc_res1);
        adc_fl = 1;
    }
    else if(adc_fl == 1){
        ret = ADC_GetConversionResult(&adc_1, &adc_res2);
        adc_fl =2;
    }
    else if(adc_fl == 2){
        ret = ADC_GetConversionResult(&adc_1, &adc_res3);
        adc_fl = 3;
    }
    else if(adc_fl == 3){
        ret = ADC_GetConversionResult(&adc_1, &adc_res4);
        adc_fl = 0;
    }
    else {/*nothing*/}
}
