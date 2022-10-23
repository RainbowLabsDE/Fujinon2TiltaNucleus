

#include "main.h"
#include "gpio.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "usart.h"

#include <errno.h>
#include <sys/unistd.h>

#include "tiltaNucleus.h"

extern "C" {
    void SystemClock_Config(void);

    // enable printf functionality on PRINTF_UART
    int _write(int file, char *data, int len) {
        if ((file != STDOUT_FILENO) && (file != STDERR_FILENO)) {
            errno = EBADF;
            return -1;
        }

        // HAL_StatusTypeDef status = HAL_UART_Transmit(&PRINTF_UART, (uint8_t *)data, len, 1000);
        // return (status == HAL_OK ? len : 0);
        // HAL_GPIO_TogglePin(LED_2_B_GPIO_Port, LED_2_B_Pin);
        uint8_t statusU = CDC_Transmit_FS((uint8_t *)data, len);
        return (statusU == USBD_OK ? len : 0);
    }
}

int main(void) {
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();
    MX_USART3_UART_Init();
    MX_USART4_UART_Init();
    MX_USB_DEVICE_Init();

    huart2.Init.BaudRate = 115200;
    UART_SetConfig(&huart2);

    TiltaNucleus *tn1 = new TiltaNucleus(&huart2);
    

    while (1) {
        HAL_Delay(50);
        printf("Hello World!\n");
        tn1->setPosition((HAL_GetTick() / 5) % 10000);
    }
}

