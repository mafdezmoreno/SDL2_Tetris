#include "apilado.h"
#include "main.h"

SDL_Window*   Ventana = NULL;     // Ventana
SDL_Renderer* Render = NULL; // Elementos a renderizar en interior


void Dibuja_tablero(){
												//coord x //coord y	 //ancho 25		           //alto 35
	SDL_Rect cuadrado = { REJILLA, REJILLA, ANCHO_TABLERO* REJILLA , ALTO_TABLERO* REJILLA};
	SDL_SetRenderDrawColor( Render, 0x00, 0x00, 0x00, 0x00 );   //Borde tablero en negro    
	SDL_RenderDrawRect( Render, &cuadrado );
}



void Mueve_Pieza_Si_Se_Puede( SDL_Keycode tecla, Pieza &pieza, Tablero &tablero) //Mueve la pieza si no choca con bordes u otras piezas
{
	switch( tecla ){				
		case SDLK_RIGHT:
			if(tablero.Comprueba_derecha(pieza))
            	pieza.coordenada.x_columna++;
			break;
							
		case SDLK_LEFT:
			if(tablero.Comprueba_izquierda(pieza)){
            	pieza.coordenada.x_columna--;
        	}
		break;

		case SDLK_DOWN:
			if(tablero.Comprueba_bajada(pieza))
            	pieza.coordenada.y_fila++;
		break;
							
		case SDLK_SPACE: //Rota la pieza
			if(tablero.Comprueba_giro(pieza))
				pieza.posiciones = pieza.Gira_Pieza_90(pieza.posiciones);

		break;
	}
}

Coordenada Mapeado_Coord_Tablero(Coordenada &coord)//transforma coordenadas de rejilla de tablero a coordenadas de rendererizado
{
	Coordenada coord_rejilla;
	coord_rejilla.x_columna = coord.x_columna*(REJILLA); //x
	coord_rejilla.y_fila = coord.y_fila*(REJILLA);//y
	return coord_rejilla;
}

void Actualiza_Pantalla(Pieza &pieza, Tablero &tablero_estatico){

	SDL_SetRenderDrawColor( Render, 200, 200, 200, 0xFF ); //Colores de la pantalla
	SDL_RenderClear( Render );

	Coordenada coord_mapeada = Mapeado_Coord_Tablero(pieza.coordenada);
	//Renderiza la pieza recorriendo todas sus casillas
    for(int8_t i = 0; i < pieza.posiciones.size() ; i++){	
    	for(int8_t j = 0; j<  pieza.posiciones[0].size(); j++){
			if (pieza.posiciones[i][j]==true){
				SDL_Rect fillRect = { coord_mapeada.x_columna+j*REJILLA, coord_mapeada.y_fila+i*REJILLA, REJILLA, REJILLA};
				SDL_SetRenderDrawColor( Render, pieza.colores[0], pieza.colores[1], pieza.colores[2], 0xFF );		
				SDL_RenderFillRect( Render, &fillRect );
			}
		}
	}

	//Renderizado de las posiciones ocupadas del tablero
	for(int8_t i = 1; i < (tablero_estatico._tablero.size()-1) ; i++){	
    	for(int8_t j = 1; j<  (tablero_estatico._tablero[0].size()-1); j++){
			if (tablero_estatico._tablero[i][j]==true){
				SDL_Rect fillRect = {j*REJILLA, i*REJILLA, REJILLA, REJILLA};
				SDL_SetRenderDrawColor( Render, pieza.colores[0], pieza.colores[1], pieza.colores[2], 0xFF );		
				SDL_RenderFillRect( Render, &fillRect );
			}
		}
	}


	Dibuja_tablero();//Dibuja Tablero
	SDL_RenderPresent( Render ); //Actualiza la pantalla
}

void Actualiza_Tablero_Dinamico(Pieza &pieza, Tablero &tablero){
	
	if((pieza.coordenada.y_fila!=pieza.coordenada_previa.y_fila)||
		(pieza.coordenada.x_columna!=pieza.coordenada_previa.x_columna)){ //si la pieza se mueve se actualiza posición
		tablero.borra_coord_tabla(pieza); //borra la posición obsoleta de la tabla
		pieza.pieza_a_coordenadas(); //Actualiza el set de coordenadas
		tablero.intro_coord_tabla(pieza); //Introduce la pieza en la tabla
	}
}
void Actualiza_Tablero_Estatico(Pieza &pieza, Tablero &tablero){
		pieza.pieza_a_coordenadas(); //Actualiza el set de coordenadas
		tablero.intro_coord_tabla(pieza); //Introduce la pieza en la tabla
}

bool inicializar()
{
	bool correcto = true;

	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 ) 
	// También hay q inicializar el timer
	{
		printf( "SDL_Init Error: %s\n", SDL_GetError() );
		correcto = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
			printf( "SDL_SetHint Error" );

		// Creación de la ventana
		Ventana = SDL_CreateWindow( "Tetris ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO, ALTO, SDL_WINDOW_SHOWN );
		if( Ventana == NULL )
		{
			printf( "SDL_CreateWindow Error: %s\n", SDL_GetError() );
			correcto = false;
		}
		else
		{
			Render = SDL_CreateRenderer( Ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( Render == NULL )
			{
				printf( "SDL_CreateRenderer Error: %s\n", SDL_GetError() );
				correcto = false;
			}
			else
			{
				SDL_SetRenderDrawColor( Render, 0xFF, 0xFF, 0xFF, 0xFF );
			}
		}
	}

	return correcto;
}

void cerrar()
{

	//Libera los recursos de ventanas	
	SDL_DestroyRenderer( Render );
	SDL_DestroyWindow( Ventana );
	Ventana = NULL;
	Render = NULL;
	
	//Cierra Componentes de SDL
	IMG_Quit();
	SDL_Quit();
}
