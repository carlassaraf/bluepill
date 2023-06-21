# Ejemplos para Platformio

La extension de PlatformIO de Visual Studio Code permite trabajar en un entorno de desarrollo liviano con la posibilidad de compilar, flashear y debuggear con diversas interfaces. Para el caso de la Bluepill, esta extencion tiene soporte para distintas plataformas como CMSIS, Arduino o el propio framework de STM32, lo que hace que el codigo sea compatible con programas desarrollados en el propio STM32Cube IDE. 
La desventaja que presenta esta extension es la falta de el inicializador de dispositivo que nos permite habilitar perifericos con una interfaz grafica, por lo que eso debera desarrollarse directamente con las bibliotecas de abstraccion que provee ST. Documentacion sobre como funcionan los drivers para cada periferico pueden hallarse en el directorio [docs](../docs/) de este repositorio.
A continuacion se describen los ejemplos hasta ahora disponibles que fueron desarrollados y probados con esta extension:

## ADC

| Ejemplo | Descripcion |
| --- | --- |
| [ADC polling](adc_polling) | Lectura de un NTC con polling
| [ADC interrupt](adc_interrupt) | Lectura de un NTC con interrupcion
| [ADC dual channel polling](adc_dual_channel_polling) | Lectura de un NTC y potenciometro con polling 

## FreeRTOS

| Ejemplo | Descripcion |
| --- | --- |
| [FreeRTOS GPIO blinky](freertos_gpio_blinky) | Parpadeo de un LED de forma intermitente

## GPIO

| Ejemplo | Descripcion |
| ------- | ----------- |
| [Blinky](gpio_blinky) | Parpadeo de un LED de forma intermitente |
| [Input](gpio_input) | Uso de entrada digital con pulsador | 

[gpio_blinky]: gpio_blinky/
[gpio_input]: gpio_input/
[adc_polling]: adc_polling/
[adc_interrupt]: adc_interrupt/
[adc_dual_channel_polling]: adc_dual_channel_polling/
[freertos_gpio_blinky]: freertos_gpio_blinky/