# Procesos

## Definiciones
### Programa (estático):
- Texto escrito en un lenguaje de programación.
- Código compilado (objeto / máquina).

### Proceso (dinámico):
- Tiene un estado.
    - Program Counter: instrucción actual.
    - Memoria Dinámica (heap).
    - Pila de Ejecución (stack).
- Tiene un identificador único **(PID)**.

## Process Control Block (PCB)
Estructura que contiene la información del contexto proceso.

- Estado
- Program Counter, Stack Pointer
- Registros de la CPU
- Metadatos del scheduler (ejemplo prioridad)
- Metadatos del manejador de memoria, IO.

## Máquina de estados
```
    admitted       -->dispatch-->            exit
NEW -------> READY                 RUNNING ------> TERMINATED
               ^   <--interrupt<--   V
               |                     |
    (io event)  \                   /   (io event)
    (complete)   \                 /    (waiting)
                  <-- WAITING <----			
```
### Estados
- **RUNNING**: Está usando la CPU.
- **WAITING**: Está bloqueado, usando o esperando algún recurso de IO.
- **READY**: Está libre, listo para correr.

## Acciones de un proceso
- Realizar operaciones entre registro y memoria del usuario (User Address Space)
- Acceder a un servicio del kernel **(SYSCALL)**
    - Realizar IO
    - Lanzar un proceso hijo
    - Salir - `exit()`
        - Liberar todos los recursos del proceso.
        - Status de terminación.
        - Linux (C standard): EXIT_SUCCESS , EXIT_FAILURE
        - Este código de status le es reportado al padre.
- **Domain Crossing** a través de las System Calls

## Acciones del SO
- Admitir un proceso **(NEW-->READY)**
- Otorgar (dispatch) CPU a un proceso **(READY-->RUNNING)**
- Desalojar un proceso:
    - Preemption: El proceso es interrumpido **(RUNNING->READY)**

    - Blocking: El proceso se bloquea al requerir un recurso **(RUNNING->WAITING)**

### Scheduling
- ¿Cuánto tiempo se ejecuta el proceso?
    - Hasta que termine (sin time-sharing).
    - Un quantum.
- Los sistemas operativos modernos hacen **preemption**.
    - Scheduler: decide cómo y a quién le toca.
    - Context Switch: se cambia el contexto a otro proceso.

### Context Switch
- Guardar el PCB del proceso desalojado.
- Cargar el PCB del proceso alojado.
- El tiempo usado en el cambio se desperdicia.
    - Duración: depende del Hardware
    - Cantidad: debe haber un Quantum apropiado.
- Se implementa a través de la interrupción de clock.

#### Context Switch: Artículos para leer
- Costo
    - Chuanpeng Li, Chen Ding, and Kai Shen. 2007. Quantifying the cost of context switch. http://goo.gl/GqGvKt
    - Francis M. David, et al. 2007. Context switch overheads for Linux on ARM platforms. http://goo.gl/pj9Dwj
- Prevención
    - Jaaskelainen, et al. Reducing context switch overhead with compiler-assisted threading. 2008. http://goo.gl/8th0dy.
    - Kloukinas, Yovine. 2011. A model-based approach for multiple QoS in scheduling: from models to implementation. http://goo.gl/4xL1JT

## Arbol de Procesos
- Jerarquía.
- Existe un proceso **root**, o **init**.
- Los procesos pueden lanzar procesos hijos.
    - `fork()` crea un proceso igual al padre, y devuelve su PID.
    - `exec()` carga un binario ejecutable sobre un proceso existente.
    - `wait()` suspende al padre hasta que el hijo termine; cuando termina, recibe su status.

```
(parent) --> FORK() --> --> (parent) -------------------> WAIT() --> (resumes)
                       |                                    /
                       \--> child --> EXEC() --> EXIT() -->/
```

# API

## Llamadas al Sistema (SYSCALLS)

### Tipos de llamadas al sistema

| Tipo de llamada                | Windows | Unix |
| ------------------------------ | ------- | ---- |
| Control de procesos            | CreateProcess <br/> ExitProcess() <br/> WaitForSingleObject() | fork() <br/> exit() <br/> wait() |
| Administración de archivos     | CreateFile() <br/> ReadFile() <br/> WriteFile() <br/> CloseHandle() | open() <br/> read() <br/> write() <br/> close() |
| Administración de dispositivos | SetConsoleMode() <br/> ReadConsole() <br/> WriteConsole() | ioctl() <br/> read() <br/> write() |
| Mantenimiento de información   | GetCurrentProcessID() <br/> SetTimer() <br/> Sleep() | getpid() <br/> alarm() <br/> sleep() |
| Comunicaciones                 | CreatePipe() <br/> CreateFileMapping() <br/> MapViewOfFile() | pipe() <br/> shmget() <br/> mmap() |

### POSIX
Portable Operating System Interface. And X from Unix.

- IEEE 1003.1/2008 http://goo.gl/k7WGnP
- POSIX.1: **Core Services**
    - Creación y control de procesos
    - Pipes
    - Señales
    - Operaciones de archivos y directorios
    - Excepciones
    - Errores del bus.
    - Biblioteca C
    - Instrucciones de E/S y de control de dispositivo (ioctl).
- POSIX.1b: **extensiones para tiempo real**
    - Planificación (scheduling) con prioridad.
    - Señales de tiempo real.
    - Temporizadores.
    - Semáforos.
    - Intercambio de mensajes (message passing).
    - Memoria compartida.
    - Entrada/salida síncrona y asíncrona.
    - Bloqueos de memoria.
- POSIX.1c: **extensiones para hilos (threads)**:
    - Creación, control y limpieza de hilos.
    - Planificación (scheduling).
    - Sincronización.
    - Manejo de señales.
- POSIX.2: **Shell y Utilidades**
    - Intérprete de Comandos
    - Programas de Utilidad
