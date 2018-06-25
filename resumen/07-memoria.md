# Administración de Memoria
Es uno de los roles del Sistema Operativo, y por lo general es un subsistema propio.

La memoria se comparte:
	- IPC
	- Multiprogramación

## Roles de un subsistema de memoria

- Manejar el espacio libre (y ocupado)
- Asignar (y liberar) memoria
- Swapping (memoria principal <-> disco)

## Objetivos

- Si hay un solo proceso en memoria, no es necesario compartir nada.
- Si hay varios procesos corriendo concurrentemente:
	- Se puede hacer swapping siempre (cada proceso que no esté corriendo se pasa a disco). Esto es lento, e innecesario.
	- Mejor opción: se pueden dejar todos los procesos que se puedan en memoria, mientras entren en ella.
	- Si no hay espacio en la memoria, se hace swapping para desalojar los procesos que no estén corriendo. ¡Cuando se necesiten volver a alojar, el espacio de memoria que les toque seguramente no sea el mismo!

## Problemas

- Manejo del espacio libre (evitando la fragmentación).
- Protección (memoria privada de los procesos).
- Reubicación (cambio de contexto, swapping).

## Manejo del espacio libre / Fragmentación

### Fragmentación

#### Fragmentación Externa
Cuando los bloques de memoria están dispersos, de forma tal que no es posible asignarle una determinada cantidad de memoria **contigua** a un proceso.

Ejemplo, se cuenta con el siguiente mapa de memoria:
```
| proceso A | libre | libre | proceso B | libre | libre | proceso C | libre |
```
Un proceso D necesita 3 bloques de memoria. El sistema cuenta con 5 bloques libres, por lo que debería poder asignarle la memoria al proceso. Pero debido a que la misma está fragmentada, no puede ser asignada (la máxima cantidad de bloques contiguos de la que dispone el sistema es 2).

Una solución sería compactar/reubicar los bloques:
```
| proceso A | libre | libre | proceso B | libre | libre | proceso C | libre |
pasaría a ser
| proceso A | proceso B | proceso C | libre | libre | libre | libre | libre |
```
Pero esto es costoso en tiempo, y a veces no es posible (ejemplo: sistemas RT).

#### Fragmentación Interna
Cuando se divide la memoria en bloques de tamaño fijo, un proceso necesita una cantidad X de memoria, y se le asigna una cantidad de memoria Y>X, de forma tal que el espacio (Y-X) se desperdicia, ya que el proceso no lo utiliza, y no puede ser asignado a otros procesos.

### Organización de la Memoria

#### Mapa de Memoria de una Tarea

```
+ HIGHER ADDRESSES

------- <- bottom
 STACK		<- Variable Size (grows down --)
------- <- top
   .	\	
   .	 \	
   .      |	<- Free Space
   .	 /	
   .	/	
-------
  HEAP		<- Variable Size (grows up ++)
-------
  BSS		<- Fixed Size
-------
  DATA 		<- Fixed Size
-------
  TEXT 		<- Fixed Size
-------

- LOWER ADDRESSES
```

#### Bitmap
Se divide la memoria en bloques de tamaño fijo. El bitmap es un arreglo de booleanos. Cada posición del bitmap representa un bloque, y se guarda 0 si está libre, 1 si está ocupado.

- Asignar y liberar bloques es sencillo O(1)
- Encontrar bloques consecutivos es O(N)
- Hay un tradeoff entre granularidad y el tamaño del bitmap:
	- bloques de menor tamaño -> menos fragmentación interna -> mayor tamaño de bitmap
	- menor tamaño de bitmap -> bloques de mayor tamaño -> más fragmentación interna
- No es muy usado

#### Lista Enlazada
Cada nodo representa a la memoria de un proceso, o a un bloque libre (en cuyo caso figura el tamaño del bloque)

- Liberar y asignar es O(1) (manejar punteros)
- Se puede combinar con Bitmap
- ¿Dónde asignar los bloques?
	- First Fit: usa el primer bloque libre.
		- Es rápido.
		- Genera fragmentación.
	- Best Fit: busca el bloque más adecuado (el más pequeño posible)
		- Es más lento.
		- ¡...no es mejor que First Fit!
	- Quick Fit: variación de Best Fit.
		- Se mantiene una lista de los bloques libres de los tamaños más solicitados.
		- No es tan lento como Best Fit.
	- Buddy System
		- Usa splitting* de bloques.

Todos los esquemas anteriores fallan, produciendo fragmentación (externa o interna). En la práctica se usan esquemas más sofisticados, y no son triviales (¡están fuera del alcance de la materia!).

### Memoria Virtual

==TODO: 07-teorica-administracion-de-memoria.pdf, página 16/44==