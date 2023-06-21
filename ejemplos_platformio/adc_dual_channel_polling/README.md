# ADC dual channel polling

Este ejemplo consiste en usar un termistor para medir temperatura y un potenciometro con el ADC de la Bluepill sin trabajar con interrupciones.
Se mide la temperatura indicada por el termistor y luego se enciende el LED de la Bluepill cuando supera una temperatura fijada por el potenciometro.
Se usan dos canales del mismo ADC, no se usa un ADC distinto.

Materiales necesarios:

- NTC (10K @ 25 °C)
- Resistencia 10K
- Potenciometro 10K

Conexiones:

| Bluepill | Componente |
| --- | --- |
| 3V3 | Resistencia 10K (1) |
| PA0 | Resistencia 10K (2) |
| PA0 | Termistor NTC (1) |
| GND | Termistor NTC (2) |
| 3V3 | Potenciometro 10K (1) |
| PA0 | Potenciometro 10K (2) |
| GND | Potenciometro 10K (3) |