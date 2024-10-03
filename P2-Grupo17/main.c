#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ABB.h"
#include "LSO.h"
#include "LSOBB.h"
/*
CONCLUSION
A continuacion se adjuntan los costos de las estructuras trabajadas en base al archivo
proporcionado por la catedra y junto a ellas una breve descripcion:

                                ARBOL BINARIO
Altas Exitosas:
Máx: 1.500 | Med: 1.500
La eficiencia en la inserción es muy buena, indicando que el ABB es la mejor opción
para altas exitosas.
Bajas Exitosas:
Máx: 1.500 | Med: 0.799
La baja en el ABB es altamente efectiva, con un costo promedio significativamente menor
que en otras estructuras.
Evocaciones Exitosas:
Máx: 27 | Med: 11.000
Aunque hay un costo máximo un poco elevado, el promedio es normal, mostrando buena
eficiencia en la recuperación de datos.
Evocaciones Fallidas:
Máx: 25 | Med: 13.000
Se mantiene la tendencia de costos moderados, lo que resalta la eficiencia del ABB
incluso en casos fallidos.

                          LISTA SECUENCIAL ORDENADA
Altas Exitosas:
Máx: 108 | Med: 27.000
La LSO presenta un costo máximo y promedio mucho más altos, lo que refleja su ineficiencia
en altas.
Bajas Exitosas:
Máx: 97 | Med: 30.000
Similar a las altas, la baja en LSO resulta costosa, siendo la estructura menos eficiente.
Evocaciones Exitosas:
Máx: 98 | Med: 36.000
La evocación muestra los costos más altos de todas las estructuras, indicando que la
recuperación de datos es muy ineficiente.
Evocaciones Fallidas:
Máx: 83 | Med: 31.000
Los costos en los casos fallidos son igualmente altos, confirmando la ineficiencia de
esta estructura.

                    LISTA SECUENCIAL ORDENADA CON BUSQUEDA BINARIA
Altas Exitosas:
Máx: 107 | Med: 26.000
La LSOBB mejora ligeramente en comparación con la LSO, aunque sigue siendo menos eficiente
que el ABB.
Bajas Exitosas:
Máx: 96 | Med: 29.000
Mantiene una eficiencia intermedia, siendo más eficiente que la LSO, pero aún menos que el ABB.
Evocaciones Exitosas:
Máx: 13 | Med: 9.000
Esta estructura muestra un desempeño sólido en evocaciones exitosas, siendo la más eficiente
de las tres en este aspecto.
Evocaciones Fallidas:
Máx: 15 | Med: 12.000
La LSOBB se sitúa en un punto intermedio, con costos más manejables que la LSO.

CONCLUSIONES GENERALES:
El ABB es la opción más eficiente en términos de costos, sobresaliendo en altas y bajas.
La LSO es la menos recomendable debido a su alto costo en todas las operaciones.
La LSOBB se posiciona como una alternativa intermedia, mejorando respecto a la LSO pero sin
alcanzar la eficiencia del ABB.
 */
char* to_lower_str(char *str) {
    int i;
    for (i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

int memorizar_datos(ABB *arbol, LSO *listaO,LSOBB *listaBB){
    FILE *file;
    int operacion;
    int aux_DNI;
    prestador aux, aux_evocar;
    if((file=fopen("Operaciones-Prestadores.txt","r"))==NULL){
        printf("No hay archivo disponible. Ingrese uno para operar.\n");
        return 0;
    }
    else
    {
        while(!feof(file)){
        fscanf(file,"%d\n",&operacion);
        fscanf(file,"%d\n",&aux.DNI);
        if((operacion == 1 || operacion == 2 ||operacion == 3)){
            if((operacion == 1 || operacion == 2)&& (aux.DNI>0))
            {
                        fgets(aux.nom_y_ape,sizeof(aux.nom_y_ape),file);
                        strcpy(aux.nom_y_ape,to_lower_str(aux.nom_y_ape));
                        fgets(aux.servicios,sizeof(aux.servicios),file);
                        strcpy(aux.servicios,to_lower_str(aux.servicios));
                        fgets(aux.domicilio,sizeof(aux.domicilio),file);
                        strcpy(aux.domicilio,to_lower_str(aux.domicilio));
                        fgets(aux.email,sizeof(aux.email),file);
                        strcpy(aux.email,to_lower_str(aux.email));
                        fgets(aux.celular,sizeof(aux.celular),file);
                        strcpy(aux.celular,to_lower_str(aux.celular));
                        if(operacion == 1){
                            alta_ABB(arbol, aux);
                            if(listaBB->ultimo != 109){
                                alta_LSOBB(listaBB, aux);
                            }
                            if(aux_DNI<99999999 && listaO->ultimo != 109)
                            {
                                alta_LSO(listaO, aux);
                            }
                    }
                    else
                    {
                        baja_ABB(arbol,aux.DNI,aux);
                        baja_LSOBB(listaBB,aux);
                        if(aux_DNI<99999999)
                        {
                            baja_LSO(listaO,aux);
                        }
                    }
                }
                if(operacion == 3)
                {
                    evocar_LSO(*listaO,aux.DNI);
                    evocar_LSOBB(*listaBB,aux.DNI);
                    evocar_ABB(*arbol, aux.DNI);
                }
            }
            else
            {
                printf("Codigo invalido\n");
            }
        }
    }

}
int main()
{
    ABB arb;
    LSO lista_ord;
    LSOBB lista_ordBB;
    int opcion, opcionM;
    float esfMedioAltaLSO, esfMedioBajaLSO,esfMedioAltaLSOBB,
    esfMedioBajaLSOBB,esfMedioAltaABB,esfMedioBajaABB,
    esfMedioEvocarExitoLSO,esfMedioEvocarFracasoLSO,
    esfMedioEvocarExitoLSOBB,esfMedioEvocarFracasoLSOBB,
    esfMedioEvocarExitoABB,esfMedioEvocarFracasoABB;
    inicializar_ABB(&arb);
    iniciar_LSO(&lista_ord);
    iniciar_LSOBB(&lista_ordBB);
    if( memorizar_datos(&arb,&lista_ord,&lista_ordBB)== 0){
        return 0;
    }
       while(opcion!=3){
        printf("--------------------MENU--------------------\n");
        printf("[1]Comparacion de estructuras\n");
        printf("[2]Mostrar estructuras\n");
        printf("[3]Salir\n");
        printf("--------------------------------------------\n");
        printf("Ingrese una opcion: ");
        while(scanf("%d", &opcion) != 1 || (opcion < 1 || opcion > 3)) {
            fflush(stdin);
            printf("\nError: Debe ingresar un valor valido.");
            printf("\nIntentelo nuevamente: ");
    }
        if(opcion==1){
            system("cls");
            if(arb.raiz == NULL && lista_ord.ultimo == -1 && lista_ordBB.ultimo==-1)
            {
                printf("Todas las estructuras estan vacias\n");
                printf("Presione enter para volver al menu.\n");
                getchar();
                getchar();
                system("cls");
            }
            else
            {
                printf("--------------------------------Arbol Binario-------------------------------\n");

                printf("Esfuerzo Maximo de Alta Exitosa %.3f\n",costosAltaABB[1]);

                if(costosAltaABB[2]==0)
                    esfMedioAltaABB = 0;
                else
                    esfMedioAltaABB = (costosAltaABB[0] / costosAltaABB[2]);
                printf("Esfuerzo Medio de Alta Exitosa: %.3f\n",esfMedioAltaABB);

                printf("Esfuerzo Maximo de Baja Exitosa: %.3f\n",costosBajaABB[1]);

                if(costosBajaABB[2]==0)
                    esfMedioBajaABB = 0;
                else
                    esfMedioBajaABB = (costosBajaABB[0] / costosBajaABB[2]);
                printf("Esfuerzo Medio de Baja Exitosa: %.3f\n",esfMedioBajaABB);

                printf("Esfuerzo Maximo de Evocacion Exitosa: %d\n",costosEvocarExitoABB[1]);

                if(costosEvocarExitoABB[2]==0)
                    esfMedioEvocarExitoABB=0;
                else
                    esfMedioEvocarExitoABB=(costosEvocarExitoABB[0]/costosEvocarExitoABB[2]);

                printf("Esfuerzo Medio de Evocacion Exitosa %.3f\n",esfMedioEvocarExitoABB);

                printf("Esfuerzo Maximo de Evocacion con Fracaso: %d\n",costosEvocarFracasoABB[1]);

                if(costosEvocarFracasoABB[2]==0)
                    esfMedioEvocarFracasoABB=0;
                else
                    esfMedioEvocarFracasoABB=(costosEvocarFracasoABB[0]/costosEvocarFracasoABB[2]);
                printf("Esfuerzo Medio de Evocacion con Fracaso: %.3f\n",esfMedioEvocarFracasoABB);

                printf("----------------------------------------------------------------------------\n\n");



                printf("-------------------------------------LSO------------------------------------\n");

                printf("Esfuerzo Maximo de Alta Exitosa %d\n",costosAltaLSO[1]);

                if(costosAltaLSO[2]==0)
                    esfMedioAltaLSO=0;
                else
                    esfMedioAltaLSO=(costosAltaLSO[0]/costosAltaLSO[2]);
                printf("Esfuerzo Medio de Alta Exitosa: %.3f\n",esfMedioAltaLSO);

                printf("Esfuerzo Maximo de Baja Exitosa: %d\n",costosBajaLSO[1]);

                if(costosBajaLSO[2]==0)
                    esfMedioBajaLSO=0;
                else
                    esfMedioBajaLSO=(costosBajaLSO[0]/costosBajaLSO[2]);
                printf("Esfuerzo Medio de Baja Exitosa: %.3f\n",esfMedioBajaLSO);

                printf("Esfuerzo Maximo de Evocacion Exitosa: %d\n",costosEvocarExitoLSO[1]);

                if(costosEvocarExitoLSO[2]==0)
                    esfMedioEvocarExitoLSO=0;
                else
                    esfMedioEvocarExitoLSO=(costosEvocarExitoLSO[0]/costosEvocarExitoLSO[2]);

                printf("Esfuerzo Medio de Evocacion Exitosa %.3f\n",esfMedioEvocarExitoLSO);

                printf("Esfuerzo Maximo de Evocacion con Fracaso: %d\n",costosEvocarFracasoLSO[1]);

                if(costosEvocarFracasoLSO[2]==0)
                    esfMedioEvocarFracasoLSO=0;
                else
                    esfMedioEvocarFracasoLSO=(costosEvocarFracasoLSO[0]/costosEvocarFracasoLSO[2]);
                printf("Esfuerzo Medio de Evocacion con Fracaso: %.3f\n",esfMedioEvocarFracasoLSO);

                printf("----------------------------------------------------------------------------\n\n");



                printf("--------------------------LSO con Busqueda Binaria--------------------------\n");

                printf("Esfuerzo Maximo de Alta Exitosa %d\n",costosAltaLSOBB[1]);

                if(costosAltaLSOBB[2]==0)
                    esfMedioAltaLSOBB=0;
                else
                    esfMedioAltaLSOBB=(costosAltaLSOBB[0]/costosAltaLSOBB[2]);
                printf("Esfuerzo Medio de Alta Exitosa: %.3f\n",esfMedioAltaLSOBB);

                printf("Esfuerzo Maximo de Baja Exitosa: %d\n",costosBajaLSOBB[1]);

                if(costosBajaLSOBB[2]==0)
                    esfMedioBajaLSOBB=0;
                else
                    esfMedioBajaLSOBB=(costosBajaLSOBB[0]/costosBajaLSOBB[2]);
                printf("Esfuerzo Medio de Baja Exitosa: %.3f\n",esfMedioBajaLSOBB);

                printf("Esfuerzo Maximo de Evocacion Exitosa: %d\n",costosEvocarExitoLSOBB[1]);

                if(costosEvocarExitoLSOBB[2]==0)
                    esfMedioEvocarExitoLSOBB=0;
                else
                    esfMedioEvocarExitoLSOBB=(costosEvocarExitoLSOBB[0]/costosEvocarExitoLSOBB[2]);

                printf("Esfuerzo Medio de Evocacion Exitosa %.3f\n",esfMedioEvocarExitoLSOBB);

                printf("Esfuerzo Maximo de Evocacion con Fracaso: %d\n",costosEvocarFracasoLSOBB[1]);

                if(costosEvocarFracasoLSOBB[2]==0)
                    esfMedioEvocarFracasoLSOBB=0;
                else
                    esfMedioEvocarFracasoLSOBB=(costosEvocarFracasoLSOBB[0]/costosEvocarFracasoLSOBB[2]);
                printf("Esfuerzo Medio de Evocacion con Fracaso: %.3f\n",esfMedioEvocarFracasoLSOBB);

                printf("----------------------------------------------------------------------------\n\n");
                printf("Presione enter para volver al menu.");
                getchar();
                getchar();
                system("cls");
            }
        }

        if(opcion==2){
            printf("Que estructura desea observar?\n");
            printf("[1]Arbol Binario de busqueda\n");
            printf("[2]Lista Ordenada de busqueda binaria\n");
            printf("[3]Lista Ordenada\n");
            scanf("%d",&opcionM);
            system("cls");
            switch(opcionM)
            {
                case 1:
                    system("cls");
                    mostrar_ABB_con_paginacion(arb,2);
                break;
                case 2:
                    mostrar_LSOBB(lista_ordBB);
                break;
                case 3:
                    mostrar_LSO(lista_ord);
                break;
                default:
                    printf("Opcion incorrecta");
                break;
            }
        }
    }
}
