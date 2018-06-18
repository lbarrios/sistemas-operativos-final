### Elegir una primitiva de sincronización para los siguientes casos y justificar su elección. 

    Sincronizar procesos para: 

      1. acceso exclusivo a disco 
      2. acceso a una estructura que soporta hasta 3 procesos concurrentes
      3. acceso exclusivo a un contador que se quiere incrementar.

==TODO:==

### Considere el modelo de memoria compartida.

    1) Dé dos primitivas de sincronización. 
    2) De implementaciones para cada una de ellas. Explique y justifique todo lo que asuma. 
    3) Explique ventajas y desventajas de cada una.

==TODO:==

### ¿Cómo cambiaría la implementación de los locks distribuidos para sistemas non-preemptive (sistemas sin desalojo)?

==TODO:==

### Defina condición de carrera (race condition).

==TODO:==

### ¿Cuáles son las 4 condiciones de Koffman y para qué nos sirven?

==TODO:==

### ¿Por qué es necesaria la primitiva Test & Set para la implementación de semáforos? ¿Alcanza con la primitiva T&S en arquitecturas multiprocesador? En caso afirmativo justificar. En caso negativo, proponer una solución.

==TODO:==

### Desarrollar ReentrantLock que soporte locks recursivos.

==TODO:==

### Explicar por qué la implementación de una cola FIFO no es correcta.

```c++
atomic<int> tail, head = 0;
int capacidad = N;
T[] items = new T[N];
void queue(x){
  assert(!full());
  items[tail.getAndInc() % capacidad] = x;
}
T dequeue(){
  assert(!empty());
  T x = items[head.getAndInc() % capacidad];
  return x;
}
bool full(){return tail.get() - head.get() == capacity};
bool empty(){return tail.get() - head.get() == 0};
```

==TODO:==

### Dar una implementación correcta wait-free para 1 productor y 1 consumidor.

==TODO:==

### Defina la operación atómica TestAndSet (TAS)

==TODO:==

### Provea dos implementaciones de un objeto lock basadas en TAS y argumente sobre sus ventajas y desventajas.

==TODO:==

### Cuál es el número mínimo de registros atómicos RW necesarios para garantizar exclusión mutua para n procesos. ¿Es posible hacerlo con menos registros si se asume que el tiempo que tarda ejecutar una operación de lectura o escritura sobre un registro atómico está acotado por una constante δ conocida? Justifique.

==TODO:==

### Qué es la instrucción Test and Set? Para qué sirve? Justificar.

==TODO:==

### Dar dos soluciones (al menos una correcta) para el problema de la cena de los filósofos. Compararlas.

==TODO:==

### Dos procesos, P0 y P1, ejecutan los siguientes programas: (06/08/2015)

```c++
----------------------------|----------------------------
P0                          |P1
----------------------------|----------------------------
while(1) {                  | while(1) {
  flag[0] = 1;              |   flag[1] = 1;
  waitfor(flag[1] == 0);    |   while(flag[0] == 1) {
                            |    flag[1] = 0;
                            |    waitfor(flag[0] == 0);
                            |    flag[1] = 1;
                            |   }
  /*Sección Crítica*/       |   /*Sección Crítica*/
  flag[0] = 0;              |   flag[1] = 0;
}                           | }
----------------------------|----------------------------
```

    ¿Hay exclusión mutua? Justificar.
    ¿Están libres de deadlock? Justificar.
    ¿Hay inanición de algún proceso? Justificar.
    Si P1 empieza a ejecutar el código de P0, cambiando flag[0] por flag[1], ¿qué ocurriría?

==TODO:==