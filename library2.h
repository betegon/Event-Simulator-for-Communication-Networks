#ifndef LIBRARY2_H_
#define LIBRARY2_H_
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
// Tipos de evento
#define PKT_END 0 // tipo  final
#define PKT_IN 1  // tipo llegada
#define PKT_OUT 2 // tipo salida
// Tiempo fijados para la simulacion.
#define TIEMPO_INICIAL 0
#define TIEMPO_FINAL 10000
// Parametros del grupo 2
#define MU 0.0055555  // 1/Ts= 1/(180seg) = 0.0055555 (PKTS/SEG)
#define RECURSOS_TOTALES  10 //engset 40 
#define LLEGADAS_FUENTE_LIBRE 0.001111111 // engset 0.00166667 TASA LLEGADAS POR FUENTE LIBRE  (PKTS/SEGUNDO) 
#define NFUENTES  40 
#define NMEDIDAS  10 // 	Numero de medidas que se quieren realizar para calcular la media. 

// Ejemplo Tema 5 DPR:
/*
a = 	lambda 			  *  Ts
a = llegadas fuente libre * tiempo servicio 
	 0.1 (llamadas/minuto)* 2min 
*/
typedef struct evento 
{ 
	float tiempo; 
	int tipo; 
	int fuente; 
	struct evento *next; // puntero al siguiente evento.
} evento; 

// VARIABLE GLOBAL
evento *lista_eventos = NULL; //lista_eventos es un puntero a una estructura de tipo evento.


// Crear un nuevo elemento de tipo evento en la lista dados los miembros de la estructura.
evento *CrearEvento(float tnuevo, int tipo, int fuente){
        evento *newp;
        newp = (evento *) malloc (sizeof(evento)); // reservar espacio para el evento.
        newp -> tiempo = tnuevo;
        newp -> tipo = tipo;
		newp -> fuente = fuente;
		newp -> next = NULL;
        return newp;
}  

/*
para las funciones de insercion y borrado no se necesita devolver un evento *, no es necesario.
por eso son de tipo void.

head apunta a la variable global lista_eventos. el efecto es que el contenido 
de lista_eventos de mantiene actualizado automaticamente.
por tanto no hace falta devolver un puntero  evento* al inicio 
de la lista en las funciones de insertar y borrar.
*/


//Insertar elemento nuevo en la lista
/* No se contemplan entradas con el mismo tiempo, se supone 
el tiempo continuo y por tanto diferente para cada evento.*/
void InsertarEvento(evento **head, evento *newp)
//head: puntero a puntero del inicio de la lista
// preparamos *newp evento que se insertara
{
	evento **tracer = head; // tracer apunta al puntero de inicio de la lista.
	//while(*tracer !=NULL) ES LO MISMO QUE while(*tracer)
	while((*tracer) && (*tracer)->tiempo < (*newp).tiempo){		
		tracer = &(*tracer)->next;
	}
	newp -> next = *tracer;
	*tracer = newp;
}

// Borrar el elemento de la lista que coincida con el tiempo que se desee
// si no existe un evento con ese tiempo, no pasa nada. Se puede poner un print o devolver un error...
void BorrarEvento(evento **head, float tborrar)
{
	evento *old;
	evento **tracer = head;
	
	while((*tracer) && !(tborrar == (*tracer)->tiempo))
		tracer = &(*tracer)->next;

	if(tborrar == (*tracer)->tiempo)
	{
		old = *tracer;
		*tracer = (*tracer)->next;
		free(old); // Liberar el espacio del evento
	}
}

// Pintar la Lista.
void PintarLista(evento **head)
{
	evento **tracer = head;
	while (*tracer) {
		printf("tiempo %f tipo %i fuente %i \n",(*tracer)->tiempo,(*tracer)->tipo,(*tracer)->fuente);
		tracer = &(*tracer)->next;
	}
}

// Borrar la lista, destruirla.
void BorrarLista(evento **head) {
	evento *current = *head;
	evento* next;

    while (current != NULL)
    {
       next = current->next;
       free(current);
       current = next;
    }
    *head = NULL;
}


// Exponencial negativa.
double random_poisson(double lambda){ 
    double x, poisson;
    int i;
    for (i=0;i<5;i++){
        x =(double)(rand()*1.0/RAND_MAX);
        poisson = (-(1/lambda)*log(x))*1; 
        //printf ("%lf",x);
    }
	return poisson;
}

#endif
