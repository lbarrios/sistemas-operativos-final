### ¿Para qué sirve setuid y cuales son sus riesgos?

#### Nacho:
Setuid sirve para permitirle a los usuarios correr programas en modo kernel, con ciertas restricciones para que no se pueda modificar el proceso en vuelo. Por ejemplo, agrega seguridad contra metodos del tipo ptrace.

Esto es necesario para permitirle a los usuarios de bajo privilegios correr ciertas tereas de alto privilegio sin tener que pedir autorizacion. El ejemplo clasico es la tarea de cambio de Password ante una potencial falla de seguridad.

El claro riesgo es que se estan corriendo una aplicacion con privilegios de Kernel. Si la aplicacion tiene cualquier falla de seguridad, un usuario malicioso podria aprovecharla para correr codigo malicioso (y escalar privilegios).

#### Eze:
Setuid es un flag de acceso de los sistemas unix-like que permite a un usuario correr un ejecutable con los permisos del dueño del mismo. Por ejemplo, si hay un ejecutable que pertenece a root, y tiene el bit de setuid activo, este ejecutable será corrido en el contexto del usuario root.

Esto sirve para permitir a los usuarios escalar privilegios de forma controlada, por ejemplo, si se requiere realizar una operación de bajo nivel o que necesite correr en el contexto del kernel (cambiar la contraseña de un usuario, correr sudo, reiniciar servicios, etcétera).

El principal riesgo es que el ejecutable va a correr, efectivamente, con los permisos del usuario, lo cual ante una vulnerabilidad del mismo (ejemplo, una vulnerabilidad de desbordamiento de buffer) puede llegar a ser explotado por un usuario malicioso para generar un escalamiento de privilegios, o sin llegar a ese punto, realizar operaciones que no estaban previstas por el ejecutable.

### Explicar que es el bit de SETUID. Dar un ejemplo de uso.

#### Nacho:
==POTENTIAL CHAMUYO WARNING==
Esto no estoy seguro. Si no me equivoco, es el bit que indica si un archivo fue activado con SETUID. Para que sirve esto esta explicado en el punto anterior.

#### Eze:
==TODO:==

### Explicar DAC y comparar DAC en unix y windows.

#### Nacho: 
DAC = Discretionary Access Control. En pocas palabras, es un whitelist. 

Los sujetos tienen derecho para acceder, modificar o ejecutar un recurso si tienen permisos explicitos.

El de linux lo conoces "[tipo] usuario[r w x] grupo[r w x] otro[r w x]". (tipo puede ser file/directory/symlink/char device/block device/pipe) Ademas, cada archivo tiene un "owner group" y "owner user". Usando ciertos comandos, los usuarios pueden correr aplicaciones creadas por ROOT en ROOT. Adicionalmente, esta SETUID para correr dichos programas.

==POTENTIAL CHAMUYO WARNING==
El resumen que encontre dice que windows usa MAC (Mandatory Access Control). La idea de MAC es que hay jerarquias de control, y cada usuario puede correr aplicaciones o acceder a archivos que tengan una jerarquia igual o menor a la suya. Hay 4 jerarquias: sistema, alta, media y baja.

#### Eze:

* DAC = Discretionary Access Control. Significa que cada usuario puede definir los permisos sobre los objetos de los cuales es propietario (en realidad, con la definición más amplia de DAC, cualquier usuario debería poder definir los permisos, o en todo caso podría existir un permiso que sea justamente la "definición de nuevos permisos").

En Unix la administración de permisos se realiza, por cada archivo, asignando los siguientes bits:
```
rwxrwxrwx
|u||g||o|

u = user
g = group
o = other
```

En Windows, en cambio, a cada archivo se le asignan los permisos a los grupos o usuarios que se requieran. Esto se combina a su vez con MAC, en donde los archivos tienen niveles de integridad: sistema, alta, media y baja.

### ¿Se puede considerar al deadlock como un problema de seguridad?

#### Nacho:
==POTENTIAL CHAMUYO WARNING==

Si tenemos en cuenta que los DDOS son considerados fallas de seguridad, tambien tendrian que serlo los deadlocks. Si como usuario hostil puede imponer un deadlock, el sistema dejaria de funcionar de forma correspondiente.

#### Eze:

Sí.

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