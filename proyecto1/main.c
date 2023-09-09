#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "contrasena.h"

// comando para compilar main.c y contrasena.c
// gcc main.c contrasena.c -o main

// Variables globales
int dia, mes, anio;
int multaPorDia = 75;
int multaPorExtravio = 500;

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
    int numLibros;           // Número de libros prestados
};

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
    printf("1. Solicitar un préstamo.\n");
    printf("2. Devolver un libro.\n");
    printf("3. Reportar libro perdido.\n");
    printf("4. Salir\n");
}

// Función para guardar el usuario y la contraseña en un archivo
void guardarUsuario(struct Usuario usuario)
{
    FILE *archivo;
    archivo = fopen("usuarios.txt", "a"); // Abre el archivo en modo de añadir

    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fprintf(archivo, "Correo: %s\n", usuario.correo);
    fprintf(archivo, "Nombre: %s\n", usuario.nombre);
    fprintf(archivo, "Apellido: %s\n", usuario.apellido);
    fprintf(archivo, "Contraseña: %s\n", usuario.contrasena);
    fprintf(archivo, "Número de libros prestados: %d\n", usuario.numLibros);

    fclose(archivo);
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

    // Solicitar una contraseña válida
    bool contrasenaValida = false;
    while (!contrasenaValida)
    {
        printf("La contraseña debe tener al menos 8 caracteres, una letra mayúscula, una letra minúscula y un número.\n");
        printf("Contraseña: ");
        scanf("%s", usuarios[*numUsuarios].contrasena);

        // Verificar si la contraseña es válida
        contrasenaValida = esContrasenaValida(usuarios[*numUsuarios].contrasena);

        if (!contrasenaValida)
        {
            printf("La contraseña no cumple con los requisitos. Inténtelo de nuevo.\n");
        }
    }

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
        if (strcmp(correo, usuarios[i].correo) == 0)
        {
            if (strcmp(contrasena, usuarios[i].contrasena) == 0)
            {
                return i; // Inicio de sesión exitoso
            }
            else
            {
                printf("Contraseña incorrecta.\n");
                return -1; // Contraseña incorrecta
            }
        }
    }

    printf("Correo electrónico no encontrado.\n");
    return -1; // Correo electrónico no encontrado
}

void solicitarPrestamo(struct Usuario *usuario, struct Libro biblioteca[], int tamanoBiblioteca)
{
    // aca hay que meter la informacion del libro en el array de libros del usuario, agregar que fecha se presto y cambiar el estado del libro a prestado
    int contador = 0;
    int opcion;
    int cantidadDeLibrosDelUsuario = usuario->numLibros;
    printf("Función: Solicitar un préstamo para el usuario %s %s.\n", usuario->nombre, usuario->apellido);
    printf("Libros disponibles en la Biblioteca:\n");
    // Imprimir libros disponibles
    for (int i = 0; i < tamanoBiblioteca; i++)
    {
        if (biblioteca[i].estado == 0)
        {
            printf("  %d. %s\n", i, biblioteca[i].titulo);
            contador++;
        }
    }
    printf("  %d. Salir\n", tamanoBiblioteca);
    printf("Seleccione el libro que desea solicitar: ");
    scanf("%d", &opcion);
    // Registrar prestamo
    if (opcion < tamanoBiblioteca)
    {
        biblioteca[opcion].estado = 1;
        usuario->libros[cantidadDeLibrosDelUsuario].estado = biblioteca[opcion].estado;
        strcpy(usuario->libros[cantidadDeLibrosDelUsuario].titulo, biblioteca[opcion].titulo);
        usuario->libros[cantidadDeLibrosDelUsuario].multa = biblioteca[opcion].multa;
        usuario->libros[cantidadDeLibrosDelUsuario].fechaPrestamo.tm_mday = dia;
        usuario->libros[cantidadDeLibrosDelUsuario].fechaPrestamo.tm_mon = mes;
        usuario->libros[cantidadDeLibrosDelUsuario].fechaPrestamo.tm_year = anio;

        printf("Se ha solicitado el prestamo del libro %s de manera exitosa para el usuario %s.\n", usuario->libros[cantidadDeLibrosDelUsuario].titulo, usuario->nombre);

        usuario->numLibros++;
        cantidadDeLibrosDelUsuario++;
    }
}

void devolverLibro(struct Usuario *usuario, struct Libro biblioteca[], int tamanoBiblioteca)
{
    int opcion;
    printf("Función: Devolver un libro para el usuario %s %s.\n", usuario->nombre, usuario->apellido);
    // aca hay que meter todo lo de devolver un libro, tanto el costo de pagar por dias sin pagar, como el costo si se extravio

    if (usuario->numLibros == 0)
    {

        printf("  No tiene libros por devolver.\n ");
    }
    else
    {

        // Imprimir la lista de libros.
        printf("Libros prestados: %d\n", usuario->numLibros);
        int i = 0;
        do
        {
            if (usuario->libros[i].estado == 1)
            {
                // recorre el arreglo biblioteca para determinar el índice del libro
                for (int j = 0; j < tamanoBiblioteca; j++)
                {
                    // verifica el índice en el arreglo biblioteca para mostrarlo a la hora de imprimir en pantalla el libro prestado
                    if (strcmp(usuario->libros[i].titulo, biblioteca[j].titulo) == 0)
                    {
                        printf("    %d. %s.\n", j, biblioteca[j].titulo);
                        // i ++;
                        break;
                    }
                }
            }
            i++;
        } while (i < usuario->numLibros);

        printf("      Seleccione el libro que desea devolver: ");
        scanf("%d", &opcion);

        if (opcion > tamanoBiblioteca)
        {
            printf("  Seleccione un libro válido.");
        }
        else
        {
            // recorre el arreglo biblioteca para determinar el índice del libro
            for (int j = 0; j < tamanoBiblioteca; j++)
            {
                // marca como devuelto el libro en el arreglo de la biblioteca y en el arreglo de libros de usuario
                if (strcmp(usuario->libros[j].titulo, biblioteca[opcion].titulo) == 0)
                {
                    biblioteca[opcion].estado = 0;
                    usuario->libros[j].estado = 0;
                    break;
                }
            }
            usuario->numLibros--;
            printf("  Libro devuelto a la biblioteca.\n");
        }
    }
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
    if (aniosDiferencia > 0 || (aniosDiferencia == 0 && mesesDiferencia > 0) || (aniosDiferencia == 0 && mesesDiferencia == 0 && diasDiferencia > 0))
    {
        totalMulta = (aniosDiferencia * 365 + mesesDiferencia * 30 + diasDiferencia) * multaPorDia;
    }

    return totalMulta;
}

int calcularMultaPorExtravio()
{

    return multaPorExtravio;
}

void reportarLibroPerdido(struct Usuario *usuario)
{
    // Imprimir la lista de libros.
    if (!usuario->numLibros == 0)
    {
        printf("Libros con multa:\n");
        for (int i = 0; i < usuario->numLibros; i++)
        {
            printf("%d. %s\n", i + 1, usuario->libros[i].titulo);
        }

        // Solicitar el libro que quiere reportar perdido
        int opcionLibro;
        printf("Elija el libro que desea reportar como perdido: ");
        scanf("%d", &opcionLibro);

        // Obtener el libro seleccionado
        struct Libro *libro = &usuario->libros[opcionLibro - 1];

        // Calcular la multa total
        int totalMulta = calcularMultaPorExtravio();

        // Imprimir la multa total
        printf("Multa total: %d\n", totalMulta);

        // Imprimir mensaje de multa cancelada
        printf("Multa cancelada para el usuario %s %s.\n", usuario->nombre, usuario->apellido);
    }
    else
    {
        printf("No tiene ningun prestamo de libro para reportarlo como perdido.");
    }
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
    struct Libro biblioteca[10];

    // Inicializar usuarios
    int numUsuarios = 0;
    int numLibros = 0;

    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    dia = tlocal->tm_mday;
    mes = tlocal->tm_mon + 1;
    anio = tlocal->tm_year + 1900;
    // imprimir dia actual
    printf("Fecha actual: %d/%d/%d\n", dia, mes, anio);

    printf("Dia: %d\n", dia);
    printf("Mes: %d\n", mes);
    printf("Anio: %d\n", anio);

    // Agregar libros a la biblioteca
    strcpy(biblioteca[numLibros].titulo, "Don Quijote");
    biblioteca[numLibros].estado = 0;
    biblioteca[numLibros].multa = 400;
    numLibros++;

    strcpy(biblioteca[numLibros].titulo, "El Principito");
    biblioteca[numLibros].estado = 1;
    biblioteca[numLibros].multa = 300;
    numLibros++;

    strcpy(biblioteca[numLibros].titulo, "Cocori");
    biblioteca[numLibros].estado = 0;
    biblioteca[numLibros].multa = 200;
    numLibros++;

    strcpy(biblioteca[numLibros].titulo, "El Gran Divorcio");
    biblioteca[numLibros].estado = 0;
    biblioteca[numLibros].multa = 750;
    numLibros++;

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
    usuarios[numUsuarios].libros[0].fechaPrestamo.tm_mday = 1;    // Día de préstamo
    usuarios[numUsuarios].libros[0].fechaPrestamo.tm_mon = 1;     // Mes de préstamo
    usuarios[numUsuarios].libros[0].fechaPrestamo.tm_year = 2020; // Año de préstamo
    usuarios[numUsuarios].libros[0].estado = 1;                   // Libro prestado
    usuarios[numUsuarios].libros[0].multa = 1;                    // Multa asociada al libro
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
            if (esContrasenaValida(usuarios[numUsuarios - 1].contrasena))
            {
                guardarUsuario(usuarios[numUsuarios - 1]);
            }
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
                            solicitarPrestamo(usuarioActual, biblioteca, numLibros);
                            break;
                        case 2:
                            devolverLibro(usuarioActual, biblioteca, numLibros);
                            break;
                        case 3:
                            reportarLibroPerdido(usuarioActual);
                            break;
                        case 4:
                            printf("Saliendo del menú de usuario.\n");
                            break;
                        default:
                            printf("Opción no válida.\n");
                        }
                    } while (opcionUsuario != 4);
                }
            }
            else
            {
                printf("Inicio de sesión fallido.\n");
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
