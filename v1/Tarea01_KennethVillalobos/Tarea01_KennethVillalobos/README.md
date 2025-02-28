# Tarea 01 - Creaci�n de Videojuegos

## Descripci�n

Esta tarea consiste en la implementaci�n de un programa que simula un motor de videojuegos b�sico utilizando las bibliotecas SDL2 y GLM, junto con el lenguaje de programaci�n C++. El programa leer� un archivo de configuraci�n (`config.txt`) que especifica las caracter�sticas de la ventana, la fuente y los elementos (entidades) que se dibujar�n en la ventana. Las entidades se mover�n dentro de la ventana y rebotar�n cuando alcancen los bordes.

## Profesor

Alberto Rojas Salazar  
Correo electr�nico: alberto.rojassalazar@ucr.ac.cr

## Estudiante

Kenneth Daniel Villalobos Sol�s - C18548
Correo electr�nico: kenneth.villalobossolis@ucr.ac.cr

## Contenidos

- Entrega
- Especificaci�n del Programa
- Archivo de configuraci�n
- Archivos suministrados

## Entrega

- **Fecha de entrega:** 14 de abril de 2024
- **Formato de entrega:** Proyecto comprimido en un archivo zip. NO incluir archivos y carpetas generadas autom�ticamente (por ejemplo, /Debug, etc.).
- **Presentaci�n:** Debe presentar el programa en la clase siguiente a la entrega.

## Especificaci�n del Programa

El programa debe cumplir con los siguientes requisitos:

- Implementar un motor de videojuegos utilizando SDL2 y GLM en C++.
- Leer un archivo de configuraci�n (`config.txt`) para obtener las caracter�sticas de la ventana, la fuente y las entidades.
- Las entidades deben aparecer en la posici�n indicada en el archivo y moverse seg�n su velocidad.
- Cuando una entidad llegue a alg�n borde de la ventana, debe "rebotar" cambiando la direcci�n de la velocidad.
- Cada entidad tiene una etiqueta que debe dibujarse centrada en la imagen de la entidad.

### Ventana

- El ancho, alto y color de fondo de la ventana se indican en el archivo de configuraci�n.

### Fuente

- La fuente, tama�o y color del texto se especifican en el archivo de configuraci�n.

### Entidades

- Las entidades se implementan como class o struct y solo deben almacenar variables.
- Las caracter�sticas de cada entidad se indican en el archivo de configuraci�n.
- Cada entidad tiene una imagen, un texto, dimensiones, posici�n, velocidad, �ngulo y etiqueta.
- La textura de la imagen y el texto deben dibujarse juntos, con la etiqueta centrada en la imagen.

### Clase Game

- Expandir el c�digo de la clase Game para almacenar y dibujar varias entidades.
- El m�todo encargado de dibujar la ventana debe actualizarse aproximadamente 60 veces por segundo.
- Modularizar la clase Game de la mejor manera posible.
- Liberar la memoria solicitada por SDL.

### Teclas y Eventos

- Al presionar el bot�n de cerrar ventana, el programa debe terminar.
- Al presionar la tecla ESC, se debe cerrar la ventana y terminar el programa.
- Al presionar la tecla P, el programa debe pausar el movimiento de las entidades.

## Archivo de configuraci�n (`config.txt`)

El archivo de configuraci�n sigue el siguiente formato:

- `window w h r g b`
- `font p r g b s`
- `entity l p w h px py vx vy a`

Donde:
- `w`, `h`, `r`, `g`, `b`: Ancho, alto y color de fondo de la ventana en formato RGBA.
- `p`, `r`, `g`, `b`, `s`: Directorio de la tipograf�a, color de la fuente en formato RGBA y tama�o de la fuente.
- `l`: Etiqueta de la entidad.
- `p`: Directorio del sprite.
- `w`, `h`, `px`, `py`, `vx`, `vy`, `a`: Dimensiones de la imagen, posici�n (coordenadas x e y), velocidad (valores x e y), y �ngulo de rotaci�n de la imagen.

## Archivos suministrados

Se proporcionan los siguientes archivos y bibliotecas:

- Archivo de configuraci�n `config.txt`.
- Carpeta de assets, que contiene im�genes (sprites) y una fuente en formato .ttf.
- Biblioteca GLM en un archivo comprimido.
