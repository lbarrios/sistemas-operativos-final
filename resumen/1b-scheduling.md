#Scheduling
##Políticas de Scheduling
- Parte ==fundamental== de un Sistema Operativo.
- Muy importante ==optimizar==.

##Objetivos
- ==Ecuanimidad / Justicia==: recibir **dosis "justas"** de CPU.
- ==Eficiencia==: que la **CPU no desperdicie** recursos.
- ==Carga del sistema==: **cantidad** de procesos en espera.
- ==Tiempo de espera==: **tiempo** que un proceso está en espera.
- ==Latencia==: **tiempo de respuesta** (resultados, interactividad)
- ==Tiempo de ejecución== (_Completion Time_ o _Turn Around_): tiempo en que cada proceso **termina**
- ==Rendimiento== (_Throughput_): número de **procesos terminados** por tiempo
- ==Liberación de Recursos==: **liberar** rápidamente los recursos.

###Soluciones de Compromiso
> Cada política va a intentar __maximizar__ uno o más 
> __objetivos__, y __minimizar el impacto__ en el resto.

- **No se puede tener todo**.
- Objetivos contradictorios.
- ==Distintos intereses== <- depende de los usuarios ->

## Cooperativo vs Con Desalojo.
Los Schedulers normalmente combinan ambos métodos.

### Con Desalojo (Preemptive, Apropiativo)
> El scheduler utiliza la **interrupción de clock**, 
> y decide si el proceso debe seguir ejecutándose.

- ¡Se requiere un **procesador con interrupciones** de clock!.
- El clock interrumpe sólamente **50 o 60 veces por segundo**.
- No se les da **garantías de continuidad** a los procesos
	- Esto es problema en REAL-TIME.

### Cooperativo
> El scheduler analiza la situación 
> **cuando el Kernel toma control** (en los syscalls).

- Entrada/Salida.
- Syscalls explícitos para permitir ejecución de otros procesos.

## Tipos de Scheduling
### FIFO / FCFS
==First In - First Out / First Came - First Served==
> Cualquier esquema de **prioridad fija** 
> representa un **riesgo de inanición**.

- Se asume que *todos los procesos son iguales*.
- **Un solo proceso** grande puede **saturar la CPU**.
- Solución, **agregar prioridades**:
	- ==Problema: Inanición (Starvation)==: Los procesos 
	de mayor prioridad **demoran infinitamente** a los de 
	menor prioridad, que nunca se ejecutan.
- Solución 2, **aumentar prioridad con envejecimiento**.

== [Seguir en página 12](/home/lbarrios/facultad/sistemas-operativos-final/clases/teoricas/1b-scheduling-20172c.pdf) ==