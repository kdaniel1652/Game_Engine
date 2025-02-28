# Tarea 01 - Creación de Videojuegos

## Descripción

Esta tarea consiste en la implementación de un programa que simula un motor de videojuegos básico utilizando las bibliotecas SDL2 y GLM, junto con el lenguaje de programación C++. El programa leerá un archivo de configuración (`config.txt`) que especifica las características de la ventana, la fuente y los elementos (entidades) que se dibujarán en la ventana. Las entidades se moverán dentro de la ventana y rebotarán cuando alcancen los bordes.

## Profesor

Alberto Rojas Salazar  
Correo electrónico: alberto.rojassalazar@ucr.ac.cr

## Estudiante

Kenneth Daniel Villalobos Solís - C18548
Correo electrónico: kenneth.villalobossolis@ucr.ac.cr

## Contenidos

- Entrega
- Especificación del Programa
- Archivo de configuración
- Archivos suministrados

## Entrega

- **Fecha de entrega:** 14 de abril de 2024
- **Formato de entrega:** Proyecto comprimido en un archivo zip. NO incluir archivos y carpetas generadas automáticamente (por ejemplo, /Debug, etc.).
- **Presentación:** Debe presentar el programa en la clase siguiente a la entrega.

## Especificación del Programa

El programa debe cumplir con los siguientes requisitos:

- Implementar un motor de videojuegos utilizando SDL2 y GLM en C++.
- Leer un archivo de configuración (`config.txt`) para obtener las características de la ventana, la fuente y las entidades.
- Las entidades deben aparecer en la posición indicada en el archivo y moverse según su velocidad.
- Cuando una entidad llegue a algún borde de la ventana, debe "rebotar" cambiando la dirección de la velocidad.
- Cada entidad tiene una etiqueta que debe dibujarse centrada en la imagen de la entidad.

### Ventana

- El ancho, alto y color de fondo de la ventana se indican en el archivo de configuración.

### Fuente

- La fuente, tamaño y color del texto se especifican en el archivo de configuración.

### Entidades

- Las entidades se implementan como class o struct y solo deben almacenar variables.
- Las características de cada entidad se indican en el archivo de configuración.
- Cada entidad tiene una imagen, un texto, dimensiones, posición, velocidad, ángulo y etiqueta.
- La textura de la imagen y el texto deben dibujarse juntos, con la etiqueta centrada en la imagen.

### Clase Game

- Expandir el código de la clase Game para almacenar y dibujar varias entidades.
- El método encargado de dibujar la ventana debe actualizarse aproximadamente 60 veces por segundo.
- Modularizar la clase Game de la mejor manera posible.
- Liberar la memoria solicitada por SDL.

### Teclas y Eventos

- Al presionar el botón de cerrar ventana, el programa debe terminar.
- Al presionar la tecla ESC, se debe cerrar la ventana y terminar el programa.
- Al presionar la tecla P, el programa debe pausar el movimiento de las entidades.

## Archivo de configuración (`config.txt`)

El archivo de configuración sigue el siguiente formato:

- `window w h r g b`
- `font p r g b s`
- `entity l p w h px py vx vy a`

Donde:
- `w`, `h`, `r`, `g`, `b`: Ancho, alto y color de fondo de la ventana en formato RGBA.
- `p`, `r`, `g`, `b`, `s`: Directorio de la tipografía, color de la fuente en formato RGBA y tamaño de la fuente.
- `l`: Etiqueta de la entidad.
- `p`: Directorio del sprite.
- `w`, `h`, `px`, `py`, `vx`, `vy`, `a`: Dimensiones de la imagen, posición (coordenadas x e y), velocidad (valores x e y), y ángulo de rotación de la imagen.

## Archivos suministrados

Se proporcionan los siguientes archivos y bibliotecas:

- Archivo de configuración `config.txt`.
- Carpeta de assets, que contiene imágenes (sprites) y una fuente en formato .ttf.
- Biblioteca GLM en un archivo comprimido.
