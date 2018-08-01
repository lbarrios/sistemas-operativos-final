# Sincronización

* El problema de sincronización de procesos surge a partir del punto en que se los quiere ejecutar de forma concurrente.
    * Los procesos pueden ser interrumpidos, dejando ejecuciones parciales.
    * El acceso concurrente a los datos puede ocasionar inconsistencias.

## Contención

* El problema es cuando los procesos comparten recursos, y acceden a los mismos de forma concurrente.

## Race Condition / Condición de carrera

* El resultado de una ejecución concurrente varía según el orden en que se ejecutan las operaciones concurrentes.
* Dicho de otro modo, es cuando una ejecución concurrente se corresponde a más de una serialización, y estas producen distintos resultados.

### Ejemplo de Race Condition:
```
Proceso 1: 
    (1)     temp1 <- lee(A)
    (2)     temp1 <- temp1 + 1
    (3)     escribe(A) <- temp1

Proceso 2:
    (4)     temp2 <- lee(A)
    (5)     temp2 <- temp2 + 1
    (6)     escribe(A) <- temp2
```

Se establece el siguiente orden relativo entre las operaciones (dependencias):
* (1) -> (2) -> (3): 2 se ejecuta luego de 1, y 3 se ejecuta luego de 2
* (4) -> (5) -> (6): 5 se ejecuta luego de 4, y 6 se ejecuta luego de 5

```python
Serialización 1:
    (0)     (Pre: A = 0)

    (1)     temp1 <- lee(A)         # temp1 = 0
    (2)     temp1 <- temp1 + 1      # temp1 = 1
    (3)     escribe(A) <- temp1     # A     = 1
    (4)     temp2 <- lee(A)         # temp2 = 1
    (5)     temp2 <- temp2 + 1      # temp2 = 2
    (6)     escribe(A) <- temp2     # A     = 2

    (7)     (Post: A = 2)

Serialización 2:
    (0)     (Pre: A = 0)

    (1)     temp1 <- lee(A)         # temp1 = 0
    (4)     temp2 <- lee(A)         # temp2 = 0
    (5)     temp2 <- temp2 + 1      # temp2 = 1
    (2)     temp1 <- temp1 + 1      # temp1 = 1
    (6)     escribe(A) <- temp2     # A = 1
    (3)     escribe(A) <- temp1     # A = 1

    (7)     (Post: A = 1)
```

* Ambas serializaciones son correctas, puesto que respetan las dependencias mencionadas previamente.
* Sin embargo, ¡ambas producen distintos resultados!

## Critical Section / Sección Crítica

* En el caso anterior, el acceso a A debería ser protegido.
    * Proceso 2 no debería poder utilizar A mientras Proceso 1 lo esté utilizando.
    * Proceso 1 no debería poder utilizar A mientras Proceso 2 lo esté utilizando.
* La solución a esto, es establecer una sección crítica.
* Una sección crítica es un bloque de código en donde el acceso a un recurso compartido está protegido, de forma tal que sólamente un proceso puede entrar en esta sección a la vez.
* Normalmente una sección crítica se divide en tres partes:
    * **Entry Section / Entrada**: Donde el proceso solicita permiso para acceder a un recurso. Mientras no se le otorgue este permiso, el proceso va a permanecer en esta sección.
    * **Critical Section**: Es el código que utiliza el recurso compartido.
    * **Exit Section / Salida**: Donde el proceso entrega el permiso de acceso a ese recurso. De este modo, cualquier otro proceso que esté esperando para entrar a la sección crítica, puede hacerlo.
* Se considera también una **Remainder Section** como aquella sección del proceso que se encuentra totalmente por fuera de la sección crítica.
* Es importante que la sección crítica sea lo más pequeña posible.

### Resolución de Sección Crítica

Se requieren satisfacer tres condiciones:

1. Exclusión mútua: Si el proceso Pi está ejecutando en su sección crítica, entonces ningún otro proceso puede ejecutar en la sección crítica correspondiente.
2. Progreso: Si ningún proceso está en su sección crítica, y existe algún proceso que desea entrar, se le debe garantizar su entrada a uno de ellos.
3. Espera Acotada: Ningún proceso debería esperar indefinidamente para entrar a su sección crítica, es decir, una vez que se encuentra encolado, su tiempo de espera se debería considerar acotado (sin deadlock, sin starvation).

## Algoritmo de Peterson
    El algoritmo de Peterson resuelve exclusión mútua para dos procesos.

```c++
do {
    //////////////////////////////////////
    // Entry Section
    flag[i] = true;
    turn = j; 
    while (flag[j] && turn == j); 
    //////////////////////////////////////

    //////////////////////////////////////
    // Critical Section
    // ...
    //////////////////////////////////////

    //////////////////////////////////////
    // Exit Section
    flag[i] = false; 
    //////////////////////////////////////

    //////////////////////////////////////
    // Remainder Section
    // ...
    //////////////////////////////////////
} while (true); 
```

* flag[i] indica si el proceso "i" está interesado en entrar a la sección crítica.
* turn indica de quién es el turno de entrar en la sección crítica.

### Peterson - idea
* Si un sólo proceso está interesado en entrar en la sección crítica, entonces entra.
    * Si mientras un proceso está en su sección crítica el otro proceso quiere entrar en la sección crítica, va a marcar su flag de interés en true. 
    * Como el flag de interés del otro proceso va a estar en true, va a evaluar de quién es el turno.
    * Como cada proceso le cede el turno al otro, va a tener que esperar a que el otro termine.
* Una vez que el proceso que estaba en la sección crítica termina, pone su flag de interés en falso.
    * Si el otro proceso quería entrar a la sección crítica, lo va a poder hacer ahora.
* Si ambos procesos quieren entrar a la sección crítica "a la vez", alguno de ellos va a ganar (el primero que setee la variable turn, termina ganando acceso a la sección crítica).

### Peterson - correctitud
* Se preserva exclusión mútua porque los dos procesos no pueden estar a la vez en la sección crítica.
* Se preserva progreso, porque si ambos quieren entrar a la vez (o si uno solo quiere entrar), va a terminar entrando.
* Se preserva espera acotada, porque si un proceso quiere entrar a la sección crítica, a lo sumo va a tener que esperar un turno (si entra el otro), y apenas termine el otro va a poder entrar.
    * Esto sucede incluso aunque el otro pueda hacer todo el loop y volver a entrar a la zona de entrada de sección crítica, ya que cada proceso le cede el turno al otro.

### Peterson - Desventajas
* Está limitado a dos procesos.
* Realiza busy waiting.

## Primitivas de Hardware
* Muchos sistemas de hardware proveen soluciones para implementar una solución al problema de la sección crítica.
* Normalmente se basan en locks.
* Sistemas mononúcleo, pueden simplemente deshabilitar interrupciones.
    * El código va a correr sin desalojo (preemption), ¡esto es un peligro!
    * No es eficiente, y no es sencillo de hacer en multinúcleo.
* Sistemas modernos, proveen instrucciones de hardware especiales
    * Instrucciones atómicas: **no pueden ser interrumpidas**, se realizan en un solo paso.
    * Test-And-Set: Obtiene un valor de memoria, y al mismo tiempo lo setea en true.
    * Compare-And-Swap: Intercambia dos posiciones de memoria.

## Solución genérica a sección crítica usando locks

```c++
do {
    //////////////////////////////////////
    // Entry Section
    acquire_lock()
    //////////////////////////////////////

    //////////////////////////////////////
    // Critical Section
    // ...
    //////////////////////////////////////

    //////////////////////////////////////
    // Exit Section
    release_lock()
    //////////////////////////////////////

    //////////////////////////////////////
    // Remainder Section
    // ...
    //////////////////////////////////////
} while (true);
```

## Test-And-Set

```c++
atomic boolean test_and_set (boolean *target)
{
   boolean rv = *target;
   *target = true;
   return rv:
}
```

### Test-And-Set: Shared Boolean variable lock

```c++
do {
    //////////////////////////////////////
    // Entry Section
    while (test_and_set(&lock)) {
        /* do nothing */
    }
    //////////////////////////////////////

    //////////////////////////////////////
    // Critical Section
    // ...
    //////////////////////////////////////

    //////////////////////////////////////
    // Exit Section
    lock = false;
    //////////////////////////////////////

    //////////////////////////////////////
    // Remainder Section
    // ...
    //////////////////////////////////////
} while (true);
```

### Test-And-Set: Bounded-waiting Mutual Exclusion

```c++
do {
    //////////////////////////////////////
    // Entry Section
    waiting[i] = true;
    key = true;
    while (waiting[i] && key){
        key = test_and_set(&lock);
    }
    waiting[i] = false;
    //////////////////////////////////////

    //////////////////////////////////////
    // Critical Section
    // ...
    //////////////////////////////////////

    //////////////////////////////////////
    // Exit Section
    j = (i + 1) % n;
    while ((j != i) && !waiting[j]){
        j = (j + 1) % n;
    }
    if (j == i){
        lock = false;
    }
    else{
        waiting[j] = false;
    }
    //////////////////////////////////////

    //////////////////////////////////////
    // Remainder Section
    // ...
    //////////////////////////////////////
} while (true);
```

## Compare-And-Swap

```c++
atomic int compare_and_swap(int *value, int expected, int new_value) {
    int temp = *value;

    if (*value == expected) {
        *value = new_value;
    }
    return temp;
}
```

### Compare-And-Swap: Shared integer “lock”

```c++
do {
    //////////////////////////////////////
    // Entry Section
    while (compare_and_swap(&lock, 0, 1) != 0); {
        /* do nothing */
    }
    //////////////////////////////////////

    //////////////////////////////////////
    // Critical Section
    // ...
    //////////////////////////////////////

    //////////////////////////////////////
    // Exit Section
    lock = 0;
    //////////////////////////////////////

    //////////////////////////////////////
    // Remainder Section
    // ...
    //////////////////////////////////////
} while (true);
```

## Get-And-Inc

```c++
atomic int get_and_inc (int *target)
{
    int res = target;
    target++;
    return res;
}
```

## Get-And-Add

```c++
atomic int getAndAdd ( int *target, int v ) 
{
    int res = *target;
    *target = *target + v;
    return res;
}
```

## Spinlock / Test-And-Set lock / TASLock

### Usando primitivas del Sistemas Operativo
```c++
atomic acquire() {
    while (!available) {
        /* busy wait */
    }
    available = false;
}

atomic release() {
    available = true;
}

do {
    acquire()
    /* Critical Section */
    release()
    /* Remainder Section */
} while (true);
```

### Usando TAS
```c++
atomic bool testAndSet (reg) {
    bool tmp = reg;
    reg = true;
    return tmp;
}

available = false;

tas_acquire() {
    while (testAndSet(available)) {
        /* busy wait */
    }
}

tas_release() {
    available = false
}

do {
    tas_acquire()
    /* Critical Section */
    tas_release()
    /* Remainder Section */
} while (true);
```

## Local Spinning / TTASLock
    Variante del TASLock, que primero verifica la variable

```c++
atomic bool get (reg) {
    return reg;
}

atomic void set( reg, b ) {
    reg = b;
}

atomic bool testAndSet (reg) {
    bool tmp = reg;
    reg = true;
    return tmp;
}

mutex mtx;

void create () {
    mtx.set( false );
}

void lock () {
    while ( true ) {
        while (get(mtx)) {
            /* busy wait */
        }
        if (!testAndSet(mtx)) {
            return;
        }
    }
}

void unlock () {
    mtx.set( false );
}
```

## Cola Atómica

```c++
private mutex mtx;
private queue q;

atomic enqueue (T item) {
    mtx.lock();
    q.push(item);
    mtx.unlock();
}

atomic bool dequeue (T * pitem) {
    bool success;
    mtx.lock ();
    if (q.empty()) {
        pitem = null; 
        success = false;
    }
    else {
        pitem = q.pop (); 
        success = true;
    }
    mtx.unlock();
    return success;
}
```

## Mutex Recursivo

```c++
int calls;
atomic<int> owner;
private int self = 0x1234; // PID, o lo que sea

void create () {
    owner.set(-1);
    calls = 0;
}

void lock() {
    if (owner.get() != self) {
        while (owner.compareAndSwap(-1, self) != self) {
            /* busy wait */
        }
    }
    // owner == self
    calls ++;
}

void unlock () {
    if (--calls == 0) {
        owner.set(-1);
    }
}
```

## Deadlock
    Cuando por un conflicto de dependencias, la ejecución queda parada
    Ejemplo: 
        - el proceso A tiene el recurso 2, y espera el recurso 1 
        - el proceso B tiene el recurso 1, y espera el recurso 2
        - ninguno libera sus recursos.

### Modelo Coffmann (para detectar Deadlock)
    Serie de condiciones necesarias
    para la existencia de un deadlock

* Exclusión Mutua: existe un recurso que no puede ser asignado a más de un proceso
* Hold and Wait: los procesos pueden retener un recurso y solicitar otro
* No preemption: no hay un mecanismo compulsivo para quitarle los recursos a un proceso
* Espera circular: Tiene que haber un ciclo de N>=2 procesos, tal que P_i espera un recurso de P_i+1

### Modelo de Grafos Bipartitos (para detectar Deadlock)
    Hay deadlock cuando hay un ciclo

* Procesos: nodos P
* Recursos: nodos R
* Aristas: 
    * **P->R** si P ==solicita== R
    * **R->P** si P ==adquirió== R

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


==TODO: Completar==

## Registros Atómicos

### Exclusión Mútua

* Teorema de Burns & Lynch: El mínimo número de registros atómicos necesarios para garantizar exclusión mútua sin restricciones de tiempo es N.

* Algoritmo de Fischer: Se asumen restricciones de tiempo. Suponiendo FAIRNESS, garantiza LOCK-FREEDOM si ∆ > δ.

```c++
void proceso(int i){
    // TRY
    while(turn!=i){
        waitfor(turn==0);
        turn = i;           // tarda a lo sumo T
        pause(W);       // espera un tiempo W > T
    }
    
    // CRIT
    …

    // EXIT
    turn = 0
}
```

* Algoritmo de Dijkstra: Garantiza EXCL. Suponiendo FAIRNESS, garantiza LOCK-FREEDOM, pero no WAIT-FREEDOM.

```c++
/*
Registros
        * flag[i]: atomic single-writer / multi-reader
        * turn: atomic multi-writer / multi-reader
*/

void proceso(int i){
    // TRY
    flag[i] = 1;
    while(turn != i) {
        if(flag[turn]==0){
            turn = i ;
        }
    }
    flag[i] = 2;

    foreach(j!=i) {
        if (flag [j] == 2) goto TRY;
    }

    /* CRIT */
    ...
    
    /* EXIT */
    flag[i] = 0;

```
}

* Panadería de Lamport:

```c++
/*
Registros:
    choosing[i], number[i]: atomic single-writer / multi-reader
*/

/* TRY */
choosing[i] = 1;
number[i] = 1 + max{j!=i}(number [j]);
choosing[i] = 0;
foreach j != i {
    waitfor choosing [j]==0;
    waitfor number [j]==0 || (number[i], i) < (number[j] , j);
}

/* CRIT */
...

/* EXIT */
number [i] = 0;
```

### Consenso
* Teorema Herlihy & Lynch: No se puede garantizar consenso para un n arbitrario con registros RW atómicos.