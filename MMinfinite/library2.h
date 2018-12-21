#ifndef LIBRARY2_H_
#define LIBRARY2_H_
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
// tipos de evento
#define PKT_END 0 // tipo  final
#define PKT_IN 1  // tipo llegada
#define PKT_OUT 2 // tipo salida
// tiempo fijados para la simulacion.
#define TIEMPO_INICIAL 0
#define TIEMPO_FINAL 30
// parametros del grupo
#define LAMBDA 20 // Tasa de llegadas.
#define MU 10     // 1/Ts= 1/(100*10^(-3)) = Tasa muerte o tasa de salida.

typedef struct evento 
{ 
	float tiempo; 	
	int tipo;
	struct evento *next;  // puntero al siguiente evento.
	} evento;  


// VARIABLE GLOBAL
evento *lista_eventos = NULL; //lista_eventos es un puntero a una estructura de tipo evento.


// Crear un nuevo elemento de tipo evento en la lista dados los miembros de la estructura.
evento *CrearEvento(float tnuevo, int tipo){
        evento *newp;
        newp = (evento *) malloc (sizeof(evento)); // reservar espacio para el evento.
        newp -> tiempo = tnuevo;
        newp -> tipo = tipo;
		newp -> next = NULL;
        return newp;
}  
/*
Las funciones de insercion y borrado no necesitan devolver un evento *. por eso son de tipo void.
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
	//while(*tracer !=NULL) es lo mismo que while(*tracer)
	while((*tracer) && (*tracer)->tiempo < (*newp).tiempo){		
		tracer = &(*tracer)->next;
	}
	newp -> next = *tracer;
	*tracer = newp;
}

// Borrar el elemento de la lista que coincida con el tiempo que se desee
// si no existe un evento con ese tiempo, no ocurre nada.
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

// Pintar La lista
void PintarLista(evento **head)
{
	evento **tracer = head;
	while (*tracer) {
		printf("tiempo %f tipo %i \n",(*tracer)->tiempo,(*tracer)->tipo);
		tracer = &(*tracer)->next;
	}
}

// Exponencial negativa 
double random_poisson(float lambda){
    double x, poisson;
    int i;
    time_t t;
    srand((unsigned)time(&t));
        x =(double)(rand()%(int)100);
        x = x/100; // hasta aqui es una variable aleatoria uniforme entre 0 y 1.
        poisson = (-(1/lambda)*log(x))*1; 
    return poisson;
}
#endif