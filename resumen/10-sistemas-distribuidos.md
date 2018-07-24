# Sistemas Distribuídos
    Conjunto de recursos interconectados
    que interactúan entre sí.

## Ejemplos:
* Varias máquinas conectadas en red.
* Un procesador con varias memorias.
* Varios procesadores con una memoria.
* Cualquier combinación de las anteriores.
* Etcétera.

## Ventajas:
* Paralelismo: el trabajo se reparte, por lo que se hace más rápido.
* Replicación: la misma información o trabajo puede estar en varias partes, aumentando la confiabilidad.
* Descentralización: previene la contención.

## Problemas:
* Sincronizar las operaciones.
* Mantener coherencia.
* Información parcial.
* No suelen compartir clock.
	* No se puede trabajar de forma sincrónica.

## Sistemas con Memoria compartida
	Se trabaja con algún mecanismo de Memoria Compartida, de forma tal que el Software de usuario no sabe que en realidad se cuenta con un Sistema Distribuído.

### Por Hardware
* Uniform Memory Access (UMA)
* Non Uniform Memory Access (NUMA)
* Híbrida

### Por Software
* Estructurada
	* Memoria Asociativa.
	* Distributed Arrays.
* No estructurada
	* Memoria Virtual global.
	* Memoria Virtual particionada.

## Sistemas sin Memoria Compartida
	Se depende de la cooperación del software para realizar las operaciones necesarias. La arquitectura del software es diseñada para trabajar como un sistema distribuído.

### Sincrónicos

* Telnet: es un protocolo para conectarse remotamente a un equipo, pero sirve como ejemplo de un programa delegando una tarea en una terminal remota. Entonces, los recursos invoulcrados (CPU, Memoria, etc) no son los locales, sino los de la máquina remota. En la máquina cliente, sólamente se requiere correr el propio protocolo de conexión, el cual es muy liviano.

* RPC (Remote Procedure Call): Es un mecanismo que permite a los programas llamar a funciones de manera remota (en un principio diseñado para C). Involucra bibliotecas que ocultan los detalles de la comunicación al programador, y permiten realizar el envío de datos de forma transparente. Es un mecanismo sincrónico.
	* Java Remote Method Invocation (RMI)
	* JavaScript Object Notation (JSON-RPC)
	* Simple Object Access Protocol (SOAP)

* Este tipo de arquitecturas se suelen llamar **cliente/servidor**.
	* El servidor proporciona servicios cuando el cliente se lo pide.
	* El servidor no tiene un rol activo en el procesamiento, simplemente espera que se le pidan cosas.
	* Para completar la tarea, entonces, el programa hace de cliente de los distintos servicios/servidores que va necesitando.

### Asincrónicos

* RPC asincrónico
	* Promises
	* Futures
	* Windows Asynchronous RPC

* Pasaje de mensajes (send / receive)
	* Mailbox
	* Pipe
	* Message Passing Interface (MPI) para C/C++
	* Scala actors: send, receive/react

#### Pasaje de Mensajes

* Es el mecanismo más general.
* No asume que haya nada compartido, excepto el canal de comunicación.
	* Al haber un canal de comunicación, si el mismo serializa las operaciones, puede no ser necesario contar con Mutex.
* Desafíos
	* Codificación de los datos
	* Hay que dejar de procesar para atender los llamados de mensajes
	* Es lento
	* El canal puede perder mensajes
	* Podría haber un costo económico relacionado a la transmisión de cada mensaje (ej. supongamos que cada mensaje es un SMS).
* Existen bibliotecas que ayudan con estos problemas, la más popular es MPI.
* Curiosidad: **Conjetura de Brewer**, en un sistema distribuído no se puede tener a la vez consistencia, disponibilidad y tolerancia a fallas.

## Locks en Sistemas Distribuídos
* No existe TestAndSet atómico (!)
* ¿Cómo se implementan los locks?
* ### Centralizado
	* Poner el control de los recursos (¡no los recursos en sí!) bajo un único nodo (coordinador).
		* Esto genera contención
	* Dentro de ese nodo hay procesos que ofician de representantes (proxies) de los procesos remotos.
		* Es decir, este nodo central recibe los pedidos, e internamente los delega a los otros nodos, y viceversa.
	* Cuando un proceso necesita un recurso, se lo pide al proxy, que se encarga de negociar con los otros proxies utilizando los mecanismos de sincronización habituales (al ser procesos locales).
	* Problemas:
		* Todo depende de un nodo.
		* Hay un punto único de falla.
		* Cuello de botella en procesamiento y red.
		* Se requiere consultar al coordinador incluso para acceder a los propios recursos, o aquellos cercanos.
		* Cada interacción con el coordinador requiere de mensajes, lo cual agrega overhead.

## Lamport
### Idea general
* No importa cuándo suceden exactamente las cosas.
* Lo único importante es si algo ocurre antes o después de otra cosa.
* Se define un **orden parcial no reflexivo**.
	* Si dentro de un proceso A sucede antes que B, entonces A -> B
	* Si E es el envío de un mensaje y R es su recepción, E -> R. Incluso si E y R suceden en procesos distintos.
	* Si A -> B y B -> C, entonces A -> C.
	* Si no vale A -> B y tampoco vale B -> A, entonces A y B son concurrentes.

### Implementación:
* Cada procesador tiene un reloj; tiene que ser un valor monótonamente creciente en función de las lecturas.
* En cada mensaje se incluye el valor del reloj.
* Como la recepción siempre es posterior al envío, al recibir un mensaje con una marca de tiempo T, con T mayor al reloj actual, se actualiza el reloj a T+1. 
* Todo lo anterior da un orden parcial. Para generar un orden total, hay que desempatar.
	* Es necesario buscar una forma de ordenar arbitrariamente.
	* Por ejemplo, a través del PID.

## Acuerdo Bizantino
	El problema de nunca poder estar seguro de que el mensaje (o la confirmación, o la confirmación de la confirmación, etc) llegó a destino.

### Teoremas
* No existe ningún algoritmo para resolver consenso en un escenario de fallas en la comunicación.
* En caso de que hayan k < n procesos que dejen de funcionar, se puede resolver el consenso en O((k+1) . n^2) mensajes.
* Si los procesos no son confiables, se puede resolver consenso ssi n>3.k y la conectividad es mayor que 2.k

## Clusters
* Desde el punto de vista científico: conjunto de computadoras conectadas por una red de alta velocidad, con un scheduler de trabajos en común.
* Desde el punto de vista común: conjunto de computadoras que trabajan cooperativamente desde alguna perspectiva.
* Grids: conjunto de clusters, cada uno bajo un dominio administrativo distinto.
* Clouds: clusters en donde uno puede alquilar una capacidad fija o variable bajo demanda.

## Scheduling en Sistemas Distribuídos

* Local: dar el procesador a un proceso.
* Global: asignar un proceso a un procesador (mapping).
	* Estático: en el momento de la creación del proceso (**afinidad**)
	* Dinámico: la asignación puede variar durante la ejecución (**migración**)
		* Iniciada por el procesador sobrecargado (**Sender Initiated**)
		* Iniciada por el procesador libre (**Receiver Initiated / Work Stealing**)
	* Compartir vs Balancear:
		* Compartir: repartir.
		* Balancear: repartir equitativamente.

### Factores de una Política de Scheduling
* Transferencia: cuándo hay que migrar un proceso.
* Selección: qué proceso hay que migrar.
* Ubicación: a dónde hay que enviar el proceso.
* Información: cómo se difunde el estado.