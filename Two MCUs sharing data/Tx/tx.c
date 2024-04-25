/* 
 * File:   appplication.c
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 5:48 AM
 */


#include "application.h"

usart_t usart_obj;

uint8 rec_data;

//led_t led1 = {.port_name = PORTD_INDEX, .pin = GPIO_PIN0, .led_status = LED_off};

int main() {
    Std_ReturnType ret = E_NOT_OK;
    
    usart_obj.baudrate = 9600;
    usart_obj.baudrate_config = BAUDRATE_ASYNC_8BIT_LOW_SPEED;

    usart_obj.usart_rx_cfg.usart_rx_enable = EUSART_ASYNCHRONOUS_RX_ENABLE;
    usart_obj.usart_rx_cfg.usart_rx_9bit_enable = EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE;
    usart_obj.usart_rx_cfg.usart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_RX_INTERRUPT_DISABLE;
    
    usart_obj.usart_tx_cfg.usart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE;
    usart_obj.usart_tx_cfg.usart_tx_9bit_enable = EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE;
    usart_obj.usart_tx_cfg.usart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_TX_INTERRUPT_DISABLE;
    usart_obj.EUSART_FramingErrorHandler = NULL;
    usart_obj.EUSART_OverrunErrorHandler = NULL;
    usart_obj.EUSART_Rx_DefaultInterruptHandler = NULL;
    usart_obj.EUSART_Tx_DefaultInterruptHandler = NULL;
    
    ret = EUSART_ASYNC_Init(&usart_obj);
//    ret = led_initialize(&led1);
    
    while(1)
    {
        ret = EUSART_ASYNC_WriteByteBlocking('a');
        __delay_ms(1000);
        ret = EUSART_ASYNC_WriteByteBlocking('b');
        __delay_ms(1000);
//        ret = EUSART_ASYNC_ReadByteBlocking(&rec_data);
//        if(ret == E_OK){
//            if('a' == rec_data){
//            ret = led_turn_on(&led1);
//            ret = EUSART_ASYNC_WriteStringBlocking("led on\r", 7);
//            }
//            else if('b' == rec_data){
//                ret = led_turn_off(&led1);
//                ret = EUSART_ASYNC_WriteStringBlocking("led off\r", 8);
//            }
//            else {}
//        }
//        else {}
    }
    return (EXIT_SUCCESS);
}



