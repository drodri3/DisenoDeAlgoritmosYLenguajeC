#include <stdio.h>
#include <string.h>

struct Usuario
{
    char correo[100];
    char nombre[50];
    char apellido[50];
    char contrasena[50];
    int tieneMultas;
    int tienePrestamo;
};

void imprimirMenuPrincipal()
{
    printf("\nMenú Principal\n");
    printf("1. Registrarse\n");
    printf("2. Iniciar sesión\n");
    printf("3. Salir\n");
}

void imprimirMenuUsuario()
{
    printf("\nMenú de Opciones\n");
    printf("1. Solicitar un préstamo\n");
    printf("2. Devolver un libro\n");
    printf("3. Salir\n");
}

void imprimirMenuMultas()
{
    printf("\nMenú de Multas\n");
    printf("1. Cancelar multa\n");
    printf("2. Salir\n");
}

void registrarUsuario(struct Usuario usuarios[], int *numUsuarios)
{
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
    usuarios[*numUsuarios].tienePrestamo = 0;

    (*numUsuarios)++;
}

int iniciarSesion(struct Usuario usuarios[], int numUsuarios)
{
    char correo[100];
    char contrasena[50];

    printf("Inicio de Sesión\n");
    printf("Correo electrónico: ");
    scanf("%s", correo);
    printf("Contraseña: ");
    scanf("%s", contrasena);

    for (int i = 0; i < numUsuarios; i++)
    {
        if (strcmp(correo, usuarios[i].correo) == 0 && strcmp(contrasena, usuarios[i].contrasena) == 0)
        {
            return i;
        }
    }

    return -1;
}

void solicitarPrestamo(struct Usuario *usuario)
{
    printf("Función: Solicitar un préstamo para el usuario %s %s.\n", usuario->nombre, usuario->apellido);
}

void devolverLibro(struct Usuario *usuario)
{
    printf("Función: Devolver un libro para el usuario %s %s.\n", usuario->nombre, usuario->apellido);
}

void menuMultas(struct Usuario *usuario)
{
    printf("Función: menu multas para el usuario %s %s.\n", usuario->nombre, usuario->apellido);
}

void cancelarMulta(struct Usuario *usuario)
{
    printf("Multa cancelada para el usuario %s %s.\n", usuario->nombre, usuario->apellido);
    usuario->tieneMultas = 0;
}

void reportarPerdida(struct Usuario *usuario)
{
    printf("Pérdida reportada para el usuario %s %s.\n", usuario->nombre, usuario->apellido);
}

int main()
{
    struct Usuario usuarios[100];
    int numUsuarios = 0;

    int opcion;
    do
    {
        imprimirMenuPrincipal();
        printf("Elija una opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            registrarUsuario(usuarios, &numUsuarios);
            break;
        case 2:
        {
            int indiceUsuario = iniciarSesion(usuarios, numUsuarios);
            if (indiceUsuario != -1)
            {
                struct Usuario *usuarioActual = &usuarios[indiceUsuario];

                if (usuarioActual->tieneMultas)
                {
                    printf("No puede acceder al menú de opciones debido a multas pendientes.\n");
                    int opcionMultas;
                    do
                    {
                        imprimirMenuMultas();
                        printf("Elija una opción: ");
                        scanf("%d", &opcionMultas);

                        switch (opcionMultas)
                        {
                        case 1:
                            cancelarMulta(usuarioActual);
                            break;
                        case 2:
                            printf("Saliendo del menú de multas.\n");
                            break;
                        default:
                            printf("Opción no válida.\n");
                        }
                    } while (opcionMultas != 2);
                }
                else
                {
                    printf("Inicio de sesión exitoso. Bienvenido, %s %s!\n", usuarioActual->nombre, usuarioActual->apellido);

                    int opcionUsuario;
                    do
                    {
                        imprimirMenuUsuario();
                        printf("Elija una opción: ");
                        scanf("%d", &opcionUsuario);

                        switch (opcionUsuario)
                        {
                        case 1:
                            solicitarPrestamo(usuarioActual);
                            usuarioActual->tienePrestamo = 1;
                            break;
                        case 2:
                            devolverLibro(usuarioActual);
                            usuarioActual->tienePrestamo = 0;
                            break;
                        case 3:
                            printf("Saliendo del menú de usuario.\n");
                            break;
                        default:
                            printf("Opción no válida.\n");
                        }
                    } while (opcionUsuario != 3);
                }
            }
            else
            {
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
