#if defined(_GLIBCXX_HAS_GTHREADS) 
#defined(_GLIBCXX_USE_C99_STDINT_TR1)
#endif

#include "main.h"
#include "apilado.h"
#include "tablero.h"
#include <iostream>
#include <Windows.h> //Sleep
#include <stdlib.h>  //cls
#include <SDL.h>
#include <SDL_thread.h>

//! TO DO:
//! Imprimir puntuación en la ventana al lado del tablero.
//! Imprimir el nivel del juego al lado del tablero
//!	Generar la pieza siguiente, y renderizarla al lado del tablero
//! Implementar incremento automático de la velocidad
//! Color en las piezas del tablero estático
//! Crear una clase para guardar el color de las casillas del tablero
//! Implementar refresco de la pantalla y eliminar los sleep introducidos

// VARIABLES GLOBALES
int Nivel = 0;	//1	//2	 //3  //4  //5  //6  //7  //8  //9 //10
Uint32 MS_Nivel[] = {2000, 1000, 900, 800, 700, 600, 500, 450, 400, 350, 300, 250}; //ms para cada intervalo


//Inicializa tableros lógico
Tablero tablero_dinamico; //Para comprobar los movimientos de las piezas
Tablero tablero_estatico; //Para guardar las piezas fijas.

Uint32 my_callbackfunc(Uint32 interval, void *param);
void bajar_pieza_si_puede(Pieza* p_pieza);

bool bajar_pieza = false;
bool pieza_bloqueada;
bool tablero_lleno = false;
bool cerrar_programa = false;


int main( int argc, char* args[] )
{
	Uint32 delay = MS_INTERVALO_MOV_INICIAL;
	Pieza* pieza;


	if( !inicializar() ) //Inicializa SDL y crea la ventana
		printf( "ERROR!\n" );
	else{
				
		SDL_Event eventos;   // Gestor (cola) de eventos
		SDL_RendererFlip flipType = SDL_FLIP_NONE;

		while(true){
			//! TO DO: Implementar incremento velocidad del programa	
			pieza = new Pieza;//Crear e inicializar pieza
			std::cout<< "PIEZA "<< pieza << " CREADA "<< std::endl;
			delay = SDL_AddTimer(delay, my_callbackfunc, pieza);
			pieza_bloqueada = false;
			while(true){

				Sleep(200);//ms //! TO DO: Implementar tasa de refresco de 60HZ
				//std::cout<< cerrar << " " << pieza<< std::endl;				
				while( SDL_PollEvent( &eventos ) != 0 ){ //Cola de eventos	
					if( eventos.type == SDL_QUIT ){ //Para cerrar (pulsando X de ventana)
						cerrar_programa = true;
						std::cout<<"TERMINASTE EL VIDEOJUEGO"<<std::endl;
						break;
					}
					else if( eventos.type == SDL_KEYDOWN ){
						Mueve_Pieza_Si_Se_Puede(eventos.key.keysym.sym, *pieza, tablero_estatico);
					}
				}// No sale del bucle hasta que la cola de eventos es 0		
				if(pieza_bloqueada){
					std::cout<<"LA PIEZA HA SIDO BLOQUEADA"<<std::endl;					
					delete pieza; //no funciona si la borro en el callback
					break;
				}
				if(cerrar_programa)
					break;
				if(tablero_lleno)
					break;
				if(bajar_pieza){
					bajar_pieza = false;
					bajar_pieza_si_puede(pieza);
				}
				Actualiza_Pantalla(*pieza, tablero_estatico); //renderizado de tablero con piezas fijas y actual pieza moviéndose
			}
			if(cerrar_programa)
				break;
			if(tablero_lleno)
				break;
		}
		Sleep(3000);//ms
		//! TO DO imprimir resultados (puntuación) en la ventana
	} 
	cerrar(); //Liberar recursos reservados
	

	std::cout<<"PROGRAMA FINALIZADO CORRECTAMENTE"<<std::endl;
	return 0;
}

void bajar_pieza_si_puede(Pieza* p_pieza){
	
	if(p_pieza!=nullptr){
		if(tablero_estatico.Comprueba_bajada(*p_pieza)){ //Si puede bajar

			p_pieza->coordenada.y_fila = p_pieza->coordenada.y_fila + 1;
			std::cout<< "PIEZA BAJADA AUTOMÁTICAMENTE "<<std::endl;
			Actualiza_Tablero_Dinamico(*p_pieza, tablero_dinamico);
			tablero_dinamico.imprime_tabla();//para debug en consola
		}
		else{
			//! Cuando no se puede bajar, aquí se pasa la pieza al tablero estático
			Actualiza_Tablero_Estatico(*p_pieza, tablero_estatico);//borra filas ocupadas

			std::cout<< "TABLERO ESTATICO COPIADO AL DINAMICO. ELIMINADO DE HUECOS "<<std::endl;
			tablero_dinamico = tablero_estatico;
			tablero_estatico.imprime_tabla();//para debug en consola
			pieza_bloqueada = true;
			
			if(p_pieza->coordenada.y_fila<=1){
				std::cout<<"FIN DEL JUEGO"<<std::endl;
				tablero_lleno=true;
			}
		}
	}
}

Uint32 my_callbackfunc(Uint32 interval, void *param_pieza)
{
	bajar_pieza = true;
	//Pieza* p_pieza = static_cast<Pieza*>(param_pieza);
	/*if(p_pieza!=nullptr){
		if(tablero_estatico.Comprueba_bajada(*p_pieza)){ //Si puede bajar
			p_pieza->coordenada_previa = p_pieza->coordenada;//actualizo la coordenada previa antes de que cambie
			p_pieza->coordenada.y_fila = p_pieza->coordenada.y_fila + 1;
			std::cout<< "p_pieza moved "<< p_pieza<<std::endl;
		}
		else{
			tablero_estatico.intro_coord_tabla(*p_pieza); // como no puede bajar más, se introduce al tablero estatico		
			std::cout<< "p_pieza deleted "<< p_pieza<<std::endl;
			tablero_estatico.imprime_tabla();//para debug en consola
			//delete p_pieza;
			//p_pieza = nullptr;
			pieza_bloqueada = true;
			
			if(p_pieza->coordenada.y_fila<=1){
				std::cout<<"FIN DEL JUEGO"<<std::endl;
				tablero_lleno=true;
			}

		}

		Actualiza_Pantalla(*p_pieza, tablero_estatico);
		Actualiza_Tablero(*p_pieza, tablero_dinamico);
		tablero_dinamico.imprime_tabla();//para debug en consola
	}*/
    //return MS_Nivel[Nivel]; //devuelve la velocidad para la siguiente ejecución
	return 2000;
}