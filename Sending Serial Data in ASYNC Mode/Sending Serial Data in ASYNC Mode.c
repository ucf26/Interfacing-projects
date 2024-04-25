/* 
 * File:   appplication.c
 * Author: Yousef Mahmoud
 *
 * Created on October 4, 2023, 5:48 AM
 */


#include "application.h"

usart_t usart_obj;





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
    
    ret = EUSART_ASYNC_Init(&usart_obj);
    
    while(1)
    {
        ret = EUSART_ASYNC_WriteByteBlocking('a');
        __delay_ms(500);
        ret = EUSART_ASYNC_WriteByteBlocking('b');
        __delay_ms(500);
        
    }
    return (EXIT_SUCCESS);
}



