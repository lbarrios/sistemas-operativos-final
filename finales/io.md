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
==TODO:==

### Dado un disco de 100 cilindros, numerados de 0 a 99. Determine el orden de visita de los cilindros para una de las estrategias anteriores. Considere que desplazar el cabezal de un cilindro a uno consecutivo toma una unidad de tiempo y que se empieza en el cilindro 0.

==TODO:==
