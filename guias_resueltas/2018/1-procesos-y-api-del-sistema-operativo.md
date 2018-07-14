Ver: [Guía 1](../../guias/2018/1-procesos-y-api-del-so.pdf)

---------------

# Ejercicio 1
Los pasos que deben realizarse para llevar a cabo un cambio de contexto son:

1) Se entra en una interrupción o se llama a un syscall, que corre en nivel supervisor, y se encargará de realizar el cambio de contexto. Se corre la rutina de atención de dicha interrupción.
2) Se guarda el contexto actual en la PCB del proceso que se retira.
3) Se recupera el contexto del proceso entrante desde la PCB correspondiente.
4) La ejecución continúa en el contexto recuperado.

# Ejercicio 2
```c++
// Sumo y reseteo el CPU time
pcb_0->CPU_TIME += ke_current_user_time()
ke_reset_current_user_time()

// Cambio el estado de los procesos
pcb_0->STAT = KE_READY
pcb_1->STAT = KE_RUNING

// Guardo los registros del proceso saliente (paso 2)
pcb_0->R0 = R0
...
pcb_0->R15 = R15

// Recupero los registros del proceso entrante (paso 3)
R0 = pcb_1->R0
...
R15 = pcb_1->R15

// Se continúa la ejecución a partir del siguiente proceso (paso 4)
set_current_process(pcb_1->P_ID)
```

# Ejercicio 3
Un system call es una función provista por el sistema operativo, generalmente implementada mediante una interrupción. La misma implica un cambio de modo (privilegios), en el cual el sistema pase de correr en modo usuario a correr en modo kernel. Esto permite realizar operaciones de bajo nivel o que requieran privilegios, tales como acceder al hardware, a la memoria del kernel, administrar procesos, abrir archivos, etc. Los syscalls forman parte de la API del Sistema Operativo, y por obvias razones de retrocompatibilidad no son algo que se pueda cambiar fácilmente.

Una llamada a una función de una biblioteca es como cualquier otra llamada a una función, es decir, corre en modo usuario (lo cual no significa que dentro de la función de la biblioteca no se puedan llegar a realizar syscalls). Las bibliotecas no forman parte de la API del Sistema Operativo (si bien hay bibliotecas muy comunes y utilizadas como la de C), y por lo tanto pueden llegar a sufrir más cambios o variaciones según su versión. Además, hoy en día es muy común que haya una gran cantidad de biblitecas disponibles.

# Ejercicio 4
```

NEW   ->   READY   ->   RUNNING   ->   TERMINATED
             \             /
              <- BLOCKED <-

```
Trancisiones:

* NEW -> READY: Cuando un proceso termina de crearse, pasa a estar disponible para su ejecución.
* READY -> RUNNING: Cuando un proceso está disponible, y le toca su turno para correr, entonces pasa a estar RUNNING.
* RUNNING -> BLOCKED: Cuando un proceso está corriendo, y realiza una llamada bloqueante (ejemplo, acceder a IO), se lo desaloja y su estado pasa a ser el de bloqueado (ya que no puede correr mientras esté esperando que finalice la llamada); de este modo, otro proceso que esté en READY puede correr.
* BLOCKED -> READY: Cuando un proceso está bloqueado, y el recurso que estaba bloqueándolo se libera, entonces pasa a estar disponible nuevamente para su ejecución, por lo que su estado pasa a READY. No puede pasar directo a RUNNING nuevamente, ya que seguramente haya otro proceso en ejecución en ese momento.
* RUNNING -> TERMINATED: Cuando un proceso está corriendo, y realiza una llamada a sistema para terminar, ejemplo EXIT(0), el estado pasa a terminated, mientras los recursos que tenía asignados son liberados.