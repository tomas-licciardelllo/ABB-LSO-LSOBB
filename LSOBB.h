#ifndef LSOBB_H_INCLUDED
#define LSOBB_H_INCLUDED
#include "Prestador.h"
#include <math.h>
#define MAX 110
typedef struct{
    prestador prestadores[MAX];
    int ultimo;
}LSOBB;


void iniciar_LSOBB(LSOBB *lista)
{
        lista->ultimo=-1;
}

int costosAltaLSOBB[3] = {0}; //0: Sumatoria de corrimientos. 1: Costo Maximo de Alta. 2: Cantidad de altas.
int costosBajaLSOBB[3] = {0}; //0: Sumatoria de corrimientos. 1: Costo Maximo de Baja. 2: Cantidad de bajas.
int costosEvocarExitoLSOBB[3] = {0}; //0: Sumatoria comparaciones con x. 1: Costo Maximo de Evocar exitosamente. 3: Cantidad de evocaciones exitosas.
int costosEvocarFracasoLSOBB[3] = {0};//0: Sumatoria comparaciones con x. 1: Costo Maximo de Evocar con fracaso. 3: Cantidad de evocaciones con fracaso.

int localizar_LSOBB(LSOBB lista, int x, int *pos, int marca){
    int m, li=0;
    int ls=lista.ultimo+1, esfMaxAux=0;
    m=(li+ls)/2;
        while(li!=ls && lista.prestadores[m].DNI!=x){
        if(lista.prestadores[m].DNI<x){
            li=m+1;
        }
        else
        {
            ls=m;
        }
        m=(li+ls)/2;
        esfMaxAux+=2;
    }
    esfMaxAux+=1;
    *pos= m;
    if(marca){
        if(li!=ls){
            costosEvocarExitoLSOBB[0]+=esfMaxAux;
            costosEvocarExitoLSOBB[2]+=1;
            if(esfMaxAux>costosEvocarExitoLSOBB[1])
                costosEvocarExitoLSOBB[1]=esfMaxAux;
            return 1;
        }
        else
        {
            if (lista.prestadores[m].DNI != x){
            costosEvocarFracasoLSOBB[0]+=esfMaxAux;
            costosEvocarFracasoLSOBB[2]+=1;
            if(esfMaxAux>costosEvocarFracasoLSOBB[1])
                costosEvocarFracasoLSOBB[1]=esfMaxAux;
            return 0;
        }
        }
    }
    else {
        if (lista.prestadores[m].DNI == x)
            return 1;
        else
            return 0;
    }
}

int alta_LSOBB(LSOBB *lista, prestador x)
{
    int aux;
    int posicion,esfMaxAux=0;
    if(!localizar_LSOBB(*lista,x.DNI,&posicion,0))
    {
        aux=lista->ultimo;
        while(posicion<=aux)
        {
            lista->prestadores[aux+1]=lista->prestadores[aux];
            aux--;
            costosAltaLSOBB[0]++;
            esfMaxAux++;
        }
        lista->prestadores[posicion]=x;
        costosAltaLSOBB[2] = costosAltaLSOBB[2] + 1;
        if(esfMaxAux>costosAltaLSOBB[1]){
            costosAltaLSOBB[1] = esfMaxAux;
        }
        lista->ultimo++;
        return 1;
    }
        else
    {
        return -1;
    }
}

int baja_LSOBB(LSOBB *lista,prestador x)
{
    int decision;
    int posicion;
    int aux, aux_INF,esfMaxAux=0;
    if(localizar_LSOBB(*lista, x.DNI, &posicion,0))
    {
        if((lista->prestadores[posicion].DNI == x.DNI) &&
         (strcmp(lista->prestadores[posicion].celular, x.celular) == 0) &&
         (strcmp(lista->prestadores[posicion].domicilio, x.domicilio) == 0) &&
         (strcmp(lista->prestadores[posicion].email, x.email) == 0) &&
         (strcmp(lista->prestadores[posicion].nom_y_ape, x.nom_y_ape) == 0) &&
         (strcmp(lista->prestadores[posicion].servicios, x.servicios) == 0))
        {
            aux=posicion;
            while(aux<lista->ultimo)
            {
                lista->prestadores[aux]=lista->prestadores[aux+1];
                aux++;
                costosBajaLSOBB[0] = costosBajaLSOBB[0] + 1;
                esfMaxAux++;
            }
            lista->prestadores[lista->ultimo].DNI=-1;
            lista->ultimo--;
            costosBajaLSOBB[2] = costosBajaLSOBB[2] + 1;
            if(esfMaxAux>costosBajaLSOBB[1])
                costosBajaLSOBB[1] = esfMaxAux;
            return 1;
        }
    }
    else
    {
        return 0;
    }

}


prestador evocar_LSOBB(LSOBB lista, int x)
{
    int pos;
    prestador aux = {0,"x","x","x","x","x"};
    if(localizar_LSOBB(lista,x,&pos,1)){
        return lista.prestadores[pos];
    }
    else
    {
        return aux;
    }
}

int mostrar_LSOBB(LSOBB lista) {
    int i;
    int tecla;
    int pagina_actual = 0;
    int total_paginas = (lista.ultimo / 2) + 1;

    if (lista.ultimo == -1) {
        printf("No hay elementos en la estructura.\n");
        printf("Presione Enter para volver al menu.\n");
        getchar();
        getchar();
        system("cls");
        return 0;
    } else {
        while (1) {
            system("cls");
            printf("Pagina %d de %d\n\n", pagina_actual + 1, total_paginas);

            if (pagina_actual * 2 <= lista.ultimo) {
                printf("Elemento %d de %d\n", pagina_actual * 2 + 1, lista.ultimo + 1);
                mostrar_prestador(lista.prestadores[pagina_actual * 2]);
            }
            if (pagina_actual * 2 + 1 <= lista.ultimo) {
                printf("Elemento %d de %d\n", pagina_actual * 2 + 2, lista.ultimo + 1);
                mostrar_prestador(lista.prestadores[pagina_actual * 2 + 1]);
            }

            if (pagina_actual < total_paginas - 1) {
                printf("\nPresione Enter para continuar, Backspace para regresar, Esc para salir");
            } else {
                printf("\nPresione Backspace para regresar, Esc para salir");
            }

            tecla = _getch();

            if (tecla == 13) {
                if (pagina_actual < total_paginas - 1) {
                    pagina_actual++;
                }
            } else if (tecla == 8) {
                if (pagina_actual > 0) {
                    pagina_actual--;
                }
            } else if (tecla == 27) {
                system("cls");
                break;
            }
        }
    }
    return 0;
}


#endif // LSOBB_H_INCLUDED
