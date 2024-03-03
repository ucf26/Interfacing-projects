/* 
 * File:   appplication.c
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 5:48 AM
 */


#include "application.h"
#include "MCAL_Layer/EEPROM/eeprom.h"
#include "MCAL_Layer/ADC/hal_adc.h"

uint16 adc1, adc2, adc3, adc4, adc_flag;
uint8 adc1_txt[6],  adc2_txt[6], adc3_txt[6], adc4_txt[6];

adc_cfg_t adc_1={
    .ADC_InterruptHandler = adc_default_handler,
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
    __delay_ms(2000);
    ret = lcd_4bit_send_string_pos(&lcd_1, 1 , 5, "              ");
    
    ret = lcd_4bit_send_string_pos(&lcd_1, 1 , 1, "Pot0: ");
    ret = lcd_4bit_send_string_pos(&lcd_1, 2 , 1, "Pot1: ");
    ret = lcd_4bit_send_string_pos(&lcd_1, 3 , 1, "Pot2: ");
    ret = lcd_4bit_send_string_pos(&lcd_1, 4 , 1, "Pot3: ");
    
    while(1)
    {
        // ret = ADC_StartConversion_Interrupt(&adc_1, ADC_CHANNEL_AN0);
        ret = ADC_GetConversion_Blocking(&adc_1, &adc1, ADC_CHANNEL_AN0);
        ret = ADC_GetConversion_Blocking(&adc_1, &adc2, ADC_CHANNEL_AN1);
        ret = ADC_GetConversion_Blocking(&adc_1, &adc3, ADC_CHANNEL_AN2);
        ret = ADC_GetConversion_Blocking(&adc_1, &adc4, ADC_CHANNEL_AN3);
        
        ret = convert_uint16_to_string(adc1, adc1_txt);
        ret = convert_uint16_to_string(adc2, adc2_txt);
        ret = convert_uint16_to_string(adc3, adc3_txt);
        ret = convert_uint16_to_string(adc4, adc4_txt);
        
        
        ret = lcd_4bit_send_string_pos(&lcd_1, 1 , 7, adc1_txt);
        ret = lcd_4bit_send_string_pos(&lcd_1, 2 , 7, adc2_txt);
        ret = lcd_4bit_send_string_pos(&lcd_1, 3 , 7, adc3_txt);
        ret = lcd_4bit_send_string_pos(&lcd_1, 4 , 7, adc4_txt);
    }
    return (EXIT_SUCCESS);
}

