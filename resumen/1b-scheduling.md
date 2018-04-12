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

### Round-Robin
> Darle un poco de *quantum* a cada proceso, e ir alternando

#### ¿Cuánto quantum es adecuado?
- Si es muy largo, los procesos interactivos podrían hacer parecer que el sistema no está respondiendo.
- Si es muy corto, el tiempo de cambio de contexto (desperdiciado) pasa a ser muy grande en relación al quantum, por lo que el SO pasa mucho tiempo haciendo "mantenimiento".

#### Prioridades
- Asignadas por el usuario (administrativas)
- Decididas por el proceso (no suele funcionar)
- A medida que el proceso envejece, la prioridad disminuye para evitar la inanición.
- Los procesos que hacen E/S reciben prioridad, al liberar su quantum antes de tiempo.

### Múltiples colas
> Colas con distinto quantum

- menos quantum <=> más prioridad
- cuando un proceso agota su quantum, es promovido a una cola de más quantum
- procesos interactivos <- colas de mayor prioridad >
- cuando un proceso termina de hacer E/S, se lo vuelve a una cola de máxima prioridad
- la idea general es minimizar el tiempo de respuesta para procesos interactivos, asumiendo que los procesos largos son menos sensibles a demoras.

### SJF 
==Shortest Job first==
> Los procesos más cortos van primero

- Orientado a esquemas de trabajo batch.
- Se debe poder predecir el tiempo de duración de un proceso, o al menos clasificarlo.
- Si las predicciones son buenas, es óptimo en cuanto a latencia promedio.

- Una variante es no pensar en la duración total, sino en el que menos tiempo tenga hasta la próxima E/S.
	- El problema es saber cuánta CPU va a utilizar un proceso.
	- Una opción es usar información del pasado para predecir.
	- Si el proceso es irregular, no es posible.

### Real-Time
> Los deadlines (tiempo de finalización) son estrictos

- Scheduling en RT es todo un mundo aparte, fuera del scope de la materia.
- Normalmente se entiende que el deadline es algo crítico: si no se lo cumple, algo malo va a pasar.
- Una opción es ejecutar el proceso que tenga un deadline más próximo.

### SMP
==Symmetric Multiprocessing==
> Múltiples procesadores corriendo al mismo tiempo

- Como sucede con RT, es un problema en sí mismo.
- El caché es un problema.
	- Es de vital importancia para el rendimiento de los programas.
	- Si el scheduler hace pasar un proceso de un procesador a otro, se pierde la caché.
- Surge el concepto de **afinidad al procesador**.
	- Se divide en afinidad débil y afinidad fuerte.

## Consideraciones Prácticas
==Elegir un buen algoritmo de scheduling es difícil==

### Consideraciones Básicas
- ¿La ecuanimidad, es por proceso o por usuario? ¿Y un proceso con muchos hijos?
- ¿Qué hacer con un proceso que requiera mucha CPU?
- Un buen algoritmo de scheduling debe ajustarse a medida que cambien los patrones de uso.
	- A veces se pueden armar modelos matemáticos.
	- Se pueden tomar patrones de carga de sistemas estandarizados o benchmarks previos.
- Se puede obtener información útil a partir del comportamiento de un proceso.
	- Si un proceso abre una terminal, puede estar por volverse interactivo.
	- Se puede hacer un análisis estático.

### Consideraciones Adicionales
- Usos específicos:
	- Bases de Datos.
	- Cómputo Científico.
	- Benchmarking.
- Threads
- Virtualización.

==[Ver gráfico en página 19](/home/lbarrios/facultad/sistemas-operativos-final/clases/teoricas/1b-scheduling-20172c.pdf)==