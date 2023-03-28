# Bluepill

Este repo busca juntar informacion y ejemplos sobre el STM32F103C8T6 
(Bluepill)

## Sobre clon de Bluepill

Existe una version clonada de la Bluepill con un CKS32F103C8T6 
que no es posible de momento de debuggear con el _ST-LINK GDB server_. 
Aparentemente es posible debuggearla con el mismo ST-LINK pero usando 
OpenOCD y cambiando en el archivo `stm32f1x.cfg` del OpenOCD la linea:

```
set _CPUTAPID 0x1ba01477
```

Por:

```
set _CPUAPID 0x2ba01477
```

Queda pendiente evaluar la posibilidad de crear un .cfg alternativo para 
programar las versiones clonadas sin alterar el original, lo que haria 
imposible programar las originales.
