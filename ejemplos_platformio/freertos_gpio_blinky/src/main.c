#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"

#include "clocks.h"

#define LED_GPIO    GPIOC           // Puerto del LED de la Bluepill
#define LED_PIN     GPIO_PIN_13     // Pin del LED de la Bluepill

/**
 * @brief Programa principal
 */
int main(void) {
    // Inicializo clocks del sistema y perifericos
    SystemClock_Config();

    // Declaro estructura de configuracion de GPIO
    GPIO_InitTypeDef gpio_config = {
        .Pin = LED_PIN,
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_LOW
    };

    // Habilito clock para el GPIOC
    __HAL_RCC_GPIOC_CLK_ENABLE();
    // Habilito el GPIO del LED con la cofiguracion elegida
    HAL_GPIO_Init(LED_GPIO, &gpio_config);

    while(1) {

    }

    return 0;
}