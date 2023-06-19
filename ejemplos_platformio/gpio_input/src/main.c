#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"

#include "clocks.h"

#define LED_GPIO    GPIOC           // GPIO para el LED
#define LED_PIN     GPIO_PIN_13     // Pin para el LED
#define BTN_GPIO    GPIOB           // GPIO para el boton
#define BTN_PIN     GPIO_PIN_9      // Pin para el boton

/**
 * @brief Programa principa;
 */
int main(void) {
    // Inicializaciond e clock del sistema y perifericos
    SystemClock_Config();

    // Habilito clocks para GPIOB y GPIOC
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    // Estructura de configuracion de GPIO para LED
    GPIO_InitTypeDef gpio_led_config = {
        .Pin = LED_PIN,
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_LOW
    };
    // Estructura de configuracion de GPIO para boton
    GPIO_InitTypeDef gpio_btn_config = {
        .Pin = BTN_PIN,
        .Mode = GPIO_MODE_INPUT,
        .Pull = GPIO_PULLUP,
        .Speed = GPIO_SPEED_LOW
    };
    // Configuro ambos pines
    HAL_GPIO_Init(LED_GPIO, &gpio_led_config);
    HAL_GPIO_Init(BTN_GPIO, &gpio_btn_config);

    while(1) {
        // Pregunto por el estado del pulsador
        if(HAL_GPIO_ReadPin(BTN_GPIO, BTN_PIN) == GPIO_PIN_RESET) {
            // Prendo el LED
            HAL_GPIO_WritePin(LED_GPIO, LED_PIN, GPIO_PIN_SET);
        }
        else {
            // Apago el LED
            HAL_GPIO_WritePin(LED_GPIO, LED_PIN, GPIO_PIN_RESET);
        }
        // Demora
        HAL_Delay(20);
    }

    return 0;
}