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

///2. Menu Principal
int mainEstadoMenuPrincipal (int estadoActual);

///3.Registrarse
stJugador cargarJugador (stJugador arregloJugadores[], int *validosJugadores, int aux);
char* establecerEmail (stJugador arregloJugadores[], int validosJugadores, int aux);
char* establecerUsername (stJugador arregloJugadores[], int validosJugadores, int aux);
char* establecerPassword ();


///4.Iniciar Sesion
int mainEstadoIniciarSesion (int estadoActual);

///5.Perfil Jugador
int mainEstadoPerfilJugador (int estadoActual);


///Otros
int mostrarArreglo (int estadoActual, stJugador arregloJugadores[], int *validosJugadores) ;
void mostrarJugador (stJugador jugador);


int main()
{
 int estadoActual = 1;

 int iTransicion = 0;


 stJugador arregloJugadores[15];

 int validosJugadores = 0;

 while (estadoActual != 0) {
    estadoActual = diagrama (estadoActual, JUGADORES, arregloJugadores, &validosJugadores); ///Paso direccion de validos
 }
}

int diagrama (int estadoActual, char nombreArchivo[], stJugador arregloJugadores[], int *validosJugadores) {

    switch (estadoActual) {

        case 1: //PRESENTACION
            estadoActual = mainEstadoPresentacion (estadoActual, nombreArchivo,arregloJugadores, validosJugadores); ///ValidosJugadores es direccion
        break; ///Fin case 1


        case 2: //MENU PRINCIPAL
            estadoActual = mainEstadoMenuPrincipal(estadoActual);
        break; /// Fin case 2

        case 3: ///REGISTRARSE
            estadoActual = mainEstadoRegistrarse (estadoActual,arregloJugadores,validosJugadores,1);
        break; ///Fin case 3

        case 4: ///INICIAR SESION
            estadoActual = mainEstadoIniciarSesion(estadoActual);
        break; ///Fin case 4

        case 5: ///PERFIL JUGADOR
            estadoActual = mainEstadoPerfilJugador(estadoActual);
        break;

        case 99: ///VER ARREGLO
            estadoActual = mostrarArreglo (estadoActual,arregloJugadores, validosJugadores);
        break;

    }

    return estadoActual;
}

///1. Funciones Estado PRESENTACION
int mainEstadoPresentacion (int estadoActual, char nombreArchivo[], stJugador arregloJugadores[], int *validosJugadores) {

            stJugador jugador;
            int iTransicion = 0;
            //system ("cls");
            printf ("__________________________ \n");
            printf ("Bienvenido \n");
            printf ("    a \n");
            printf ("TA TE TI \n");
            printf ("__________________________ \n");

            FILE *archi = fopen (nombreArchivo, "rb");
            if (archi) {
                 while (fread (&jugador, sizeof (stJugador), 1, archi)) {
                    arregloJugadores[*validosJugadores] = jugador;
                    (*validosJugadores)++;
                 }

                //Logica de transicion
                iTransicion = 2;    ///Transición a Menú principal
                fclose (archi);
            } else {
                printf ("Sin datos. Se cargara el primer jugador \n");
                FILE *archi = fopen (nombreArchivo, "wb");
                printf ("Direccion: %i \n", validosJugadores);
                    printf ("Contenido: %i \n", *validosJugadores);

                if (archi) {
                    ///Crear primer jugador del archivo
                    jugador = cargarJugador (arregloJugadores, validosJugadores, 0);
                    fwrite (&jugador, sizeof(stJugador), 1, archi);
                    fclose (archi);
                }
                iTransicion = 1;    ///Transición a PRESENTACION
            }
            system ("pause");



            //Transicion al siguiente estado
            switch (iTransicion) {
            case 1:
              estadoActual        = 1; ///PRESENTACION
              break;
            case 2:
              estadoActual        = 2; ///MENU PRINCIPAL
              break;
            }
            return estadoActual;
}

///2. Funciones Estado MENU PRINCIPAL
int mainEstadoMenuPrincipal (int estadoActual) {

        int opcionInicio = 0;

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
        printf ("3. VER ARREGLO\n");
        printf ("4. SALIR \n");
        printf ("\n");
        printf ("\n");
        printf ("------------------------------------------- \n");
        scanf ("%i", &opcionInicio);

        } while (opcionInicio != 1 && opcionInicio != 2 && opcionInicio != 3 && opcionInicio != 4);

        //Logica de transicion y transicion al siguiente estado
        switch (opcionInicio) {
            case 1:
                    estadoActual  = 4; ///INICIAR SESION
                    break;
            case 2:
                    estadoActual  = 3; ///REGISTRARSE
                    break;
            case 3:
                    estadoActual  = 99; ///VER ARREGLO DE JUGADORES
                    break;
            case 4:
                    estadoActual  = 1; ///PRESENTACION
                    break;
        }

        return estadoActual;
}

///3. Funciones Estado REGISTRARSE

int mainEstadoRegistrarse (int estadoActual, stJugador arregloJugadores[], int *validosJugadores, int aux) {

    stJugador jugadorNuevo;
    int iTransicion = 0;

    system ("cls");
    printf ("------------------------------------------- \n");
    printf ("             REGISTRO \n");
    printf ("------------------------------------------- \n");
    printf ("\n");
    printf ("Ingrese datos del nuevo jugador \n");

    jugadorNuevo = cargarJugador (arregloJugadores, validosJugadores, 1);
    (*validosJugadores)++;
    system ("pause");
    //Logica de transicion
    iTransicion = 4;    ///Transición a INICIAR SESION

    //Transicion al siguiente estado
    switch (iTransicion) {
    case 4:
      estadoActual        = 4; //INICIAR SESION
      break;
    }
    return estadoActual;
}

stJugador cargarJugador (stJugador arregloJugadores[], int *validosJugadores, int aux) {

    stJugador jugadorNuevo;
    char emailTentativo[50];
    char passwordTentativo[50];

        printf("Validos cargarJugador %i \n", validosJugadores);
        printf("Validos cargarJugador  & %i \n", &validosJugadores);
        printf("Validos cargarJugador  * %i \n", *validosJugadores);
    printf ("Ingrese nombre del jugador: \n");
    scanf (" %s", &jugadorNuevo.nombre);

    printf ("Ingrese apellido del jugador: \n");
    scanf (" %s", &jugadorNuevo.apellido);

    strcpy(jugadorNuevo.email, establecerEmail (arregloJugadores, *validosJugadores, aux)); /// Solicita y valida nombre de usuario

    strcpy(jugadorNuevo.username, establecerUsername (arregloJugadores, *validosJugadores, aux)); /// Solicita y valida nombre de usuario

    strcpy(jugadorNuevo.password, establecerPassword ()); /// Solicita y valida password

    jugadorNuevo.ptsTotales = 0;
    jugadorNuevo.eliminado = 0;

    return jugadorNuevo;
}

///3.1 Validacion Email (@, ".com", unico)
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
                        printf ("Entro!\n");
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

///3.2 Validacion Usuario (Unico)
char* establecerUsername (stJugador arregloJugadores[], int validosJugadores, int aux) {

    stJugador jugador;
    char usernameTentativo[30];

    int validacionUsername = 1; ///1:Validado, 0:No Validado

    int i = 0;

    do {
        ///printf("Validos %i \n", validosJugadores);
        printf ("Ingrese username del jugador: \n");
        scanf (" %s", &usernameTentativo);

        if (aux == 1) {
        i = 0;
            while (i < validosJugadores){
                    printf("Juagador iteracion %s \n", arregloJugadores[i].username);
            printf("Juagador en registro %s \n", usernameTentativo);
                    if (strcmp(usernameTentativo, arregloJugadores[i].username) == 0){
                        validacionUsername = 0;
                    }
                    i = i + 1;
            }
        }
    } while (validacionUsername != 1);

    return strdup(usernameTentativo);; ///Deberia retornar directamente usernameTentativo?
}

///3.3 Validacion contraseña (1 min, 1 MAY)
char* establecerPassword () {

    char password[30];

    int condicionMinuscula = 0;
    int condicionMayuscula = 0;

    int validacionPassword = 0; ///1:Validado, 0:No Validado
    int i = 0;

    do {
        condicionMinuscula = 0;
        condicionMayuscula = 0;

        printf ("Ingrese password del jugador: \n");
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

///FUNCIONES ESTADO 4: INICIAR SESION

int mainEstadoIniciarSesion (int estadoActual) {

        int validacionUsuario = 0;
        int iTransicion = 0;
        char usuarioJugador[15];
        char passwordIngresado [15];

        do {
        system ("cls");
        printf ("_______________________________________\n");
        printf ("            INICIO DE SESION\n");
        printf ("_______________________________________\n");
        printf ("_______________________________________\n");
        printf ("Ingrese Usuario: \n");
        scanf (" %s", &usuarioJugador);

        ///validar Usuario
        printf ("Ingrese Password: \n");
        scanf (" %s", &passwordIngresado);
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

        return estadoActual;
}

///Funciones estado 5: PERFIL JUGADOR
int mainEstadoPerfilJugador (int estadoActual) {

        int opcionPerfil = 0;
        char usuarioJugador[15];
        do {
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
        } while (opcionPerfil != 1 && opcionPerfil != 2 && opcionPerfil != 3 && opcionPerfil != 0);
        ///Logica de transición
        switch (opcionPerfil) {
            case 1:
                    estadoActual  = 6; ///MODIFICAR DATOS
                    break;
            case 2:
                    estadoActual  = 7;  ///ESTADISTICAS
                    break;
            case 3:
                    estadoActual  = 8;      ///JUGAR PARTIDA
                    break;
            case 0:
                    estadoActual = 2;   ///MENU PRINCIPAL
                    break;

        }

        return estadoActual;
}

///Otras Funciones
void mostrarJugador (stJugador jugador) {

    printf ("Nombre: %s \n", jugador.nombre);
    printf ("Apellido: %s \n", jugador.apellido);
    printf ("email: %s \n", jugador.email);
    printf ("Usuario: %s \n", jugador.username);
    printf ("Password: %s \n", jugador.password);
}

int mostrarArreglo (int estadoActual, stJugador arregloJugadores[], int *validosJugadores) {

    for (int i = 0; i < *validosJugadores; i++) {
        mostrarJugador(arregloJugadores[i]);
        printf ("____________________________________\n");
    }
    int iTransicion = 2;
    switch (iTransicion) {
    case 2:
            estadoActual  = 2; ///MENU PRINCIPAL
            break;
    }
    system ("pause");
    return estadoActual;
}

