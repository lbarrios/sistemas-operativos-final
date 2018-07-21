# Sistemas de Archivos

## Archivo:
* Secuencia de bytes.
* Sin estructura interna (a priori).
* Se los identifica con un nombre.
* El nombre puede incluir una extensión.
	* archivo.txt: archivo de texto
	* archivo.tex: archivo de LaTeX
	* archivo.c: archivo de código fuente en C

## Filesystems:
	El filesystem es un módulo del kernel.

* Algunos SO soportan sólamente un filesystem (DOS sólo soporta FAT)
* Otros soportan más de uno (Windows soporta FAT, FAT32 y NTFS)
* Otros soportan algunos, pero pueden soportar más mediante **módulos dinámicos** (ej Unix modernos)

## Filesystem populares:
* Locales:
	* FAT / FAT32: popular en DOS y Windows viejos
	* NTFS: popular en Windows basados en NT
	* UFS / Unix file system / FFS / BSD Fast File System: popular en BSD
	* ext2 / ext3 / ext4: los más populares en Linux
	* XFS: 64 bits, alta performance
	* ZFS: es al mismo tiempo un filesystem y un LVM; incluye conceptos como integridad, redundancia (RAID-Z), compresión, snapshots, ACLs, etc.
	* RaiserFS: journaled, el creador mató a la esposa xdxd
	* ISO-9660: el filesystem de los CDROM

* De red:
	* NFS: Network File System, es un protocolo para sistemas de archivo de red
	* SMBFS / CIFS / SAMBA: Server Message Block / Common Internet File System: el protocolo para el filesystem de red de Windows, que también tiene una implementación libre
	* DFS: Distributed File System, protocolo que permite, en líneas generales, agrupar varios filesystem de red (ejemplo varios SMB) en uno solo.
	* AFS / CodaFS / etc: Andrew File System, just another distributed file system...

## Responsabilidades de un Filesystem:

* ### **Organización lógica** de los archivos (visible desde fuera).
	* Organización interna: cómo se estructura la información dentro del archivo. 
		* Ejemplo, en Windows y Unix por lo general se usa secuencia de a bytes. Esto significa que la responsabilidad de organizar el archivo internamente es del usuario.
	* Organización externa: cómo se ordenan y distribuyen los distintos archivos. 
		* Hoy en día la mayoría de los Filesystem adhieren al concepto de directorios, conformando una organización jerárquica, con forma de arbol.
		* Casi todos soportan, además, una noción de link: un alias para un mismo archivo (es decir, el mismo archivo físico aparece como dos archivos lógicos distintos).
		* Con esta última noción, la estructura deja de ser un árbol, y se transforma en un grafo dirigido, introduciendo la posibilidad de que existan ciclos.
* ### Nombre y ruta de los archivos.
	* Caracteres de separación de directorios, ejemplo "/" (Linux) o "\" (Windows).
	* Extensión de los archivos.
	* Restricciones de longitus, y caracteres permitidos (ejemplo acentos).
	* Distinción entre mayúsculas y minúsculas (case sensitive o insensitive).
	* Prefijado o no por el equipo en el que se encuentran.
	* Ejemplos:
		* /usr/local/etc/apache.conf
		* C:\Program Files\Antivirus\Antivirus.exe
		* \\SERVIDOR3\Parciales\parcial1.doc
		* servidor4:/ejercicios/practica3.pdf
* ### Punto de montaje.
	* A partir de qué nombre en la ruta se considera que un dispositivo está montado.
	* En Unix, se realiza mediante el comando mount.
	* Ejemplo: `mount /dev/sda1 /media/disco1` va a montar la primera partición del disco `sda` en la ruta `/media/disco1`. O sea que si existe el archivo `/carpeta/pepito.txt` en este disco, se va a poder acceder mediante la ruta `/media/disco1/carpeta/pepito.txt`.
* ### Representación del archivo (¡Importante!)
	* Esto es la organización lógica interna (no visible desde fuera del filesystem)
	* ¿El archivo está todo junto, o se divide en partes?
* ### Gestión del espacio libre.
* ### Metadatos.

La forma de manejar muchas de estas responsabilidades determinan las características, las ventajas y desventajas, de cada filesystem, principalmente en cuanto a su rendimiento, usabilidad y confiabilidad.

## Representación de archivos
* Un archivo es una lista de bloques + metadatos.

* La forma más sencilla de representarlo es poner todos los bloques juntos en el disco.
	* Las lecturas son muy rápidas...
	* ¡Genera fragmentación externa!
	* Si el archivo crece y no tiene espacio para hacerlo, debe ser relocalizado.
	* Las escrituras, en el caso general, terminan siendo lentísimas.
	* Nadie usa este esquema.

* Otra forma de representar es mediante una lista enlazada de bloques.
	* Las lecturas consecutivas son rápidas.
	* Las lecturas aleatorias son muy lentas.
	* Se desperdicia un espacio constante en cada bloque para indicar cuál es el siguiente.

* ### Solución de DOS, FAT: 
	* Una forma de mejorar esto es mediante una tabla global que me indique, para cada bloque, dónde está el bloque siguiente.
	* No desperdicio espacio interno del bloque.
	* Al tener la tabla en memoria, puedo leer los bloques fuera de orden.
	* Las lecturas aleatorias no son tan lentas.
	* Tengo que tener toda la tabla en memoria, no escala.
	* Hay una única tabla, genera contención (cuello de botella / todo depende de un mismo recurso).
	* Es poco robusto, toda la tabla está en memoria.
	* Además, no maneja permisos/seguridad.

* ### Solución de Unix, Inodos:
	* Cada archivo tiene un inodo.
	* El inodo tiene metadatos / atributos (tamaños, permisos, etc).
	* También tiene las direcciones de algunos bloques de acceso directo, permitiendo acceder rápidamente a archivos pequeños (ejemplo, con bloques de 8KB, se puede acceder hasta 96 KB).
	* Tiene una entrada llamada Single Indirect Block, que apunta a un bloque que contiene punteros a bloques de datos. Siguiendo el ejemplo anterior, esto permite manejar archivos de hasta 16 MB.
	* Tiene otra entrada llamada Double Indirect Block, que apunta a un bloque que contiene punteros a Single Indirect Blocks. Permite manejar archivos de hasta 32 GB.
	* Tiene otra entrada llamada Triple Indirect Block, que apunta a un bloque que contiene punteros a Double Indirect Blocks. Permite manejar archivos de hasta 70 TB.
	* Permite tener en memoria sólamente los inodos correspondientes a archivos abiertos.
	* Genera menos contención.
	* Consistencia/robustez, sólo están en memoria los inodos de los archivos abiertos.

	* #### Inodos: Directorios
		* Un inodo es una entrada al **ROOT DIRECTORY**.
		* Por cada archivo en ese directorio, hay una entrada.
			* En ese bloque se guarda una lista de (inodos, nombre de archivo).

==TODO: REPASAR ESTO==

#### Inodos: Links
==TODO: REPASAR ESTO==

## Atributos / Metadatos
* Permisos (default y ACL)
* Tamaño
* Propietario
* Fechas de creación, modificación acceso
* Tipo de archivo (regular, dispositivo virtual, pipe, socket, etc)
* Flags
* Conteo de referencias
* CRC o similar

## Manejo del espacio libre
* Una posibilidad es utilizar un mapa de bits de bloques, donde 1 significa libre.
* También es posible tener una lista enlazada de bloques libres.
* Por lo general se clusteriza.
==TODO: REPASAR ESTO==