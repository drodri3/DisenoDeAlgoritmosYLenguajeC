#include "contrasena.h"
#include <string.h>
#include <ctype.h>

bool esContrasenaValida(const char *contrasena) {
    size_t largoContrasena = strlen(contrasena);
    bool mayuscula = false, minuscula = false, especial = false, decimal = false;

    if (largoContrasena <= 12) {
        return false;
    } else {
        for (size_t i = 0; i < largoContrasena; i++) {
            char caracter = contrasena[i];
            if (islower(caracter)) {
                minuscula = true;
            }

            if (isupper(caracter)) {
                mayuscula = true;
            }

            if (isalnum(caracter)) {
                // No hacemos nada aquí, solo queremos saber si es alfanumérico.
            } else {
                especial = true;
            }

            if (isdigit(caracter)) {
                decimal = true;
            }
        }

        return (mayuscula && minuscula && especial && decimal);
    }
}
