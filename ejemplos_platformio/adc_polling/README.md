# ADC polling

Este ejemplo consiste en usar un termistor para medir temperatura con el ADC de la Bluepill sin trabajar con interrupciones.
Se mide la temperatura indicada por el termistor y luego se enciende el LED de la Bluepill cuando supera una temperatura fija establecida.

Materiales necesarios:

- NTC (10K @ 25 °C)
- Resistencia 10K

Conexiones:

| Bluepill | Componente |
| --- | --- |
| 3V3 | Resistencia 10K (1) |
| PA0 | Resistencia 10K (2) |
| PA0 | Termistor NTC (1) |
| GND | Termistor NTC (2) |