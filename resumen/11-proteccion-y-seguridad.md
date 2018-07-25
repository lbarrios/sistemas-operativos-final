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
* Elegir un entero `2 < e < n' -1` que sea coprimo con `n'`.