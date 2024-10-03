#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED
#include <string.h>
#include <conio.h>
#define MAX 111
#define INFINITO 99999999
#include "prestador.h"

typedef struct
{   prestador prestadores[MAX];//LSO
    int ultimo;//contiene el ultimo elemento de la estructura
} LSO;

void iniciar_LSO(LSO *lista)
{
    lista->prestadores[0].DNI=INFINITO;
    lista->ultimo=-1;
}

int costosAltaLSO[3] = {0}; //0: Sumatoria de corrimientos. 1: Costo Maximo de Alta. 2: Cantidad de altas.
int costosBajaLSO[3] = {0}; //0: Sumatoria de corrimientos. 1: Costo Maximo de Baja. 2: Cantidad de bajas.
int costosEvocarExitoLSO[3] = {0}; //0: Sumatoria comparaciones con x. 1: Costo Maximo de Evocar exitosamente. 3: Cantidad de evocaciones exitosas.
int costosEvocarFracasoLSO[3] = {0};//0: Sumatoria comparaciones con x. 1: Costo Maximo de Evocar con fracaso. 3: Cantidad de evocaciones con fracaso.

int localizar_LSO(LSO lista,int x,int *pos, int marca)
{
    int c=0;
    int esfMaxEvocarAux = 0;
        while(lista.prestadores[c].DNI<x){
            c++;
            esfMaxEvocarAux++;
        }
        *pos = c;
        esfMaxEvocarAux++;
    if(marca){
        if (x == lista.prestadores[c].DNI){
        costosEvocarExitoLSO[0]+=esfMaxEvocarAux;
        costosEvocarExitoLSO[2]+=1;
        if(esfMaxEvocarAux>costosEvocarExitoLSO[1])
            costosEvocarExitoLSO[1]=esfMaxEvocarAux;
        return 1;
        }
        else if (x != lista.prestadores[c].DNI){
            costosEvocarFracasoLSO[0]+=esfMaxEvocarAux;
            costosEvocarFracasoLSO[2]+=1;
            if(esfMaxEvocarAux>costosEvocarFracasoLSO[1])
                costosEvocarFracasoLSO[1]=esfMaxEvocarAux;
            return 0;
        }
    }
    else{
        return (x==lista.prestadores[c].DNI);
    }
}

int alta_LSO(LSO *lista, prestador x)
{
    int aux,inf,posicion,esfMaxAux=0;
    if(!localizar_LSO(*lista,x.DNI,&posicion,0))
    {
        /*aux=lista->ultimo;
        while(posicion<=aux)
        {
            lista->prestadores[aux+1]=lista->prestadores[aux];
            aux--;
            costosAltaLSO[0]=costosAltaLSO[0] + 1;
            esfMaxAux++;
        }
        lista->prestadores[posicion]=x;
        lista->ultimo++;
        //inf=lista->ultimo+1;
        lista->prestadores[lista->ultimo+1].DNI=INFINITO;*/
        aux= lista->ultimo+1;
        while(posicion<=aux)
        {
            lista->prestadores[aux+1]=lista->prestadores[aux];
            aux--;
            costosAltaLSO[0]=costosAltaLSO[0] + 1;
            esfMaxAux++;
        }
        lista->prestadores[posicion]=x;
        lista->ultimo++;
        esfMaxAux++;
        costosAltaLSO[0] += 1;
        costosAltaLSO[2] = costosAltaLSO[2] + 1;
        if(esfMaxAux>costosAltaLSO[1])
            costosAltaLSO[1]=esfMaxAux;
        return 1;
    }
        else
    {
        return -1;
    }
}

int baja_LSO(LSO *lista,prestador x)
{
    int decision;
    int pos;
    int aux, aux_INF,esfMaxAux=0;
    if(localizar_LSO(*lista,x.DNI,&pos,0))
    {
        if((lista->prestadores[pos].DNI == x.DNI) &&
         (strcmp(lista->prestadores[pos].celular, x.celular) == 0) &&
         (strcmp(lista->prestadores[pos].domicilio, x.domicilio) == 0) &&
         (strcmp(lista->prestadores[pos].email, x.email) == 0) &&
         (strcmp(lista->prestadores[pos].nom_y_ape, x.nom_y_ape) == 0) &&
         (strcmp(lista->prestadores[pos].servicios, x.servicios) == 0))
        {
            aux=pos;
            while(aux<lista->ultimo)
            {
                lista->prestadores[aux]=lista->prestadores[aux+1];
                aux++;
                costosBajaLSO[0]=costosBajaLSO[0] + 1;
                esfMaxAux++;
            }
            aux_INF=lista->ultimo;
            lista->prestadores[aux_INF+1].DNI=0;
            lista->prestadores[lista->ultimo].DNI=INFINITO;
            lista->ultimo--;
            esfMaxAux++;
            costosBajaLSO[0] +=1;
            costosBajaLSO[2] = costosBajaLSO[2] + 1;
            if(esfMaxAux>costosBajaLSO[1])
                costosBajaLSO[1]=esfMaxAux;
            return 1;
        }
    }
    else
    {
        return 0;
    }
}

prestador evocar_LSO(LSO lista, int x)
{
    int pos;
    prestador aux = {0,"x","x","x","x","x"};
    if(localizar_LSO(lista,x,&pos,1)){
        return lista.prestadores[pos];
    }
    else
    {
        return aux;
    }
}

int mostrar_LSO(LSO lista) {
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
#endif // LSO_H_INCLUDED
