#ifndef PRESTADOR_H_INCLUDED
#define PRESTADOR_H_INCLUDED
#include <string.h>
#define NYA 80
#define SER 120
#define DOM 80
#define EMA 50
#define CEL 30
typedef struct{
    int DNI;
    char nom_y_ape[NYA];
    char servicios[SER];
    char domicilio[DOM];
    char email[EMA];
    char celular[CEL];//cadena numeros enteros
}prestador;

//preguntar si se puede imprimir en esta funcion
void mostrar_prestador (prestador p){
    printf("------------------------------------------\n");
    printf("DNI: %d\n",p.DNI);
    printf("Nombre y Apellido: %s",p.nom_y_ape);
    printf("Servicio: %s",p.servicios);
    printf("Domicilio: %s",p.domicilio);
    printf("Email: %s",p.email);
    printf("Celular: %s",p.celular);
    printf("------------------------------------------\n");
}

#endif // PRESTADOR_H_INCLUDED
