# 0 - Introducción

## Hardware Vs Software
División de los sistemas informáticos entre **Hardware < - > Software**. El sistema operativo es el **intermediario** entre ellos:

- **Visión del usuario**: Para que el software no se tenga que preocupar de detalles de bajo nivel.
- **Visión del fabricante**: Para que el hardware no se vea afectado por un mal uso por parte del software.

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

Al ser el programa más importante, corre con máximos privilegios (nivel 0).