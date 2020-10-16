#if defined(_GLIBCXX_HAS_GTHREADS) 
#defined(_GLIBCXX_USE_C99_STDINT_TR1)
#endif
#include "apilado.h"
#include "tablero.h"
#include <iostream>
#include <Windows.h> //Sleep
#include <stdlib.h>  //cls
//#include <thread>    // std::thread    
//#include <mutex>

// VARIABLES GLOBALES
int Nivel = 0;	//1	//2	 //3  //4  //5  //6  //7  //8  //9 //10
Uint32 MS_Nivel[] = {2000, 1000, 900, 800, 700, 600, 500, 450, 400, 350, 300, 250}; //ms para cada intervalo

//Inicializa tableros lógico
Tablero tablero_dinamico;
Tablero tablero_estatico;

Uint32 my_callbackfunc(Uint32 interval, void *param);

bool Generar_nueva_pieza;

//std::mutex m;

int main( int argc, char* args[] )
{
	
	Pieza* pieza = new Pieza(1,1);//Crear e inicializar pieza

	if( !inicializar() ) //Inicializa SDL y crea la ventana
		printf( "ERROR!\n" );
	else{
		bool cerrar = false; // Control bucle principal
		SDL_Event eventos;   // Gestor (cola) de eventos

		SDL_RendererFlip flipType = SDL_FLIP_NONE;

		Uint32 delay = MS_INTERVALO_MOV_INICIAL;  //SE INICIALIZA EL INTERVALO DE EJECUCIÓN
		SDL_TimerID my_timer_id = SDL_AddTimer(delay, my_callbackfunc, pieza);	

		while( !cerrar ){ //While application is running				
			while( SDL_PollEvent( &eventos ) != 0 ){ //Cola de eventos	
				if( eventos.type == SDL_QUIT ){ //Para cerrar (pulsando X de ventana)
					cerrar = true;
				}
				else if( eventos.type == SDL_KEYDOWN ){
					//m.unlock();
					Mueve_Pieza_Si_Se_Puede(eventos.key.keysym.sym, *pieza, tablero_estatico);
					//m.unlock();
				}	
				// No se sale del bucle hasta que la cola de eventos es 0		
			}
			Actualiza_Pantalla(Mapeado_Coord_Tablero(pieza->coordenada), pieza->posiciones);
			system("cls");

			//! TO DO: TRANSFORMAR EN FUNCIÓN INDEPENDIENTE
			if((pieza->coordenada.y_fila!=pieza->coordenada_previa.y_fila)||
			   (pieza->coordenada.x_columna!=pieza->coordenada_previa.x_columna)){ //si la pieza se mueve se actualiza posición
				
				tablero_dinamico.borra_coord_tabla(*pieza); //borra la posición obsoleta de la tabla
				pieza->pieza_a_coordenadas();
				tablero_dinamico.intro_coord_tabla(*pieza);
				tablero_dinamico.imprime_tabla();
			}

			Sleep(1000);//ms 
		}
	} 
	tablero_dinamico.intro_coord_tabla(*pieza);
	std::cout<<"Tablero dinamico:"<< std::endl;
	tablero_dinamico.imprime_tabla();
	std::cout<<"Tablero estatico:"<< std::endl;
	tablero_estatico.imprime_tabla();
	cerrar(); //Liberar recursos reservados
	return 0;
}


Uint32 my_callbackfunc(Uint32 interval, void *param_pieza)
{
	Pieza* p_pieza = reinterpret_cast<Pieza*>(param_pieza);

	if(tablero_estatico.Comprueba_bajada(*p_pieza)){ //Si puede bajar
		p_pieza->coordenada_previa = p_pieza->coordenada;//actualizo la coordenada previa antes de que cambie
        p_pieza->coordenada.y_fila = p_pieza->coordenada.y_fila + 1;
    }
	else if(p_pieza!=NULL) {//Para no destruir varias veces la pieza
		tablero_estatico.intro_coord_tabla(*p_pieza); // como no puede bajar más, se introduce al tablero estatico		
		p_pieza = NULL;
		delete p_pieza;
	}

	//! TO DO: Implementar incremento velocidad del programa
    return MS_Nivel[Nivel];
}