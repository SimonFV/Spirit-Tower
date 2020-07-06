#  Proyecto #2  -  Spirit Tower 
<br/>
* <p align="justify"> Spirit tower es un juego de aventura que consiste en investigar un templo lleno de tesoros, donde patrullan espectros, los cuales al encontrar al jugador, lo perseguirán para evitar que avance a través de los niveles del templo. El juego consta de 5 niveles, diferentes tipos de espectros y además, posee un servidor que va a contener toda la información del juego así como un cliente que se va a desarrollar con el propósito de ser multiplataforma y que este interactúe propiamente con el jugador.</p>
<br/>
<p align="center">
  <img width="880" height="480" src="https://clio44.files.wordpress.com/2014/09/wpid-1409968796236.gif">
</p>
<br/>
<br/>

# Historias de usuario

1. Yo como cliente quiero poder interactuar con una interfaz de usuario para jugar al juego Spirit Tower.
2. Yo como cliente quiero poder usar un personaje el cual pueda moverse y atacar a los enemigos.
3. Yo como cliente quiero poder obtener recompensas al avanzar en el juego.
4. Yo como cliente quiero que el juego aumente su dificultad conforme se avanza en este.
5. Yo como cliente quiero poder enfrentar a un enemigo final.
6. Yo como cliente quiero poder interactuar con el juego mediante una arquitectura cliente-servidor.
7. Yo como cliente quiero tener la posibilidad de visualizar las peticiones del cliente al sevidor.
8. Yo como cliente quiero que se guarde el juego en el servidor y así no utilizar un almacenamiento local.

# Features
### Interacción con GUI
* Historia de usuario: 1, 2 

### Jugabilidad
* Historia de usuario: 3, 4, 5

### Arquitectura cliente-servidor
* Historia de usuario: 6, 7, 8
<br/>
<br/>

# Tareas

1. Programar una interfaz de usuario para interactuar con el juego.
2. Programar la movilidad del personaje, así como sus ataques.
3. Programar la obtención de recompensas conforme se avanza en el juego y se destruyen enemigos.
4. Programar el aumento de la dificultad del juego mediante el uso de ciertos algoritmos requeridos.
5. Programar las mejoras de los enemigos del juego mediante el uso de ciertos algoritmos requeridos.
6. Programar el nivel final del juego con dificultad máxima. 
7. Programar el cliente para que el usuario lo pueda utilizar al jugar el juego.
8. Programar el servidor que contendrá todos los datos del juego.
<br/>
<br/>

# Diagrama de clases

* <p align="justify"> En las siguiente imágen se presentan las clases que se pensaron inicialmente para realizar el proyecto. En ella se encuentran el diagrama pensado para el cliente y el servidor, así como sus métodos requeridos para ejecutar los algoritmos necesarios.</p>
<br>
<br>
<p align="center">
  <img width="780" height="380" src="https://github.com/SimonFV/Spirit-Tower/blob/master/Diagrama%20de%20clases%20UML%20-%20Proyecto%20%232%20-%20Spirit%20Tower.png">
</p>
<br/>
<br/>

# Estructuras de datos utilizadas
<br/>
* <p align="justify"> Para lograr almacenar los datos requeridos por los algoritmos desarrollados, se implementó el uso de vectores bidimensionales con el fin de generar matrices que incluyeran la población inicial, el resultado de la función de fitness, el proceso de selección y reproducción, así como el de mutación. Con esto, se lograron ordenar correctamente las características más óptimas para cada individuo y así, realizar el proceso que requería cada algoritmo. </p>
<br/>
<br/>
<p align="center">
  <img width="880" height="480" src="https://media.geeksforgeeks.org/wp-content/uploads/3D-array.jpg">
</p>
<br/>
<br/>

# Algoritmos desarrollados
<br/>
* <p align="justify"> Se implementó el uso de un algoritmo de backtracking con la finalidad de que la movilidad de los enemigos del juego les permita a estos poder devolverse en la ruta que siguieron al perseguir al jugador, en caso de que este llegase a una zona segura.</p>
<p align="center">
  <img width="600" height="600" src="https://thumbs.gfycat.com/BabyishTightJanenschia-size_restricted.gif">
</p>
* <p align="justify"> Se implementó el uso del algoritmo A-star con la finalidad de que en el momento en el cual el jugador sea detectado por los enemigos, estos se muevan hacia él mediante el uso de este algoritmo.
</p><br/><br/>
<p align="center">
  <img width="600" height="600" src="https://i.imgur.com/JHrNW00.gif?noredirect">
</p><br/><br/>
* <p align="justify"> Se implementó el uso de un algoritmo genético con la finalidad de escoger a los enemigos con las condiciones más óptimas para que se logre aumentar la dificultad del juego conforme se avanza en este.
</p><br/><br/>
<p align="center">
  <img width="680" height="400" src="https://blog.datascienceheroes.com/content/images/2019/01/evolutionary_algortihm-1.gif">
</p><br/><br/>
<br/>
<br/>

# Bugs
<br/>
<br/>
