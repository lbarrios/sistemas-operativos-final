### ¿Qué desafíos enfrentan los algoritmos de scheduling para sistemas con varios procesadores?

#### Nacho:
Son 5 los desafios

* Identificar: que parte de los procesos son paralelizables

* Balance: asegurarse que cada parte haga un trabajo razonable. No tiene sentido separar una tarea en micro tareas que son demasiado pequeñas.

* Distribucion/Separacion de la informacion: que la data este bien separada para poder correr en las tareas paralelizadas.

* Data dependency: si la informacion de una tarea depende de ejecutar antes otra tarea, esta tarea se tiene que ejecutar antes.

* Testear y debuggear: el espacio para testear se vuelve mucho mas grande si ademas de branches y paths tenes que considerar el paralelismo.  

#### Eze:
==TODO:==

### ¿Qué es el problema de inversión de prioridades y qué schedulers afecta?

#### Nacho:
La inversion de prioridad es cuando una tarea de menor prioridad toma el control de un recurso que luego es solicitado por una tarea de mayor prioridad. Luego, la tarea de mayor prioridad tiene que esperar a que la de menor prioridad le libere el recurso, es decir, se invierten las prioridades. 

El problema empeora si una tarea de prioridad media desaloja a la tarea de prioridad baja. En este caso, la tarea de prioridad alta terminaria esperando a la tarea de prioridad media en su totalidad. 

Para solucionar el caso anterior se utiliza el metodo de "herencia de prioridades". Esto quiere decir que si una tarea de prioridad alta esta esperando que una tarea de prioridad baja termine, esta tarea de prioridad baja pasa a tener prioridad alta momentaneamente. De esta manera, no podra ser desalojada por una tarea de prioridad media.

#### Eze:
==TODO:==

### Teniendo un algoritmo de scheduling al que los procesos le pueden pedir que se le agregue un quantum en determinado momento, y el scheduler te lo da sólo si eso ayuda al rendimiento total del sistema. ¿En que se tendría que fijar el scheduler para decidir si le corresponde quantum o no?

==TODO:==

### Suponga un sistema operativo que utiliza RR como scheduler, donde cada entrada de la cola de procesos es un puntero a la PCB. (a) ¿Es posible implementar un sistema de asignación de prioridades (i.e. darle más tiempo de procesamiento) a procesos manteniendo RR como scheduler? Justificar. (b) Esta implementación, ¿soporta scheduling de threads? Si la respuesta es afirmativa, muestre un ejemplo. Si la respuesta es negativa, proponga una modificación que lo permita.

==TODO:==

### ¿Puede haber inanición en MFQ (Multilevel Feedback Queue)? En caso afirmativo dar un ejemplo. En caso negativo, indicar el mecanismo que lo evita.

No, MFQ tiene un mecanismo de aging que hace que las tareas que estan en colas de menor prioridad suban a otras colas de mayor prioridad si no fueron llamadas hace mucho tiempo. Esto evita que haya inanición.

### Defina la propiedad de carga.

==TODO:==
