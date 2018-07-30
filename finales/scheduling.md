### ¿Qué desafíos enfrentan los algoritmos de scheduling para sistemas con varios procesadores?

#### Nacho:
Son 5 los desafios

* Identificar: que parte de los procesos son paralelizables

* Balance: asegurarse que cada parte haga un trabajo razonable. No tiene sentido separar una tarea en micro tareas que son demasiado pequeñas.

* Distribucion/Separacion de la informacion: que la data este bien separada para poder correr en las tareas paralelizadas.

* Data dependency: si la informacion de una tarea depende de ejecutar antes otra tarea, esta tarea se tiene que ejecutar antes.

* Testear y debuggear: el espacio para testear se vuelve mucho mas grande si ademas de branches y paths tenes que considerar el paralelismo.  

#### Eze:

* Afinidad: Definir la afinidad de los procesos a los distintos procesadores.
	* ¿Usar afinidad dura o afinidad blanda?
	* Caché: Migrar un proceso es costoso, porque se desperdicia caché de un procesador, y en el otro hay que leer todo nuevamente.
* Balance de carga: Distribución adecuada de la carga entre los múltiples procesadores. 
	* Por ejemplo, no me sirve un scheduler que asigna todos los procesos a un único procesador mientras el resto no hacen nada.

### ¿Qué es el problema de inversión de prioridades y qué schedulers afecta?

#### Nacho:
La inversion de prioridad es cuando una tarea de menor prioridad toma el control de un recurso que luego es solicitado por una tarea de mayor prioridad. Luego, la tarea de mayor prioridad tiene que esperar a que la de menor prioridad le libere el recurso, es decir, se invierten las prioridades. 

El problema empeora si una tarea de prioridad media desaloja a la tarea de prioridad baja. En este caso, la tarea de prioridad alta terminaria esperando a la tarea de prioridad media en su totalidad. 

Para solucionar el caso anterior se utiliza el metodo de "herencia de prioridades". Esto quiere decir que si una tarea de prioridad alta esta esperando que una tarea de prioridad baja termine, esta tarea de prioridad baja pasa a tener prioridad alta momentaneamente. De esta manera, no podra ser desalojada por una tarea de prioridad media.

#### Eze:
El problema de inversión de prioridades es cuando un proceso de prioridad alta requiere de un recurso que tiene un proceso de prioridad baja. Entonces, la ejecución del proceso de prioridad alta está supeditada a la del de prioridad baja, es decir, se genera una dependencia que si no es bien manejada puede terminar en deadlock, y en casos no tan graves que la ejecución de una tarea crítica se retarde de una manera inaceptable.

Supongamos que entra en juego un proceso de prioridad media. El scheduler le va a dar prioridad a la ejecución de este proceso sobre la del de prioridad baja, ocasionando que el proceso de prioridad baja no se ejecute y no libere el recurso que necesita el proceso de prioridad alta. Esto termina generando que el proceso de prioridad media termine teniendo, en un sentido práctico, más prioridad que el de prioridad alta.

Dicho de otro modo, se termina generando un riesgo de inanición en el proceso de prioridad alta.

En principio afecta a los schedulers que usan distintas colas de prioridad, ya que en un scheduler con prioridad única, como RoundRobin, la ejecución del proceso de prioridad baja eventualmente va a terminar.

Formas de solucionarlo son, por ejemplo, utilizar herencia de prioridades, en donde cuando un proceso de prioridad alta solicita un recurso que tiene asignado un proceso de prioridad baja, este último pasa a tener prioridad alta temporalmente (hasta que libere el recurso). Otrá forma posible sería hacer preemption, es decir, que de algún modo el proceso de prioridad alta pueda solicitar la liberacioń inmediata de un recurso que necesita y que otro proceso de menor prioridad esté bloqueando. Esto último suena un poco violento, pero puede llegar a tener sentido en algunos sistemas críticos, ejemplo un sistema RT de un vehículo autónomo en donde un proceso de prioridad máxima se encargue de controlar el frenado del vehículo ante un riesgo de colision: en tal caso, no debería importar si otro proceso está bloqueando las ruedas, porque frenar el vehículo es urgente.

### Teniendo un algoritmo de scheduling al que los procesos le pueden pedir que se le agregue un quantum en determinado momento, y el scheduler te lo da sólo si eso ayuda al rendimiento total del sistema. ¿En que se tendría que fijar el scheduler para decidir si le corresponde quantum o no?

==TODO:==

### Suponga un sistema operativo que utiliza RR como scheduler, donde cada entrada de la cola de procesos es un puntero a la PCB. (a) ¿Es posible implementar un sistema de asignación de prioridades (i.e. darle más tiempo de procesamiento) a procesos manteniendo RR como scheduler? Justificar. (b) Esta implementación, ¿soporta scheduling de threads? Si la respuesta es afirmativa, muestre un ejemplo. Si la respuesta es negativa, proponga una modificación que lo permita.

==TODO:==

### ¿Puede haber inanición en MFQ (Multilevel Feedback Queue)? En caso afirmativo dar un ejemplo. En caso negativo, indicar el mecanismo que lo evita.

No, MFQ tiene un mecanismo de **aging** que hace que las tareas que estan en colas de menor prioridad suban a otras colas de mayor prioridad si no fueron llamadas hace mucho tiempo. Esto evita que haya inanición.

### Defina la propiedad de carga.

==TODO:==
