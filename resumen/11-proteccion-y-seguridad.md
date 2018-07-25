# Protección y Seguridad
* Protección
	* Conjunto de medidas y mecanismos.
	* Restricción: previene que usuarios accedan a recursos o datos de otros. 
	* Control: define qué usuario puede hacer cada cosa.

* Seguridad:
	* Asegurarse de la autenticidad de los usuarios.
	* Impedir la destrucción o adulteración de los datos.

## Seguridad de la Información
Preservación de las siguientes características:
* Confidencialidad
* Integridad
* Disponibilidad

**Seguridad de la Información != Seguridad Informática**

## Características de un Sistema de Seguridad
Los sistemas de seguridad suelen tener:
* Sujetos: el sujeto más común del SO es el del usuario. Pueden ejecutar acciones, y a veces ser dueños de objetos.
* Objetos: archivos, procesos, memoria, conexiones, puertos, etcétera.
* Acciones: leer, escribir, copiar, abrir, borrar, imprimir, ejecutar, matar, etcétera.

La idea es poder definir qué sujetos pueden realizar qué acciones sobre qué objetos. Un sujeto puede ser a la vez un objeto.

* Usuarios: es un sujeto básico del SO.
* Grupos: colecciones de usuarios.
* Roles: conjunto de acciones que se asignan a usuarios o grupos, para definir qué pueden (o no hacer). 
	* Ejemplo de roles: operador, usuario común, administrador.

## Propiedades de un Sistema de Seguridad
* Autenticación: verificar identidad/veracidad
	* Proporcionar algo que sé, algo que tengo, algo que soy.
	* Varios factores de autenticación.
		* Contraseñas
		* Medios biométricos
		* Tokens
	* Fuerte uso de criptografía
* Autorización: definir permisos / capacidades
* Auditoría o Contabilidad: registrar todas las acciones que fueron llevadas a cabo en el sistema, sobre qué objetos, y por qué sujetos.

## Criptografía
	Rama de las matemáticas y de la informática que se ocupa de cifrar/descifrar la información utilizando métodos y técnicas que permitan el intercambio de mensajes de manera que sólo puedan ser leídas por las personas a quienes van dirigidos.

* El criptoanálisis es el estudio de los métodos que se utilizan para quebrar textos cifrados con objeto de recuprar la información original en ausencia de la clave.

### Algoritmos de Encriptación Simétricos
	Utilizan la misma clave para encriptar y desencriptar.

* Caesar
* DES
* Blowfish
* AES

### Algoritmos de Encriptación Asimétricos
	Utilizan claves distintas para encriptar y desencriptar. Fueron un gran avance científico.

* RSA

### Algoritmos de Hash One-Way
	No son algoritmos de encriptación. No permiten revertir el resultado. Presentan colisiones. Son muy utilizados.

* MD5
* SHA1
* SHA-256

## Funciones de Hash
* En criptografía se utilizan hashes de una vía.
* La idea es que sea prácticamente imposible obtener la preimagen.
* Requisitos:
	* Resistencia a la preimagen. Dado h, debería ser difícil encontrar m tal que h=hash(m).
	* Resistencia a la segunda preimagen. Dado m1, debería ser difícil encontrar m2!=m1 tal que hash(m1)=hash(m2).
	* Etc.
* Muy útiles para almacenar contraseñas para que no se puedan leer.
* A la hora de hashear una clave, es muy importante usar un SALT y varias iteraciones, para dificultar revertir el hash, ya que las funciones de hash son muy rápidas.

## Método RSA
* Autores: Ronald Rivest, Adi Shamir, Len Adleman.

* Se toman dos números de muchos dígitos.
* A uno se lo denomina clave pública, al otro clave privada.
* Cada persona necesita ambas:
	* Su clave privada (que protege).
	* Su clave pública (que difunde).

* Para cifrar un mensaje, el emisor interpreta cada letra como si fuera un número, y luego hace una cuenta que involucra la clave pública del receptor.
* Para descifrar un mensaje, el necesario aplica una cuenta con su clave privada.

### Explicación RSA
* Tomar `p` y `q` primos
* Multiplicarlos: `n = p.q`
* Calcular: `n' = (p-1)(q-1)`
* Elegir un entero `2 < e < n'-1` que sea coprimo con `n'`.
* `e` y `n` van a ser la clave pública.
* Computar `d` para que cumpla que el resto de `d.e/n' = 1` ssi `d.e = n'` ssi `d = n'/e`.
* `d` y `n` van a ser la clave privada.

* Encriptar: calcular x = m^e (n), el resto de dividir m^e por n.
* Desencriptar: calcular y = c^d (n), el resto de dividir c^d por n.
* Este método sirve porque **factorizar es muy difícil (NP)**.

### Firma digital con RSA
* Calcular el hash de un documento.
* Encriptar el hash con la clave privada.
* Entregar el documento más el hash encriptado.
* El receptor lo desencripta con la clave pública. Luego calcula el hash del documento. si el hash desencriptado coincide con el del documento, entonces se asegura de que el autor del documento es quien dice ser.

* Todo esto está regulado mediante la Ley 25.506.

### Autenticación remota con hash
* Existe un ataque llamado **"replay-attack"**, las funciones de hash no lo impiden.
* Los métodos que se utilizan para prevenir los replay-attack se llaman **Challenge-Response**.
	* El servidor elige un número al azar, y se lo envía al cliente.
	* El cliente tiene que encriptar la contraseña utilizando ese número como input.
	* El servidor hace lo mismo, y se fija si coinciden.
	* Lamentablemente, este método tampoco es infalible.

## Autorización: Permisos
* Una forma de ver a los permisos es como una matriz de control de accesos.
	* Matriz de `Sujetos x Objetos`.
	* En cada celda figuran las acciones permitidas.
	* Se puede almacenar como una matriz centralizada, o separada por filas y columnas.
	* Los archivos suelen guardar qué puede hacer cada usuario con ellos.
* **Principio del Mínimo Privilegio**: se asume que todo lo que no está especificado, está prohibido.
	* Al crear un objeto nuevo, se le definen permisos por defecto.
	* Estos permisos por lo general están predefinidos según el tipo de objeto.

### DAC vs MAC
* Discretionary Access Control: los atributos de seguridad se tienen que definir explícitamente, el dueño de cada objeto decide los permisos.
* Mandatory Access Control: cada sujeto tiene un grado, los objetos heredan el grado del último sujeto que los modificó, y un sujeto sólo puede acceder a objetos de grado menor o igual que el de él.
	* Modelo Bell-Lapadula.
	* Se lo utiliza para manejar información altamente sensible.

### DAC en Unix
* SETUID y SETGID: permisos especiales que pueden asignarse a archivos o directorios en un sistema operativo Unix. Se utilizan principalmente para permitir a usuarios ejecutar binarios con los permisos de otro usuario, para realizar una tarea específica.
	* Si un archivo tiene el bit de SETUID activo, se identifica con una "S" al hacer `ls`, de la siguiente forma: `-rwsr-xr-x 1 root shadow 27920 ago 15 22:45 /usr/bin/passwd`
* Sticky Bit: si se activa sobre un directorio, todos los archivos contenidos en el mismo sólamente pueden ser borrados o renombrados por el dueño del archivo (o el dueño del directorio, o root). Se podría decir que cada archivo se queda "pegado" a su dueño.
* `chattr`: utilidad para cambiar atributos.
* Posix ACLs (getfacl, setfacl) y NFSv4 ACLs: son formas de ACL que se complementan y flexibilizan la forma estándar de unix, de forma que es posible definir permisos con mayor granularidad (ejemplo: a usuarios específicos, a más de un grupo, etcétera).

### Puntos importantes

* Permiso para propagar o definir permisos.
* Revocación de permisos: ¿la aplicación debe ser inmediata o diferida?
	* Inmediata: puede causar un overhead considerable, ejemplo: cada vez que se cambia un permiso a uno o más archivos hay que verificar si esos descriptores se encuentran abiertos por algún usuario o proceso.
	* Diferida: puede ser origen de vulnerabilidades; ejemplo: si un usuario tiene un archivo abierto, con permisos de escritura, y se le bloquea ese permiso con posterioridad, el usuario va a poder seguir escribiendo a ese archivo.