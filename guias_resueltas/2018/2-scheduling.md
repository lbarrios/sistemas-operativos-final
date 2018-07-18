Ver: [Guía 2](../../guias/2018/2-scheduling.pdf)

---------------

# Ejercicio 1

a)
CPU: (0, 1), (11, 12), (21, 22)
E/S: (2, ..., 10), (13, ..., 20)

b) Las ráfagas de CPU duran 2 quantums, las ráfagas de IO duran 9 y 8 quantums.

# Ejercicio 2

- P0 tendría alta prioridad, ya que se comporta como un proceso interactivo; habría que darle poco quantum, ya que las ráfagas son cortas.
- P1 tendría alta prioridad, y poco quantum; se comporta como un servidor web.
- P2 tendría baja prioridad, y mucho quantum; se comporta como un programa que procesa cosas en background.

# Ejercicio 3

A un scheduler sin desalojo.

# Ejercicio 4

a) Round-robin: no puede generar starvation, ya que se obliga a ciclar por todos los procesos.
b) Por prioridad: los procesos con mayor prioridad pueden generar starvation de los de menor prioridad.
c) SJF (trabajo más corto primero): suponiendo que se agregan muchos trabajos cortos constantemente, esto puede generar starvation de los trabajos más largos.
d) FIFO: no puede generar starvation ya que al haber un orden predefinido, en algún momento se va a pasar por cada uno de los procesos.

# Ejercicio 5

a) Si se ponen dos punteros a la misma PCB en un scheduler RR, se le da el doble de quantum al proceso correspondiente.
b) Las ventaja es que se puede regular el quantum que le corresponde a cada proceso, agregando más entradas del mismo proceso a la cola de round robin. La desventaja es que esto ocupa más memoria, no es eficiente para agregar, para recorrer, ni para borrar.
c) Se podría agregar al PCB un contador de tics, que indique cuantos tics le quedan a ese proceso. Se cambia de proceso cuando el proceso agota sus tics.