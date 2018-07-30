### ¿Qué es el superbloque en ext2 y que pasa si se pierde su información?

El superbloque es una estructura especial que tiene metadatos críticos del filesystem y cada vez que se realiza un chequeo de consistencia del filesystem se guarda una copia de este al principio de cada block group. Entre otras cosas, contiene información como el tamaño de bloque, la cantidad de bloques que hay en el filesystem, flags (ejemplo, si el filesystem fue desmontado correctamente), cuántas veces fue montado el filesystem, el uuid del filesystem, cantidad de bloques por block group, cantidad de inodos por block group, etc.

Dado que hay una copia del superbloque (y de otros metadatos como los group descriptor) en cada block group, si se pierde la información del superbloque principal, este puede ser restaurado a partir de uno de los backups viejos, y en la mayoría de los casos esto es suficiente para restaurar el filesystem a un estado consistente.

Suponiendo que no se pueda acceder a ninguna de las copias del superbloque, entonces para el humano común y silvestre se puede dar por perdido al filesystem. Sería posible restaurar "la información" a partir de técnicas de recuperación de información de bajo nivel, por ejemplo reconstruyendo el superbloque "a mano" mediante heurísticas, o directamente buscando {archivos / inodos / etc} entre los datos binarios. Pero ya estaríamos hablando de un trabajo super especializado.

### ¿Cuál es la diferencia a nivel de operaciones, de cuando se hace ls y ls -l?

Cuando se hace `ls`, se listan los datos directamente desde el directory entry, mientras que al hacer `ls -l` es necesario leer para cada archivo listado su inodo correspondiente para extraer los metadatos adicicionales (tamaño, permisos, usuarios, fecha de modificación). Es decir, se realizan muchos más accesos a disco que para un ls normal.

### Comparar FAT vs INODOS para la facilidad de hacer un backup total de un disco. Lo mismo para backup incremental.

==TODO:==

### Se quiere implementar una funcionalidad de snapshots. ¿Qué sistema de archivos tomaría como base para hacerle los cambios necesarios (inodos o FAT) y cómo sería la implementación?

==TODO:==