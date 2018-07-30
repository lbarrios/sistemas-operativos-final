### Explicar ventajas y desventajas de 3 estrategias de E/S a disco. (Se refiere a algoritmos de scheduling de disco)

#### Nacho:
==Duda: scheduling de disco? No sera de lectura de disco?==
==En caso de no serlo, esto esta mal==

- FCFS(FIFO): el problema que tiene es que es completamente ineficiente. No toma en cuenta el movimiento de la cabeza. La ventaja es que es trivialmente facil de implementar. 

- Shortest seek time first: prioriza la busqueda de archivos mas cercanos a donde se encuentra la cabeza. La ventaja es que optimo. La desventaja es que puede generar starvation.

- Scan: recorre de izquierda a derecha, una vez que llega al final, vuelve de izquierda a derecha. Esto permite optimizar los accessos a disco. ==Esto que sigue es chamuyo== El problema es que puede generar trabajo inutil, moviendo la cabeza de mas.

- Look: igual que Scan, pero si no hay posiciones "mas adelante" vuelve y no sigue avanzando. Sobre esto no encontre nada malo, pero imagino ==chamuyo again== que un problema es que genera una respuesta mas rapida en las "primeras entradas" del disco, mientras que da un tiempo de respuesta mas lento a las que estan en el final.

- Mejora C a Scan o Look (C-Scan, C-Look): es lo mismo que los anteriores, pero cuando termina de hacer el seek de izquierda a derecha, vuelve al comienzo (en vez de hacerlo de derecha a izquierda). La logica es que si acabo de terminar, es mas probable que haya pedidos a la izquierda que a la derecha. Entonces siempre hago seek donde es mas probable que haya entradas.

#### Eze:
* FCFS (FIFO): los pedidos se atienden en el mismo orden en que fueron recibidos.
	* Ventajas: Sencillo. Fácil de implementar, fácil de mantener. Funciona bien, y previene la inanición.
	* Desventajas: Puede llegar a funcionar muy mal si se intercalan pedidos accesos a sectores del disco que se encuentran alejados el uno del otro de forma tal que requieren mover el cabezal constantemente; esto hace que aumente el tiempo de seek time.

* Escaneo/Ascensor: el cabezal se mueve de un extremo al otro del disco, atendiendo todos los pedidos que encuentre en el medio.
	* Ventajas: Fácil de implementar. Suele funcionar mejor que enfoques como FCFS. Optimiza el uso del cabezal, y previene la inanición porque siempre va a recorrer (en algún momento) cada pista.
	* Desventajas: Pueden llegar a haber casos patológicos. Si voy agregando pedidos a los sectores a medida que el cabezal va recorriéndolos (es decir, en el "rastro" que va dejando el cabezal), se maximiza el tiempo de espera para esos pedidos, ya que hay que esperar que el cabezal llegue hasta el final, y regrese, para que vuelva a pasar por allí.

* Shortest Seek Time: los pedidos se atienden según el que se encuentre más cerca del cabezal.
	* Ventajas: Relativamente fácil de implementar. La utilización del cabezal es óptima, ya que se asegura que siempre se va a mover lo menos posible.
	* Desventajas: Pueden llegar a haber casos patológicos; **¡puede generar starvation/inanición!**, esto es muy malo. Si hay varios pedidos a sectores que se encuentran todos cercanos, y el cabezal se encuentra leyendo allí, y entra un pedido a un sector muy lejano, la idea es que se van a atender primero todos los pedidos que se encuentran cercanos. Pero si los pedidos a esa zona siguen entrando indefinidamente, el otro pedido jamás se va a atender, porque siempre va a ser más prioritario atender los que están cerca.

### Dado un disco de 100 cilindros, numerados de 0 a 99. Determine el orden de visita de los cilindros para una de las estrategias anteriores. Considere que desplazar el cabezal de un cilindro a uno consecutivo toma una unidad de tiempo y que se empieza en el cilindro 0.

==TODO:==
