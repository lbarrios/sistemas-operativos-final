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

Las cuatro condiciones de koffman dicen las pre-condiciones necesarias para generar un deadlock. Sirven por que dan cuatro vectores potenciales para evitar deadlocks, cualquier estrategia que ataque uno de estos cuatro puntos garantiza que el sistema ande bien. 

Las 4 condiciones son:

* Exclusion Mutua: cuando se entra en una session critica, se toma posesion absoluta sobre ese recurso. No se puede compartir, a diferencia de, por ejemplo, una lectura. (donde varios procesos pueden leer la misma informacion)

* Hold and request: Despues de pedir un recurso, el proceso pide un nuevo recurso sin soltar el anterior.

* No preemption: No hay forma de desalojar los procesos una vez que estos tienen un recurso. Ese recurso sera del proceso hasta que este mismo decida soltarlo.

* Dependencia circular: debe haber una dependencia circular entre procesos. Es decir, debe ser posible formar un ciclo entre los recursos ya pedidos de los procesos y los necesarios para que termine.

### ¿Por qué es necesaria la primitiva Test & Set para la implementación de semáforos? ¿Alcanza con la primitiva T&S en arquitecturas multiprocesador? En caso afirmativo justificar. En caso negativo, proponer una solución.

La primitiva test and set le permite al procesador recibir un valor y modificarlo de forma atomica. Esto es necesario por que de ser una operacion que tome varios pasos, la operacion podria ser interrumpida en la mitad y esto generaria errores.

Para tirar un ejemplo, supongamos que tenemos dos procesos, A y B, que quieren acceder al recurso x.

Podria ocurrir que el proceso A despues de obtener el valor de x (x = 0) pero antes de setearlo en 1 es interrumpido por el scheduler. Entonces se pasa al proceso B, que obtiene el valor de x (x = 0), y lo setea en 1. El proceso B continua ejecutandose hasta que es nuevamente interrumpipdo por el scheduler SIN liberar el recurso x. Luego, el proceso A continua, seteando x en 1 (es decir, no cambia nada) y prosiguendo. Ambos procesos estan usando x. 

Hay dos potenciales problemas con usar Test & Set en multiprocesador:

==Potential Chamuyo Warning==  A. Los procesadores no comparten CACHE. Al trabajar, la primitiva Test & Set intentara leer el CACHE (y no la RAM), por lo cual podrian haber un error en el que dos procesos hagan test&set sobre variables que se encuentran en su respectivo CACHE.

>  La forma de solucionar esto es forzando a que Test & Set trabaje sobre el RAM. El inconvenient de esta solucion es que seria mas lento implementar Test & Set. 

>  Otra forma seria teniendo un CACHE separado para todos los procesadores, que trabaje con los Test & Set. El problema con esta solucion es que seria mas caro de implementar. (se requiere mas hardware)

B. Si (A) esta resulto, todavia tenemos el problema que la operacion Test & Set podria no ser atomica en multi processadores. Es decir, si hay un T&S en el procesador 1 y el procesador 2 lee a mitad del T&S podria tener un valor distinto que si lee al final del T&S (condicion de carrera). Para solucionar esto, el T&S tiene que ser atomico para todos los procesadores.

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

En pseudo-codigo:

[deshabilitar interrupciones]
viejo valor = x
x = 1
[habilitar interrupciones]
xreturn viejo valor


### Provea dos implementaciones de un objeto lock basadas en TAS y argumente sobre sus ventajas y desventajas.

==TODO:==

### Cuál es el número mínimo de registros atómicos RW necesarios para garantizar exclusión mutua para n procesos. ¿Es posible hacerlo con menos registros si se asume que el tiempo que tarda ejecutar una operación de lectura o escritura sobre un registro atómico está acotado por una constante δ conocida? Justifique.

==TODO:==

### Qué es la instrucción Test and Set? Para qué sirve? Justificar.

Ver "¿Por qué es necesaria la primitiva Test & Set para la implementación de semáforos?"

### Dar dos soluciones (al menos una correcta) para el problema de la cena de los filósofos. Compararlas.

==TODO:==

### Dos procesos, P0 y P1, ejecutan los siguientes programas: (06/08/2015)

```c++
----------------------------|----------------------------
P0                          |P1
----------------------------|----------------------------
while(1) {                  | while(1) {
  ## flag[0] = 1;           |   flag[1] = 1;
  waitfor(flag[1] == 0);    |   while(flag[0] == 1) {
                            |    flag[1] = 0;
                            |    waitfor(flag[0] == 0);
                            |    ## flag[1] = 1;
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

### Proponer una primitiva de sincronización para cada caso y justificar:

    1. Acceso exclusivo a disco
    2. Estructura que permite hasta 3 accesos simultáneos
    3. Contador que se quiere incrementar

==TODO:==