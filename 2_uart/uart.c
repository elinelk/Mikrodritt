#include <stdint.h>
#include "gpio.h"
#include "uart.h"

void uart_init(){

    GPIO0->PIN_CNF[6]=1; //UART_INT_RX
    GPIO1->PIN_CNF[8]=0; //UART_INT_TX
    UART->PSEL_RXD=6;//(0b000110);
    UART->PSEL_TXD = 40;//(0b101000);
    UART->BAUDRATE = 0x00275000;
    UART->PSEL_RTS = 0xffffffff;
    UART->PSEL_CTS = 0xffffffff;
    UART->ENABLE=4;
    UART->TASKS_STARTRX=1;

}
void uart_send(char letter){
    UART->TASKS_STARTTX=1;
    UART->TXD = letter;
    while (!UART->EVENTS_TXDRDY){

    }
    UART->EVENTS_TXDRDY=0;
    UART->TASKS_STOPTX = 1;
}

char uart_read(){
    char letter = 0;
    if (UART->EVENTS_RXDRDY){
        UART->EVENTS_RXDRDY = 0;
        letter = UART->RXD;
        return letter;
    }
    return 0;
}