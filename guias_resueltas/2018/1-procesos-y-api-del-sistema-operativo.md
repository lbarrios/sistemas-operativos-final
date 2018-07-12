Ver: [Guía 1](../../guias/2018/1-procesos-y-api-del-so.pdf)

---------------

# Ejercicio 1
Los pasos que deben realizarse para llevar a cabo un cambio de contexto son:

1) Se entra en una interrupción o se llama a un syscall, que corre en nivel supervisor, y se encargará de realizar el cambio de contexto. Se corre la rutina de atención de dicha interrupción.
2) Se guarda el contexto actual en la PCB del proceso que se retira.
3) Se recupera el contexto del proceso entrante desde la PCB correspondiente.
4) La ejecución continúa en el contexto recuperado.