### ¿Para qué sirve setuid y cuales son sus riesgos?

Setuid sirve para permitirle a los usuarios correr programas en modo kernel, con ciertas restricciones para que no se pueda modificar el proceso en vuelo. Por ejemplo, agrega seguridad contra metodos del tipo ptrace.

Esto es necesario para permitirle a los usuarios de bajo privilegios correr ciertas tereas de alto privilegio sin tener que pedir autorizacion. El ejemplo clasico es la tarea de cambio de Password ante una potencial falla de seguridad.

El claro riesgo es que se estan corriendo una aplicacion con privilegios de Kernel. Si la aplicacion tiene cualquier falla de seguridad, un usuario malicioso podria aprovecharla para correr codigo malicioso (y escalar privilegios).

### Explicar que es el bit de SETUID. Dar un ejemplo de uso.

==POTENTIAL CHAMUYO WARNING==
Esto no estoy seguro. Si no me equivoco, es el bit que indica si un archivo fue activado con SETUID. Para que sirve esto esta explicado en el punto anterior.

### Explicar DAC y comparar DAC en unix y windows.

DAC = Discretionary Access Control. En pocas palabras, es un whitelist. 

Los sujetos tienen derecho para acceder, modificar o ejecutar un recurso si tienen permisos explicitos.

El de linux lo conoces "[tipo] usuario[r w x] grupo[r w x] otro[r w x]". (tipo puede ser file/directory/symlink/char device/block device/pipe) Ademas, cada archivo tiene un "owner group" y "owner user". Usando ciertos comandos, los usuarios pueden correr aplicaciones creadas por ROOT en ROOT. Adicionalmente, esta SETUID para correr dichos programas.

==POTENTIAL CHAMUYO WARNING==
El resumen que encontre dice que windows usa MAC (Mandatory Access Control). La idea de MAC es que hay jerarquias de control, y cada usuario puede correr aplicaciones o acceder a archivos que tengan una jerarquia igual o menor a la suya. Hay 4 jerarquias: sistema, alta, media y baja.

### ¿Se puede considerar al deadlock como un problema de seguridad?

==POTENTIAL CHAMUYO WARNING==

Si tenemos en cuenta que los DDOS son considerados fallas de seguridad, tambien tendrian que serlo los deadlocks. Si como usuario hostil puede imponer un deadlock, el sistema dejaria de funcionar de forma correspondiente.

### Explicar una API general para una encriptación asimétrica y las características generales de la implementación.

==TODO:==

### Dé las definiciones de algoritmo de encriptación simétrico y asimétrico.

==TODO:==

### Detalle RSA.

==TODO:==

### Explique firma digital con RSA.

==TODO:==

### ¿Qué es el Hash de una vía? Dar 2 usos y justificar.

==TODO:==

### ¿Qué problemas de seguridad se pueden solucionar con los canaries para buffer overflow? Dar las desventajas.

==TODO:==