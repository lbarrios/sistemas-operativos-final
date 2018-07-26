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

## Elección de Líder
	Problema: Una serie de procesos debe elegir a uno como líder para la ejecución de algún tipo de tarea.

* En una red sin fallas, es sencillo.
	* Le Lann, Chang y Roberts (N. Lynch, cap 3 y cap 15.1)
	* Mantengo un status que dice que no soy el líder.
	* Organizo los procesos en anillo, hago circular mi ID.
	* Cuando recibo un mensaje, comparo el ID que circula con el mío. Hago circular el mayor.
	* Cuando el mensaje dio toda una vuelta, todos los procesos saben quién es el lider.
	* Ponemos a girar un mensaje de notificación para que todos lo sepan.
* Complicaciones posibles:
	* Varias elecciones simultáneas.
	* Procesos que suben y bajan del anillo.
* Tiempo:
	* Sin fase de stop O(n)
	* Con fase de stop O(2n)
* Comunicación:
	* O(N²)
	* Cota inferior Ω(n log n). 
		* Algoritmo de Hirshberg y Sinclair.

## Instantánea Global Consistente
* Sea un estado `E = ΣEi`, siendo Ei la parte del estado que le corresponde al proceso Pi. 
* Lo único que modifica el estado son los mensajes que los procesos se mandan entre sí, y no los eventos externos.
* Quiero obtener una **instantánea (snapshot)** consistente de E.
* Esto es, en un momento dado, a partir de que hago el pedido, cuánto valían los Ei y qué mensajes había circulando en la red.
* Para ello, se envía un mensaje de _marca_.
* Cuando Pi recibe un mensaje de marca por primera vez, guarda una copia Ci = Ei, y envía un mesnaje de marca a todos los otros procesos.
* Luego, Pi empieza a registrar todos los mensajes que recibe de cada vecino Pj, hasta que recibe marca de todos ellos.
* En ese momento queda conformada la escuencia Recibidos(i,j) de todos los mensajes que recibió Pi de Pj antes de que éste tomara la instantánea.
* El estado global es que cada proceso está en el estado Ci y los mensajes que están en Recibidos están circulando por la red.

== TODO: Repasar esto de https://en.wikipedia.org/wiki/Chandy-Lamport_algorithm ==

## Two-Phase Commit
* La idea es realizar una transacción de manera atómica. Todos los nodos deben estar de acuerdo en qué se hizo y qué no se hizo.
* En la primera fase se le preguntan a todos si están de acuerdo con realizar la transacción.
	* Si se recibe un no, se aborta la transacción.
	* Se van anotando todos los sí que se reciben, hasta tenerlos todos.
	* Si pasado un tiempo no se recibieron todos los sí, también se aborta.
* Si se reciben todos los sí, se avisa a todos que la transacción quedó confirmada.
* No protege contra todas las fallas, pero sí contra muchas.
* Terminación débil: si no hay fallas, todo proceso decide.
* Terminación fuerte: todo proceso que no falla, decide.
* **Teorema**: Two-phase commit resuelve COMMIT con terminación débil.
	* Two-phase commit no satisface terminación fuerte.
	* La solución es three-phase commit (N. Lynch, cap 7.2 y 7.3)

## Consenso: acuerdos y aplicaciones

* Acuerdos:
	* k-agreement (o k-set agreement): decide(i) pertenece a W, tal que `|W| = k`
	* Aproximado: para todo i!=j, `|decide(i)-decide(j)| <= e`
	* Probabilístico: `Pr[existe i!=j, decide(i)!=decide(j)] < e`

* Aplicaciones:
	* Sincronización de relojes (NTP, RFC 5905 y anteriores)
	* Tolerancia a fallas en sistemas críticos

## Bibliografía Adicional

* Nancy Lynch, Distributed Algorithms, Morgan Kaufmann, 1996. ISBN 1-55860-348-4.
* Hermann Kopetz, Gunther Bauer: The time-triggered architecture. Proceedings of the IEEE 91(1): 112-126 (2003). http://goo.gl/RPqfas
* R. Jain. FDDI Handbook. Addison Wesley, 1994. http://goo.gl/YZ2Hyl