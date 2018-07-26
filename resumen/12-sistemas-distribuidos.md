# Sistemas Distribuidos

## Modelo de Fallas
* Nadie falla.
* Los procesos caen pero no se levantan.
* Los procesos caen y se levantan.
* Los procesos caen y se levantan pero sólo en determinados momentos.
* La red se particiona.
* Los procesos pueden comportarse de manera impredecible.

Cada modelo induce algoritmos distintos.

## Métricas
* Cantidad de mensajes que se envían a través de la red.
* Tipos de fallas que soportan.
* Cuánta información requieren.
	* El tamaño de la red.
	* La cantidad de procesos.
	* Cómo ubicar a cada uno de ellos.

## Problemas
* Orden de ocurrencia de los eventos
* Exclusión mutua
* Consenso

## Exclusión mutua distribuida
* La forma más sencilla se llama **token passing**
	* La idea es armar un anillo lógico entre los procesos y poner a circular un token.
	* Cuando quiero entrar a la sección crítica espero a que me llegue el token.
	* *Si no hay fallas, no hay inanición*.
	* Siempre hay mensajes circulando aún cuando no son necesarios.
	* Fiber Distributed Data Interface (FDDI)
	* Time-Division Multiple-Access (TDMA)
	* Timed-Triggered Architecture (TTA)
* Otra forma
	* **No circulan mensajes si no se quiere entrar a la sección crítica.**
	* Cuando quiero entrar a la sección crítica envío `solicitud(Pi, ts)`, siendo ts el timestamp.
	* Cada proceso puede responder inmediatamente, o encolar la respuesta.
	* Sólamente puedo entrar a la sección crítica cuando recibí todas las respuestas.
	* Al salir, respondo a todos los pedidos pendientes.
	* Respondo inmediatamente si:
		* No quiero entrar a la sección crítica.
		* Si quiero entrar, aún no lo hice, y el ts del pedido que recibo es menor que el mío.
	* Este algoritmo exige que todos conozcan la existencia de todos.
* **Se asume que:**
	- No se pierden mensajes
	- Ningún proceso falla

## Locks Distribuídos
* Procolo de Mayoría
	* Queremos obtener un lock sobre un objeto del cual hay copia en `n` lugares.
	* Para obtener un lock, debemos pedirlo a por lo menos `n/2+1` sitios.
	* Cada sitio responde si puede o no dárnoslo.
	* Cada copia del bojeto tiene un número de versión. Si lo escribimos, tomamos el más alto, y lo incrementamos en uno.
	* **Puede producir deadlock, hay que adaptar los algoritmos de detección.**
	* No es posible otorgar dos locks a la vez, ya que para ello cada proceso debería tener al menos `n/2+1` locks. Es decir que habrían `2(n/2+1)=2n+2` locks, lo cual es imposible.
	* Tampoco es posible leer una copia desactualizada, ya que para que eso suceda deberían haber `k>=n/2+1` locks cuya máxima marca sea `t` y existir otra copia `j` cuya marca `t_j > t`. Eso significiaría (por contradicción) que el último que escribió la versión `t_j`, lo hizo en menos de `n/2+1` copias, ya que si lo hubiera hecho en más de `n/2+1` copias, habrían en total más de `2n+2` copias, al menos `n/2+1` con la versión desactualizada, y al menos `n/2+1` con la versión actualizada.