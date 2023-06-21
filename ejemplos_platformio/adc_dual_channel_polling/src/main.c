#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_adc.h"
#include "stm32f1xx_hal_gpio.h"

#include <math.h>
#include "clocks.h"

#define NTC_GPIO    GPIOA           // GPIO usado para el NTC
#define NTC_PIN     GPIO_PIN_0      // Pin usado para el NTC
#define NTC_CHANNEL ADC_CHANNEL_0   // Canal de ADC usado para el NTC
#define POT_GPIO    GPIOA           // GPIO usado para el potenciometro
#define POT_PIN     GPIO_PIN_1      // Pin usado para el potenciometro
#define POT_CHANNEL ADC_CHANNEL_1   // Canal de ADC usado para el potenciometro
#define LED_GPIO    GPIOC           // GPIO para el LED
#define LED_PIN     GPIO_PIN_13     // Pin para el LED

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
    GPIO_InitTypeDef ntc_gpio_config = {
        .Pin = NTC_PIN,
        .Mode = GPIO_MODE_ANALOG,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_LOW
    };
    // Configuracion de GPIO para el potenciometro
    HAL_GPIO_Init(NTC_GPIO, &ntc_gpio_config);

    // Declaro estructura de configuracion de GPIO
    GPIO_InitTypeDef pot_gpio_config = {
        .Pin = POT_PIN,
        .Mode = GPIO_MODE_ANALOG,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_LOW
    };
    // Configuracion de GPIO para el ADC
    HAL_GPIO_Init(POT_GPIO, &pot_gpio_config);

    // Estructura de configuracion de ADC
    ADC_InitTypeDef adc_config = {
        .DataAlign = ADC_DATAALIGN_RIGHT,
        .ScanConvMode = ADC_SCAN_ENABLE,
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
    // Inicializo el ADC
    HAL_ADC_Init(&hadc1);

    // Estructura de configuracion de canal de ADC para el NTC
    ADC_ChannelConfTypeDef ntc_channel_config = {
        .Channel = NTC_CHANNEL,
        .Rank = ADC_REGULAR_RANK_1,
        .SamplingTime = ADC_SAMPLETIME_1CYCLE_5
    };

    // Estructura de configuracion de canal de ADC para el potenciometro
    ADC_ChannelConfTypeDef pot_channel_config = {
        .Channel = POT_CHANNEL,
        .Rank = ADC_REGULAR_RANK_1,
        .SamplingTime = ADC_SAMPLETIME_1CYCLE_5
    };

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
        // Configuro canal
        HAL_ADC_ConfigChannel(&hadc1, &ntc_channel_config);
        // Empiezo una conversion
        HAL_ADC_Start(&hadc1);
        // Espero a que este lista
        while(HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY) != HAL_OK);
        // Primer conversion (rank 1) es la del NTC
        uint16_t adc_rank_1_val = HAL_ADC_GetValue(&hadc1);
        // Calculo el valor de la temperatura marcada por el NTC
        int16_t celsius = 1 / (log(1 / (4095. / adc_rank_1_val - 1)) / 3950.0 + 1.0 / 298.15) - 273.15;
        // Configuro canal
        HAL_ADC_ConfigChannel(&hadc1, &pot_channel_config);
        // Empiezo una conversion
        HAL_ADC_Start(&hadc1);
        // Espero a que este lista
        while(HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY) != HAL_OK);
        // Primer conversion (rank 2) es la del potenciometro
        uint16_t adc_rank_2_val = HAL_ADC_GetValue(&hadc1);
        // Calculo el valor de temperatura que marca el potenciometro (max 35 grados)
        int16_t ref_pot = (30.0 / 4095.0) * adc_rank_2_val;
        // Verifico el valor para encender o apagar el LED
        if(celsius > ref_pot) {
            // Enciendo el LED
            HAL_GPIO_WritePin(LED_GPIO, LED_PIN, GPIO_PIN_RESET);
        }
        else {
            // Apago el LED
            HAL_GPIO_WritePin(LED_GPIO, LED_PIN, GPIO_PIN_SET);
        }
    }

    return 0;
}