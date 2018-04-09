# Final de Sistemas Operativos
Repositorio para estudiar para el final de Sistemas Operativos

# Programa

## Introducción
### Qué es un SO
### Introducción histórica
### Elementos básicos de un SO
### Manejo básico de un shell Unix

## Procesos y API
### Procesos
### Estados de un proceso
### Introducción al scheduler
### E/S bloqueante / no bloqueante
### IPC

## Scheduling
### Objetivos de la política de scheduling
### Scheduling con y sin desalojo
### Políticas de scheduling
### Scheduling para tiempo real y para SMP

## Sincronización entre procesos 1
### Contención
### Condiciones de carrera
### Secciones críticas
### TestAndSet
### Busy waiting / sleep
### Productor - Consumidor
### Semáforos
### Introducción a deadlock
### Monitores
### Variables de condición

## Administración de memoria
### Segmentación
### Paginación
### Swapping
### MMU
### Memoria virtual
### Copy-on-write
### Algoritmos de reemplazo de páginas

## Administración de entrada/salida
### Polling, interrupciones, DMA
### Almacenamiento secundario
### Drivers
### Políticas de scheduling de E/S a disco
### Gestión del disco (formateo, booteo, bloques dañados)
### RAID
### Copias de seguridad
### Spooling
### Clocks

## Protección y seguridad
### Conceptos de protección y seguridad
### Matrices de permisos
### MAC vs. DAC
### Autenticación, autorización y auditoría
### Funciones de hash de una vía
### Encriptación simétrica
### RSA
### Privilegios de procesos
### Buffer overflows
### Inyección de parámetros
### Condiciones de carrera
### Sandboxes
### Principios generales de seguridad

## Sistemas de archivos
### Responsabilidades del FS
### Punto de montaje
### Representación de archivos
### Manejo del espacio libre
### FAT, inodos
### Atributos
### Directorios
### Caché
### Consistencia, journaling
### Características avanzadas
### NFS, VFS

## Sistemas distribuidos
### Taxonomía de Flynn
### Arquitecturas de HW y SW para sistemas distribuidos
### RPC
### Threads
### Pasaje de mensajes
### Orden parcial entre eventos
### Livelock
### Acuerdo bizantino
### Intuición de safety, liveness, fairness
### Algoritmo del banquero
### Panadería de Lamport
### Modelos de fallas y métricas de complejidad
### Exclusión mutua y locks distribuidos
### Elección de líder
### Instantánea global consistente
### 2PC

## Programación concurrente
### Algoritmos wait-free
### Algoritmos lock-free
### CAS
### ABA
### Programación de multicores
### Invalidación de caché
### Reorden de instrucciones

## Conceptos avanzados
### Microkernels
### Virtualización
