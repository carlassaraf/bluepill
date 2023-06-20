#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_adc.h"
#include "stm32f1xx_hal_gpio.h"

#include <math.h>
#include "clocks.h"

#define ADC_GPIO    GPIOA       // GPIO usado para el ADC
#define ADC_PIN     GPIO_PIN_0  // Pin usado para el ADC
#define LED_GPIO    GPIOC       // GPIO para el LED
#define LED_PIN     GPIO_PIN_13 // Pin para el LED

ADC_HandleTypeDef hadc1;

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

    // Habilito interrupcion
    HAL_NVIC_EnableIRQ(ADC1_IRQn);

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
    hadc1.Instance = ADC1;
    hadc1.Init = adc_config;

    // Inicializo el ADC
    HAL_ADC_Init(&hadc1);

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

    // Inicio una nueva conversion
    HAL_ADC_Start_IT(&hadc1);

    while(1);

    return 0;
}

/**
  * @brief Esta funcion atiende las interrupciones del ADC1 y ADC2
  */
void ADC1_2_IRQHandler(void) {
    // Resuelve la interrupcion
    HAL_ADC_IRQHandler(&hadc1);
}

/**
 * @brief Implementacion del callback de interrupcion de ADC
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    // Leo el valor del ADC
    uint16_t adc_val = HAL_ADC_GetValue(hadc);
    float celsius = 1 / (log(1 / (4095. / adc_val - 1)) / 3950.0 + 1.0 / 298.15) - 273.15;
    // Verifico el valor para encender o apagar el LED
    if(celsius > 27) {
        // Enciendo el LED
        HAL_GPIO_WritePin(LED_GPIO, LED_PIN, GPIO_PIN_RESET);
    }
    else {
        // Apago el LED
        HAL_GPIO_WritePin(LED_GPIO, LED_PIN, GPIO_PIN_SET);
    }
    // Inicio una nueva conversion
    HAL_ADC_Start_IT(hadc);
}