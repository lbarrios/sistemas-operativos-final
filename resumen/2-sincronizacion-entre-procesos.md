# Sincronización entre Procesos
Ver qué pasa cuando se tienen ejecuciones Secuenciales vs Concurrentes. 
¿Da lo mismo la forma en que se ejecutan los procesos?

## Condición de carrera (Race Condition)
> Fenómeno en donde los resultados varían 
> según en qué orden se ejecuten las cosas.

Solución: Garantizar ==Exclusión Mutua==

## Mecanismos de Sincronización

### Test-And-Set
Se lee la variable, y al mismo tiempo se la setea en true. 
Este es un mecanismo provisto por el procesador, de forma 
que resulta ==atómico/indivisible y libre de bloqueos==.

```
private atomic <bool > reg;
atomic bool get () {return reg;}
atomic void set(bool b) {reg = b;}
atomic bool getAndSet (bool b) {
    bool m = reg;
    reg = b;
    return m;
}
atomic bool testAndSet () {
    return getAndSet (true);
}
```

### TAS-Lock (Test-And-Set Lock)
Se utiliza la variable como un lock, y se hace TAS 
mediante ==Busy Waiting== hasta que el valor leído
sea falso (o sea, que se libere el lock).

- no es atómico
- la espera no es acotada


```
public class TASLock {
    private atomic <bool > reg;
    public void create () {
        reg.set(false);
    }
    public void lock () {
        while (reg.testAndSet()) {}
    }
    public void unlock () {
        reg.set(false);
    }
}
```

Soluciones al Busy Waiting:

- Poner un sleep() en el cuerpo del while:
```
void lock (time delay) {
    while (reg.testAndSet()) {sleep(delay);}
}
```

- No iterar sobre TestAndSet() (ver TTAS-Lock)

### TTAS-Lock (Test and Test-And-Set Lock)
El protocolo de Test-And-Set es complejo, y requiere bloquear 
la memoria para escritura. En vez de hacer spin (busy waiting)
sobre la instrucción TAS, se hace sobre la instrucción get(), 
de forma tal que sólamente cuando el get() devuelva falso, se 
intentará hacer el TAS.

```
void lock () {
    do {
        while (reg.get()){} // busy waiting
    } while (!reg.testAndSet());
}
```

Tiene más escalabilidad que TAS-Lock

- ==Caché hit== mientras el get es true
- ==Caché miss== cuando hay un unlock

### Read-Modify-Write Atómicos

==TODO: Completar esta sección==

```
atomic int getAndInc () {
    int tmp = reg;
    reg ++;
    return tmp;
}

atomic int getAndAdd (int v) {
    int tmp = reg;
    reg = reg + v;
    return tmp;
}

atomic T compareAndSwap (T u, T v) { // CAS
    T tmp = reg;
    if (u == tmp) reg = v;
    return tmp;
}
```

### Semáforo

==TODO: Revisar esta sección==
¿Son atómicos? (rta en sistemas distribuidos)

- Una ==variable entera==: capacidad
- Una cola de ==procesos en espera==.
- ==wait()== (P() o down()): Esperar hasta que se pueda entrar.
- ==signal()== (V() o up()): Salir y dejar entrar a alguno.

```
void wait () {
// adquirir lock del kernel
    
    while (!capacidad) { // ocupado ( espera no acotada !!)
        fila.enqueue(self); // encolarse
        towaiting(self); // liberar lock y dormir
        // SIGNALED (recupera lock del kernel)
    }
    capacidad--;

// liberar el lock del kernel
}

void signal () {
// adquirir el lock del kernel
    
    capacidad++; // liberar semáforo
    if (q.dequeue(&p)) {
        toready(p); // despertarlo 
    }

// liberar el lock del kernel
}
```

## Errores de sincronización
==TODO: Revisar esta sección==

- Race condition (condición de carrera)
El resultado no corresponde a ninguna secuencialización.

- Deadlock (bloqueo para siempre):
Uno o más procesos quedan bloqueados para siempre.

- Starvation (innanición):
Un proceso espera un tiempo no acotado para adquirir un lock
porque otro(s) proceso(s) le gana(n) de mano.

- Convoying (demora en cascada):
Un proceso que detiene un lock es sacado de running antes de
liberar el lock.

### Prevención
==TODO: Revisar esta sección==

- Patrones de diseño
- Reglas de programación
- Prioridades
- Protocolos (e.g., Priority Inheritance)


### Detección
==TODO: Revisar esta sección==

- Análisis de programas
	- Análisis estático
	- Análisis dinámico
- En tiempo de ejecución
	- Preventivo (antes que ocurra)
	- Recuperación (deadlock recovery)


# Bibliografía

- Hoare, C. Monitors: an operating system structuring concept, Comm. ACM 17 (10): 549-557, 1974. http://goo.gl/eVaeeo
- M. Herlihy, N. Shavit. The Art of Multiprocessor Programming. Morgan Kaufmann, 2008.
- N. Lynch. Distributed Algorithms. Morgan Kaufmann, 1996.
- Ch. Kloukinas, S. Yovine. A model-based approach for multiple QoS in scheduling: from models to implementation. Autom. Softw. Eng. 18(1): 5-38 (2011). https://goo.gl/5FuU6x
- M. C. Rinard. Analysis of Multithreaded Programs. SAS 2001: 1-19 http://goo.gl/pyfg0G
- L. Sha, R. Rajkumar, J. P. Lehoczky. Priority Inheritance Protocols: An Approach to Real-Time Synchronization. IEEE Transactions on Computers, September 1990, pp. 1175-1185. http://goo.gl/0Qeujs
- Valgrind tool. http://valgrind.org/
- Java Pathfinder (JPF). http://babelfish.arc.nasa.gov/trac/jpf