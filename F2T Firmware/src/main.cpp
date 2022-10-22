

#include "main.h"
#include "gpio.h"
#include "usart.h"

extern "C" {
    void SystemClock_Config(void);
}

int main(void) {
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();
    MX_USART3_UART_Init();
    MX_USART4_UART_Init();

    while (1) {
        
    }
}

