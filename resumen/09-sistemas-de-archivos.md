# Sistemas de Archivos

## Archivo:
* Secuencia de bytes.
* Sin estructura interna (a priori).
* Se los identifica con un nombre.
* El nombre puede incluir una extensión.
    * archivo.txt: archivo de texto
    * archivo.tex: archivo de LaTeX
    * archivo.c: archivo de código fuente en C

### Atributos de un Archivo:
* Nombre: ejemplo "archivo.txt"
* Identificador: identificador único de archivo, interno al sistema operativo
* Tipo: si pueden haber distintos tipos de archivo (ejemplo archivo o carpeta), es necesario identificarlos
* Ubicación: dónde está guardado el archivo (dispositivo) y en qué ruta.
* Tamaño: el tamaño del archivo
* Proteción: ACL, usuarios, permisos (lectura, escritura, ejecución), etc
* Fechas: creación, modificación, acceso, etc
* Atributos extendidos: checksum, encoding (ej: TF8), etc
* Toda esta información se almacena en el **Directory Structure** del FileSystem.

### Operaciones de un Archivo:
    El archivo se puede ver como un tipo abstracto de datos.
    En ese sentido, es definido a través de sus operaciones.

Ejemplos:
* create: crear el archivo
* read: leer de un archivo
* write: escribir en un archivo
* seek: moverse a través de un archivo
* delete: eliminar un archivo
* truncate: truncar un archivo (eliminar a partir de una posición)
* append: escribir en un archivo a partir del final
* rename: renombrar un archivo
* copy: copiar un archivo
* lock: bloquear un archivo (para que otros no lo usen)

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

==TODO: PROFUNDIZAR ESTO CON BIBLIOGRAFIA==

#### Inodos: Links
==TODO: PROFUNDIZAR ESTO CON BIBLIOGRAFIA==

## Atributos / Metadatos de un filesystem
    Por lo general son los atributos de los archivos
    y además atributos particulares que pueda tener el FileSystem

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
    * Calcular el espacio libre cuesta O(N), donde N es la cantidad de bloques.
    * Pero al ser mapa de bits, se puede comparar un registro entero (32 o 64 bits), y si es cero, se lo saltea
    * Esto hace que se puedan ahorrar comparaciones, pero no deja de ser una optimización.
* También es posible tener una lista enlazada de bloques libres.
* Por lo general se clusteriza.
    * La idea de esto es tener una lista de nodos que adentro tengan varios punteros a bloques.
    * ==TODO: PROFUNDIZAR ESTO CON BIBLIOGRAFIA==

## Caché
    Se copia cierta información que está en disco, a memoria principal.

* Mejora el rendimiento
* En la práctica, se utiliza junto con el mecanismo de paginación (cada página en sí es una caché).
* Puede grabar las páginas de manera ordenada, ayudando a la planificación de escritura de IO.
    * Las aplicaciones pueden requerir la _escritura sincrónica_, es decir, grabar los cambios de forma inmediata. Obviamente, esto es más lento.

## Consistencia
    Es importante asegurar la coherencia/consistencia en las operaciones del disco
    ante un evento inesperado (ejemplo: corte de luz), el filesystem puede quedar
    en un estado inconsistente (operaciones fuera de orden, inodos a medio escribir, ...).

* Si se quiere desmontar un filesystem, primero se deben aplicar todas las operaciones pendientes (en caché).
    * Para ello, el Sistema Operativo provee `fsync`, que se encarga de grabar todas las páginas sucias de la caché.
    * Para saber si una página de caché está sucia, basta con ver el bit correspondiente `dirty`.
* En ext existe un bit de consistencia, que se marca cuando se monta el filesystem, y se desmarca cuando el mismo es desmontado correctamente (ejemplo, ante un apagado normal de la PC).
* Cuando existe algún evento que produce un desmontaje imprevisto del filesystem (ej un corte de luz), este bit queda marcado.
* Cada vez que se quiere montar el FS, se chequea previamente que el mismo esté en un estado coherente, mirando el bit en cuestión.
* En caso contrario, no se lo monta sin antes realizar un chequeo y restauración de consistencia en el mismo.
    * En Unix, esto se hace mediante el programa **fsck**.
    * Este programa recorre todo el disco, verifica consistencia (ej CRC) de cada inodo, y por cada bloque de datos cuenta cuántos inodos le apuntan, y también se fija si el mismo aparece referenciado como un bloque libre.
    * Hacer todo esto puede llegar a ser muy lento.
* Otra opción es hacer **Soft Updates**.
    * Permite iniciar el Sistema Operativo de forma mucho más rápida.
    * Mantiene un registro de operaciones/dependencias.
    * Este es flusheado períodicamente a disco.
    * Cuando se detecta un filesystem inconsistente, se busca la última secuencia de operaciones válidas en este registro. Esto es, aquellas operaciones que no tengan dependencias sin flushear.
    * Cualquier otra operación que haya sido flusheada, pero cuyas dependencias no se cumplan, es revertida.
    * Luego, ya se puede montar el filesystem e iniciar el sistema.
    * Resta chequear el listado de bloques libres, para verificar que no haya quedado ningún bloque marcado como ocupado, y que en realidad esté libre. Pero esto se puede hacer con el sistema andando.

## Características Avanzadas
### Cuotas de disco
    Limitar cuánto espacio puede utilizar cada usuario

* Puede llegar a ser difícil de implementar.
* Soft Quota: Se avisa al usuario que está sobrepasando el límite, pero se le permite seguir violándolo.
* Hard Quota: Se le bloquea todo tipo de escritura al usuario.

### Encriptación
* ¿Cómo y dónde guardar la clave?
    * Ejemplo: Clustered File System: ¿la clave se distribuye por los nodos?
* ¿Cómo desencriptar la clave? ¿Si pierdo la clave, pierdo todo el filesystem?
* Esto agrega un overhead de procesamiento.
    * **Más lento (!)**

### Snapshots
* Son fotos del estado del disco en un determinado momento.
* Se realizan instantáneamente (o casi).
* El sistema operativo, luego, va a duplicar sólamente los archivos que sean modificados.
* Es muy útil para hacer backups.

### Raid por Software
* Mayor control.
* Independencia del proveedor.
* Agrega un overhead de procesamiento
    * **Más lento (!)**
* Se agregan nuevas posibilidades y/o niveles de redundancia (ej: ZFS)

### Compresión
* Los datos se guardan comprimidos.
* El driver del FS actúa como capa intermedia entre el dato físico comprimido, y el dato que se lee (descomprimido).
* Esto agrega un overhead de procesamiento.
    * **Más lento (!)**

## Performance de un filesystem

El rendimiento de un FS se ve afectado por muchos factores.

* Tecnología de disco (hdd vs sdd, velocidad de lectura secuencial/aleatoria, velocidad de escritura, etc).
* Política de scheduling de IO.
* Tamaños de bloque.
* Cachés del SO (ej de IO).
* Cachés de las controladora (ej de SATA).
* Cachés de los propios discos.
* Sincronización / manejo de locks en IO.
* Journaling vs. softupdates.
    * ==TODO: PROFUNDIZAR ESTO CON BIBLIOGRAFIA==
* Tradeoffs: hay cosas por las que vale la pena sacrificar performance
    * Seguridad
    * Estabilidad
    * Robustez
    * Mantenibilidad

## NFS: Network File System
* Permite acceder a un FS remoto, como si fuera local.
    * Utiliza RPC.
    * Esto se hace de forma transparente.
    * El NFS se monta en un mountpoint, como cualquier otro FS, y las aplicaciones no saben que es remoto.
* Para funcionar, requiere de una capa adicional del SO, llamada VFS (Virtual File System).
    * Esta capa tiene _vnodes_ por cada archivo abierto.
    * Cada vnode se corresponde con un inode si el archivo es local.
    * Si el archivo es remoto, se almacenan metadatos adicionales.
    * De este modo, los pedidos que llegan al VFS son despachados al FS real, o al NFS.
    * Cada FS a su vez se encarga de los detalles implementativos del pedido (ej, NFS maneja el protocolo de red necesario para enviar el RPC)
* Es similar a otros sistemas distribuidos.
* NFS no es 100% distribuído.
    * Todos los datos de un mountpoint deben pertenecer al mismo "medio físico".
    * AFS o Coda son realmente distribuídos.

## EXT2
==TODO: PROFUNDIZAR ESTO CON BIBLIOGRAFIA==