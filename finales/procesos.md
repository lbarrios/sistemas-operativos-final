### ¿Qué es y para qué sirve una System Call? Explicar los pasos involucrados por hardware y software. Ejemplificar.

Una System Call es un mecanismo por el cual los procesos o tareas pueden solicitar servicios al Sistema Operativo. Este tipo de servicios pueden ser, por ejemplo, abrir/cerrar/leer/escribir sobre un descriptor, realizar un fork, pedir memoria, terminar el proceso, etc. A bajo nivel, pueden ser representados mediante una interrupción (ejemplo: INT 0x80 en la API de Linux) o mediante instrucciones específicas (ejemplo: la instrucción SYSCALL en Intel 64 bits).

Los pasos involucrados son:

1. El programa en ejecución prepara los parámetros para el syscall (ya sea en la pila, o en registros, según lo indique la API del Sistema Operativo).
2. El programa en ejecución llama a la interrupción correspondiente a la rutina de atención del Syscall.
3. Por hardware, se preserva la dirección actual (CS:IP), la pila (SS:SP), y los flags, y se salta a la dirección de la rutina de atención de la interrupción correspondiente, que utiliza una pila de nivel 0.
4. Dentro de la rutina de atención, se pushea cualquier registro que sea necesario (depende de cómo esté definida la API, pero por lo general la rutina no debe modificar ningún registro, excepto aquellos que estén indicados explícitamente, como el valor de retorno), y se realiza la tarea solicitada.
5. Finalmente, se retorna al proceso.

### Una PCB clásica para el manejo de procesos contiene todos los recursos para que el proceso pueda ejecutar, por ejemplo registros, archivos abiertos, etc. ¿Cómo debe modificarse para soportar threads?

Para soportar threads, basta con agregar algún tipo de estructura (ejemplo una Lista Enlazada) que permita incluir información de tamaño variable dentro de la PCB. Entonces, cada proceso pasa a tener una lista de Thread Control Block que almacena en cada uno de sus nodos la información propia de cada thread.

PCB Normal:
```
|                Process Control Block              |
|    | código |     | datos |     | archivos |      |
|          | registros |      | pila |              |
```

PCB con threads:
```
|          Process Control Block  (threads)         |
|    | código |     | datos |     | archivos |      |
|                                                   |
|                                                   |
|    | thread 1  |   ->  ...  ->   | thread n  |    |
|    | registros |   ->  ...  ->   | registros |    |
|    | pila      |   ->  ...  ->   | pila      |    |
|    | ...       |   ->  ...  ->   | ...       |    |
```

### Proponga un escenario en donde un proceso requiera la modificación de algún valor de la PCB. Escriba el pseudocódigo de las rutinas para realizar ese cambio y quién (SO o proceso) es responsable de cada una.

El proceso no puede realizar la modificación del PCB, sino de forma indirecta a través de **llamados al sistema operativo**, o mediante la modificación del propio estado del programa (ejemplo registros).

Ejemplo: el proceso quiere abrir un archivo.

1. Se ponen en los registros del procesador los parámetros adecuados (ejemplo: eax=OPEN, ebx=filename).
2. Se llama a INT 80.
3. El sistema operativo busca el archivo correspondiente, realiza todas las verificaciones necesarias (ejemplo, que el proceso tenga permisos para abrir ese archivo).
    * Si todo está bien, el Sistema Operativo modifica la PCB del proceso agregando un descriptor de ese archivo, indexado por un número entero (ej, si el último descriptor abierto es el 5, lo agrega en el 6).
    * Si hay algún problema, retorna un código de error.
4. Se retorna del syscall, devolviendo el resultado de la operación (el índice del descriptor del archivo, o el código de error).
5. El proceso puede utilizar el archivo abierto a través de posteriores llamadas al sistema, refiriéndose al mismo a través del descriptor provisto previamente.

Es notable que la modificación del PCB se realizó de forma transparente al proceso.

### En Unix/Linux los procesos no pueden acceder a puertos de entrada/salida directamente, salvo que explícitamente se le de permiso. ¿Cómo podría implementarse?

El manual de intel detalla un campo IOMAP en la TSS de una tarea, que sirve para definir para cada puerto de IO si se van a chequear los privilegios (bit en 1) o no (bit en 0) al querer usar las instrucciones IN/OUT. Usando este mecanismo, la forma de darle permisos explícitos a una tarea (o sea, a un proceso) de acceder directamente a un puerto de IO, sería modificando el bit correspondiente en el IOMAP de su TSS.

==No sé si la pregunta apunta a esto==

### ¿Qué son las funciones reentrantes y cuál es su relación con los threads? Dar dos ejemplos de transición de running a ready.

Una funcion re-entrante es una funcion cuyo cuerpo principal puede ser llamado nuevamente de forma segura mientras el mismo se esta ejecutando. El ejemplo clasico son las funciones iterativas, donde el mismo cuerpo se ejecuta muchas veces para completar una sola ejecucion.

En el caso de los threads es importante por si se ejecuta muchas veces el mismo cuerpo en distintos threads, es clave saber que el codigo no genera ningun error.  

### Se puede ir directo de waiting a running? Explicar las razones.

En principio, según el modelo tradicional de estados, la respuesta sería que no, ya que el mismo establece que cuando un proceso está waiting, y se libera, debe pasar a running.

De cualquier modo, nada impide que un proceso pueda pasar de waiting a running bajo determinadas condiciones. Ejemplo, en un sistema en donde se puedan marcar determinados procesos como "urgentes", sería posible que cuando un proceso esté waiting, y se libere el recurso que lo estaba bloqueando, este pase de forma inmediata a running (desalojando a cualquier proceso que esté corriendo en ese momento). También podría suceder que no hubiera ningún proceso en estado running, por lo que más allá de la máquina de estados, se podría considerar que el proceso pasaría directamente a running.

### Cuál es la diferencia entre mode switch y context switch?

El cambio de contexto es cuando se cambia el contexto de ejecución del procesador. Es uno de los mecanismos que provee el procesador (al menos en el caso de IA-32) para administración de tareas. En el caso de Linux, por cuestiones históricas y de compatibilidad, dicho mecanismo está implementado por software, es decir, el cambio de contexto se hace a mano, en este caso mediante los PCB. Cuando se quiere cambiar de un proceso a otro, se guarda el estado actual del proceso (registros, IP, etc) en el PCB de ese proceso, y se carga el estado del otro proceso a partir del PCB correspondiente.

El cambio de modo es cuando se cambia el modo de ejecución, pasando de modo usuario a modo kernel (cambio de privilegios). Esto no implica necesariamente un cambio de contexto, aunque a veces van acompañados.

### Dibujar el mapa de memoria de un proceso.

*********
*heap	*
*------	*
*stack	*
*------	*
*data	*
*text	*
*********

### Qué pasa con la memoria cuando se crea un proceso hijo? Explicar los casos de fork() y vfork().

Cuando se crea un proceso hijo, en el caso de fork se copia completamente el proceso padre (registros, espacio de memoria, descriptores de archivos, etc), y en lo que respecta al espacio de memoria particularmente, se crea uno nuevo, que es una copia del del proceso padre; es decir, se copia todo el directorio de páginas, junto con las tablas de paǵinas, y el contenido de las páginas en sí (lo cual puede llegar a ser bastante lento), manteniendo las direcciones virtuales, pero usando nuevas direcciones físicas. 

Cuando se hace vfork, en cambio, se crea una copia del proceso padre, pero el espacio de memoria no se copia, sino que se toma prestado el del padre. Normalmente, en el caso de vfork, se espera que se realice una llamada a exec, o exit, sin utilizar realmente el espacio de memoria del padre, ya que de lo contrario se puede llegar a producir comportamiento indefinito.

`man vfork` tiene información útil:

* Standard description: The  vfork() function has the same effect as fork(2), **except that the behavior is undefined** (...) (!!)
* Linux description: vfork(), just like fork(2), creates a child process of the calling process.
* Historic description: Under Linux, fork(2) is implemented using copy-on-write pages, so the only penalty incurred by fork(2) is the time and memory required to duplicate  the  parent's  page  tables,  and to create a unique task structure for the child.  However, in the bad old days a fork(2) would require making a complete copy of the caller's data space, often needlessly, since usually immediately afterward an exec(3) is done.  Thus, for greater efficiency, BSD introduced the vfork()  system call,  which did not fully copy the address space of the parent process, but borrowed the parent's memory and thread of control until a call to execve(2) or an exit occurred.  The parent process was suspended while the child was using its resources.  The use of vfork() was tricky:  for  example,  not  modifying data in the parent process depended on knowing which variables were held in a register.

**NOTES**

Some consider the semantics of vfork() to be an _architectural blemish_, and the 4.2BSD man page stated: "This system call will be eliminated when proper system sharing mechanisms are implemented. Users should not depend on the memory sharing semantics of vfork() as it will, in that case, be made synonymous to fork(2)."

![<esta grasa no se quita.jpg>](img/vfork.jpg  "vfork")

Es decir, en los procesadores que soportan mecanismos de CopyOnWrite, la diferencia de performance entre vfork y fork se vuelve despreciable, ya que el espacio de memoria del padre no se copia, sino sólamente para aquellas páginas que se modifiquen.

### Qué es Copy on Write? Cómo funciona en sistemas con Paginación?

Copy on Write es un mecanismo provisto por el procesador / la MMU mediante el cual se pueden duplicar páginas sin necesidad de copiarlas (lo cual es lento), por ejemplo para ser utilizado cuando un proceso hace un fork. Entonces, sólamente se realiza la copia de una página cuando el proceso hijo intenta escribir en ella. Si, en cambio, intenta leer de una página, o ni siquiera la utiliza, la página efectivamente mapeada es la del padre.

Este mecanismo está fuertemente relacionado con paginación, ya que por lo general la forma de implementarlo es duplicando el mapa de memoria (Page Directory, Page Tables) del proceso, y marcando todas las páginas como de "solo lectura". En cuanto el proceso hijo intenta realizar una escritura, se produce una excepción en el procesador (eg: Page Fault), y la rutina de atención se encarga de copiar la página a una dirección física distinta, y marcarla como de lectura-escritura. Luego, se retorna al proceso, y la escritura se realiza sin problemas. Todo esto sucede de forma transparente al proceso.

### ¿Cuántas veces imprime "Hello, world!" el siguiente programa? Explicar. ¿Qué pasa si se usa vfork() en lugar de fork()?
```c++
foo () {
    int i;
    for(i = 0; i<3; i++) fork();
    printf("Hello, world!\n");
}
```

**Versión con FORK**: 8 veces.

i=0:
    p1.fork() -> p2.
i=1:
    p1.fork() -> p3.
    p2.fork() -> p4.
i=2:
    p1.fork() -> p5.
    p2.fork() -> p6.
    p3.fork() -> p7.
    p4.fork() -> p8.
i=3:
    p1.printf("...")
    p2.printf("...")
    p3.printf("...")
    p4.printf("...")
    p5.printf("...")
    p6.printf("...")
    p7.printf("...")
    p8.printf("...")

**Versión con VFORK**: 4 veces.

i=0:
    p1.vfork() -> p2.
i=1:
    p2.vfork() -> p3.
i=2:
    p3.vfork() -> p4.
i=3:
    p4.printf("...")
    p3.printf("...")
    p2.printf("...")
    p1.printf("...")