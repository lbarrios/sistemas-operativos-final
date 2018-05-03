# Sincronización entre Procesos
Ver qué pasa cuando se tienen ejecuciones Secuenciales vs Concurrentes. 

¿Da lo mismo la forma en que se ejecutan los procesos?

- ==contención==: dos procesos quieren acceder al mismo recurso
- ==concurrencia==: dos procesos se ejecutan de forma simultánea

## Condición de carrera (Race Condition)
> Fenómeno en donde los resultados varían 
> según en qué orden se ejecuten las cosas.

Solución: Garantizar ==Exclusión Mutua== 
mediante ==secciones críticas== (CRIT).

## Mecanismos de Sincronización

### Sección Crítica
Es un pedazo de código tal que se cumple

- sólo hay un proceso en CRIT
- todo proceso esperando para CRIT va a entrar
- ningún proceso fuera de CRIT puede bloquear a otro

Un proceso puede:

- entrar a la sección crítica
- salir de la sección crítica

Generalmente, se resuelve mediante locks 
(booleanos indicando si la sección está bloqueada) 
y es necesario utilizar hardware adicional.

### Test-And-Set
> Se lee la variable, y al mismo tiempo se la setea en true. 
> Este es un mecanismo provisto por el procesador, de forma 
> que resulta ==atómico/indivisible y libre de bloqueos==.

```
private atomic <bool> reg;
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

### TAS-Lock (Test-And-Set Lock) (spin lock)
> Se utiliza la variable como un lock, y se hace TAS 
> mediante ==Busy Waiting== hasta que el valor leído
> sea falso (o sea, que se libere el lock).

- **no es atómico**
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

#### Problema: Busy Waiting
> El código se la pasa intentando obtener 
> el lock de una ==forma agresiva==.

- consume muchísima CPU
- **perjudica al resto de los procesos**
- ==Su overhead, sin embargo, puede ser menor
que el de usar semáforos.==

#### Soluciones al Busy Waiting

- Poner un sleep() en el cuerpo del while
	- poco tiempo -> desperdicia CPU
	- mucho tiempo -> mucha espera
```
void lock (time delay) {
    while (reg.testAndSet()) {sleep(delay);}
}
```

- No iterar sobre TestAndSet(), es decir, testear 
antes de intentar el lock (ver TTAS-Lock)

### TTAS-Lock (Test and Test-And-Set Lock) (local spinning)
> El protocolo de Test-And-Set es complejo, y requiere bloquear 
> la memoria para escritura. En vez de hacer spin (busy waiting)
> sobre la instrucción TAS, se hace sobre la instrucción get(), 
> de forma tal que sólamente cuando el get() devuelva falso, se 
> intentará hacer el TAS.

```
void create() {
    mutex.set(false);
}

void lock () {
    do {
        while (mutex.get()){
            // busy waiting
        }
    } while (!mutex.testAndSet());
}

void unlock() {
    mutex.set(false);
}
```

==Tiene más eficiencia/escalabilidad que TAS-Lock==

- El while hace get() en lugar de testAndSet()
- ==Caché hit== mientras el get es true
- ==Caché miss== cuando hay un unlock

### Otros objetos atómicos
> Read-Modify-Write Atómicos

```
/**
 * Obtiene un valor y lo incrementa en 1
 * (devuelve el valor original)
 */
atomic int getAndInc () {
    int tmp = reg;
    reg ++;
    return tmp;
}

/**
 * Obtiene un valor y le suma un entero
 * (devuelve el valor original)
 */
atomic int getAndAdd (int v) {
    int tmp = reg;
    reg = reg + v;
    return tmp;
}

/**
 * Compara contra el primer parámetro, si es igual
 * lo cambia por el segundo parámetro.
 * (devuelve el valor original)
 */
atomic T compareAndSwap (T u, T v) { // CAS
    T tmp = reg;
    if (u == tmp) reg = v;
    return tmp;
}

atomic enqueue(T item) {
    mutex.lock();
    queue.push(item);
    mutex.unlock();
}

atomic bool dequeue(T *pitem) {
    bool success;
    mutex.lock();
    if (queue.empty) {
        pitem = null;
        success = false;
    } else {
        pitem = queue.pop();
        success = true;
    }
    mutex.unlock();
    return success;
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

### Mutex
> MUTual EXclusion

Se puede ver como un semáforo que sólamente toma
los valores 0 o 1.

## Modelo Coffmann (para detectar Deadlock)
> Serie de condiciones necesarias
> para la existencia de un deadlock

- Exclusión Mutua: existe un recurso que no puede 
ser asignado a más de un proceso
- Hold and Wait: los procesos pueden retener un recurso 
y solicitar otro
- No preemption: no hay un mecanismo compulsivo para
quitarle los recursos a un proceso
- Espera circular: Tiene que haber un ciclo de N>=2
procesos, tal que P_i espera un recurso de P_i+1

## Modelo de Grafos Bipartitos (para detectar Deadlock)
> Hay deadlock cuando hay un ciclo

- Procesos: nodos P
- Recursos: nodos R
- Aristas: 
	- **P->R** si P ==solicita== R
	- **R->P** si P ==adquirió== R

```
Ejemplo de deadlock

     P1
   /   <
  <     \
R2       R1
  \     >
   >   /
     P2
```

## Problemas de sincronización

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


## Modelo teórico

```
R ->try-> T ->crit-> C ->exit-> E
 ^                             /
  \___________________________/

```

- Estado: σ : [0 ... N−1] → {R,T, C, E}
- Transición: σ → σ', l ∈ {rem, try, crit, exit}
- Ejecución: τ = τ_0 → τ_1 ...
- Garantizar PROP: ==Toda ejecución satisface PROP==
- Notación: #S = cantidad de elementos del conjunto S

### Propiedades

#### Exclusión Mutua (EXCL)
> Para toda ejecución T y estado T_k, no puede 
> haber más de un proceso i tal que T_k(i) = C.

- #CRIT ≤ 1

#### Progreso (PROG)
> Para toda ejecución τ y estado τ_k, 
> si en τ_k hay un proceso i en T y ningún i' en C, 
> entonces ∃j > k tal que en el estado τj 
> algún proceso i' está en C.

- (#TRY ≥ 1 ∧ #CRIT = 0 =⇒ ♦#CRIT > 0)

#### Progreso global absoluto (WAIT-FREE)
> Para toda ejecución τ, estado τ_k y proceso i,
> si τ_k (i) = T
> entonces ∃j > k, tal que τ_j(i) = C

- ∀i. IN(i)
- IN(i): TRY (i) ⇒ ♦ CRIT(i)

#### Progreso global dependiente (G-PROG)
(deadlock-, lockout-, o starvation-free)
> Para toda ejecución τ,
> si para todo estado τ_k y proceso i tal que τ_k(i) = C,
> ∃j > k, tal que τ_j(i) = R
> entonces para todo estado τ_k' y todo proceso i',
> si τ_k'(i') = T
> entonces ∃j' > k' tal que τ_j'(i) = C.

- ∀i. OUT(i) ⇒ ∀i. IN(i)
- OUT(i): CRIT(i) ⇒ ♦ REM(i)

#### Justicia (FAIR) (fairness)
> Para toda ejecución τ y todo proceso i,
> si i puede hacer una transición L_i en una cantidad
> infinita de estados de τ
> entonces existe un k tal que τ_k →(L_i)→ τ_{k+1}.

#### Observaciones

- EXCL es una propiedad de safety: nada malo pueda pasar nunca.
- PROG, G-PROG y WAIT-FREE son propiedades de liveness: algo bueno debe pasar en el futuro.
- FAIR se asume: debe ser garantizada por el scheduler
- No hacer nada garantiza safety.
- Siempre hay que tener ambas propiedades.

## Bibliografía

- Hoare, C. Monitors: an operating system structuring concept, Comm. ACM 17 (10): 549-557, 1974. http://goo.gl/eVaeeo
- M. Herlihy, N. Shavit. The Art of Multiprocessor Programming. Morgan Kaufmann, 2008.
- N. Lynch. Distributed Algorithms. Morgan Kaufmann, 1996.
- Ch. Kloukinas, S. Yovine. A model-based approach for multiple QoS in scheduling: from models to implementation. Autom. Softw. Eng. 18(1): 5-38 (2011). https://goo.gl/5FuU6x
- M. C. Rinard. Analysis of Multithreaded Programs. SAS 2001: 1-19 http://goo.gl/pyfg0G
- L. Sha, R. Rajkumar, J. P. Lehoczky. Priority Inheritance Protocols: An Approach to Real-Time Synchronization. IEEE Transactions on Computers, September 1990, pp. 1175-1185. http://goo.gl/0Qeujs
- Valgrind tool. http://valgrind.org/
- Java Pathfinder (JPF). http://babelfish.arc.nasa.gov/trac/jpf