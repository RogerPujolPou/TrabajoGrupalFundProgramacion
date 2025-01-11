#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

//Dimensiones del tablero y Número de barcos

#define FILAS 7
#define COLUMNAS 7
#define NUM_PORTAVIONES 1
#define NUM_CRUCEROS 2
#define NUM_PATRULLERAS 3

// Función para mostrar el menú del juego

int menuJuego() {
  
  int resp;                                   // Declaración de la variable global "resp" que es la opción que elegirá el jugador.


  // Cóigo para mostrar el menú del juego HUNDIR LA FLOTA:

  do{
    printf("\nHUNDIR LA FLOTA\n");
    printf("\nBIENVENIDO AL JUEGO\n");                        // Esta línea hace que se muestre un mensaje de Bienvenida.
    printf("\nMenu de Opciones\n");                           // Esta otra hace que se muestre en pantalla el menú del juego y que el jugador pueda elegir una de las 3 opciones disponibles.
    printf("1. Jugar\n");                                     // La opción 1 sirve para jugar al juego. 
    printf("2. Ver Mejores Puntuaciones\n");                  // La opción 2 sirve para ver las mejores puntuaciones.
    printf("3. Salir del Videojuego\n");                      // La opción 3 sirve para poder salir del programa
    printf("Elige una opcion: "); 
    scanf(" %d", &resp);                                      //Aquí el código guarda la opción elegida por el jugador.

    // Código para procesar la opción seleccionada dentro del menú:

    switch (resp) {
      case 1:                                                 // Case por si el jugador escribe 1, si no el bucle sigue ejecutandose gracias al break.
          printf("Has elegido Jugar.\n");
          break;
      case 2:                                                 // Case por si el jugador escribe 2, si no el bucle sigue ejecutandose gracias al break.
          printf("Has elegido Ver Mejores Puntuaciones.\n");
          break;
      case 3:                                                 // Case por si el jugador escribe 3, si no el bucle sigue ejecutandose gracias al break.
          printf("Saliendo del programa. ¡Nos Vemos!\n");
          break;
      default:                                                // Si el jugador escribe un número diferente a 1, 2 o 3, gracias a este "default" saltará el mensaje de "opción no válida".
          printf("Opcion no valida. Intentalo de nuevo.\n");  // El bucle seguirá ejecutandose gracias al break.
          break;
    }

  } while (resp < 1 || resp > 3);     // El bucle se asegura que la opción sea válida  

  return resp;
}

// Función para inicializar el mapa vacío

void inicializarTablero(char tablero [FILAS][COLUMNAS]) { 
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            tablero [i][j] = '*';                                           // Casillas sin probar
        }
    }
}

// Función para mostrar el mapa oculto o el mapa visible

void mostrarTablero(char tablero [FILAS][COLUMNAS], bool posOculta){        // True, muestra el tablero, False lo oculta
    printf("  ");
    for (int i = 0; i < COLUMNAS; i++) {
        printf(" %d", i);
    }
    printf("\n");

    for (int i = 0; i < FILAS; i++) {
        printf("%d ", i);
        for (int j = 0; j < COLUMNAS; j++) {
            if (!posOculta) {                                               // Modo oculto
                if (tablero[i][j] == 'X') {
                    printf(" X");                                           // Mostrar impactos en el barco
                } else {
                    printf(" *");                                           // Ocultar agua y barcos intactos
                }    
            } else {
                if (tablero[i][j] == 'B') {
                    printf(" B");                                           // Partes del barco intactas
                } else if (tablero[i][j] == 'A') {
                    printf(" A");                                           // Agua visible 
                } else if (tablero[i][j] == 'X') {
                    printf(" X");                                           // Partes del barco con impactos
                } else {
                    printf(" *", tablero[i][j]);                           // Otros símbolos
                }
            }
        }
        printf("\n");
    }
}    

//Función para verificar si un barco se puede colocar en una posición

int verificarEspacio(char tablero [FILAS][COLUMNAS], int fila, int columna, int longitud, char orientacion){
    for (int i = 0; i < longitud; i++) {
        if (orientacion == 'H') {                                           // Si la orientación es horizontal (H)
            if (columna + i >= COLUMNAS) {                  
                return -1;                                                  //Si el barco está fuera del tablero, la función devuelve -1
            }
            if (tablero[fila][columna + i] != '*') {                        // Si el barco está solapado con otro, la función devuelve -2  
                return -2;                                  
            }
        }   else if (orientacion == 'V') {                                  // Si la orientación es vertical (V)
                if (fila + i >= FILAS) {
                    return -1;                                              //Si el barco está fuera del tablero, la función devuelve -1
                }
                if (tablero[fila + i][columna] != '*') {    
                    return -2;                                              // Si el barco está solapado con otro, la función devuelve -2   
                }
            }
        
    }
    return 1;                                                               //Si el barco está bien colocado, la función devuelve 1
}

// Función para colocar los barcos del jugador

void colocarBarJug(char tablero [FILAS][COLUMNAS], int longitud, int cantidad, const char *tipoBarco) {
    for(int i = 0; i < cantidad; i++) {                                                 // Bucle para poner barcos hasta que se llegue a la cantidad de barcos que se piden
        int fila, columna;
        char orientacion;
        int valido = 0;

        printf("Coloca tu %s de longitud %d (quedan %d barcos de este tipo) \n", tipoBarco, longitud, cantidad - i);
        while(!valido) {
            printf("Introduce la fila y la columna inicial del barco (ejemplo: 0 1) \n");
            scanf("%d %d", &fila, &columna);
            printf("Introduce la orientación del barco ('H' para horizontal y 'V' para vertical)\n");
            scanf(" %c", &orientacion);

            if (orientacion == 'H' || orientacion == 'h') {
                orientacion = 'H';
            }   else if (orientacion == 'V' || orientacion == 'v') {
                orientacion = 'V';
                }   else {
                        printf("Error: Orientación no valida. Debes ingresar 'H' o 'V'. Vuelve a intentarlo \n");
                        continue;
                }

            valido = verificarEspacio(tablero, fila, columna, longitud, orientacion);   // Llamada a la función "verificarEspacio" para verificar que los espacios sean válidos

            if (valido == 1) {                                                          // Bucle para cuando el barco se coloca en un espacio válido
                for (int j = 0; j < longitud; j++) {
                    if (orientacion == 'H'){
                    tablero[fila][columna+j] = 'B';                                     // Si se elige la orientación horizontal, la fila se queda igual y va aumentando el valor de las columnas 
                    }   else if (orientacion == 'V'){
                        tablero[fila+j][columna] = 'B';                                 // Si se elige la orientación vertical, se aumenta el valor de las filas y la columna se queda igual
                    }
                }
                printf("Barco colocado correctamente\n");
                for (int j = 0; j < longitud; j++) {
                    if (orientacion == 'H') {
                        printf("Posición %d,%d\n", fila, columna + j);
                    } else if (orientacion == 'V') {
                        printf("Posición %d,%d\n", fila + j, columna);
                    }
                }
                printf("Estado actual del tablero:\n");
                mostrarTablero(tablero, true);
            }   else if (valido == -1) {                                                // Mensaje para cuando el barco NO se coloca en un espacio válido (error 1, fuera del tablero)
                printf("Error: Barco fuera de los límites. Intentalo de nuevo\n");    
            }   else if (valido == -2) {                                                // Mensaje para cuando el barco NO se coloca en un espacio válido (error 2, se solapa)
                printf("Error: Barco solapado con otro barco. Intentalo de nuevo\n");
            }
        }
    }
}

// Función para colocar los barcos de la máquina (inicializar semilla "rand" al principio del main)

void colocarBarMaq(char tablero[FILAS][COLUMNAS], int longitud, int cantidad) {
    for(int i = 0; i < cantidad; i++) {                                                 // Bucle para poner barcos hasta que se llegue a la cantidad de barcos que se piden
        int valido = 0;

        while (!valido) {
            int fila = rand() % FILAS;                                                  // Se genera un número aleatorio para seleccionar una fila
            int columna = rand () % COLUMNAS;                                           // Se genera un número aleatorio para seleccionar una columna
            char orientacion; 
            int aleatorio = rand() % 2;                                                 // Elige un número aleatorio entre 0 y 1 para decidir la orientación del barco
                if (aleatorio == 0) {
                    orientacion = 'H';
                }   else {
                    orientacion = 'V';
                }
            
            valido = verificarEspacio(tablero, fila, columna, longitud, orientacion);   // Llamada a la función "verificarEspacio" para verificar que los espacios sean válidos    

             if (valido == 1) {                                                         // Bucle para cuando el barco se coloca en un espacio válido
                for (int j = 0; j < longitud; j++) {
                    if (orientacion == 'H'){
                    tablero[fila][columna+j] = 'B';                                     // Si se elige la orientación horizontal, la fila se queda igual y va aumentando el valor de las columnas
                    }   else if (orientacion == 'V'){
                        tablero[fila+j][columna] = 'B';                                 // Si se elige la orientación vertical, se aumenta el valor de las filas y la columna se queda igual
                    }
                }
                printf("La maquina ha colocado sus barcos\n");                              // En este caso no hay errores ya que es la máquina quien los detecta automaticamente
            }
        }
    }
}

int main() {
    // Inicializa la semilla para generar números aleatorios
    srand(time(NULL));

    // Tableros para el jugador y la máquina
    char tableroJugador[FILAS][COLUMNAS];
    char tableroMaquina[FILAS][COLUMNAS];

    // Inicializa los tableros vacíos
    inicializarTablero(tableroJugador);
    inicializarTablero(tableroMaquina);

    // Mostrar menú del juego
    int opcion = menuJuego();

    if (opcion == 3) {
        // Si la opción es "Salir", termina el programa
        return 0;
    }

    if (opcion == 1) {

    // Colocación de los barcos
        printf("Coloca tus barcos:\n");
        colocarBarJug(tableroJugador, 4, NUM_PORTAVIONES, "Portaaviones");
        colocarBarJug(tableroJugador, 3, NUM_CRUCEROS, "Crucero");
        colocarBarJug(tableroJugador, 2, NUM_PATRULLERAS, "Patrullera");

        printf("La máquina está colocando sus barcos...\n");
        colocarBarMaq(tableroMaquina, 4, NUM_PORTAVIONES);
        colocarBarMaq(tableroMaquina, 3, NUM_CRUCEROS);
        colocarBarMaq(tableroMaquina, 2, NUM_PATRULLERAS);

    // Mostrar los tableros iniciales (opcional: oculta el tablero de la máquina)
        printf("\nTu tablero:\n");
        mostrarTablero(tableroJugador, true);

        printf("\nTablero de la máquina (oculto):\n");
        mostrarTablero(tableroMaquina, false);

    // Aquí puedes agregar la lógica del juego principal: disparos, turnos, y comprobaciones.
        printf("\n¡Ahora empieza el juego! Esta parte está pendiente de implementación.\n");
    
    }   else if (opcion == 2) {
        printf("La funcionalidad de mejores puntuaciones un no ha sido implementada.\n");
        }   

return 0;
}

// Función para colocar todos los barcos

// Función para atacar

// Función para el turno del jugador

// Función para el turno de la máquina

// Función para verificar e fin del juego

// Función para llevar un contador de turnos y almacenar las mejores puntuaciones

// Función main



