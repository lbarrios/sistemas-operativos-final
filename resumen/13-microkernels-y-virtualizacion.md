# Microkernels

## Ventajas vs Kernel Monolítico
* Menos código privilegiado
* Facilidad de actualizar
* Mayor flexibilidad y extensibilidad
* La caída de un servicio no tira abajo el sistema
* Diferentes "sabores" de los servicios

## Idea Inicial
Para lograr esto la idea era que tener un kernel que hiciera:
* Manejo básico de memoria
* Manejo básico de E/S
* Manejo básico de IPC

El resto de las cosas serían provistas por servicios.

## En la práctica...
* Resultó más lento que los kernels monolíticos.
* Hubo una segunda generación de microkernels que buscó solucionar estos problemas.
* La idea nunca terminó de ser exitosa.
* Excepciones:
	* QNX, un Unix RT con arquitectura microkernel, diseñado para sistemas embebidos.
	* MacOS tiene código de Mach, un microkernel. Pero el código que tiene es de cuando Mach no era un microkernel... así que técnicamente MacOS no usa microkernel.

## Ideas útiles
Algunas ideas se salvaron.

* IPC más rápido.
* **Módulos de Kernel (!)**
* Intentar sacar _algunos servicios_ del Kernel.

*Esto significa que hoy en día los Kernel se pueden considerar híbridos.*

# Virtualización
    Es la posibilidad de que un conjunto de recursos físicos sean vistos como varios recursos lógicos distintos (O sea, como si fueran distintos recursos físicos).
    Coloquialmente, una computadora ejecutando varias computadoras.

* Máquinas virtuales, concepto que viene desde hace rato (al menos 1960).
	* Portabilidad (ej JVM)
	* Simulación
	* Testing
	* Aislamiento (chroot, jail, containers)
	* Particionamiento de Hardware
	* Agrupamiento de funciones (consolidation)
	* Protección ante fallas

## Conceptos:
* VMM/Hypervisor: es un software/firmware/hardware específico destinado a crear, correr y administrar máquinas virtuales.

	* Tipo 0 (Hardware / Firmware): Es un tipo especial de virtualización, en donde el propio hardware se encarga de la virtualización, generando "particiones" o "dominios" de ejecución. 
		* Cualquier Sistema Operativo que corra en un dominio, ve el hardware como si fuera exclusivo, no sabe que en realidad posiblemente está siendo compartido con otros Sistemas Operativos en otros dominios.
		* Funciona de forma "transparente".
		* La administración de IO puede generar problemas.

	* Tipo 1 (Nativo / Unhosted / Bare Metal): Se ejecuta directamente sobre el hardware.
		* Si bien se ejecuta directamente sobr el hardware, el VMM en sí es un Sistema Operativo, que provee funciones mínimas e indispensables (CPU scheduling, administración de IO, protección y seguridad).
		* Muchas veces se provee, además, una API de administración (local, remota).
		* Ejemplos: VMware ESXi, XEN, Citrix XenServer, Microsoft Hyper-V Server, Oracle VM.

	* Tipo 2 (Hosteado): Se ejecuta como un software más.
		* Técnicamente, puede correr sobre cualquier Sistema Operativo, sin requerir de un soporte especial.
		* Por lo general la mayoría de las opciones requieren privilegios de Kernel, y para ello usan módulos específicos en el sistema operativo Host.
		* Todo esto obviamente agrega un overhead a la virtualización.
		* Ejemplos: Virtualbox, VMware Workstation/Server/Player, QEMU, Virtual PC.
	
	* Paravirtualización: No es exactamente virtualización. Requiere de un host y un guest modificados especialmente para funcionar. 
		* Traduce las llamadas al sistema operativo guest en llamadas al sistema operativo host, por lo que estas corren localmente en el host. 
		* El sistema operativo guest tiene que estar adaptado para utilizar la para-API provista por el VMM, por lo que un sistema operativo convencional (sin modificar) no puede correr sobre un VMM con paravirtualización. 
		* Esta técnica tiene muchas ventajas en cuanto a performance. 
		* Caso típico: Xen

	* Virtualización del Entorno de Programación: es virtualización basada en un modelo de ejecución distinto al típico, en donde lo que se virtualiza es el entorno de ejecución. Requiere contar con un soporte de Lenguaje/Software.
		* Caso típico: JVM

* Características esenciales de los VMM (Popek and Goldberg virtualization requirements)
	* Fidelidad (equivalence): Un programa corriendo en una VMM debe exhibir un comportamiento esencialmente idéntico al que tendría si estuviese corriendo en una máquina física.
	* Performance (efficiency): Una porción estadísticamente significativa de las instrucciones de máquina deben ser ser ejecutadas sin la intervención del VMM (es decir, para que no sea emulación).
	* Control de Recursos (safety): El VMM debe estar en completo control de los recursos virtualizados.

## Simulación
* En el sistema _Host/Anfitrión_ se construye una estructura de estado artificial que representa al sistema huésped. 
* Se lee cada instrucción, y se modifica el estado, como si la instrucción se estuviese ejecutando realmente.
* ### Problemas:
	* Este mecanismo puede ser muy lento.
	* Hay cosas difíciles de simular, como DMA, concurrencia, etc.

## Emulación de Hardware
* Se emulan los componentes de Hardware.
	* Cuando una máquina cree que está haciendo E/S, en realidad se está comunicando con el controlador de máquinas virtuales.
	* Este a su vez hace de proxy, ya sea usando el dispositivo real como backend, o el sistema de emulación que esté utilizando (puede ser emulación pura).
* La mayor parte del código se corre mediante traducción binaria.
* ### Problemas:
	* ¿Cómo logro separación de privilegios dentro de la máquina virtual? Toda la máquina virtual corre en modo usuario.
	* Overhead en el acceso a los dispositivos. Más lento.

## Virtualización asistida por Hardware
	Extensiones de arquitectura de procesador, que buscan facilitar la tarea de virtualizar un Sistema Operativo.

* Busca evitar los problemas descriptos anteriormente.
	* Ring aliasing: es el problema que surge de correr programas que fueron hechos para correr en un determinado anillo de protección, pero terminan corriendo en otro. Por ejemplo, programas pensados para correr en modo kernel, que terminan corriendo en modo usuario. Esto trae problemas, por ejemplo, de permisos al intentar ejecutar instrucciones privilegiadas.
	* Address-space compression: proteger el espacio de memoria del VMM, pero sin restringirla totalmente; es decir, se debe permitir el acceso (no arbitrario) del guest a dicha memoria. Por otro lado, para el Sistema Operativo Host, el VMM y el guest son el mismo proceso, por lo que la protección de memoria no se puede dar por ese lado.
	* Non-faulting access to privileged state: la protección basada en privilegios impide que el software no privilegiado acceda a determinados componentes del estado del CPU (necesarios para correr un Sistema Operativo). Algunas instrucciones privilegiadas generan un trap cuando se ejecutan sin permiso, y eso es bueno ya que se pueden capturar y resolver. Pero hay otras que no.
	* Interrupt virtualization: es necesario proveer soporte a interrupciones externas.
	* Access to hidden state: algunas cuestiones del estado del procesador no son accesibles por software.
	* Ring compression: tanto el kernel huésped como sus programas corren en el mismo nivel de privilegio; esto significa que no hay protección en el sistema operativo guest.
	* Frequent access to privileged resources: bloquear el acceso a cada recurso mediante un TRAP puede generar un overhead y un cuello de botella importante para recursos accedidos con frecuencia.

* En el caso de Intel, se agregaron las extensiones VT-x
	* Se agrega un nuevo anillo de privilegios (-1).
	* Se proveen dos modos:
		* VMX root: Las instrucciones se comportan de forma similar, pero con algunas extensiones (modo anfitrión).
		* VMX non-root: El mismo set de instrucciones, pero con comportamiento restringido (modo huésped).
	* Se proveen 10 instrucciones que permiten alternan entre modos.
	* Se agrega la VMCS (Virtual Machine Control Structure).
		* Campos de control: indica qué interrupciones recibe el huésped, qué puertos de E/S, etc.
		* Estado completo del huésped.
		* Estado completo del anfitrión.
	* La idea es que el CPU salga automáticamente del modo VMX non-root cuando el huésped realice alguna acción "prohibida" de acuerdo a la VMCS.
		* En ese momento el controlador de VM recibe el control, y emula, ignora o termina la acción prohibida.

## Desafíos / Problemas

* Los sistemas operativos tienen optimizaciones que suponen que están en una máquina real.
	* Por ejemplo, el Kernel y el FS están optimizados para acceder al disco de forma eficiente.
	* La administración de memoria y scheduler de CPU suponen que la carga que ven es la real del hardware. Si no cuentan con esa información, pueden terminar tomando decisiones que impacten en la performance del sistema.
* Contención: al estar todo en una misma máquina física, hay un único punto de falla.

## Escenarios de uso / Ventajas

* Correr sistemas viejos o legacy.
* Aprovechamiento del equipamiento.
* Desarrollo / Testing / Debugging.
* Abaratar costos.
	* Maximizar la utilización del HW.

## Bibliografía

- http://www.cs.cornell.edu/home/ulfar/ukernel/ukernel.html
- “Formal Requirements for Virtualizable Third Generation Architectures”, de Popek y Goldberg.
- “Intel Virtualization Technology: Hardware Support for Efficient Processor Virtualization”. http://www.intel.com/technology/itj/2006/v10i3/1-hardware/1-abstract.htm
- “A comparison of software and hardware techniques for x86 virtualization”, de Adams y Agesen.