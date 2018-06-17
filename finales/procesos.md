### ¿Qué es y para qué sirve una System Call? Explicar los pasos involucrados por hardware y software. Ejemplificar.

==TODO:==

### Una PCB clásica para el manejo de procesos contiene todos los recursos para que el proceso pueda ejecutar, por ejemplo Registros, Archivos abiertos, etc. ¿Cómo debe modificarse para soportar threads?

==TODO:==

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