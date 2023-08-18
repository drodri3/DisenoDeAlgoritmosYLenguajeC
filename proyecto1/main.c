#include <stdio.h>
#include <string.h>

struct Usuario {
    char correo[100];
    char nombre[50];
    char apellido[50];
    char contrasena[50];
    int tieneMultas;
};

void imprimirMenuPrincipal() {
    printf("\nMenú Principal\n");
    printf("1. Registrarse\n");
    printf("2. Iniciar sesión\n");
    printf("3. Salir\n");
}

void imprimirMenuUsuario() {
    printf("\nMenú de Opciones\n");
    printf("1. Solicitar un préstamo\n");
    printf("2. Devolver un libro\n");
    printf("3. Salir\n");
}

void registrarUsuario(struct Usuario usuarios[], int *numUsuarios) {
    printf("Registro de Usuario\n");
    printf("Correo electrónico: ");
    scanf("%s", usuarios[*numUsuarios].correo);
    printf("Nombre: ");
    scanf("%s", usuarios[*numUsuarios].nombre);
    printf("Apellido: ");
    scanf("%s", usuarios[*numUsuarios].apellido);
    printf("Contraseña: ");
    scanf("%s", usuarios[*numUsuarios].contrasena);
    usuarios[*numUsuarios].tieneMultas = 0;

    (*numUsuarios)++;
}

int iniciarSesion(struct Usuario usuarios[], int numUsuarios) {
    char correo[100];
    char contrasena[50];

    printf("Inicio de Sesión\n");
    printf("Correo electrónico: ");
    scanf("%s", correo);
    printf("Contraseña: ");
    scanf("%s", contrasena);

    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(correo, usuarios[i].correo) == 0 && strcmp(contrasena, usuarios[i].contrasena) == 0) {
            return i;
        }
    }
    
    return -1;
}

void solicitarPrestamo(struct Usuario usuario) {
    printf("Función: Solicitar un préstamo para el usuario %s %s.\n", usuario.nombre, usuario.apellido);
}

void devolverLibro(struct Usuario usuario) {
    printf("Función: Devolver un libro para el usuario %s %s.\n", usuario.nombre, usuario.apellido);
}

void menuMultas(struct Usuario usuario) {
    printf("Función: menu multas para el usuario %s %s.\n", usuario.nombre, usuario.apellido);
}

int main() {
    struct Usuario usuarios[100];
    int numUsuarios = 0;

    int opcion;
    do {
        imprimirMenuPrincipal();
        printf("Elija una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                registrarUsuario(usuarios, &numUsuarios);
                break;
            case 2: {
                int indiceUsuario = iniciarSesion(usuarios, numUsuarios);
                if (indiceUsuario != -1) {
                    if (usuarios[indiceUsuario].tieneMultas) {
                        printf("No puede acceder al menú de opciones debido a multas pendientes.\n");
                        menuMultas(usuarios[indiceUsuario]);
                    } else {
                        printf("Inicio de sesión exitoso. Bienvenido, %s %s!\n", usuarios[indiceUsuario].nombre, usuarios[indiceUsuario].apellido);

                        int opcionUsuario;
                        do {
                            imprimirMenuUsuario();
                            printf("Elija una opción: ");
                            scanf("%d", &opcionUsuario);

                            switch (opcionUsuario) {
                                case 1:
                                    solicitarPrestamo(usuarios[indiceUsuario]);
                                    break;
                                case 2:
                                    devolverLibro(usuarios[indiceUsuario]);
                                    break;
                                case 3:
                                    printf("Saliendo del menú de usuario.\n");
                                    break;
                                default:
                                    printf("Opción no válida.\n");
                            }
                        } while (opcionUsuario != 3);
                    }
                } else {
                    printf("Inicio de sesión fallido. Usuario no encontrado.\n");
                }
                break;
            }
            case 3:
                printf("Saliendo del programa. ¡Hasta luego!\n");
                break;
            default:
                printf("Opción no válida.\n");
        }
    } while (opcion != 3);

    return 0;
}
