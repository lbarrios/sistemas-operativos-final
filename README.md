# Final de Sistemas Operativos
Repositorio para estudiar para el final de Sistemas Operativos

# Programa

## Introducción
* Qué es un SO
* Introducción histórica
* Elementos básicos de un SO
* Manejo básico de un shell Unix

## Procesos y API
* Procesos
* Estados de un proceso
* Introducción al scheduler
* E/S bloqueante / no bloqueante
* IPC

## Scheduling
* Objetivos de la política de scheduling
* Scheduling con y sin desalojo
* Políticas de scheduling
* Scheduling para tiempo real y para SMP

## Sincronización entre procesos 1
* Contención
* Condiciones de carrera
* Secciones críticas
* TestAndSet
* Busy waiting / sleep
* Productor - Consumidor
* Semáforos
* Introducción a deadlock
* Monitores
* Variables de condición

## Administración de memoria
* Segmentación
* Paginación
* Swapping
* MMU
* Memoria virtual
* Copy-on-write
* Algoritmos de reemplazo de páginas

## Administración de entrada/salida
* Polling, interrupciones, DMA
* Almacenamiento secundario
* Drivers
* Políticas de scheduling de E/S a disco
* Gestión del disco (formateo, booteo, bloques dañados)
* RAID
* Copias de seguridad
* Spooling
* Clocks

## Protección y seguridad
* Conceptos de protección y seguridad
* Matrices de permisos
* MAC vs. DAC
* Autenticación, autorización y auditoría
* Funciones de hash de una vía
* Encriptación simétrica
* RSA
* Privilegios de procesos
* Buffer overflows
* Inyección de parámetros
* Condiciones de carrera
* Sandboxes
* Principios generales de seguridad

## Sistemas de archivos
* Responsabilidades del FS
* Punto de montaje
* Representación de archivos
* Manejo del espacio libre
* FAT, inodos
* Atributos
* Directorios
* Caché
* Consistencia, journaling
* Características avanzadas
* NFS, VFS

## Sistemas distribuidos
* Taxonomía de Flynn
* Arquitecturas de HW y SW para sistemas distribuidos
* RPC
* Threads
* Pasaje de mensajes
* Orden parcial entre eventos
* Livelock
* Acuerdo bizantino
* Intuición de safety, liveness, fairness
* Algoritmo del banquero
* Panadería de Lamport
* Modelos de fallas y métricas de complejidad
* Exclusión mutua y locks distribuidos
* Elección de líder
* Instantánea global consistente
* 2PC

## Programación concurrente
* Algoritmos wait-free
* Algoritmos lock-free
* CAS
* ABA
* Programación de multicores
* Invalidación de caché
* Reorden de instrucciones

## Conceptos avanzados
* Microkernels
* Virtualización

# Bibliografía


## General
* Modern Operating Systems, Andrew S. Tanenbaum.
* Operating Systems Concepts, Abraham Silberschatz & Peter B. Galvin.

## Concurrencia
* Multithreaded Programming With PThreads, Bil Lewis, Daniel J. Berg, Sun Microsystems Press.

## Shell
* Unix Programming Environment, Brian W. Kernighan, Rob Pike, Prentice-Hall Software Series.

## Algunos links
* http://www-03.ibm.com/ibm/history/exhibits/mainframe/mainframe_PP7090.html
* http://www.bell-labs.com/history/unix/

## Opcionales:
* UNIX Network Programming Volume 1, Second edition, W. Richard Stevens, Prentice Hall, 1998.

## Intro histórica
* Ritchie, Dennis M. The Evolution of the Unix Time-sharing System. AT&T Bell Laboratories Technical Journal 63, no. 6, Part 2 (October 1984): 1577-93.

## Semáforos
* Downwy, A. The little book of semaphores. http://www.greenteapress.com/semaphores/.

## FS avanzados
* Ganger, Gregory R., M. Kirk McKusick, Craig A. N. Soules, and Yale N. Patt. Soft Updates: A Solution to the Metadata Update Problem in File Systems. ACM Transactions on Computer Systems 18, 2 (May 2000): 127-153.

## Microkernels
* Liedtke, Jochen. Improving IPC by Kernel Design. 14th ACM Symposium on Operating System Principles (SOSP). Asheville, North Carolina: 5-8 December 1993.

## Máquinas virtuales
* Bugnion, Edouard, Scott Devine, and Mendel Rosenblum. Disco: Running Commodity Operating Systems on Scalable Multiprocessors. In Proceedings of the Sixteenth ACM Symposium on Operating Systems Principles. Saint-Malo, France: October 1997.

## Sincronización
* The Art of Multiprocessor Programming. Maurice Herlihy and Nir Shavit. Morgan Kaufmann Publishers Inc., San Francisco, CA, USA. 2008.

## Sistemas distribuidos
* Distributed Algorithms. Nancy A. Lynch. Morgan Kaufmann Publishers Inc., San Francisco, CA, USA. 1996.


# Bibliografía

* https://warwick.ac.uk/fac/sci/physics/research/condensedmatt/imr_cdt/students/david_goodwin/teaching/operating_systems/
