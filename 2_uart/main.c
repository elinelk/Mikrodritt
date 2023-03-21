#include <stdint.h>
#include "gpio.h"
#include "uart.h"

int main(){
	gpio_init();
    uart_init();

	int sleep = 0;
	while(1){
        
		if (!(GPIO0->IN&(1<<23))){
            uart_send('B');
		}else if (!(GPIO0->IN&(1<<14))){
            uart_send('A');
		}
		sleep = 10000;
		while(--sleep);
	}
	return 0;
}