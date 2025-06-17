#include <stdio.h>
#include <stdlib.h>

#define JUGADORES "jugadores.dat"
#define PARTIDAS "partidas.dat"
#define RELACION "partidaXjugador.dat"

typedef struct {
int idJugador;
char nombre[30];
char apellido[30];
char email[50];
char username[30];
char password[20];
char dni[10];
int ptsTotales;
int eliminado; // 0 = activo, 1 = eliminado
} stJugador;

typedef struct {
int idPartida;
int dificultad;
int esContraCpu;
} stPartida;

typedef struct {
int idPartidaJugador;
int idPartida;
int idJugador;
int resultado; // 0 = pierde, 1 = gana, 2 = empate
int puntosJugador; // 3 = gana, 1 = empate y 0 = derrota
} stPartidaXJugador;


///Prototipados de las funciones:
int diagrama (int estadoActual, int iTransicion);

stJugador cargarJugador (char nombreArchivo[]);
char* establecerUsername (char nombreArchivo []);




int main()
{
 int estadoActual = 1;
 int iTransicion = 0;
 while (estadoActual != 0) {
    estadoActual = diagrama (estadoActual, iTransicion);
 }
}

int diagrama (int estadoActual, int iTransicion) {

    int opcionInicio = 0;
    int opcionPerfil = 0;
    int validacionUsuario = 0;
    char usuarioJugador [15];
    char passwordIngresado [15];

    switch (estadoActual) {

        case 1: //PRESENTACION
            system ("cls");
            printf ("--------------------------- \n");
            printf ("Bienvenido \n");
            printf ("    a \n");
            printf ("TA TE TI \n");
            printf ("--------------------------- \n");

            system ("pause");

            //Logica de transicion
            iTransicion = 2;    ///Transición a Menú principal

            //Transicion al siguiente estado
            switch (iTransicion) {
            case 2:
              estadoActual        = 2; //MENU PRINCIPAL
              break;
            }
        break; ///Fin case 1


        case 2: //MENU PRINCIPAL

            do {
            system ("cls");
            printf ("------------------------------------------- \n");
            printf ("             MENU PRINCIPAL \n");
            printf ("------------------------------------------- \n");
            printf ("\n");
            printf ("Seleccione opcion:\n");
            printf ("\n");
            printf ("1. INICIAR SESION\n");
            printf ("2. REGISTRARSE\n");
            printf ("3. SALIR \n");
            printf ("\n");
            printf ("\n");
            printf ("------------------------------------------- \n");
            scanf ("%i", &opcionInicio);

            } while (opcionInicio != 1 & opcionInicio != 2 &opcionInicio != 3 );

            //Logica de transicion y transicion al siguiente estado
            switch (opcionInicio) {
                case 1:
                        estadoActual  = 4;
                        break;
                case 2:
                        estadoActual  = 3;
                        break;
                case 3:
                        estadoActual  = 1;
                        break;
            }
        break; /// Fin case 2

        case 3: ///REGISTRARSE




        break; ///Fin case 3

        case 4: ///INICIAR SESION

            do {
            system ("cls");
            printf ("_______________________________________\n");
            printf ("            INICIO DE SESION\n");
            printf ("_______________________________________\n");
            printf ("Ingrese Usuario: \n");
            scanf (" %s", &usuarioJugador);
            ///printf ("%s \n", usuarioJugador);
            ///validar Usuario
            printf ("Ingrese Password: \n");
            scanf (" %s", &passwordIngresado);
            ///printf ("%s \n", passwordIngresado);
            ///validar Contraseña
            } while (validacionUsuario != 0);

            printf ("%s bienvenido al juego TA TE TI\n", usuarioJugador);
            system ("pause");

            ///Logica de transicion
            iTransicion = 5;

            ///Transicion al siguiente estado
            switch (iTransicion) {
                case 5:
                        estadoActual  = 5; ///PERFIL JUGADOR
                        break;
                case 2:
                        estadoActual  = 2; ///MENU PRINCIPAL
                        break;
            }


        break; ///Fin case 4

        case 5:
            system ("cls");
            printf ("_______________________________________\n");
            printf ("         HOLA %s \n", usuarioJugador);
            printf ("_______________________________________\n");
            printf ("1. MODIFICAR DATOS\n");
            printf ("2. VER ESTADISTICAS\n");
            printf ("3. JUGAR PARTIDA\n");
            printf ("0. CERRAR SESION\n");
            printf ("_______________________________________\n");
            scanf ("%i", &opcionPerfil);

            ///Logica de transición
            switch (opcionPerfil) {
                case 1:
                        estadoActual  = 6;
                        break;
                case 2:
                        estadoActual  = 7;
                        break;
                case 3:
                        estadoActual  = 8;
                        break;
                case 0:
                        estadoActual = 2;
                        break;

            }

        break;




    }


    return estadoActual;
}

stJugador cargarJugador (char nombreArchivo[]) {

    stJugador jugadorNuevo;
    char emailTentativo[50];
    char passwordTentativo[50];

    printf ("Ingrese nombre del jugador: \n");
    scanf (" %s", &jugadorNuevo.nombre);

    printf ("Ingrese apellido del jugador: \n");
    scanf (" %s", &jugadorNuevo.apellido);

    printf ("Ingrese email del jugador: \n");
    scanf (" s", &emailTentativo);

    strcpy(jugadorNuevo.username, establecerUsername (nombreArchivo)); /// Solicita y valida nombre de usuario

    printf ("Ingrese password del jugador: \n");
    scanf (" s", &passwordTentativo);

    jugadorNuevo.ptsTotales = 0;
    jugadorNuevo.eliminado = 1;

    return jugadorNuevo;
}

char* establecerUsername (char nombreArchivo []) {

    stJugador jugador;
    char usernameTentativo[30];
    char usernameValidado[30];

    int validacionUsername = 0;

    FILE *archi = fopen (nombreArchivo, "rb");

    do {
        printf ("Ingrese username del jugador: \n");
        scanf (" s", &usernameTentativo);

        if (archi) {
            while (fread(&jugador, sizeof(stJugador), 1, archi)>0 & validacionUsername == 0 ){
                if (strcmp(usernameTentativo, jugador.username) == 0){
                    validacionUsername = 1;
                }
            }
            fclose (archi);
        }
    } while (validacionUsername != 0);

    strcpy(usernameValidado, usernameTentativo);

    return usernameValidado; ///Deberia retornar directamente usernametentativo?
}
