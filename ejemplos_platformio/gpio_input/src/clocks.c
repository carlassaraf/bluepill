#include "clocks.h"

/**
 * @brief Configuracion de clock 
 */
void SystemClock_Config(void) {
    // Estructura de configuracion del clock
    RCC_OscInitTypeDef rcc_osc_init = {
        .OscillatorType = RCC_OSCILLATORTYPE_HSE,       // High Speed Clock para usar cristl externo (8MHz)
        .HSEState = RCC_HSE_ON,                         // Habilito el HSE
        .HSEPredivValue = RCC_HSE_PREDIV_DIV1,          // Divisor del HSE 1
        .HSIState = RCC_HSI_ON,                         // Habilito el HSI
        .PLL.PLLState = RCC_PLL_ON,                     // Habilito PLL
        .PLL.PLLSource = RCC_PLLSOURCE_HSE,             // Uso el HSE para el PLL
        .PLL.PLLMUL = RCC_PLL_MUL9                      // HSE x 9 da el clock de 72 MHz
    };
    // Habilito el clock
    HAL_RCC_OscConfig(&rcc_osc_init);
    // Estructura de configuracion de clocks de sistema y perifericos
    RCC_ClkInitTypeDef rcc_clk_init = {
        .ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2,
                                                        // Clocks a configurar
        .SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK,        // Toma el clock generado del PLL (72MHz) para el sistema
        .AHBCLKDivider = RCC_SYSCLK_DIV1,               // Divisor para el clock del bus (AHB) es 1 (72MHz)
        .APB1CLKDivider = RCC_HCLK_DIV2,                // Divisor para perifericos es 2 para maximo de 36MHz
        .APB2CLKDivider = RCC_HCLK_DIV1,                // Divisor para otros perifericos es 1 para 72MHz
    };
    // Configuro clocks con la 
    HAL_RCC_ClockConfig(&rcc_clk_init, FLASH_LATENCY_2);
}

/**
 * @brief Handler de interrupcion del Systick
 */
void SysTick_Handler(void) {
    // Se incrementa el tick para la base de tiempo del delay
    HAL_IncTick();
}