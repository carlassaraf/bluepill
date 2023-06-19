#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_adc.h"
#include "stm32f1xx_hal_gpio.h"

#include <math.h>

#include "clocks.h"

#define ADC_GPIO    GPIOA       // GPIO usado para el ADC
#define ADC_PIN     GPIO_PIN_0  // Pin usado para el ADC
#define LED_GPIO    GPIOC       // GPIO para el LED
#define LED_PIN     GPIO_PIN_13 // Pin para el LED

/**
 * @brief Programa principal 
 */
int main(void) {
    // Inicializacion de clocks del sistema y perifericos
    SystemClock_Config();

    // Habilito clock de ADC
    __ADC1_CLK_ENABLE();

    // Estructura de configuracion de clock para ADC
    RCC_PeriphCLKInitTypeDef adc_clock_init = {
        .PeriphClockSelection = RCC_PERIPHCLK_ADC,
        .AdcClockSelection = RCC_ADCPCLK2_DIV6          // Maximo clock de 14MHz, real de 12MHz
    };
    // Configuro clock de ADC
    HAL_RCCEx_PeriphCLKConfig(&adc_clock_init);

    // Habilito clock para el GPIO que usa el ADC
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Declaro estructura de configuracion de GPIO
    GPIO_InitTypeDef adc_gpio_config = {
        .Pin = ADC_PIN,
        .Mode = GPIO_MODE_ANALOG,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_LOW
    };
    // Configuracion de GPIO para el ADC
    HAL_GPIO_Init(ADC_GPIO, &adc_gpio_config);

    // Estructura de configuracion de ADC
    ADC_InitTypeDef adc_config = {
        .DataAlign = ADC_DATAALIGN_RIGHT,
        .ScanConvMode = ADC_SCAN_DISABLE,
        .ContinuousConvMode = DISABLE,
        .NbrOfConversion = 1,
        .DiscontinuousConvMode = DISABLE,
        .NbrOfDiscConversion = 1,
        .ExternalTrigConv = ADC_SOFTWARE_START
    };

    // Handle de ADC
    ADC_HandleTypeDef hadc1 = {
        .Instance = ADC1,
        .Init = adc_config
    };

    // Estructura de configuracion de canal de ADC
    ADC_ChannelConfTypeDef adc_channel_config = {
        .Channel = ADC_CHANNEL_0,
        .Rank = ADC_REGULAR_RANK_1,
        .SamplingTime = ADC_SAMPLETIME_1CYCLE_5
    };
    // Configuro canal
    HAL_ADC_ConfigChannel(&hadc1, &adc_channel_config);

    // Habilito clock para el GPIO que usa el ADC
    __HAL_RCC_GPIOC_CLK_ENABLE();

    // Declaro estructura de configuracion de GPIO
    GPIO_InitTypeDef led_gpio_config = {
        .Pin = LED_PIN,
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_LOW
    };
    // Configuracion de GPIO para el ADC
    HAL_GPIO_Init(LED_GPIO, &led_gpio_config);

    while(1) {
        // Inicio conversion
        HAL_ADC_Start(&hadc1);
        // Espero el resultado
        uint16_t adc_val = HAL_ADC_GetValue(&hadc1);
        // Calculo el valor de la temperatura marcada por el NTC
        float celsius = 1 / (log(1 / (4095. / adc_val - 1)) / 3950.0 + 1.0 / 298.15) - 273.15;
        // Verifico el valor para encender o apagar el LED
        if(celsius > 27) {
            // Enciendo el LED
            HAL_GPIO_WritePin(LED_GPIO, LED_PIN, GPIO_PIN_SET);
        }
        else {
            // Apago el LED
            HAL_GPIO_WritePin(LED_GPIO, LED_PIN, GPIO_PIN_RESET);
        }
    }

    return 0;
}