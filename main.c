#include "library2.h"

int main(int argc, char **argv){

	int pkt_numero, i; 
    float tiempo_primera_llegada, tiempo_corriendo, tiempo, tiemposistema;
	
	FILE*t_entre_llegadas;	// fichero para almacenar el Tiempo entre llegadas.
	FILE*t_en_sistema;		// fichero para almacenar el Tiempo en el sistema.
    t_entre_llegadas = fopen("tllegadas.txt","w");	// Fichero de escritura
	t_en_sistema = fopen("tsistema.txt","w");
	
	pkt_numero = 0; 	// Se inicializa el numero de pkts.
	tiempo_corriendo = TIEMPO_INICIAL;// Se inicializa el tiempo, se actualiza tras cada pkt nuevo.
	
	// Generacion e insercion del evento genesis:
	tiempo_primera_llegada = random_poisson(LAMBDA);
	tiempo_corriendo += tiempo_primera_llegada;  
    InsertarEvento(&lista_eventos,CrearEvento(tiempo_corriendo,PKT_IN)); // Creacion e insercion del evento en la lista.

	// Generacion en insercion del evento final:
	InsertarEvento(&lista_eventos,CrearEvento(TIEMPO_FINAL, PKT_END)); // el tiempo en el que llega este pkt es 30, marcando el fin de la simulacion.
	
	// La lista debe contenter el primer y ultimo evento:
	PintarLista(&lista_eventos); 
    
	// Se muestra al usuario que ha llegado un pkt (sin tener en cuenta el final):
	printf("llega 1 pkt.\n");

	// se pausa el programa esperando interaccion del usuario.
    getchar(); 

	// Bucle infinito usando i como contador del numero de iteraciones que se realizan.
	for (i=1; i>=1; i++){
		
		// Dependiendo del tipo de pkt se realiza una u otra accion.
		switch ( lista_eventos->tipo) {
			
		case PKT_IN: 
			
			// Se escribe el tiempo en el que llega el pkt para conseguir el tiempo entre llegadas:
			fprintf(t_entre_llegadas,"%f \n",lista_eventos -> tiempo);	

			//Creacion e insercion de un evento nuevo de llegada:
			tiempo = (lista_eventos->tiempo) + random_poisson(LAMBDA);	
			InsertarEvento(&lista_eventos,CrearEvento(tiempo, PKT_IN));
			tiemposistema = random_poisson(MU); // tiempo que va a permanecer en el sistema.
		  	fprintf(t_en_sistema,"%f \n",tiemposistema); //Se escribe el tiempo que va a permanencia del pkt en el sistema.
		  	
			// Creacion e insercion de un evento nuevo de salida:
		  	tiempo = (lista_eventos->tiempo) + tiemposistema;
		  	InsertarEvento(&lista_eventos,CrearEvento(tiempo,PKT_OUT));
		  	break;

		case PKT_OUT:
			
			puts("Paquete Transmitido.");
			tiemposistema = lista_eventos->tiempo;
			fprintf(t_en_sistema,"%f \n",tiemposistema); // se escribe en fichero el tiempo.
		  	break;

		case PKT_END:
			puts("Programa Finalizado");
			exit(1);
			break;
		}
		printf("iteracion %i \n",(i));
		PintarLista(&lista_eventos);

		// se elimina de la lista el evento puesto que ya ha sido procesado.	
		BorrarEvento(&lista_eventos,lista_eventos->tiempo);		
	}
}
