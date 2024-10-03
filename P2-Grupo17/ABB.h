#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#include <conio.h>
#include "Prestador.h"
typedef struct {
    prestador info;
    struct Nodo *pd;
    struct Nodo *pi;
}Nodo;

typedef struct {
    Nodo *raiz;
}ABB;

typedef struct{
    Nodo *info;
    struct Nodo_pila *ps;
}Nodo_pila;

typedef struct{
    Nodo_pila *raiz;

}pila;

void inicializar_pila(pila *a)
{
    a->raiz=NULL;

}

int push_pila(pila *a, Nodo* n)
{
    Nodo_pila *new_nodo;
    new_nodo=(Nodo_pila *)malloc(sizeof(Nodo_pila));
    if(new_nodo == NULL){
        return -1;
    }
    new_nodo->info=n;
    new_nodo->ps=NULL;
   if(a->raiz == NULL){
    a->raiz=new_nodo;
   }
   else
   {
        new_nodo->ps=a->raiz;
        a->raiz=new_nodo;

   }
   return 1;
}

Nodo *pull_pila(pila *a) {
    Nodo *aux = a->raiz->info;
    Nodo_pila *temp = a->raiz;
    a->raiz = a->raiz->ps;
    free(temp);
    return aux;
}

void inicializar_ABB(ABB *arb)
{
    arb->raiz=NULL;
}

float costosAltaABB[3] = {0}; //0: Sumatoria actualizaciones de punteros y copia de info. 1: Costo Maximo de Alta. 2: Cantidad de altas.
float costosBajaABB[3] = {0}; //0: Sumatoria actualizaciones de punteros y copia de info. 1: Costo Maximo de Baja. 2: Cantidad de bajas.
int costosEvocarExitoABB[3] = {0}; //0: Sumatoria comparaciones con x. 1: Costo Maximo de Evocar exitosamente. 3: Cantidad de evocaciones exitosas.
int costosEvocarFracasoABB[3] = {0};//0: Sumatoria comparaciones con x. 1: Costo Maximo de Evocar con fracaso. 3: Cantidad de evocaciones con fracaso.

int localizar_ABB(ABB arbol, int x, Nodo **pos, Nodo **papi, int marca) {
    Nodo *aux = arbol.raiz;
    *papi = NULL;
    if(marca){
        int esfMaxAux=0;
        while (aux != NULL && aux->info.DNI != x) {
        *papi = aux;  // Actualizamos el nodo padre
        if (x < aux->info.DNI)
            aux = aux->pi;  // Vamos hacia la izquierda
        else
            aux = aux->pd;  // Vamos hacia la derecha
            esfMaxAux+=2;
        }
        esfMaxAux++;
        *pos = aux;  // Actualizamos *pos al nodo encontrado o NULL si no existe
        if(aux!=NULL){
            costosEvocarExitoABB[0]+=esfMaxAux;
            costosEvocarExitoABB[2]++;
            if(esfMaxAux>costosEvocarExitoABB[1])
                costosEvocarExitoABB[1]=esfMaxAux;
            return 1;
        }
        else{
            costosEvocarFracasoABB[0]+=esfMaxAux;
            costosEvocarFracasoABB[2]++;
            if(esfMaxAux>costosEvocarFracasoABB[1])
                costosEvocarFracasoABB[1]=esfMaxAux;
            return 0;
        }
        *pos = aux;
    }
    else{
        while (aux != NULL && aux->info.DNI != x) {
        *papi = aux;  // Actualizamos el nodo padre
        if (x < aux->info.DNI)
            aux = aux->pi;  // Vamos hacia la izquierda
        else
            aux = aux->pd;  // Vamos hacia la derecha
        }
        *pos = aux;
        return (aux != NULL);  // Retornamos si el nodo fue encontrado o no
    }
}

int alta_ABB(ABB *arbol, prestador x)
{
    Nodo *aux;
    Nodo *nuevo_nodo;
    Nodo *papini;
    float esfMaxAltaAux=0;
    if(localizar_ABB(*arbol, x.DNI, &aux,&papini,0)){
        return -1;
    }
    else
    {
        nuevo_nodo= (Nodo *)malloc(sizeof (Nodo));
        if(nuevo_nodo == NULL){
            return -1;
        }
        nuevo_nodo->info=x;//copia de info
        costosAltaABB[0] += 1;
        esfMaxAltaAux++;
        nuevo_nodo->pd=NULL;
        nuevo_nodo->pi=NULL;
        if(arbol->raiz == NULL){
            arbol->raiz=nuevo_nodo; //mod puntero
            costosAltaABB[0] += 0.5;
            esfMaxAltaAux += 0.5;
        }
        else
        {
            if(papini->info.DNI<x.DNI)
            {
                papini->pd=nuevo_nodo; //mod puntero
            }
            else
            {
                papini->pi=nuevo_nodo;
            }
            costosAltaABB[0] += 0.5;
            esfMaxAltaAux += 0.5;
        }
        costosAltaABB[2]+=1;
        if(esfMaxAltaAux>costosAltaABB[1])
            costosAltaABB[1] = esfMaxAltaAux;
        return 1;
    }
}

int baja_ABB(ABB *arbol,int DNI,prestador x)
{
    Nodo *aux;
    Nodo *padre_aux;
    Nodo *padre_reemplazo;
    Nodo *reemplazo;
    float esfMaxBajaAux=0;
    if(!localizar_ABB(*arbol, DNI,&aux,&padre_aux,0) ||
        (aux->info.DNI != x.DNI) ||
        (strcmp(aux->info.celular, x.celular) != 0) ||
        (strcmp(aux->info.domicilio, x.domicilio) != 0) ||
        (strcmp(aux->info.email, x.email) != 0) ||
        (strcmp(aux->info.nom_y_ape, x.nom_y_ape) != 0) ||
        (strcmp(aux->info.servicios, x.servicios) != 0)) //Lo devolvemos al main al toque si no lo encuentra o no es igual
    return 0;

    ///Caso sin hijos
    else{
        if(aux->pi ==NULL && aux->pd == NULL){
            if(padre_aux == NULL){
                arbol->raiz = NULL;
            }
            else
            {
                if(padre_aux->pd==aux){
                    //padre_aux->pd = aux->pd;
                    padre_aux->pd=NULL;
                    }
                    else
                    {
                        if (padre_aux->pi=aux){
                        //padre_aux->pi = aux->pd;
                        padre_aux->pi = NULL;
                    }
                }
            }
            costosBajaABB[0] += 0.5;
            esfMaxBajaAux += 0.5;
            free(aux);
        }
    ///Caso con un hijo a derecha
    else if(aux->pi==NULL){
        if(aux==arbol->raiz)
            arbol->raiz=aux->pd;
        else if(padre_aux->pd==aux)
            padre_aux->pd = aux->pd;
        else if (padre_aux->pi=aux)
            padre_aux->pi = aux->pd;
        costosBajaABB[0] += 0.5;
        esfMaxBajaAux += 0.5;
        free(aux);
        }
    ///Caso con un hijo a izquierda
    else if(aux->pd==NULL){
        if(aux==arbol->raiz)
            arbol->raiz=aux->pi;
        else if (padre_aux->pd==aux)
            padre_aux->pd = aux->pi;
        else if(padre_aux->pi==aux)
            padre_aux->pi = aux->pi;
        costosBajaABB[0] += 0.5;
        esfMaxBajaAux += 0.5;
        free(aux);
    }
    ///Caso con dos hijos
    else if (aux->pd!=NULL && aux->pi!=NULL){
        padre_reemplazo=aux;
        reemplazo=aux->pi;
        while(reemplazo->pd!=NULL){
            padre_reemplazo = reemplazo;
            reemplazo = reemplazo->pd;
        }
        aux->info=reemplazo->info;//copia de info
        costosBajaABB[0] += 1;
        esfMaxBajaAux += 1;
        if(padre_reemplazo->pd == reemplazo)
            padre_reemplazo->pd = reemplazo->pi;
        else
            padre_reemplazo->pi = reemplazo->pi;
        costosBajaABB[0] += 0.5;
        esfMaxBajaAux += 0.5;
        free(reemplazo);
        }
    }
    costosBajaABB[2] += 1;
    if(esfMaxBajaAux>costosBajaABB[1])
        costosBajaABB[1] = esfMaxBajaAux;
    return 1;
}

prestador evocar_ABB(ABB arbol, int x){
    Nodo *aux;
    Nodo *papini;
    if(localizar_ABB(arbol, x,&aux,&papini,1))
    {
        return aux->info;
    }
}

int mostrar_ABB_con_paginacion(ABB arbol, int nodos_por_pagina) {
    pila p;
    inicializar_pila(&p);
    Nodo *aux = arbol.raiz;
    if (aux != NULL) {
        push_pila(&p, aux);
    }

    int contador_nodos = 0;  // Contador para nodos mostrados en la página actual
    int pagina_actual = 1;   // Número de página
    char opcion;

    // Procesamos mientras haya nodos en la pila
    while (p.raiz != NULL) {
        aux = pull_pila(&p);
        if (contador_nodos == 0) {
            printf("\n--- Página %d ---\n", pagina_actual);
        }

        mostrar_prestador(aux->info);  // Mostrar información del prestador

        // Apilamos los hijos derecho e izquierdo (primero derecho para que el izquierdo quede arriba en la pila)
        if (aux->pd != NULL) {
            push_pila(&p, aux->pd);
        }
        if (aux->pi != NULL) {
            push_pila(&p, aux->pi);
        }

        contador_nodos++;

        // Si alcanzamos la cantidad de nodos por página
        if (contador_nodos == nodos_por_pagina) {
            // Verificamos si hay más nodos en la pila para saber si es la última página
            if (p.raiz == NULL) {
                // Es la última página, solo permitir salir con 'Esc'
                printf("\n--- Última página ---\n");
                printf("\nNo hay más nodos para mostrar.\n");
                printf("Presione 'Esc' para salir...\n");
                do {
                    opcion = getch();  // Esperar a que el usuario presione 'Esc'
                } while (opcion != 27);  // ASCII 27 es 'Esc'
                system("cls");  // Limpiar la pantalla
                break;  // Salir de la función
            } else {
                // No es la última página, permitir avanzar o salir
                printf("\nPresione 'Enter' para continuar o 'Esc' para salir...\n");
                do {
                    opcion = getch();  // Obtener la opción del usuario
                    if (opcion == 27) {  // Si presiona 'Esc'
                        system("cls");  // Limpiar la pantalla
                        return 0;  // Salir de la función
                    }
                } while (opcion != 13);  // Continuar solo si se presiona 'Enter'
                system("cls");  // Limpiar la pantalla para la siguiente página
                // Reiniciar el contador de nodos para la próxima página
                contador_nodos = 0;
                pagina_actual++;
            }
        }
    }

    printf("\nSe han mostrado todos los nodos.\n");
    printf("Presione enter para volver al menú.\n");
    getchar();
    getchar();
    system("cls");
    return 1;

    if (arbol.raiz == NULL) {
        printf("El árbol está vacío.\n");
    }

    printf("\nFin de la muestra.\n");
    printf("Presione enter para volver al menú.\n");
    getchar();
    getchar();
    system("cls");
    return 1;
}

#endif // ABB_H_INCLUDED
