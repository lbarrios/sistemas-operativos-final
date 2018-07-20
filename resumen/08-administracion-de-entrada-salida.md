# Entrada / Salida
    Transferencia de datos desde y hacia dispositivos externos.

## Tipos de dispositivos

* Almacenamiento (discos, cdrom, pendrive, ...)
* Comunicaciones (placa de red, modem, ...)
* Interface de usuario (teclado, mouse, monitor, ...)
* Otros

## Dispositivos de Almacenamiento

* Discos rígidos
* Unidades de cinta
* Discos removibles
* Unidades de red

## Esquema de un dispositivo (en capas)

### Desde el Hardware
* Dispositivo físico: es el dispositivo en sí.
* Controlador del dispositivo: es el hardware que interactúa con el SO mediante un bus o registro.
* Bus: es el hardware comunica el controlador de dispositivo con la CPU, muchas veces tiene un controlador.

### Desde el Software
```
-------------------------------------
| Proceso | Proceso | Proceso | ... |
-------------------------------------
|            API del SO             |
-------------------------------------
| Subsistema de E/S | Otros subsist |
-------------------------------------
| Driver      | ... |      ...      |
-------------------------------------
| Dispositivo | ... |      ...      |
-------------------------------------
```

## Drivers

* Son componentes de software muy específicos.
* Saben comunicarse a bajo nivel con el hardware particular.
* Por lo general, cada hardware requiere un Driver específico.
* Son muy importantes:
    * Forman parte del kernel, o se incorporan como módulos
    * Corren con máximo privilegio
    * El rendimiento de E/S depende de ellos
    * Un driver mal programado puede repercutir en el rendimiento (!)
    * Un driver mal programado puede colgar el sistema operativo (!)

### Formas de interactuar con el Hardware

#### Polling
* El driver verifica cada un tiempo X si el dispositivo se comunicó
* Ventajas: sencillo, fácil de implementar, cambios de contexto controlados (pensar en un SO RT)
* Desventajas: CPU-intensivo, puede representar un desperdicio de recursos

#### Interrupciones (o push)
* El dispositivo avisa al SO que se quiere comunicar (mediante una interrupción)
* Ventajas: eficiencia en la utilización de CPU; sólamente se avisa cuando sucede un evento real
* Desventajas: más difícil de implementar, los cambios de contexto son impredecibles

#### DMA
* El dispositivo accede (lee/escribe) directamente a memoria.
* La CPU no interviene en el acceso a esa memoria.
* Cuando el dispositivo termina, avisa a la CPU mediante una interrupción.
* Ventaja: se pueden transferir grandes volúmenes de datos, sin necesidad de que la CPU intervenga.
* Desventaja: necesita hardware adicional (controlador de DMA)

## Subsistema de E/S
* Brinda a los procesos API sencilla:
    * open() / close()
    * read() / write()
    * seek()
* A pesar de lo anterior, hay cosas que no se deben ocultar.
    * Ejemplo: acceso **exclusivo** al dispositivo.
* El SO tiene que hacer todo esto de manera *correcta y eficiente*
* La responsabilidad se comparte entre el Manejador de E/S y el Driver (!)

### Char Device
    La información se transmite byte a byte

* No soportan acceso aleatorio.
* No utilizan caché.
* Ejemplo: Mouse, teclado, tty, puerto serie, ...

### Block Device
    La información se transmite en bloques

* Permiten acceso aleatorio.
* Pueden utilizar un caché.
* Ejemplo: disco rígido, cdrom, ...

## Subsistema de E/S Linux: 
    Acceso mediante /dev

### Características:
* lectura, escritura, o lecto-escritura
* secuenciales o aleatorios
* compartidos o dedicados
* char o block
* sincrónicos o asincrónicos
* tienen distinta velocidad de respuesta

Una de las funciones del SO es brindar mediante su API un acceso *consistente*, ocultando en la medida de lo posible las particularidades de cada uno de los dispositivos.

### API del subsistema de E/S de Linux:
* Todo es un archivo (!)
* Se proveen funciones de alto nivel para el acceso:
    * fopen, fclose: abrir y cerrar un descriptor
    * fread, fwrite: leer y escribir en modo **bloque**
    * fgetc, fputc: leer y escribir en modo **char**
    * fgets, fputs: leer y escribir en modo **char stream**
    * fscanf, fprintf: leer y escribir en modo char con formato

## Planificación de E/S:
* Una de las claves para tener un buen rendimiento en un disco es manejarlo correctamente. Ejemplo, hay un cabezal que se mueve, y eso lleva tiempo. Queremos minimizar esos movimientos.
* Los pedidos a E/S llegan constantemente, incluso antes de terminar con los que se estén ejecutando.
* La planificación de E/S se trata de cómo manejar la **cola de pedidos** para lograr el mejor rendimiento posible.
    * ancho de banda: máxima cantidad de bytes que se pueden transferir por unidad de tiempo
    * latencia rotacional: tiempo necesario para que el disco rote hasta el sector deseado
    * seek time: tiempo para que la cabeza se ubique sobre el cilindro deseado (!)

### Políticas de scheduling de E/S a disco:
* FIFO / FCFS: First Come, First Served
* SSTF: Shortest Seek Time First (!)
    * El próximo pedido es el más cercano.
    * ¡Puede producir inanición! (!)
    * Además, no es óptimo.
* Scan / Ascensor: Ir en un sentido, y luego en el otro.
    * Puede producir casos patológios (ej: siempre llegan pedidos en la posición inmediata anterior, maximizando el tiempo de espera)
    * El tiempo de espera no es uniforme.
* En la práctica, ninguno de estos se utiliza de forma pura.
* Se usan híbridos.
* Además, hay lecturas y escrituras que son prioritarias sobre otras (bajar páginas de caché, swapping de procesos)

## SSD: Solid State Drive
    Mejores prestaciones, menor precio.

* Ventajas:
    * No tienen componentes mecánicos.
    * Más livianos, resistentes y silenciosos.
    * Menor consumo eléctrico.
    * Mejor performance que los HDD.
* Problemas:
    * La escritura es más compleja que en un HDD.
    * Durabilidad
    * Write Amplification

## Spooling
    Simultaneous Peripheral Operation On-Line
    Manejar acceso dedicado en sistemas multiprogramado

* Caso típico: la impresora.
* El acceso es exclusivo. 
* No queremos que un proceso se bloquee al intentar un acceso sobre un dispositivo que está siendo utilizado.
* Se pone el trabajo en una cola, y se designa un proceso específico que va desencolándolos a medida que se libera el dispositivo.
* Para el Kernel no hay ninguna diferencia, no puede distinguir si se hace spooling o no.
* Para el usuario sí hay una diferencia (!)

## Otros usos: Locking
* POSIX garantiza que open(..., O CREAT | O EXCL) es atómico, y falla si el archivo ya existe
* Esto brinda un mecanismo de exclusión mutua
* Se puede usar para implementar locks a nivel E/S

## Protección de la información
* Hay un tradeoff entre el valor de la información y el costo de protegerla (!)
* Una estrategia muy utilizada es asumir que no se va a romper. ¡Es muy mala!

### Copias de Seguridad (backup)
    Resguardar los datos importantes en otro lado

* Se suelen hacer en cintas.
* También se puede copiar los datos a otro disco (local, por red, etc).
* Como sea, toma tiempo, y por eso se suele hacer durante la noche.
* Copiar todos los datos es costoso.
    * Una vez a la {semana/mes/etc} hacer un **backup total**
    * Realizar períodicamente un **backup incremental**: sólo los archivos modificados desde la última copia incremental (menos espacio / más procesamiento).
    * Otra opción es hacer períodicamente un **backup diferencial**: sólo los archivos modificados desde la última copia total (más espacio / menos procesamiento).
* Restaurar los datos también puede ser costoso.
    * Si sólamente hago copias totales, basta con tomar el backup de ese día.
    * Si hago copias diferenciales, tomo el último backup total, y el backup diferencial de ese día, y los junto.
    * Si hago copias incrementales, tengo que tomar el último backup total, y todos los backups incrementales que hayan habido hasta ese día, y juntarlos. ¡Esto es costoso!

### Redundancia
    Prevenir que el sistema quede fuera de línea

* Método muy común: RAID (Redundant Array of Inexpensive Discs)
* La idea (en general) es usar más de un disco, en donde se replica la información; si alguno se rompe, los otros sirven de resguardo.

#### Métodos:

* Raid 0 / Stripping
    * Por lo general un mismo archivo está distribuido en varios discos
    * La lectura y la escritura se pueden hacer en paralelo
    * Mejora el rendimiento
    * No aporta redundancia

* Raid 1 / Espejo / Mirror: 
    * Los discos son copias idénticas el uno del otro.
    * Mejora el rendimiento de la lectura.
    * Las escrituras están supeditadas en el caso general al disco más lento. Además, en el mejor caso tardan lo mismo, en el peor caso tardan el doble.
    * Es muy caro de implementar, ya que para una misma cantidad de información requiere comprar el doble de discos.

* Raid 0+1:
    * Combina los dos anteriores.
    * Es un raid 0, al que se le hace Espejado.
    * Cada archivo está espejado, pero al leerlo leo un bloque de cada disco.
    * Esto significa que cada raid va a tener toda la información.
    * Es más rápido que mirroring.

* Raid 1+0 / Raid 10:
    * Combina los dos anteriores, pero al revés que Raid 0+1.
    * Es un raid 1, al que se le hace Stripping.
    * Cada bloque está repartido en un raid distinto.
    * Cada raid va a tener una parte de la información.
    * Es la configuración más rápida después de RAID 0.

* Raid 2 y 3:
    * Por cada bloque, se guarda información que permite determinar si hubo un daño o no.
    * Ejemplo: paridad.
    * Los errores se pueden corregir, recomputando el bloque dañado a partir de la información redundante.
    * Cada bloque lógico se reparte entre todos los discos.
    * RAID 2 requiere 3 discos de paridad por cada 4 discos de datos.
    * RAID 3 requiere 1 disco de paridad.
    * Todos los discos participan de todas las operaciones de E/S, por lo que es más lento que RAID 1.
    * Además, requiere un procesamiento adicional para computar la redundancia.
    * Se suele implementar por hardware, con una controladora dedicada.

* Raid 4:
    * Es como RAID 3, pero hace stripping a nivel de bloque (cada bloque en un solo disco).
    * Cada operación de bloque requiere un solo disco, más el disco de paridad, que participa de todas las operaciones.
    * Entonces, el disco de paridad sigue siendo un cuello de botella para el rendimiento.

* Raid 5: 
    * Junto con raid 0, 1 y 0+1 es uno de los más usados en la práctica.
    * También discos usa discos redundantes, pero los distribuye en todos los discos.
    * No hay un sólo disco que tenga toda la redundancia.
    * Para cada bloque, algún disco tiene los datos, y algún otro tiene la paridad.
    * No hay cuello de botella para las escrituras si se mantiene la paridad distribuída.
    * ¡Soporta la pérdida de cualquiera de los discos!
    * Cuando se pierde un disco y se reemplaza, la reconstrucción afecta el rendimiento notablemente.
    * Se suele utilizar con un **HOT SPARE**: esto es un disco de reserva, que si bien no funciona normalmente con el RAID, sirve para reemplaza de forma rápida y automática cuando se daña uno de los discos.

* Raid 6:
    * Como RAID 5, pero con un 2do bloque de paridad.
    * El objetivo es soportar la rotura de hasta 2 discos.
    * Como RAID 5 se suele utilizar con hot spare, no hay una gran diferencia de "espacio desperdiciado".

#### Peligros de RAID

* No protege contra eliminación o modificación **accidental** de archivos
* Tampoco protege contra malware, o eliminación/modificación **intencional** de archivos (!)
* ¡Se combina con copias de seguridad! Una cosa no quita la otra.
* Si una aplicación corrompe datos, ninguno de los enfoques sirve.
* Si se corrompe la estructura de los archivos, o el filesystem, ninguno de los enfoques sirve.
* Los sistemas de archivos brindan su propia capa de protección.