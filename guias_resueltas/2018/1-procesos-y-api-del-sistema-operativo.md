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

# Ejercicio 5
	a) Utilizando únicamente la llamada al sistema fork(), escribir un programa tal que construya un
	árbol de procesos que represente la siguiente genealogía: Abraham es padre de Homer, Homer es
	padre de Bart, Homer es padre de Lisa, Homer es padre de Maggie. Cada proceso debe imprimir
	por pantalla el nombre de la persona que representa.

	b) Modificar el programa anterior para que cumpla con las siguientes condiciones: 1) Homer termine
	sólo después que terminen Bart, Lisa y Maggie, y 2) Abraham termine sólo después que termine
	Homer.

```c++
void maggie() {
	print("Maggie");
	exit(0);
}
void lisa() {
	print("Lisa");
	exit(0);
}
void bart() {
	print("Bart");
	exit(0);
}
void homero() {
	printf("Abraham");
	pid bart = fork();
	if (bart == 0) {
		bart();
	}
	pid lisa = fork();
	if (lisa == 0) {
		lisa();
	}
	pid maggie = fork();
	if (maggie == 0) {
		maggie();
	}
	wait_for_child(bart);
	wait_for_child(lisa);
	wait_for_child(maggie);
	exit(0)
}
void abraham() {
	printf("Abraham");
	pid homero = fork();
	if (homero == 0) {
		homero();
	}
	wait_for_child(homero);
	exit(0)
}

void main() {
	abraham();
}
```
# Ejercicio 6
	El sistema operativo del punto anterior es extendido con la llamada al sistema 
	void exec(const char *arg). Esta llamada al sistema reemplaza el programa actual por el código
	localizado en el string. Implementar la llamada al sistema void system(const char *arg) usando
	las llamadas al sistema ofrecidas por este sistema operativo.

```c++
void system(const char *arg) {
	pid child = fork();
	if (pid == 0) {
		exec(arg);
	} else {
		wait_for_child(child);
	}
}
```

# Ejercicio 7

**a) ¿Qué variables deben residir en el área de memoria compartida?**
tiki y taka

**b) ¿Existe alguna variable que no deba residir en el espacio de memoria compartida?**
temp

**c) Escribir un procedimiento main() para el problema del tiki-taka usando el código presentado y las
llamadas al sistema para comunicación entre procesos provistas por este sistema operativo.**

```c++
#define SIZE 5
int tiki;
int taka;
int temp;

void taka_runner() {
	while (true) {
		temp = tiki;
		temp++;
		taka = temp;
	}
}

void tiki_taka() {
	while (true) {
		temp = taka;
		temp++;
		tiki = temp;
	}
}

void main() {
	share_mem(tiki);
	share_mem(taka);
	pid tiki = fork();
	if (tiki==0) {
		tiki_taka();
	} else {
		pid taka = fork();
		if (taka==0) {
			taka_runner();
		} else {
			wait_for_child(taka);
		}
		wait_for_child(tiki);
	}
}
```