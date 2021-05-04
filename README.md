# TP1 - Hill Cipher

Pablo Salvador Dimartino - 101231

Taller de Programación I (75.42) - 1º Cuatrimestre 2021

Facultad de Ingeniería

Universidad de Buenos Aires

[Link al repositorio de GitHub](https://github.com/psdimartino/TallerDeProgramacion_TP1)

## Introduccion

Para la resolucion del problema se oriento la estructura del código para permitir una compartimentalización del codigo. Estas estructuras son mas facilmente testeables y hacen que el código sea mas entendible y mantenible.

## Estructura general

Los elementos principales del código, el `Server` y el `Client` se encargan de orquestar las relaciones entre los TDAs:

1. `file`: Se encarga de la apertura y cierre de archivos
2. `sockets`: Se encargan de el envio y recepcion de mensajes a travez del protocolo TCP
3. `encoder`: Realiza la conversión entre strings y caracteres. Para dicha conversión utiliza dos TDAs:
    a. `mod26`: Es una abstracción que permite la aritmética modular entre los caracteres.
    b. `matrix`: Contiene principalmente una implementación de los algoritmos de multiplicacion de matrices de valores `mod26`.

Se pueden ilustrar dichas relaciones mediante el gráfico:

![Estructura principal del código](diagram.png)