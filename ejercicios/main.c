
//ejercicio 1

/*
#include <stdio.h>
#define PI 3.1416

int main()
{
    float radio, area;
    printf("Ingrese el radio de la circunferencia: ");
    scanf("%f", &radio);
    
    area = PI * (radio * radio);
    printf("El area de la circunferencia es: %f", area);
    return 0;
}
*/

// ejercicio 2

#include <stdio.h>

int main()
{
    float horasTrabajadas, pagoHora, sueldoSemanal;
    printf("Ingrese las horas trabajadas: ");
    scanf("%f", &horasTrabajadas);
    printf("Ingrese el pago por hora: ");
    scanf("%f", &pagoHora);
    
    sueldoSemanal = horasTrabajadas * pagoHora;
    printf("El sueldo semanal es: %f", sueldoSemanal);
    return 0;
}