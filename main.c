#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define JUGADORES "jugadores.dat"
#define PARTIDA "partidas.dat"
#define RELACION "partidaXjugador.dat"
#define ESC 27

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
int idPartidaJugador;
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
int diagrama (int estadoActual, char nombreArchivoJugadores[], stJugador arregloJugadores[], int *validosJugadores, char nombreArchivoPartida[], stPartida arregloPartida[], int *validosPartida, char nombreArchivoPartidaXJugador[], stPartidaXJugador arregloPxJ[], int *validosPxJ);

///Funciones de cada estado
///1.Presentacion
int mainEstadoPresentacion (int estadoActual);

///2. Cargar Informacion
int mainEstadoCargarInformacion (int estadoActual, char nombreArchivoJugadores[],stJugador arregloJugadores[], int *validosJugadores, char nombreArchivoPartida[], stPartida arregloPartida[], int *validosPartida, char nombreArchivoPartidaXJugador[], stPartidaXJugador arregloPxJ[], int * validosPxJ);
int mainEstadoDescargarInformacion (int estadoActual, char nombreArchivoJugadores[], stJugador arregloJugadores[], int *validosJugadores, char nombreArchivoPartida[], stPartida arregloPartida[], int *validosPartida, char nombreArchivoPartidaXJugador[], stPartidaXJugador arregloPxJ[], int *validosPxJ);

///3. Descargar Informacion
int mainEstadoDescargarInformacion (int estadoActual, char nombreArchivoJugadores[], stJugador arregloJugadores[], int *validosJugadores, char nombreArchivoPartida[], stPartida arregloPartida[], int *validosPartida, char nombreArchivoPartidaXJugador[], stPartidaXJugador arregloPxJ[], int *validosPxJ);

///4. Menu Principal
int mainEstadoMenuPrincipal (int estadoActual);

///5.Registrarse
int mainEstadoRegistrarse (int estadoActual, stJugador arregloJugadores[], int *validosJugadores);
stJugador cargarJugador (stJugador arregloJugadores[], int *validosJugadores, int aux);
char* establecerEmail (stJugador arregloJugadores[], int validosJugadores, int aux);
char* establecerUsername (stJugador arregloJugadores[], int validosJugadores, int aux);
char* establecerPassword ();


///6.Iniciar Sesion
int mainEstadoIniciarSesion (int estadoActual, stJugador arregloJugadores[], int *validosJugadores, int *idJugadorUsuario) ;

///7.Perfil Jugador
int mainEstadoPerfilJugador (int estadoActual, stJugador arregloJugadores[], int *idJugadorUsuario) ;


///10. Jugar Partida
int mainEstadoJugarPartida (int estadoActual, stJugador arregloJugadores[], int *idJugadorUsuario);

///16. MODO DOS JUGADORES
int mainEstadoJugarPartidaDosJugadores (int estadoActual, stJugador arregloJugadores[], int *validosJugadores, int *idJugadorUsuario, int *idJugadorInvitado, stPartida arregloPartidas[], int *validosPartida, stPartidaXJugador arregloPartidaXJugador[], int *validosPxJ);
void iniciarSesionInvitado (stJugador arregloJugadores[], int *validosJugadores, int *idJugadorUsuario, int *idJugadorInvitado);
void partida(stJugador arregloJugadores [], int *idJugadorUsuario, int *idJugadorInvitado, stPartida arregloPartida[], int *validosPartida, stPartidaXJugador arregloPxJ[], int *validosPxJ);
void ingresoJugada (char matrix [3][3],int arregloJugadasO[], int *validosO,int arregloJugadasX[], int *validosX, char idJugador, char nombreJugador []);
int buscarPosicionFila (int posicion);
int buscarPosicionColumna (int posicion);
int verificacionJugada (int posicion, int arregloJugadasX[], int *validosX, int arregloJugadasO[], int *validosO);

int verificarIfGanador(int arr[], int v, int posA, int posB, int posC);
int verificarVictoria(int arr[],int v);
char ganadorPartida(int arrX[], int arrO[], int vX, int vO);
int mostrarGanador(char ganador);

void mostrarMatrix (char matrix [3][3]);


///Otros
int mostrarArreglo (int estadoActual, stJugador arregloJugadores[], int *validosJugadores) ;
void mostrarJugador (stJugador jugador);


int main()
{
 int estadoActual = 1;

 stJugador arregloJugadores[15];
 int validosJugadores = 0;

  stPartida arregloPartida[15];
 int validosPartida = 0;

  stPartidaXJugador arregloPxJ[15];
 int validosPxJ = 0;

 while (estadoActual != 0) {
    estadoActual = diagrama (estadoActual, JUGADORES, arregloJugadores, &validosJugadores, PARTIDA,  arregloPartida, &validosPartida, RELACION, arregloPxJ, &validosPxJ); ///Paso direccion de validos
 }
}

int diagrama (int estadoActual, char nombreArchivoJugadores[], stJugador arregloJugadores[], int *validosJugadores, char nombreArchivoPartida[],stPartida arregloPartida[], int *validosPartida, char nombreArchivoPartidaXJugador[], stPartidaXJugador arregloPxJ[], int *validosPxJ) {

    int idJugadorUsuario;
    int idJugadorInvitado;

    switch (estadoActual) {

        case 1: ///PRESENTACION

            estadoActual = mainEstadoPresentacion (estadoActual); ///ValidosJugadores es direccion
            break; ///Fin case 1

        case 2: ///CARGAR INFORMACION
            estadoActual = mainEstadoCargarInformacion (estadoActual,nombreArchivoJugadores,arregloJugadores,validosJugadores, nombreArchivoPartida, arregloPartida, validosPartida, nombreArchivoPartidaXJugador, arregloPxJ, validosPxJ); ///ValidosJugadores es direccion
            break; ///Fin case 2

        case 3: ///DESCARGAR INFORMACION
            estadoActual = mainEstadoDescargarInformacion (estadoActual,nombreArchivoJugadores,arregloJugadores,validosJugadores, nombreArchivoPartida, arregloPartida, validosPartida, nombreArchivoPartidaXJugador, arregloPxJ, validosPxJ); ///ValidosJugadores es direccion
            break; ///Fin case 2

        case 4: ///MENU PRINCIPAL
            estadoActual = mainEstadoMenuPrincipal(estadoActual);
            break; /// Fin case 3

        case 5: ///REGISTRARSE
            estadoActual = mainEstadoRegistrarse (estadoActual,arregloJugadores,validosJugadores);    ///ValidosJugadores es direccion
            break; ///Fin case 4

        case 6: ///INICIAR SESION
            estadoActual = mainEstadoIniciarSesion(estadoActual, arregloJugadores, validosJugadores, &idJugadorUsuario);       ///ValidosJugadores es direccion
            break; ///Fin case 5

        case 7: ///PERFIL JUGADOR
            estadoActual = mainEstadoPerfilJugador(estadoActual, arregloJugadores, &idJugadorUsuario);
            break;

        case 10: ///JUGAR PARTIDA
            estadoActual = mainEstadoJugarPartida (estadoActual,arregloJugadores, &idJugadorUsuario);
            break;

        case 16: ///MODO DOS JUGADORES
            estadoActual = mainEstadoJugarPartidaDosJugadores (estadoActual,arregloJugadores,validosJugadores, &idJugadorUsuario, &idJugadorInvitado, arregloPartida, validosPartida, arregloPxJ, validosPxJ);
            break;

        case 99: ///VER ARREGLO
            estadoActual = mostrarArreglo (estadoActual,arregloJugadores, validosJugadores);        ///ValidosJugadores es direccion
            break;
    }

    return estadoActual;
}

///1. Funciones Estado PRESENTACION

int mainEstadoPresentacion(int estadoActual) {

    char cTransicion;

    system("cls");
    printf("__________________________ \n");
    printf("Bienvenido \n");
    printf("    a \n");
    printf("TA TE TI \n");
    printf("__________________________ \n");

    printf("Presione una tecla... <S: Salir>) \n");

    cTransicion = getch();

    if (cTransicion == 'S' || cTransicion == 's') {
        estadoActual = 0;  // Sale de la consola
    } else {
        estadoActual = 2;  // Transición a estado 2: CARGAR INFORMACION
    }

    return estadoActual;
}

///2. Funciones Estado CARGAR INFORMACION

int mainEstadoCargarInformacion (int estadoActual, char nombreArchivoJugadores[], stJugador arregloJugadores[], int *validosJugadores, char nombreArchivoPartida[], stPartida arregloPartida[], int *validosPartida, char nombreArchivoPartidaXJugador[], stPartidaXJugador arregloPxJ[], int * validosPxJ) {


            stJugador jugador;
            stPartida partida;
            stPartidaXJugador partidaXJugador;

            void deArchivoAArreglo (nombreArchivo, nombreArreglo, validos);

            ///Carga de informacion desde archivo JUGADORES a arregloJugadores

            FILE *archi = fopen (nombreArchivoJugadores, "rb");
            if (archi) {  ///Si el archivo existe carga la informacion en un arreglo
                            while (fread (&jugador, sizeof (stJugador), 1, archi)) {
                                arregloJugadores[*validosJugadores] = jugador;
                                (*validosJugadores)++;
                            }
                            fclose (archi);

                            ///Logica de transicion
                            estadoActual = 4; ///Transición a estado 3: MENU PRINCIPAL
                            system ("cls");
                            printf ("*** Cargando datos del juego ***  \n");
                            system ("pause");

            } else {        ///Si el archivo no existe registra al primer jugador en el archivo
                            system ("cls");
                            printf ("___________________________________________________\n");
                            printf ("                 ATENCION \n");
                            printf ("___________________________________________________\n");
                            printf ("No hay archivos creados \n");
                            printf ("Se cargara al primer jugador del sistema \n");
                            FILE *archi = fopen (nombreArchivoJugadores, "wb");

                            if (archi) {
                                ///Crear primer jugador del archivo
                                jugador = cargarJugador (arregloJugadores, validosJugadores, 0);
                                jugador.idJugador = 1;
                                fwrite (&jugador, sizeof(stJugador), 1, archi);
                                fclose (archi);
                            }

                            //Logica de transicion
                            estadoActual = 2;    ///Transicion a estado 2: CARGAR INFORMACION
            }


            ///Carga de informacion desde archivo PARTIDAS a arregloPartida - Actulizara el valor de validosPartida
            FILE *archi2 = fopen (nombreArchivoPartida, "rb");
            if (archi2) {  ///Si el archivo existe carga la informacion en un arreglo
                            while (fread (&partida, sizeof (stPartida), 1, archi2)) {
                                arregloPartida[*validosPartida] = partida;
                                (*validosPartida)++;
                            }
                            fclose (archi);
            } ///Si el archivo no existe, es creado luego de hacer la descarga arreglo a archivo

            ///Carga de informacion desde archivo PARTIDASxJUGADOR a arregloPxJ - Actulizara el valor de validosPxJ
            FILE *archi3 = fopen (nombreArchivoPartidaXJugador, "rb");
            if (archi3) {  ///Si el archivo existe carga la informacion en un arreglo
                            while (fread (&partidaXJugador, sizeof (stPartidaXJugador), 1, archi3)) {
                                arregloPxJ[*validosPxJ] = partidaXJugador;
                                (*validosPxJ)++;
                            }
                            fclose (archi);
            } ///Si el archivo no existe, es creado luego de hacer la descarga arreglo a archivo

            return estadoActual;
}

///3. Funciones Estado DESCARGAR INFORMACION

int mainEstadoDescargarInformacion (int estadoActual, char nombreArchivoJugadores[], stJugador arregloJugadores[], int *validosJugadores, char nombreArchivoPartida[], stPartida arregloPartida[], int *validosPartida, char nombreArchivoPartidaXJugador[], stPartidaXJugador arregloPxJ[], int *validosPxJ) {


            stJugador jugador;
            stPartida partida;
            stPartidaXJugador partidaXJugador;

            ///Descarga de informacion de jugadores:  Desde arregloJugadores a archivo JUGADORES

            FILE *archi = fopen (nombreArchivoJugadores, "wb"); ///Se reescribe archivo con los nuevos datos
            if (archi) {  ///Si el archivo existe descarga la informacion en un arreglo
                    for (int i = 0; i < (*validosJugadores); i++ ) {
                        jugador = arregloJugadores[i];
                        fwrite (&jugador, sizeof (stJugador), 1, archi);
                    }
                    fclose (archi);
            }

            (*validosJugadores) = 0;


            ///Descarga de informacion de partidas:  Desde arregloPartida a archivo PARTIDA

            FILE *archi2 = fopen (nombreArchivoPartida, "wb"); ///Se reescribe archivo con los nuevos datos
            if (archi2) {  ///Si el archivo existe descarga la informacion en un arreglo
                    for (int i = 0; i < (*validosPartida); i++ ) {
                        partida = arregloPartida[i];
                        fwrite (&partida, sizeof (stPartida), 1, archi);
                    }
                    fclose (archi2);
            }

            (*validosPartida) = 0;

            ///Descarga de informacion de partidasXJugador:  Desde arregloPxJ a archivo PartidaXJugador

            FILE *archi3 = fopen (nombreArchivoPartidaXJugador, "wb"); ///Se reescribe archivo con los nuevos datos
            if (archi2) {  ///Si el archivo existe descarga la informacion en un arreglo
                    for (int i = 0; i < (*validosPxJ); i++ ) {
                        partidaXJugador = arregloPxJ[i];
                        fwrite (&partidaXJugador, sizeof (stPartidaXJugador), 1, archi);
                    }
                    fclose (archi3);
            }

            (*validosPxJ) = 0;


            printf ("*** Descargando datos del juego a archivo... ****\n");
            system ("pause");

            ///Logica de transicion
            estadoActual = 1; ///Transición a estado 1: PRESENTACION

            return estadoActual;
}

///4. Funciones Estado MENU PRINCIPAL
int mainEstadoMenuPrincipal (int estadoActual) {

        char opcionInicio = 0;

        do {
        system ("cls");
        printf ("___________________________________________ \n");
        printf ("             MENU PRINCIPAL \n");
        printf ("___________________________________________ \n");
        printf ("\n");
        printf ("Seleccione opcion:\n");
        printf ("\n");
        printf ("1. INICIAR SESION\n");
        printf ("2. REGISTRARSE\n");
        printf ("3. VER ARREGLO DE JUGADORES\n");
        printf ("4. SALIR \n");
        printf ("\n");
        printf ("\n");
        printf ("___________________________________________ \n");

        ///scanf ("%i", &opcionInicio);
        opcionInicio = getch();

        } while (opcionInicio != '1' && opcionInicio != '2' && opcionInicio != '3' && opcionInicio != '4');

        //Logica de transicion y transicion al siguiente estado
        switch (opcionInicio) {
            case '1':
                    estadoActual  = 6; ///INICIAR SESION
                    break;
            case '2':
                    estadoActual  = 5; ///REGISTRARSE
                    break;
            case '3':
                    estadoActual  = 99; ///VER ARREGLO DE JUGADORES
                    break;
            case '4':
                    estadoActual  = 3; ///DESCARGAR INFORMACION EN ARCHIVO
                    break;
        }

        return estadoActual;
}

///5. Funciones Estado REGISTRARSE

int mainEstadoRegistrarse (int estadoActual, stJugador arregloJugadores[], int *validosJugadores) {

    stJugador jugadorNuevo;

    system ("cls");
    printf ("___________________________________________ \n");
    printf ("             REGISTRO \n");
    printf ("___________________________________________ \n");
    printf ("\n");
    printf ("Ingrese datos del nuevo jugador \n");

    jugadorNuevo = cargarJugador (arregloJugadores, validosJugadores, 1);
    jugadorNuevo.idJugador = (*validosJugadores)+1;



    system ("cls");
    printf ("DATOS DEL NUEVO JUGADOR : \n");
    mostrarJugador (jugadorNuevo);
    arregloJugadores[*validosJugadores]=jugadorNuevo;
    (*validosJugadores)++;

    system ("pause");


    //Logica de transicion
    estadoActual = 6;    ///Transición a INICIAR SESION

    return estadoActual;
}

stJugador cargarJugador (stJugador arregloJugadores[], int *validosJugadores, int aux) {

    stJugador jugadorNuevo;
    char emailTentativo[50];
    char passwordTentativo[50];

    printf ("Ingrese nombre: \n");
    scanf (" %s", &jugadorNuevo.nombre);

    printf ("Ingrese apellido: \n");
    scanf (" %s", &jugadorNuevo.apellido);

    strcpy(jugadorNuevo.email, establecerEmail (arregloJugadores, *validosJugadores, aux)); /// Solicita y valida nombre de usuario

    strcpy(jugadorNuevo.username, establecerUsername (arregloJugadores, *validosJugadores, aux)); /// Solicita y valida nombre de usuario

    strcpy(jugadorNuevo.password, establecerPassword ()); /// Solicita y valida password

    printf ("Ingrese DNI: \n");
    scanf (" %s", &jugadorNuevo.dni);

    jugadorNuevo.ptsTotales = 0;
    jugadorNuevo.eliminado = 0;
    jugadorNuevo.idPartidaJugador = 0;

    return jugadorNuevo;
}

///5.1 Validacion Email (@, ".com", unico)
char* establecerEmail (stJugador arregloJugadores[], int validosJugadores, int aux) {

    stJugador jugador;
    char email[50];

    int longitudEmail = 0;

    int condicionArroba = 0;
    int condicionPuntoCom = 0;
    int condicionUnico = 0;

    int validacionEmail = 0; ///1:Validado, 0:No Validado

    int i = 0;

    do {
        condicionArroba = 0;   ///Inicia no validado
        condicionPuntoCom = 0; ///Inicia no validado
        condicionUnico = 1;    ///Inicia validado


        printf ("Ingrese email (Debe contener @ y finalizar con .com): \n");
        scanf (" %s", &email);

        longitudEmail = strlen(email);

        if (longitudEmail > 5) {

                ///Condicion Arroba:
                i = 0;
                while (i < (longitudEmail - 4)) {
                    if (email[i] == '@') {
                        condicionArroba = 1; ///Valida condicion arroba
                    }
                    i = i + 1;
                }

                i=0;
                ///Condicion ".com":
                if (email[longitudEmail - 4] == '.' &&
                    email[longitudEmail - 3] == 'c' &&
                    email[longitudEmail - 2] == 'o' &&
                    email[longitudEmail - 1] == 'm') {
                        condicionPuntoCom = 1; ///Valida condicion ".com"
                }

                if (aux == 1) {
                    ///Condicion unicidad:
                    while (i < (validosJugadores) && condicionPuntoCom == 1) {
                        if (strcmp(email, arregloJugadores[i].email) == 0){
                            condicionUnico = 0; ///Si detecta email repetido sale del lazo while
                        }
                        i = i + 1;
                    }
                    i=0;
                }

                if (condicionArroba == 1 && condicionPuntoCom == 1 && condicionUnico == 1){
                    validacionEmail = 1; ///Si se verifican las 3 condiciones, se valida el mail
                }
        }
    } while (validacionEmail != 1);
    return strdup(email);
}

///5.2 Validacion Usuario (Unico)
char* establecerUsername (stJugador arregloJugadores[], int validosJugadores, int aux) {

    stJugador jugador;
    char usernameTentativo[30];

    int validacionUsername = 1; ///1:Validado, 0:No Validado

    int i = 0;

    do {
        ///printf("Validos %i \n", validosJugadores);
        printf ("Ingrese username: \n");
        scanf (" %s", usernameTentativo);

        if (aux == 1) {
            validacionUsername = 1;
            i = 0;
            while (i < validosJugadores && validacionUsername ==1){
                    if (strcmp(usernameTentativo, arregloJugadores[i].username) == 0){
                        validacionUsername = 0;
                    }
                    i = i + 1;
            }
        }
    } while (validacionUsername != 1);

    return strdup(usernameTentativo);; ///Deberia retornar directamente usernameTentativo?
}

///5.3 Validacion contraseña (1 min, 1 MAY)
char* establecerPassword () {

    char password[30];

    int condicionMinuscula = 0;
    int condicionMayuscula = 0;

    int validacionPassword = 0; ///1:Validado, 0:No Validado
    int i = 0;

    do {
        condicionMinuscula = 0;
        condicionMayuscula = 0;

        printf ("Ingrese password (debe contener al menos una letra minuscula y una letra mayuscula): \n");
        scanf (" %s", &password); ///passwordTentativo = arreglo de caracteres

        i = 0;

        while (password[i] != '\0' && validacionPassword == 0) {
            if (password[i]>= 'a' && password[i] <= 'z') {
                condicionMinuscula = 1; ///Valida condicion minuscula
            }
            if (password[i]>= 'A' && password[i] <= 'Z') {
                condicionMayuscula = 1; ///Valida condicion MAYUSCULA
            }

            i = i + 1;

            if (condicionMinuscula == 1 && condicionMayuscula ==1 ) { ///Si se verifican las 2 condiciones, se valida el password
                validacionPassword = 1;
            }
        }
    } while (validacionPassword != 1);

    return strdup(password);
}

///FUNCIONES ESTADO 6: INICIAR SESION

int mainEstadoIniciarSesion (int estadoActual, stJugador arregloJugadores[], int *validosJugadores, int *idJugadorUsuario) {

        int validacionUsuario = 0; ///1: Validado, 0: No validado
        int iTransicion = 0;

        char usuarioIngresado [15];
        char passwordIngresado [15];
        int i = 0;

        do {
            system ("cls");
            printf ("_______________________________________\n");
            printf ("            INICIO DE SESION\n");
            printf ("_______________________________________\n");

            printf ("Ingrese Usuario  (<s: Salir>): \n");
            scanf (" %s", &usuarioIngresado);


            i = 0;
            while ((i < *validosJugadores && validacionUsuario == 0) &&   strcmp(usuarioIngresado, "s") != 0) {
                if (strcmp(usuarioIngresado, arregloJugadores[i].username) == 0) { ///Valida username ingresado
                    printf ("Ingrese Password: \n");
                    scanf (" %s", &passwordIngresado);
                    if (strcmp(passwordIngresado, arregloJugadores[i].password) == 0)  { ///Valida password ingresado
                        validacionUsuario = 1;
                        (*idJugadorUsuario) = arregloJugadores[i].idJugador;
                    } else {
                        printf ("Password incorrecto, intente nuevamente \n");
                        system ("pause");
                        break;

                    }
                } else {
                    if (i == *validosJugadores - 1 && validacionUsuario == 0) {
                        printf ("El usuario no existe, intente nuevamente \n");
                        system ("pause");
                    }
                }
                i = i + 1;
            }

        } while (validacionUsuario != 1 && strcmp(usuarioIngresado, "s") != 0);

        if (strcmp(usuarioIngresado, "s") != 0) {
            system ("cls");
            printf ("%s bienvenido al juego TA TE TI\n", usuarioIngresado);
            system ("pause");

            ///Logica de transicion
            iTransicion = 7;    ///Transicion a PERFIL JUGADOR
        } else {
            ///Logica de transicion
            iTransicion = 4;    ///Transicion a MENU PRINCIPAL

        }
        ///Transicion al siguiente estado
        switch (iTransicion) {
            case 7:
                    estadoActual  = 7; ///PERFIL JUGADOR
                    break;
            case 4:
                    estadoActual  = 4; ///MENU PRINCIPAL
                    break;
        }

        return estadoActual;
}

///Funciones estado 7: PERFIL JUGADOR
int mainEstadoPerfilJugador (int estadoActual, stJugador arregloJugadores[], int *idJugadorUsuario) {

        char opcionPerfil = 0;

        do {
        system ("cls");
        printf ("_______________________________________\n");
        printf ("         HOLA %s \n", arregloJugadores[*idJugadorUsuario-1].nombre);
        printf ("_______________________________________\n");
        printf ("1. MODIFICAR DATOS\n");
        printf ("2. VER ESTADISTICAS\n");
        printf ("3. JUGAR PARTIDA\n");
        printf ("4. CERRAR SESION\n");
        printf ("_______________________________________\n");

        opcionPerfil = getch();

        } while (opcionPerfil != '1' && opcionPerfil != '2' && opcionPerfil != '3' && opcionPerfil != '4');

        ///Logica de transición
        switch (opcionPerfil) {
            case '1':
                    estadoActual  = 8; ///MODIFICAR DATOS
                    break;
            case '2':
                    estadoActual  = 9;  ///ESTADISTICAS
                    break;
            case '3':
                    estadoActual  = 10;      ///JUGAR PARTIDA
                    break;
            case '4':
                    estadoActual = 4;   ///MENU PRINCIPAL
                    (*idJugadorUsuario)=0;
                    break;
        }

        return estadoActual;
}

///Funciones estado 10: JUGAR PARTIDA
int mainEstadoJugarPartida (int estadoActual, stJugador arregloJugadores[], int *idJugadorUsuario) {

        char opcionNroJugadores = '3';

        do {
        system("cls");
        printf ("_______________________________________\n");
        printf ("         NUEVA PARTIDA \n");
        printf ("_______________________________________\n");
        printf ("1. UN JUGADOR\n");
        printf ("2. DOS JUGADORES\n");
        printf ("3. SALIR\n");
        printf ("_______________________________________\n");

        opcionNroJugadores = getch();

        } while (opcionNroJugadores != '1' && opcionNroJugadores != '2' && opcionNroJugadores!= '3');

        ///Logica de transición
        switch (opcionNroJugadores) {
            case '1':
                    estadoActual  = 15; ///MODO UN JUGADOR
                    break;
            case '2':
                    estadoActual  = 16;  ///MODO DOS JUGADORES
                    break;
            case '3':
                    estadoActual  = 7;      ///JUGAR PARTIDA
                    break;
        }

        return estadoActual;
}

///Funciones estado 15: MODO UN JUGADOR
int mainEstadoJugarPartidaUnJugador (int estadoActual, stJugador arregloJugadores[],int *validosJugadores,  int *idJugadorUsuario) {


}


///Funciones estado 16: MODO DOS JUGADORES
int mainEstadoJugarPartidaDosJugadores (int estadoActual, stJugador arregloJugadores[], int *validosJugadores, int *idJugadorUsuario, int *idJugadorInvitado, stPartida arregloPartida[], int *validosPartida, stPartidaXJugador arregloPartidaXJugador[], int *validosPxJ) {

        char opcionRevancha = 'N';

        iniciarSesionInvitado (arregloJugadores, validosJugadores, idJugadorUsuario, idJugadorInvitado);
        printf ("ID INVITADO: %i", (*idJugadorInvitado));



        do {

        arregloPartida[*validosPartida].idPartida = (*validosPartida) + 1;
        arregloPartida[*validosPartida].dificultad = 0; ///No hay dificultad en modo 2 jugadores
        arregloPartida[*validosPartida].esContraCpu = 0; ///Modo 2 jugadores
        arregloJugadores[*idJugadorUsuario].idPartidaJugador =  arregloJugadores[*idJugadorUsuario].idPartidaJugador + 1;
        arregloJugadores[*idJugadorInvitado].idPartidaJugador =  arregloJugadores[*idJugadorInvitado].idPartidaJugador + 1;

        (*validosPartida) = (*validosPartida) + 1; ///Actualiza valor de validos;


        partida(arregloJugadores, idJugadorUsuario, idJugadorInvitado, arregloPartida, validosPartida, arregloPartidaXJugador, validosPxJ); ///Se debe usar [(*validosPartida) + 1] para obtener el idPartida actual

        system("pause");
        system("cls");
        printf ("DESEA JUGAR REVANCHA <y/n>?");
        opcionRevancha = getch();

        } while (opcionRevancha != 'n' && opcionRevancha != 'N');

        estadoActual  = 10;      ///MENU JUGAR PARTIDA

        return estadoActual;

}

void partida(stJugador arregloJugadores [], int *idJugadorUsuario, int *idJugadorInvitado, stPartida arregloPartida[], int *validosPartida, stPartidaXJugador arregloPartidaXJugador[], int *validosPxJ)
{

    char Tablero [3][3] = {'7', '8', '9', '4', '5', '6', '1', '2', '3'};
    int arregloJugadasX [8];
    int validosX=0;
    int arregloJugadasO [8];
    int validosO=0;
    char idJugador = 'N';
    int win=0;
    int jugadas=0;

    mostrarMatrix(Tablero);
    while(win==0 && jugadas<9)
    {
        idJugador = 'X';
        ingresoJugada (Tablero,arregloJugadasO,&validosO,arregloJugadasX,&validosX, idJugador, arregloJugadores[*idJugadorUsuario-1].nombre);
        jugadas++;

        win=mostrarGanador(ganadorPartida(arregloJugadasX, arregloJugadasO, validosX, validosO)); /// Si win = 1: Jugador Usuario (X) gana

        if (win ==1) {

                ///Carga de informacion en arreglo (Ganador):
                printf ("GANADOR \n");
                arregloPartidaXJugador[*validosPxJ].idPartida = arregloPartida[*validosPartida - 1].idPartida;
                printf ("id Partida: %i \n", arregloPartidaXJugador[*validosPxJ].idPartida);

                arregloPartidaXJugador[*validosPxJ].idPartidaJugador = arregloJugadores[*idJugadorUsuario].idPartidaJugador;
                printf ("id PartidaJugador: %i \n", arregloPartidaXJugador[*validosPxJ].idPartidaJugador);

                arregloPartidaXJugador[*validosPxJ].idJugador = (*idJugadorUsuario);
                printf ("id Jugador: %i \n", arregloPartidaXJugador[*validosPxJ].idJugador);

                arregloPartidaXJugador[*validosPxJ].resultado = 1;
                printf ("Resultado partida: %i \n", arregloPartidaXJugador[*validosPxJ].resultado);

                arregloPartidaXJugador[*validosPxJ].puntosJugador = 3;
                printf ("Puntos obtenidos en partida: %i \n", arregloPartidaXJugador[*validosPxJ].puntosJugador);
                arregloJugadores[*idJugadorUsuario-1].ptsTotales = arregloJugadores[*idJugadorUsuario-1].ptsTotales + 3;

                (*validosPxJ) = (*validosPxJ) + 1;

                ///Carga de informacion en arreglo (Perdedor):
                printf ("PERDEDOR \n");
                arregloPartidaXJugador[*validosPxJ].idPartida = arregloPartida[*validosPartida - 1].idPartida;
                printf ("id Partida: %i \n", arregloPartidaXJugador[*validosPxJ].idPartida);

                arregloPartidaXJugador[*validosPxJ].idPartidaJugador = arregloJugadores[*idJugadorInvitado].idPartidaJugador;
                printf ("id PartidaJugador: %i \n", arregloPartidaXJugador[*validosPxJ].idPartidaJugador);


                arregloPartidaXJugador[*validosPxJ].idJugador = (*idJugadorInvitado);
                printf ("id Jugador: %i \n", arregloPartidaXJugador[*validosPxJ].idJugador);

                arregloPartidaXJugador[*validosPxJ].resultado = 0;
                printf ("Resultado partida: %i \n", arregloPartidaXJugador[*validosPxJ].resultado);

                arregloPartidaXJugador[*validosPxJ].puntosJugador = 0;
                printf ("Puntos obtenidos en partida: %i \n", arregloPartidaXJugador[*validosPxJ].puntosJugador);
                arregloJugadores[*idJugadorInvitado-1].ptsTotales = arregloJugadores[*idJugadorInvitado-1].ptsTotales + 0;

                (*validosPxJ) = (*validosPxJ) + 1;
        }


        if(jugadas<9 && win != 1)
        {
            idJugador = 'O';
            ingresoJugada (Tablero,arregloJugadasO,&validosO,arregloJugadasX,&validosX, idJugador, arregloJugadores[*idJugadorInvitado-1].nombre);
            jugadas++;
            win=mostrarGanador(ganadorPartida(arregloJugadasX, arregloJugadasO, validosX, validosO)); /// Si win = 1: Jugador Usuario (O) gana

            if (win == 1) {
                    ///Carga de informacion en arreglo (Perdedor):
                    printf ("GANADOR \n");
                    arregloPartidaXJugador[*validosPxJ].idPartida = arregloPartida[*validosPartida - 1].idPartida;
                    printf ("id Partida: %i \n", arregloPartidaXJugador[*validosPxJ].idPartida);

                    arregloPartidaXJugador[*validosPxJ].idPartidaJugador = arregloJugadores[*idJugadorUsuario].idPartidaJugador;
                    printf ("id PartidaJugador: %i \n", arregloPartidaXJugador[*validosPxJ].idPartidaJugador);

                    arregloPartidaXJugador[*validosPxJ].idJugador = (*idJugadorUsuario);
                    printf ("id Jugador: %i \n", arregloPartidaXJugador[*validosPxJ].idJugador);

                    arregloPartidaXJugador[*validosPxJ].resultado = 0;
                    printf ("Resultado partida: %i \n", arregloPartidaXJugador[*validosPxJ].resultado);

                    arregloPartidaXJugador[*validosPxJ].puntosJugador = 0;
                    printf ("Puntos obtenidos en partida: %i \n", arregloPartidaXJugador[*validosPxJ].puntosJugador);

                    arregloJugadores[*idJugadorUsuario-1].ptsTotales = arregloJugadores[*idJugadorUsuario-1].ptsTotales + 0;

                    (*validosPxJ) = (*validosPxJ) + 1;

                    ///Carga de informacion en arreglo (Ganador):
                    printf ("PERDEDOR \n");
                    arregloPartidaXJugador[*validosPxJ].idPartida = arregloPartida[*validosPartida - 1].idPartida;
                    printf ("id Partida: %i \n", arregloPartidaXJugador[*validosPxJ].idPartida);

                    arregloPartidaXJugador[*validosPxJ].idPartidaJugador = arregloJugadores[*idJugadorInvitado].idPartidaJugador;
                    printf ("id PartidaJugador: %i \n", arregloPartidaXJugador[*validosPxJ].idPartidaJugador);


                    arregloPartidaXJugador[*validosPxJ].idJugador = (*idJugadorInvitado);
                    printf ("id Jugador: %i \n", arregloPartidaXJugador[*validosPxJ].idJugador);

                    arregloPartidaXJugador[*validosPxJ].resultado = 1;
                    printf ("Resultado partida: %i \n", arregloPartidaXJugador[*validosPxJ].resultado);

                    arregloPartidaXJugador[*validosPxJ].puntosJugador = 3;
                    printf ("Puntos obtenidos en partida: %i \n", arregloPartidaXJugador[*validosPxJ].puntosJugador);

                    arregloJugadores[*idJugadorInvitado-1].ptsTotales = arregloJugadores[*idJugadorInvitado-1].ptsTotales + 3;

                    (*validosPxJ) = (*validosPxJ) + 1;
                    }
        }
    }
    if (win == 0 && jugadas == 9)
    {
        system("cls");
        mostrarMatrix(Tablero);
        printf("\nEMPATE\n\n");

        ///Carga de informacion en arreglo
        printf ("USUARIO\n");
        arregloPartidaXJugador[*validosPxJ].idPartida = arregloPartida[*validosPartida - 1].idPartida;
        printf ("id Partida: %i \n", arregloPartidaXJugador[*validosPxJ].idPartida);

        arregloPartidaXJugador[*validosPxJ].idPartidaJugador = arregloJugadores[*idJugadorUsuario].idPartidaJugador;
        printf ("id PartidaJugador: %i \n", arregloPartidaXJugador[*validosPxJ].idPartidaJugador);

        arregloPartidaXJugador[*validosPxJ].idJugador = (*idJugadorUsuario);
        printf ("id Jugador: %i \n", arregloPartidaXJugador[*validosPxJ].idJugador);

        arregloPartidaXJugador[*validosPxJ].resultado = 2;
        printf ("Resultado partida: %i \n", arregloPartidaXJugador[*validosPxJ].resultado);

        arregloPartidaXJugador[*validosPxJ].puntosJugador = 1;
        printf ("Puntos obtenidos en partida: %i \n", arregloPartidaXJugador[*validosPxJ].puntosJugador);

        arregloJugadores[*idJugadorUsuario-1].ptsTotales = arregloJugadores[*idJugadorUsuario-1].ptsTotales + 1;


        (*validosPxJ) = (*validosPxJ) + 1;


        printf ("INVITADO \n");
        arregloPartidaXJugador[*validosPxJ].idPartida = arregloPartida[*validosPartida - 1].idPartida;
        printf ("id Partida: %i \n", arregloPartidaXJugador[*validosPxJ].idPartida);

        arregloPartidaXJugador[*validosPxJ].idPartidaJugador = arregloJugadores[*idJugadorInvitado].idPartidaJugador;
        printf ("id PartidaJugador: %i \n", arregloPartidaXJugador[*validosPxJ].idPartidaJugador);


        arregloPartidaXJugador[*validosPxJ].idJugador = (*idJugadorInvitado);
        printf ("id Jugador: %i \n", arregloPartidaXJugador[*validosPxJ].idJugador);

        arregloPartidaXJugador[*validosPxJ].resultado = 2;
        printf ("Resultado partida: %i \n", arregloPartidaXJugador[*validosPxJ].resultado);

        arregloPartidaXJugador[*validosPxJ].puntosJugador = 1;
        printf ("Puntos obtenidos en partida: %i \n", arregloPartidaXJugador[*validosPxJ].puntosJugador);

        arregloJugadores[*idJugadorInvitado-1].ptsTotales = arregloJugadores[*idJugadorInvitado-1].ptsTotales + 1;

        (*validosPxJ) = (*validosPxJ) + 1;
    }
}

void ingresoJugada (char matrix [3][3],int arregloJugadasO[], int *validosO,int arregloJugadasX[], int *validosX, char idJugador, char nombreJugador []) //ok
{
    int posicion = 0;
    int fila;
    int columna;
    int verificacionJugadaIngresada=0;

    while (verificacionJugadaIngresada == 0)
    {
        system("cls");
        mostrarMatrix(matrix);
        printf("Jugador %s (%c) Ingrese posicion desde teclado numerico:\n",nombreJugador, idJugador);
        scanf ("%d", &posicion);
        verificacionJugadaIngresada = verificacionJugada (posicion, arregloJugadasO, validosO,arregloJugadasX,validosX); //0 : Jugada invalida,  1: juagada valida
        if (verificacionJugadaIngresada == 1)
        {
            fila = buscarPosicionFila (posicion);
            columna = buscarPosicionColumna (posicion);
            if (idJugador == 'X') {
                arregloJugadasX[*validosX] = posicion;
                (*validosX)++;
                matrix [fila][columna] = 'X';
            } else if (idJugador == 'O') {
                arregloJugadasO[*validosO] = posicion;
                (*validosO)++;
                matrix [fila][columna] = 'O';
            }
        }
        else
        {
            printf ("Jugada Invalida!. Intente nuevamente\n");
            system("pause");
        }
    } ///fin while

}

int buscarPosicionFila (int posicion) //ok
{
    int fila;

    if (posicion == 7 || posicion ==8 || posicion ==9)
    {
        fila = 0;
    }
    else if (posicion == 4 || posicion ==5 || posicion ==6)
    {
        fila = 1;
    }
    else if (posicion == 1 || posicion ==2 || posicion ==3)
    {
        fila = 2;
    }
    return fila;
}

int buscarPosicionColumna (int posicion) //ok
{
    int columna;

    if (posicion == 7 || posicion ==4 || posicion ==1)
    {
        columna = 0;
    }
    else if (posicion == 8 || posicion ==5 || posicion ==2)
    {
        columna = 1;
    }
    else if (posicion == 9 || posicion ==6 || posicion ==3)
    {
        columna = 2;
    }
    return columna;
}

int verificacionJugada (int posicion, int arregloJugadasX[], int *validosX, int arregloJugadasO[], int *validosO) //ok
{
    int verificacionPosicion = 1;

    for (int i=0; i<*validosX; i++)
    {
        if (posicion == arregloJugadasX [i])
        {
            verificacionPosicion =0;
        }
    }
    for (int j=0; j<*validosO; j++)
    {
        if (posicion == arregloJugadasO [j])
        {
            verificacionPosicion =0;
        }
    }
    return verificacionPosicion;
}

int verificarIfGanador(int arr[], int v, int posA, int posB, int posC)
{
    int ganador=0;


    for(int i=0; i<v; i++)
    {
        if(arr[i] == posA)
        {
            ganador++;
        }
        else if (arr[i] == posB)
        {
            ganador++;
        }
        else if (arr[i] == posC)
        {
            ganador++;
        }
    }

    if(ganador==3)
    {
        ganador=1;
    }
    else
    {
        ganador=0;
    }
    return ganador;
}

int verificarVictoria(int arr[],int v)
{
    int flag=0;
    int counter=0;
    if(flag==0 && counter==0)
    {
        flag=verificarIfGanador(arr, v, 7, 8, 9);
        if(flag==0 && counter==0)
            flag=verificarIfGanador(arr, v, 4, 5, 6);
        if(flag==0 && counter==0)
            flag=verificarIfGanador(arr, v, 1, 2, 3);
        if(flag==0 && counter==0)
            flag=verificarIfGanador(arr, v, 7, 4, 1);
        if(flag==0 && counter==0)
            flag=verificarIfGanador(arr, v, 8, 5, 2);
        if(flag==0 && counter==0)
            flag=verificarIfGanador(arr, v, 9, 6, 3);
        if(flag==0 && counter==0)
            flag=verificarIfGanador(arr, v, 7, 5, 3);
        if(flag==0 && counter==0)
            flag=verificarIfGanador(arr, v, 9, 5, 1);
        counter=1;
    }
    return flag;
}
char ganadorPartida(int arrX[], int arrO[], int vX, int vO)
{
    int winnerX=0;
    int winnerO=0;
    char ganador='n';

    winnerX=verificarVictoria(arrX, vX);
    winnerO=verificarVictoria(arrO, vO);


    if(winnerX==1)
    {
        ganador='X';
    }
    else if(winnerO==1)
    {
        ganador='O';
    }

    return ganador;
}
int mostrarGanador(char ganador)
{
    int win=0;

    if(ganador=='X')
    {
        printf("\nFELICITACIONES JUGADOR X GANASTE\n\n");
        win=1;
        ///Logica para guardar datos de partida

    }
    if(ganador=='O')
    {
        printf("\nFELICITACIONES JUGADOR O GANASTE\n\n");
        win=1;
        ///Logica para guardar datos de partida
    }
    return win;
}

void mostrarMatrix (char matrix [3][3]) //ok
{
    printf("\nTABLERO\n\n");
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            printf ("[%c]",matrix[i][j]);
        }
        printf ("\n");
    }
}

void iniciarSesionInvitado (stJugador arregloJugadores[], int *validosJugadores, int *idJugadorUsuario, int *idJugadorInvitado ) {

        int validacionUsuario = 0; ///1: Validado, 0: No validado

        char usuarioIngresado2 [15];
        char passwordIngresado2 [15];
        int i = 0;

        system ("cls");
        do {
            system ("cls");

            printf ("_______________________________________\n");
            printf ("    INICIO DE SESION DE INVITADO\n");
            printf ("_______________________________________\n");
            printf ("_______________________________________\n");

            do {
               printf ("Ingrese usuario jugador 2: \n");
               scanf (" %s", &usuarioIngresado2);
            } while (strcmp(usuarioIngresado2, arregloJugadores[*idJugadorUsuario-1].username) == 0);


            i = 0;
            while (i < *validosJugadores && validacionUsuario == 0 ) {
                    printf ("Ingrese al while - i = %i \n", i);
                  if (strcmp(usuarioIngresado2, arregloJugadores[i].username) == 0) { ///Valida username JUGADOR 2 ingresado
                            printf ("Ingrese Password jugador 2: \n");
                            scanf (" %s", &passwordIngresado2);
                            if (strcmp(passwordIngresado2, arregloJugadores[i].password) == 0)  { ///Valida password JUGADOR 2 ingresado
                                validacionUsuario = 1;
                                (*idJugadorInvitado) = arregloJugadores[i].idJugador;
                            } else {
                                validacionUsuario = 0;
                                printf ("Password incorrecto, intente nuevamente \n");
                                system ("pause");
                                break;
                            }
                   } else {
                    if (i == *validosJugadores - 1 && validacionUsuario == 0) {
                        printf ("El username no existe, intente nuevamente \n");
                        system ("pause");
                        break;
                    }
                  }
                  i = i + 1;

            }

        i = 0;
        } while (validacionUsuario != 1);

        system ("cls");
        printf ("%s bienvenido al juego TA TE TI\n", usuarioIngresado2);
        system ("pause");

}





///Otras Funciones
void mostrarJugador (stJugador jugador) {

    printf ("Id: %i \n", jugador.idJugador);
    printf ("Nombre: %s \n", jugador.nombre);
    printf ("Apellido: %s \n", jugador.apellido);
    printf ("email: %s \n", jugador.email);
    printf ("Usuario: %s \n", jugador.username);
    printf ("Password: %s \n", jugador.password);
    printf ("DNI: %s \n", jugador.dni);
    printf ("Ptos Totales: %i \n", jugador.ptsTotales);
    printf ("Eliminado: %i \n", jugador.eliminado);
}

int mostrarArreglo (int estadoActual, stJugador arregloJugadores[], int *validosJugadores) {

    printf("Validos %i \n", *validosJugadores);
    system ("cls");
    for (int i = 0; i < *validosJugadores; i++) {
        mostrarJugador(arregloJugadores[i]);
        printf ("____________________________________\n");
    }
    estadoActual  = 4; ///Transicion a MENU PRINCIPAL

    system ("pause");

    return estadoActual;
}



