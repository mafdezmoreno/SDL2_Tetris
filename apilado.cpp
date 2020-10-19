#include "apilado.h"
#include "main.h"
#include <string>

// Renderizado de texto
Texto Texto_Puntuacion;
Texto Valor_Puntuacion;
Texto Texto_Nivel;
Texto Valor_Nivel;
Texto Nombre_Jugador;
Texto Texto_Jugador;

SDL_Window*   Ventana = NULL;     // Ventana
SDL_Renderer* Render = NULL; // Elementos a renderizar en interior

int nivel_previo = -1;

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
				pieza.Gira_Pieza_90();

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

void Actualiza_Pantalla(Pieza &pieza, Tablero &tablero_estatico, Pieza &siguiente_pieza){

	SDL_SetRenderDrawColor( Render, 200, 200, 200, 0xFF ); //Colores de la pantalla
	SDL_RenderClear( Render ); //Limpia la pantalla

	Coordenada coord_mapeada = Mapeado_Coord_Tablero(pieza.coordenada);
	//Renderiza la pieza recorriendo todas sus casillas
    for(int i = 0; i < pieza.posiciones.size() ; i++){	
    	for(int j = 0; j<  pieza.posiciones[0].size(); j++){
			if (pieza.posiciones[i][j]==true){
				SDL_Rect fillRect = { coord_mapeada.x_columna+j*REJILLA, coord_mapeada.y_fila+i*REJILLA, REJILLA, REJILLA};
				SDL_SetRenderDrawColor( Render, colores[pieza.cod_color][0], colores[pieza.cod_color][1], colores[pieza.cod_color][2], 0xFF );
				SDL_RenderFillRect( Render, &fillRect );
			}
		}
	}

	//Renderizado de la pieza siguiente
	for(int i = 0; i < siguiente_pieza.posiciones.size() ; i++){	
    	for(int j = 0; j<  siguiente_pieza.posiciones[0].size(); j++){
			if (siguiente_pieza.posiciones[i][j]==true){
				SDL_Rect fillRect = { ANCHO - 6*REJILLA+j*REJILLA, 8*REJILLA+i*REJILLA, REJILLA, REJILLA};
				SDL_SetRenderDrawColor( Render, colores[siguiente_pieza.cod_color][0], colores[siguiente_pieza.cod_color][1], colores[siguiente_pieza.cod_color][2], 0xFF );
				SDL_RenderFillRect( Render, &fillRect );
			}
		}
	}

	//Renderizado de las posiciones ocupadas del tablero
	for(int i = 1; i < (tablero_estatico._tablero.size()-1) ; i++){	
    	for(int j = 1; j<  (tablero_estatico._tablero[0].size()-1); j++){
			if (tablero_estatico._tablero[i][j]==true){
				SDL_Rect fillRect = {j*REJILLA, i*REJILLA, REJILLA, REJILLA};
				SDL_SetRenderDrawColor( Render, colores[0][0], colores[0][1], colores[0][2], 0xFF );		
				SDL_RenderFillRect( Render, &fillRect );
			}
		}
	}

	//Actualiza el texto de la puntuación
	if(!Valor_Puntuacion.cargar_texto_renderizado( std::to_string(puntuacion))){
		std::cout<< "No se ha podido renderizar el texto de la puntuación" <<std::endl;
	}
	if(nivel_previo!=nivel){
		if(!Valor_Nivel.cargar_texto_renderizado( std::to_string(nivel))){
			std::cout<< "No se ha podido renderizar el texto del nivel" <<std::endl;
			nivel_previo = nivel;
		}
	}

	// Renderiza el texto
	//Fila 1
	Texto_Jugador.renderizar( ANCHO - 8*REJILLA, REJILLA );
	//Fila 2
	Nombre_Jugador.renderizar(ANCHO - Nombre_Jugador.get_ancho()-5, 2*REJILLA );
	//Fila 3
	Texto_Puntuacion.renderizar(ANCHO - 8*REJILLA, 4*REJILLA); //5 pixeles de separación del borde superior y derecho de la ventana
	Valor_Puntuacion.renderizar(ANCHO - Valor_Puntuacion.get_ancho()-5, 4*REJILLA);
	//Fila 4
	Texto_Nivel.renderizar( ANCHO - 8*REJILLA,  5*REJILLA); //5 Pixeles de separacion de la anterior linea
	Valor_Nivel.renderizar( ANCHO - Valor_Nivel.get_ancho()-5,  5*REJILLA);

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
		tablero.eliminar_filas_llenas();
}

bool inicializar()
{
	bool correcto = true;

	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 )  	// También hay q inicializar el timer
	{
		std::cout<<"SDL_Init Error: " << SDL_GetError() <<std::endl;
		correcto = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
			std::cout<<"SDL_SetHint Error"<<std::endl;

		// Creación de la ventana
		Ventana = SDL_CreateWindow( "Tetris Udacity", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO, ALTO, SDL_WINDOW_SHOWN );
		if( Ventana == NULL )
		{
			std::cout<< "SDL_CreateWindow Error: "<< SDL_GetError()  <<std::endl;
			correcto = false;
		}
		else
		{
			Render = SDL_CreateRenderer( Ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( Render == NULL )
			{
				std::cout<< "SDL_CreateRenderer Error: " << SDL_GetError() <<std::endl;
				correcto = false;
			}
			else
			{
				SDL_SetRenderDrawColor( Render, 0xFF, 0xFF, 0xFF, 0xFF );
			}
		}
	}

	if( TTF_Init() == -1 ){
		std::cout<<"No se ha podido inicializar TTF_Init() "<< TTF_GetError() <<std::endl;
		correcto = false;
	}
	else if( !cargar_texto()){
		std::cout<< "Fallo en la carga del texto"<<std::endl;
		correcto = false;
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
	SDL_Quit();
	TTF_Quit();

}

bool cargar_texto()
{
	bool carga_texto = true;

	Fuente_TTF = TTF_OpenFont( "FreeSansBold.ttf", TEXT_SIZE);
	if( Fuente_TTF == NULL ){
		std::cout<< "Error en la carga de la fuente. SDL_ttf Error: " << TTF_GetError()  <<std::endl;
		carga_texto = false;
	}
	else{
		if(!Texto_Puntuacion.cargar_texto_renderizado( "Puntuacion: ")||
			!Texto_Nivel.cargar_texto_renderizado( "Nivel: ")||
			!Nombre_Jugador.cargar_texto_renderizado( "Miguel ")||
			!Texto_Jugador.cargar_texto_renderizado( "Jugador: "))
		{
			std::cout<< "No se ha podido renderizar la textura para el texto" <<std::endl;
			carga_texto = false;
		}
	}
	return carga_texto;
}