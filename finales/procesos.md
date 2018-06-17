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

==TODO:==

### En Unix/Linux los procesos no pueden acceder a puertos de entrada/salida directamente, salvo que explícitamente se le de permiso. ¿Cómo podría implementarse?

==TODO:==

### ¿Qué son las funciones reentrantes y cuál es su relación con los threads? Dar dos ejemplos de transición de running a ready.

==TODO:==

### Se puede ir directo de waiting a running? Explicar las razones.

==TODO:==

### Cuál es la diferencia entre mode switch y context switch?

==TODO:==

### Dibujar el mapa de memoria de un proceso.

==TODO:==

### Qué pasa con la memoria cuando se crea un proceso hijo? Explicar los casos de fork() y vfork().

==TODO:==

### Qué es Copy on Write? Cómo funciona en sistemas con Paginación?

==TODO:==

### ¿Cuántas veces imprime "Hello, world!" el siguiente programa? Explicar. ¿Qué pasa si se usa vfork() en lugar de fork()?
```
foo () {
 int i;
 for(i = 0; i<3; i++) fork();
 printf("Hello, world!\n");
}
```

==TODO:==

### Elegir una primitiva de sincronización para los siguientes casos y justificar su elección. 

    Sincronizar procesos para: 

      1. acceso exclusivo a disco 
      2. acceso a una estructura que soporta hasta 3 procesos concurrentes
      3. acceso exclusivo a un contador que se quiere incrementar.

==TODO:==
