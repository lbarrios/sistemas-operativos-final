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
	* Tipo 1 (Nativo / Unhosted / Bare Metal): Se ejecuta directamente sobre el hardware. Ejemplos: VMware ESXi, XEN, Citrix XenServer, Microsoft Hyper-V Server, Oracle VM.
	* Tipo 2 (Hosteado): Se ejecuta como un software más, corriendo sobre un sistema operativo denominado Host. Esto obviamente agrega un overhead a la virtualización. Ejemplos: Virtualbox, VMware Workstation/Server/Player, QEMU, Virtual PC.

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

## Simulación + Emulación
* Se emulan los componentes de Hardware.
	* Cuando una máquina cree que está haciendo E/S, en realidad se está comunicando con el controlador de máquinas virtuales.
	* Este a su vez hace de proxy, ya sea usando el dispositivo real como backend, o el sistema de emulación que esté utilizando (puede ser emulación pura).
* La mayor parte del código se corre mediante traducción binaria.
* ### Problemas:
	* ¿Cómo logro separación de privilegios? Toda la máquina virtual corre en modo usuario.
	* ¿Qué pasa con la velocidad de acceso a los dispositivos?