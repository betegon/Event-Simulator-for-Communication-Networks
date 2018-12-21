#include "library2.h"

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


int main(int argc, char **argv){

    int pkt_numero, i, recursos, fuente,k,x,cont,j;
	float tiempo_primera_llegada, tiempollegadas, tiemposistema,tiempo2,tiempo3,p_perdida,pkts_perdidos,pkts_generados, tiempo_corriendo;	
	
	FILE*t_entre_llegadas;	// fichero para el Tiempo entre llegadas.
	FILE*t_en_sistema;		// fichero para el Tiempo en el sistema.
	FILE*fich_perdida;		// fichero para la probabilidad de perdida.
	FILE*recursos_ocupados;	// Fichero para los recursos ocupados con cada fuente.
	t_entre_llegadas = fopen("tllegadas.txt","w");		
	t_en_sistema = fopen("tsistema.txt","w");
	fich_perdida = fopen("prob_perdida.txt","w");
	recursos_ocupados = fopen("re_ocu.txt","w");
	
	time_t t;
	srand((unsigned) time(&t));
	
	for(j=0;j<NMEDIDAS;j++){ // numero de medidas para calcular la media en Matlab
		
		for (k=1;k<=NFUENTES;k++){ // numero de fuentes
				pkt_numero = 0; 	// Se inicializa el numero de pkts.
				tiempo_corriendo = TIEMPO_INICIAL;// Se inicializa el tiempo, se actualiza tras cada pkt nuevo.
	
			// Generacion e insercion del evento genesis de cada fuente.	
			for(i = 1; i<=k; i++){ // k es el numero de fuentes que hay.
				tiempo_primera_llegada = random_poisson(LLEGADAS_FUENTE_LIBRE*1.0);
				// llegada del primer pkt. 0 + v.a poisson(usando LLEGADAS_FUENTE_LIBRE)
				tiempo_corriendo = TIEMPO_INICIAL + tiempo_primera_llegada;  
				//i representa la fuente que genera el pkt
				InsertarEvento(&lista_eventos,CrearEvento(tiempo_corriendo,PKT_IN,i)); 
			}
			//generacion e insercion del evento final. lo genera la fuente 0 (no importa la fuente que lo genere).
			InsertarEvento(&lista_eventos,CrearEvento(TIEMPO_FINAL,PKT_END, 0)); 			
			//puts("LISTA DE EVENTOS:");
			//PintarLista (&lista_eventos);
			printf("\n Ha/n llegado %i pkts.\n",k);
			//getchar(); // pausa el programa hasta que el usuario pulse una tecla.
			// comentar la linea anterior para mayor rapidez.

			/*
			Tras la generacion del evento inicial y final 
			se entra en un bucle del que se sale al llegar al evento final
			*/
			pkts_perdidos = 0; // de momento no hemos perdido ningun pkt.
			pkts_generados = k; // hemos generado el primer pkt de cada fuente, el ultimo no le contamos porque se analiza difernete. (pkt_end)
			recursos = RECURSOS_TOTALES;
			x=0; // variable auxiliar para salir de while 	
			cont = 0;
			
			while (x!=10){ //while hasta que llegue un pkt tipo PKT_END y se acabe.
				cont++;
				
				if(recursos!=0){ // if para guardar en fichero si todos los recursos estan ocupados
					fprintf(recursos_ocupados,"%f 1 \n",lista_eventos->tiempo); //Si hay recursos guardamos el tiempo y un 1
				}else{
					fprintf(recursos_ocupados,"%f 0 \n",lista_eventos->tiempo);//Si no hay recursos guardamos el tiempo y un 0
				}
				switch (lista_eventos->tipo) {
					
				case PKT_IN:
					pkts_generados++; // Se genera un pkt mas
					if(recursos!=0){
						recursos--; // Se tiene un recurso disponible menos
						tiemposistema = random_poisson(MU*1.0);
						fprintf(t_en_sistema,"%f \n",tiemposistema);	//Guardamos el tiempo que va a permanecer el paquete en el sistema
						//Crear evento de Tx del paquete que llega
						tiempo3 = lista_eventos->tiempo + tiemposistema;
						InsertarEvento(&lista_eventos,CrearEvento(tiempo3,PKT_OUT,lista_eventos->fuente));
					} else{	// Si no hay recursos disponibles
						pkts_perdidos++; // se pierde el pkt
						tiemposistema = random_poisson(LLEGADAS_FUENTE_LIBRE); // la fuente perdio el pkt y generara otro cuando toque.
						tiempo3 = lista_eventos->tiempo + tiemposistema;
						InsertarEvento(&lista_eventos,CrearEvento(tiempo3,PKT_IN,lista_eventos->fuente));
						//printf("se ha perdido 1 pkt, en total: %f pkts perdidos\n",pkts_perdidos);
					}
					break;
				case PKT_OUT:
					recursos++;
					fuente = lista_eventos->fuente;
					fprintf(t_entre_llegadas,"%f \n",lista_eventos->tiempo);	
					// Tiempo de paquete que llega para calcular el tiempo entre llegadas.
					// Creacion e insercion  de un evento nuevo de llegada
					tiempo2 = lista_eventos->tiempo + random_poisson(LLEGADAS_FUENTE_LIBRE);
					InsertarEvento(&lista_eventos,CrearEvento(tiempo2,PKT_IN,fuente));
					//printf("Paquete Transmitido\n");
					break;
				case PKT_END:
					p_perdida = (pkts_perdidos/pkts_generados)*100;
					fprintf(fich_perdida,"%f\n",p_perdida);	//Guardamos el tiempo que va a permanecer el paquete en el sistema
					x = 10; // variable auxiliar para final el while.
					break;
				}
				//Avanza al siguiente evento de la lista
				//PintarLista(&lista_eventos);
				BorrarEvento(&lista_eventos,lista_eventos->tiempo);	
			}
			printf("Sistema analizado con %i fuente/s, se borra la lista de eventos.\n\n",k);
			BorrarLista(&lista_eventos);	
		}
		printf("Finalizada la medida %i \n",j+1);
	}	
	puts("Programa Finalizado");
}