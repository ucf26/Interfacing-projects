/* 
 * File:   appplication.c
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 5:48 AM
 */


#include "application.h"
#include "MCAL_Layer/EEPROM/eeprom.h"
#include "MCAL_Layer/ADC/hal_adc.h"

uint16 adc_res1, adc_res2;
uint8 adc1_txt[6],  adc2_txt[6];

adc_cfg_t adc_1={
    .ADC_InterruptHandler = NULL,
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

dc_motor_t dc_motor_1={
    .dc_motor_pin[0].port = PORTD_INDEX,
    .dc_motor_pin[0].pin = GPIO_PIN0,
    .dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor_pin[0].logic = GPIO_LOW,
    .dc_motor_pin[1].port = PORTD_INDEX,
    .dc_motor_pin[1].pin = GPIO_PIN1,
    .dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor_pin[1].logic = GPIO_LOW,
};

dc_motor_t dc_motor_2={
    .dc_motor_pin[0].port = PORTD_INDEX,
    .dc_motor_pin[0].pin = GPIO_PIN2,
    .dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor_pin[0].logic = GPIO_LOW,
    .dc_motor_pin[1].port = PORTD_INDEX,
    .dc_motor_pin[1].pin = GPIO_PIN3,
    .dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor_pin[1].logic = GPIO_LOW,
};


int main() {
    Std_ReturnType ret = E_NOT_OK;
    
    ret = ADC_Init(&adc_1);
    ret = dc_motor_initialize(&dc_motor_1);
    ret = dc_motor_initialize(&dc_motor_2);
    ret = lcd_4bit_initialize(&lcd_1);
    ret = lcd_4bit_send_string_pos(&lcd_1, 1 , 5, "ADC Is Done !!");
    
    ret = lcd_4bit_send_string_pos(&lcd_1, 2 , 1, "Temp1: ");
    ret = lcd_4bit_send_string_pos(&lcd_1, 3 , 1, "Temp2: ");

    
    while(1)
    {
        ret = ADC_GetConversion_Blocking(&adc_1, &adc_res1, ADC_CHANNEL_AN0);
        ret = ADC_GetConversion_Blocking(&adc_1, &adc_res2, ADC_CHANNEL_AN1);
        
        adc_res1 =( adc_res1 / 1023.0F )* (500.0F);
        adc_res2 =( adc_res2 / 1023.0F )* (500.0F);
        
        ret = convert_uint16_to_string(adc_res1, adc1_txt);
        ret = convert_uint16_to_string(adc_res2, adc2_txt);

        
        
        ret = lcd_4bit_send_string_pos(&lcd_1, 2 , 8, adc1_txt);
        ret = lcd_4bit_send_string_pos(&lcd_1, 3 , 8, adc2_txt);
        
        if(adc_res1 > 20){
            ret = dc_motor_move_right(&dc_motor_1);
        }
        else {
            ret = dc_motor_stop(&dc_motor_1);
        }
        
        if(adc_res2 > 20){
            ret = dc_motor_move_right(&dc_motor_2);
        }
        else {
            ret = dc_motor_stop(&dc_motor_2);
        }
    }
    return (EXIT_SUCCESS);
}

