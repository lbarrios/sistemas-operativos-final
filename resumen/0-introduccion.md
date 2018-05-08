# Introducción

## Hardware Vs Software (SBZ-1.2.1)
División de los sistemas informáticos entre **Hardware < - > Software**. El sistema operativo es el **intermediario** entre ellos:

- **Visión del usuario**: Para que el software no se tenga que preocupar de detalles de bajo nivel. Los distintos contextos de uso van a requerir distintos objetivos a cumplir por el sistema operativo.
	- Computadoras de escritorio de un solo usuario: se prioriza la ==facilidad de uso==, seguido de la performance, pero no se le da prioridad a la utilización de recursos.
	- Workstations que pertenecen a una red: tienen recursos dedicados indivualmente, se intenta buscar un ==equilibrio entre la usabilidad y el acceso a los recursos== locales vs el acceso compartido a los recursos de red.
	- Terminales conectadas a un Mainframe: los usuarios no tienen recursos individuales, por lo que se intenta ==maximizar la utilización de recursos== (uso eficiente de CPU, memoria, IO, etc).
	
- **Visión del fabricante**: Para que el hardware no se vea afectado por un mal uso por parte del software. El sistema operativo cumpliría las siguientes funciones:

	- Administrador de ==recursos== (CPU, memoria, IO).
	- Resolución de ==problemas de contención==.
	- ==Controlador== de dispositivos y programas.

## Historia - Sistemas Batch
- Antes las computadoras costaban millones, y estaban en ambientes dedicados.
- Se utilizaban tarjetas perforadas y lectores/impresoras para ejecutar programas.
- **Problema: mucho tiempo de procesamiento desperdiciado.**

### Operadores
- Se agregaron computadoras intermediarias, que leían las tarjetas y grababan en cintas (+ rápido).
- Nació el rol del "operador", intermediario que debía encargarse de cargar los programas.
- Precursor del sistema operativo.

### Sistemas Operativos
Las siguientes generaciones de computadoras ya tenían un SO formal. Esto solucionaba los problemas de desperdicio de recursos cuando el procesador se encontraba ocioso leyendo las cintas de memoria (mientras tanto, se procesaban otros trabajos).

- **Multiprogramación**.  Correr muchos programas concurrentemente. El rendimiento aumenta, ya que si bien cada trabajo tarda lo mismo individualmente, la ejecución de los trabajos _j1_ + _j2_ tarda menos que si no hubiera sistema operativo.

- **Contención**. Varios programas pueden querer acceder al mismo recurso a la vez.

- **Timesharing**. Conectar muchas terminales a una misma computadora, y darles un poco de tiempo de procesador a cada una.

## El sistema operativo
Un sistema operativo hace de intermediario entre el hardware y los programas del usuario.

Tiene que manejar la contención y la concurrencia de forma de buscar un **balance óptimo entre el rendimiento y la correctitud**.

Al ser el programa más importante, corre con máximos privilegios (nivel 0), entendiendo al sistema operativo como el Kernel (programa más importante).

También, según la definición, se pueden llegar a considerar los ==programas de sistema== (ejemplo, programas de configuración, drivers, etc), e incluso a veces los ==programas de aplicación== (ej, editores, compiladores, etc) como parte integral del Sistema Operativo.

### Organización de la Computadora

#### Distribución básica de una computadora:
```
                                   printer
                          keyboard  /
                         mouse  |  /
                              \ | /
          Disks                \|/                   Monitor
            |                   |                       |
CPU    Disk Controller    USB Controller        Graphics Adapter
 |          |                   |                       |
 --------------------------------------------------------
                      |
                    Memory
```

#### Arranque de una PC (Unix-like) (SBZ-1.2.1)

1. Bootstrap Program: Programa muy pequeño alojado en la ROM (EEPROM/Firmware), que inicializa el sistema (CPU, dispositivos, memoria) y se encarga de buscar y cargar el sistema operativo (Kernel) en memoria.

2. Kernel: Programa que provee servicios a los demás programas (ya sean de sistema o de usuario). 
	- En ocasiones, algunos de estos servicios son provistos por programas por fuera del propio Kernel (ejemplo daemons, servicios de sistema), o por programas que se incrustan como parte del Kernel (ejemplo Drivers).

3. Se carga el primer servicio/proceso de sistema (init), y este se encarga de cargar otros programas (ejemplo daemons).
	- A partir de este punto, el sistema operativo queda en estado de "esperando que sucedan eventos".

4. Cada vez que exista una interrupción o un system call (syscall, monitor call), esto es un evento que el sistema operativo "atiende". 
	- Las interrupciones pueden ser l
	- La forma de atender estas interrupciones es mediante una función global de atención de interrupciones (lento), o mediante una tabla que describa las distintas rutinas de atención de interrupciones (interrupt vector). Existe una cantidad limitada de interrupciones (IRQs), y cada dispositivo se conecta unívocamente a una de ellas.
	- Cuando un sistema operativo atiende una interrupción, el estado actual de la CPU (ejemplo el Instruction Pointer, y en ocasiones los flags, los registros) es guardado (generalmente en la pila), y al terminar la interrupción todo debe ser restaurado a su estado original.

#### Almacenamiento (SBZ-1.2.2)

Los medios de almacenamiento se pueden organizar en una jerarquía:
```
Registros
Cache
RAM
Discos SSD
Discos magnéticos
Discos ópticos
Cintas magnéticas
```

En donde normalmente se cumple que los elementos que se encuentran más arriba, tienen mayor velocidad, pero son más caros y tienen menor capacidad.

##### Memoria principal

La CPU sólo puede correr instrucciones o cargar datos desde la ==memoria principal (RAM)==, así que cualquier programa que se desee correr debe ser previamente cargado allí.

Cualquier tipo de memoria puede ser pensado como un **array de bytes**, en donde **cada byte tiene su propia dirección**, y toda interacción puede ser vista como una **secuencia de LOAD y STORE**.

Idealmente, todos los programas deberían estar almacenados en memoria principal de forma permanente. Esto no es posible porque esta es relativamente pequeña, y por otro lado es volátil, por lo que al apagar el equipo toda la información contenida en la misma se pierde.

##### Memoria Secundaria

La memoria secundaria funciona como una extensión de la memoria principal, que es capaz de almacenar grandes cantidades de datos, y de retenerlos cuando esta se encuentra apagada.

Tipos de memoria secundaria:

- Discos rígidos (magnéticos, ssd, híbridos)
- Discos ópticos (CD-ROM, Blue-Ray)
- Memorias flash (pendrives, memorias SD)
- Otros (diskettes, cintas magnéticas)

Se diferencian según distintas características: capacidad, tamaño físico, precio, confiabilidad, durabilidad, velocidad, etc. Generalmente, siempre hay un tradeoff (mejorar una de las características tienen un impacto en alguna de las otras, por ejemplo, si aumentamos la capacidad aumenta el precio y/o el tamaño, si aumentamos la capacidad manteniendo el precio y el tamaño, disminuye la velocidad, o la confiabilidad, etc).

##### Estructura de IO
El almacenamiento se puede ver como uno de los tantos dispositivos de IO del sistema.

Cada tipo de almacenamiento está ligado a un controlador de dispositivo (ejemplo, los discos IDE están conectados a un controlador IDE, y los discos SCSI están conectados a un controlador SCSI). El controlador de dispositivo es un chip o placa independiente del procesador, y se encarga de hacer de intermediario entre los dispositivos y el procesador. Así, el controlador de dispositivo provee el acceso a los dispositivos que controla, mediante una interfaz única, que evita que el procesador tenga que encargarse de detalles de Hardware específicos de cada fabricante (ejemplo: mover los platillos de un disco).

Los Sistemas Operativos tienen un driver específico para cada tipo de controlador de dispositivo, que a su vez se encargan de hacer de intermediario entre el controlador y los programas (de usuario o de sistema) que hagan uso de estos dispositivos. Así, se provee de una interfaz uniforme para el acceso a cada tipo de controlador de dispositivo.

Normalmente, existen dos formas de acceder a los dispositivos. La primera, es seteando determinados parámetros (ejemplo desde donde se desea leer) en el controlador de dispositivos, y esperando que este a su vez se encargue de realizar la lectura correspondiente en el dispositivo, y luego devolver el resultado al procesador; esto es muy lento, y sólamente sirve para transferir pequeñas cantidades de datos. La segunda forma es mediante DMA, en donde después de que el procesador le setea los parámetros correspondientes, el controlador de dispositivos se encarga de realizar la transferencia de datos directo desde el dispositivo hasta la memoria principal, sin la intervención del procesador; esto obviamente hace que el procesador pueda realizar otras tareas mientras se espera la transferencia. En ambos casos, el final de la transferencia se suele informar mediante una interrupción.

### Arquitectura de la Computadora

#### Sistemas Monoprocesador

#### Sistemas Multiprocesador

#### Sistemas Cluster

### Estructura del Sistema Operativo

### Operaciones del Sistema Operativo

### Administración de Procesos

### Administración de Memoria

### Administración de Almacenamiento

### Seguridad

### Estructura de datos de un Kernel

# Estructuras del Sistema Operativo
