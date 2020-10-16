#include "apilado.h"

SDL_Window*   Ventana = NULL;     // Ventana
SDL_Renderer* Render = NULL; // Elementos a renderizar en interior

std::vector<std::vector<bool>> Gira_Pieza_90(std::vector<std::vector<bool>> pieza){
	
	std::vector<std::vector<bool>> pieza_plus_90; //defino el vector a devolver
	
	//inicializo el vector con la dimensión necesaria
  pieza_plus_90.resize(pieza[0].size());        
  for (int8_t i = 0; i< pieza_plus_90.size(); i++)
    pieza_plus_90[i].resize(pieza.size());
 	
  // Copio el vector trasponiendo los datos
  for(int i = 0; i < pieza[0].size() ; i++){	   
    int x = pieza.size()-1;
      for(int j = 0; j<  pieza.size(); j++){
        pieza_plus_90[i][x] = pieza[j][i];
        x--;
      }
  }
	return pieza_plus_90;
}

void Dibuja_tablero(){
												//coord x //coord y	 //ancho 25		           //alto 35
	SDL_Rect cuadrado = { REJILLA, REJILLA, ANCHO_TABLERO* REJILLA , ALTO_TABLERO* REJILLA};
	SDL_SetRenderDrawColor( Render, 0x00, 0x00, 0x00, 0x00 );        
	SDL_RenderDrawRect( Render, &cuadrado );
}

std::vector<int> Mapeado_Coord_Tablero(Coordenada &coord)//transforma coordenadas de rejilla de tablero a coordenadas de rendererizado
{

	std::vector<int> coord_rejilla{1,1};

	coord_rejilla[0] = coord.x_columna*(REJILLA); //x
	coord_rejilla[1] = coord.y_fila*(REJILLA);//y

	return coord_rejilla;
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
			//pieza	= Gira_Pieza_90(pieza);
			//! TO DO: tambien hay que comprobar coche con otras piezas
		break;
	}
}

void Actualiza_Pantalla(std::vector<int>const &coord, std::vector<std::vector<bool>> &posiciones_pieza){ 
	
	//Limpia la pantalla
	SDL_SetRenderDrawColor( Render, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( Render );

	//Renderiza la pieza recorriendo todas sus casillas
    for(int8_t i = 0; i < posiciones_pieza.size() ; i++){	
      for(int8_t j = 0; j<  posiciones_pieza[0].size(); j++){
				if (posiciones_pieza[i][j]==true){
					SDL_Rect fillRect = { coord[0]+j*REJILLA, coord[1]+i*REJILLA, REJILLA, REJILLA};
					SDL_SetRenderDrawColor( Render, 0xFF, 0x00, 0x00, 0xFF );		
					SDL_RenderFillRect( Render, &fillRect );
				}
		}
	}

	Dibuja_tablero();//Dibuja Tablero

	SDL_RenderPresent( Render ); //Actualiza la pantalla
}

bool inicializar()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 ) 
	// También hay q inicializar el timer
	{
		printf( "SDL_Init Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
			printf( "Warning: Linear texture filtering not enabled!" );

		// Creación de la ventana
		Ventana = SDL_CreateWindow( "Tetris ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO, ALTO, SDL_WINDOW_SHOWN );
		if( Ventana == NULL )
		{
			printf( "SDL_CreateWindow Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			Render = SDL_CreateRenderer( Ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( Render == NULL )
			{
				printf( "SDL_CreateRenderer Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( Render, 0xFF, 0xFF, 0xFF, 0xFF );
			}
		}
	}

	return success;
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
