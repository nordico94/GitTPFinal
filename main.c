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
int diagrama (int estadoActual, char nombreArchivo[], stJugador arregloJugadores[], int *validosJugadores);

///Funciones de cada estado
///1.Presentacion
int mainEstadoPresentacion (int estadoActual, char nombreArchivo[], stJugador arregloJugadores[], int *validosJugadores);

///2. Cargar Informacion
int mainEstadoCargarInformacion (int estadoActual, char nombreArchivo[], stJugador arregloJugadores[], int *validosJugadores);

///3. Descargar Informacion
int mainEstadoDescargarInformacion (int estadoActual, char nombreArchivo[], stJugador arregloJugadores[], int *validosJugadores);

///4. Menu Principal
int mainEstadoMenuPrincipal (int estadoActual);

///5.Registrarse
stJugador cargarJugador (stJugador arregloJugadores[], int *validosJugadores, int aux);
char* establecerEmail (stJugador arregloJugadores[], int validosJugadores, int aux);
char* establecerUsername (stJugador arregloJugadores[], int validosJugadores, int aux);
char* establecerPassword ();


///6.Iniciar Sesion
int mainEstadoIniciarSesion (int estadoActual, stJugador arregloJugadores[], int *validosJugadores, int *idJugadorUsuario) ;

///7.Perfil Jugador
int mainEstadoPerfilJugador (int estadoActual, int *idJugadorUsuario);


///Otros
int mostrarArreglo (int estadoActual, stJugador arregloJugadores[], int *validosJugadores) ;
void mostrarJugador (stJugador jugador);


int main()
{
 int estadoActual = 1;

 stJugador arregloJugadores[15];
 int validosJugadores = 0;
 int idActual = 0;

 while (estadoActual != 0) {
    estadoActual = diagrama (estadoActual, JUGADORES, arregloJugadores, &validosJugadores); ///Paso direccion de validos
 }
}

int diagrama (int estadoActual, char nombreArchivo[], stJugador arregloJugadores[], int *validosJugadores) {

    int idJugadorUsuario;

    switch (estadoActual) {

        case 1: ///PRESENTACION

            estadoActual = mainEstadoPresentacion (estadoActual, nombreArchivo,arregloJugadores, validosJugadores); ///ValidosJugadores es direccion
        break; ///Fin case 1

        case 2: ///CARGAR INFORMACION
            estadoActual = mainEstadoCargarInformacion (estadoActual,nombreArchivo,arregloJugadores,validosJugadores); ///ValidosJugadores es direccion
        break; ///Fin case 2

        case 3: ///DESCARGAR INFORMACION
            estadoActual = mainEstadoDescargarInformacion (estadoActual,nombreArchivo,arregloJugadores,validosJugadores); ///ValidosJugadores es direccion
        break; ///Fin case 2

        case 4: ///MENU PRINCIPAL
            estadoActual = mainEstadoMenuPrincipal(estadoActual);
        break; /// Fin case 3

        case 5: ///REGISTRARSE
            estadoActual = mainEstadoRegistrarse (estadoActual,arregloJugadores,validosJugadores,1);    ///ValidosJugadores es direccion
        break; ///Fin case 4

        case 6: ///INICIAR SESION
            estadoActual = mainEstadoIniciarSesion(estadoActual, arregloJugadores, validosJugadores, &idJugadorUsuario);       ///ValidosJugadores es direccion
        break; ///Fin case 5

        case 7: ///PERFIL JUGADOR
            estadoActual = mainEstadoPerfilJugador(estadoActual, &idJugadorUsuario);
        break;

        case 99: ///VER ARREGLO
            estadoActual = mostrarArreglo (estadoActual,arregloJugadores, validosJugadores);        ///ValidosJugadores es direccion
        break;

    }

    return estadoActual;
}

///1. Funciones Estado PRESENTACION
int mainEstadoPresentacion (int estadoActual, char nombreArchivo[], stJugador arregloJugadores[], int *validosJugadores) {

            char cTransicion = '1';

            system ("cls");
            printf ("Validos (pre-estado): %i \n", (*validosJugadores));
            printf ("__________________________ \n");
            printf ("Bienvenido \n");
            printf ("    a \n");
            printf ("TA TE TI \n");
            printf ("__________________________ \n");

            printf ("Presione una tecla... <S: Salir>)");
            scanf (" %c", &cTransicion);

            if (cTransicion =='S' || cTransicion == 's') {
                estadoActual = 0; ///Sale de la consola
            } else {
                estadoActual = 2; ///Transicion a estado 2: CARGAR INFORMACION
            }

            return estadoActual;
}

///2. Funciones Estado GARGAR INFORMACION

int mainEstadoCargarInformacion (int estadoActual, char nombreArchivo[], stJugador arregloJugadores[], int *validosJugadores) {


            stJugador jugador;
            int iTransicion = 0;

            ///Carga de informacion desde archivo JUGADORES a arregloJugadores

            FILE *archi = fopen (nombreArchivo, "rb");
            if (archi) {  ///Si el archivo existe carga la informacion en un arreglo
                            while (fread (&jugador, sizeof (stJugador), 1, archi)) {
                                arregloJugadores[*validosJugadores] = jugador;
                                (*validosJugadores)++;
                            }
                            fclose (archi);

                            ///Logica de transicion
                            estadoActual = 4; ///Transición a estado 3: MENU PRINCIPAL
                            system ("cls");
                            printf ("Validos (pre-estado): %i \n", (*validosJugadores));
                            printf ("*** Cargando datos del juego ***  \n");
                            system ("pause");

            } else {   ///Si el archivo no existe registra al primer jugador en el archivo
                            printf ("Sin datos. Se cargara al primer jugador del sistema \n");
                            FILE *archi = fopen (nombreArchivo, "wb");

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
            return estadoActual;
}


///3. Funciones Estado DESCARGAR INFORMACION

int mainEstadoDescargarInformacion (int estadoActual, char nombreArchivo[], stJugador arregloJugadores[], int *validosJugadores) {


            stJugador jugador;

            ///Descarga de informacion de jugadores:  Desde arregloJugadores a archivo JUGADORES

            FILE *archi = fopen (nombreArchivo, "wb"); ///Se reescribe archivo con los nuevos datos
            if (archi) {  ///Si el archivo existe descarga la informacion en un arreglo
                    for (int i = 0; i < (*validosJugadores); i++ ) {
                        jugador = arregloJugadores[i];
                        fwrite (&jugador, sizeof (stJugador), 1, archi);
                    }
                    fclose (archi);
            }

            (*validosJugadores) = 0;
            printf ("Validos (pre-estado): %i \n", (*validosJugadores));
            printf ("*** Descargando datos del juego a archivo... ****\n");
            system ("pause");

            ///Logica de transicion
            estadoActual = 1; ///Transición a estado 1: PRESENTACION

            return estadoActual;
}

///4. Funciones Estado MENU PRINCIPAL
int mainEstadoMenuPrincipal (int estadoActual) {

        int opcionInicio = 0;

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
        printf ("3. VER ARREGLO\n");
        printf ("4. SALIR \n");
        printf ("\n");
        printf ("\n");
        printf ("___________________________________________ \n");
        scanf ("%i", &opcionInicio);

        } while (opcionInicio != 1 && opcionInicio != 2 && opcionInicio != 3 && opcionInicio != 4);

        //Logica de transicion y transicion al siguiente estado
        switch (opcionInicio) {
            case 1:
                    estadoActual  = 6; ///INICIAR SESION
                    break;
            case 2:
                    estadoActual  = 5; ///REGISTRARSE
                    break;
            case 3:
                    estadoActual  = 99; ///VER ARREGLO DE JUGADORES
                    break;
            case 4:
                    estadoActual  = 3; ///DESCARGAR INFORMACION EN ARCHIVO
                    break;
        }

        return estadoActual;
}

///5. Funciones Estado REGISTRARSE

int mainEstadoRegistrarse (int estadoActual, stJugador arregloJugadores[], int *validosJugadores, int aux) {

    stJugador jugadorNuevo;
    int iTransicion = 0;

    system ("cls");
    printf ("Validos (pre-estado): %i \n", (*validosJugadores));
    printf ("___________________________________________ \n");
    printf ("             REGISTRO \n");
    printf ("___________________________________________ \n");
    printf ("\n");
    printf ("Ingrese datos del nuevo jugador \n");

    jugadorNuevo = cargarJugador (arregloJugadores, validosJugadores, 1);
    jugadorNuevo.idJugador = (*validosJugadores)+1;

    system ("cls");
    printf ("Datos nuevo jugador : \n");
    mostrarJugador (jugadorNuevo);
    arregloJugadores[*validosJugadores]=jugadorNuevo;
    (*validosJugadores)++;
    printf ("validos actualizado: %i \n" , *validosJugadores );

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


        printf ("Ingrese email: \n");
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

        printf ("Ingrese password: \n");
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

        system ("cls");
        printf ("Validos (pre-estado): %i \n", (*validosJugadores));
        do {
            system ("cls");
            printf ("_______________________________________\n");
            printf ("            INICIO DE SESION\n");
            printf ("_______________________________________\n");
            printf ("_______________________________________\n");

            printf ("Ingrese Usuario: \n");
            scanf (" %s", &usuarioIngresado);

            i = 0;
            while (i < *validosJugadores && validacionUsuario == 0 ) {
            ///for (int i = 0; i < *validosJugadores; i++) {
                if (strcmp(usuarioIngresado, arregloJugadores[i].username) == 0) { ///Valida username ingresado
                    printf ("Ingrese Password: \n");
                    scanf (" %s", &passwordIngresado);
                    if (strcmp(passwordIngresado, arregloJugadores[i].password) == 0)  { ///Valida password ingresado
                        validacionUsuario = 1;
                        (*idJugadorUsuario) = arregloJugadores[i].idJugador;
                    } else {
                        printf ("Password incorrecto, intente nuevamente \n");
                        system ("pause");

                    }
                }else {
                    if (i == *validosJugadores - 1 && validacionUsuario == 0) {
                        printf ("El usuario no existe, intente nuevamente \n");
                        system ("pause");
                    }
                }
                i = i + 1;
            }

        } while (validacionUsuario != 1);

        system ("cls");
        printf ("%s bienvenido al juego TA TE TI\n", usuarioIngresado);
        system ("pause");

        ///Logica de transicion
        iTransicion = 7;    ///Transicion a PERFIL JUGADOR

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
int mainEstadoPerfilJugador (int estadoActual, int *idJugadorUsuario) {

        int opcionPerfil = 0;
        char usuarioJugador[15];
        system ("cls");
        printf ("idJugador del Usuario: %i \n", (*idJugadorUsuario));
        do {
        ///system ("cls");
        printf ("_______________________________________\n");
        printf ("         HOLA %s \n", usuarioJugador);
        printf ("_______________________________________\n");
        printf ("1. MODIFICAR DATOS\n");
        printf ("2. VER ESTADISTICAS\n");
        printf ("3. JUGAR PARTIDA\n");
        printf ("0. CERRAR SESION\n");
        printf ("_______________________________________\n");
        scanf ("%i", &opcionPerfil);
        } while (opcionPerfil != 1 && opcionPerfil != 2 && opcionPerfil != 3 && opcionPerfil != 0);
        ///Logica de transición
        switch (opcionPerfil) {
            case 1:
                    estadoActual  = 8; ///MODIFICAR DATOS
                    break;
            case 2:
                    estadoActual  = 9;  ///ESTADISTICAS
                    break;
            case 3:
                    estadoActual  = 10;      ///JUGAR PARTIDA
                    break;
            case 0:
                    estadoActual = 4;   ///MENU PRINCIPAL
                    break;

        }

        return estadoActual;
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

