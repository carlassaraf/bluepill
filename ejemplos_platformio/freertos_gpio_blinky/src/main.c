#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"

#include "clocks.h"

#include "FreeRTOS.h"
#include "task.h"

#define LED_GPIO    GPIOC           // Puerto del LED de la Bluepill
#define LED_PIN     GPIO_PIN_13     // Pin del LED de la Bluepill

/**
 * @brief Tarea de inicializacion 
 */
void task_init(void *params) {
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
    // Elimino tarea
    vTaskDelete(NULL);
}

/**
 * @brief Tarea para conmutar el LED 
 */
void task_led_blinky(void *params) {
    // Delay para bloquear la tarea
    const uint16_t delay_ms = 500;

    while(1) {
        // Conmuto LED
        HAL_GPIO_TogglePin(LED_GPIO, LED_PIN);
        // Bloqueo tarea
        vTaskDelay(delay_ms);
    }
}

/**
 * @brief Programa principal
 */
int main(void) {
    // Inicializo clocks del sistema y perifericos
    SystemClock_Config();

    // Creo tareas

    xTaskCreate(
        task_init,
        "Init",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 2UL,
        NULL
    );

    xTaskCreate(
        task_led_blinky,
        "LED",
        configMINIMAL_STACK_SIZE,
        NULL,
        tskIDLE_PRIORITY + 1UL,
        NULL
    );

    // Inicializo scheduler de FreeRTOS
    vTaskStartScheduler();

    while(1);
    return 0;
}