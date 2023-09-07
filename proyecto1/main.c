#include <stdio.h>
#include <string.h>
#include <time.h>



struct Libro
{
    char titulo[100];
    
    struct tm fechaPrestamo; // Campo para la fecha de préstamo
    
    
    int estado;
    int multa;
};

struct Usuario
{
    char correo[100];
    char nombre[50];
    char apellido[50];
    char contrasena[50];
    struct Libro libros[10]; // Cambiar el tamaño del array según sea necesario
    int numLibros; // Número de libros prestados
};

int multaPorDia = 75;
int multaPorExtravio = 500;

void imprimirMenuPrincipal()
{
    printf("\nMenú Principal\n");
    printf("1. Registrarse\n");
    printf("2. Iniciar sesión\n");
    printf("3. Salir\n");
}

void imprimirMenuMultas()
{
    printf("\nMenú de Multas\n");
    printf("1. Cancelar multa\n");
    printf("2. Salir\n");
}

void imprimirMenuUsuario()
{
    printf("\nMenú de Opciones\n");
    printf("1. Solicitar un préstamo\n");
    printf("2. Devolver un libro\n");
    printf("3. Salir\n");
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

    // Inicializar el número de libros prestados a 0
    usuarios[*numUsuarios].numLibros = 0;

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
    //aca hay que meter la informacion del libro en el array de libros del usuario, agregar que fecha se presto y cambiar el estado del libro a prestado
    
}

void devolverLibro(struct Usuario *usuario)
{
    printf("Función: Devolver un libro para el usuario %s %s.\n", usuario->nombre, usuario->apellido);
    //aca hay que meter todo lo de devolver un libro, tanto el costo de pagar por dias sin pagar, como el costo si se extravio
}


int calcularMultaPorDia(struct Libro *libro)
{
    int totalMulta = 0;
    
    // Obtener la fecha y hora actual
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);

    // Obtener el año actual completo, se agrega 1900 porque el año 0 es 1900
    int anioActual = tlocal->tm_year + 1900;

    // Calcular la diferencia en años, meses y días desde la fecha de préstamo hasta la fecha actual
    int aniosDiferencia = anioActual - libro->fechaPrestamo.tm_year;
    int mesesDiferencia = tlocal->tm_mon - libro->fechaPrestamo.tm_mon;
    int diasDiferencia = tlocal->tm_mday - libro->fechaPrestamo.tm_mday;

    // Calcular la multa total
    if (aniosDiferencia > 0 || (aniosDiferencia == 0 && mesesDiferencia > 0) || (aniosDiferencia == 0 && mesesDiferencia == 0 && diasDiferencia > 0)) {
        totalMulta = (aniosDiferencia * 365 + mesesDiferencia * 30 + diasDiferencia) * multaPorDia;
    }

    return totalMulta;
}

int calcularMultaPorExtravio(struct Libro *libro)
{

    return multaPorExtravio;
}



void cancelarMulta(struct Usuario *usuario)
{

    // Imprimir la lista de libros con multa
    printf("Libros con multa:\n");
    for (int i = 0; i < usuario->numLibros; i++)
    {
        if (usuario->libros[i].multa > 0)
        {
            printf("%d. %s\n", i + 1, usuario->libros[i].titulo);
        }
    }

    // Solicitar el libro a cancelar la multa
    int opcionLibro;
    printf("Elija el libro a cancelar la multa: ");
    scanf("%d", &opcionLibro);

    // Obtener el libro seleccionado
    struct Libro *libro = &usuario->libros[opcionLibro - 1];

    // Calcular la multa total
    int totalMulta = calcularMultaPorDia(libro);
    
    // Imprimir la multa total
    printf("Multa total: %d\n", totalMulta);

    // Cancelar la multa
    libro->multa = 0;

    // Imprimir mensaje de multa cancelada
    printf("Multa cancelada para el usuario %s %s.\n", usuario->nombre, usuario->apellido);

    
}

int tieneMultas(struct Usuario *usuario)
{
    int tieneMultas = 0;
    for (int i = 0; i < usuario->numLibros; i++)
    {
        if (usuario->libros[i].multa > 0)
        {
            tieneMultas = 1;
            break;
        }
    }
    return tieneMultas;
}

int tienePrestamo(struct Usuario *usuario)
{
    return (usuario->numLibros > 0);
}



int main()
{
    struct Usuario usuarios[100];

    // Inicializar usuarios
    

    


    int numUsuarios = 0;

    //imprimir dia actual

    int dia, mes, anio;
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    dia = tlocal->tm_mday;
    mes = tlocal->tm_mon + 1;
    anio = tlocal->tm_year + 1900;

    printf("Fecha actual: %d/%d/%d\n", dia, mes, anio);
    
    printf("Dia: %d\n", dia);
    printf("Mes: %d\n", mes);
    printf("Anio: %d\n", anio);

    
    // Agregar un usuario sin multas
    strcpy(usuarios[numUsuarios].correo, "a");
    strcpy(usuarios[numUsuarios].nombre, "Juan");
    strcpy(usuarios[numUsuarios].apellido, "Pérez");
    strcpy(usuarios[numUsuarios].contrasena, "a");
    usuarios[numUsuarios].numLibros = 0; // Sin libros prestados
    numUsuarios++;

    // Agregar un usuario con multa
    strcpy(usuarios[numUsuarios].correo, "b");
    strcpy(usuarios[numUsuarios].nombre, "María");
    strcpy(usuarios[numUsuarios].apellido, "Gómez");
    strcpy(usuarios[numUsuarios].contrasena, "b");
    usuarios[numUsuarios].numLibros = 1; // Un libro prestado
    strcpy(usuarios[numUsuarios].libros[0].titulo, "Libro con multa");
    usuarios[numUsuarios].libros[0].fechaPrestamo.tm_mday = 1; // Día de préstamo
    usuarios[numUsuarios].libros[0].fechaPrestamo.tm_mon = 1; // Mes de préstamo
    usuarios[numUsuarios].libros[0].fechaPrestamo.tm_year = 2020; // Año de préstamo

    usuarios[numUsuarios].libros[0].estado = 1; // Libro prestado
    usuarios[numUsuarios].libros[0].multa = 150; // Multa asociada al libro
    numUsuarios++;

    


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

                if (tieneMultas(usuarioActual))
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
                    } while (opcionMultas != 2 && tieneMultas(usuarioActual));
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
                            break;
                        case 2:
                            devolverLibro(usuarioActual);
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
