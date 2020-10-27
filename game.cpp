#include "game.h"
#include "texto.h"
#include "tablero.h"
#include <SDL.h>
#include <SDL_thread.h>

//! Constructor
Game::Game(Texto * nombre_jugador, bool * counter){
 
    if(_inicializar()){
		_Texto_Puntuacion = new Texto("Puntuacion: ", _Render);
		_Valor_Puntuacion = new Texto( _Render);
		_Texto_Nivel = new Texto("Nivel: " , _Render);
		_Valor_Nivel = new Texto( _Render);
		_Texto_Jugador = new Texto("Jugador: ", _Render);
		_Nombre_Jugador = nombre_jugador;
		int nivel_previo = -1;
		_bajar_pieza = counter;
		
		_tablero_dinamico = new Tablero();
		_tablero_estatico = new Tablero(&_puntuacion, &_nivel);

		std::cout << "GAME CONSTRUCTOR " << this << ": "<<std::endl;
		std::cout << _Nombre_Jugador->get_cadena_texto() <<std::endl;
	}
	else
		std::cout<<"ERROR CONSTRUCTOR GAME"<<std::endl;
}

Game::Game(Game_Init * game_start, bool * counter){

	if(_init_timer()){

		
		_Ventana = game_start->_Ventana;     // Ventana
        _Render = game_start->_Render; // Elementos a renderizar en interior

		_Texto_Puntuacion = new Texto("Puntuacion: ", _Render);
		_Valor_Puntuacion = new Texto( _Render);
		_Texto_Nivel = new Texto("Nivel: " , _Render);
		_Valor_Nivel = new Texto( _Render);
		_Texto_Jugador = new Texto("Jugador: ", _Render);
		_Nombre_Jugador = game_start->get_nombre_jugador();
		int nivel_previo = -1;
		_bajar_pieza = counter;
		
		_tablero_dinamico = new Tablero();
		_tablero_estatico = new Tablero(&_puntuacion, &_nivel);

		std::cout << "GAME CONSTRUCTOR " << this << ": "<<std::endl;

	}
	else
		std::cout<<"ERROR CONSTRUCTOR GAME"<<std::endl;
	
}

Game::~Game(){
    delete _Texto_Puntuacion;
    delete _Texto_Nivel;
    delete _Texto_Jugador;
    delete _Nombre_Jugador;
	delete _Valor_Puntuacion;
	cerrar();
	std::cout << "GAME DESTRUCTOR " << this << ": "<<std::endl;
}

bool Game::_init_timer(){

	bool correcto = true;

	if( SDL_Init( SDL_INIT_TIMER ) < 0 )  	// También hay q inicializar el timer
	{
		std::cout<<"SDL_INIT_TIMER Error: " << SDL_GetError() <<std::endl;
		correcto = false;
	}

	return correcto;
}

bool Game::_inicializar()
{ // Inicializa SDL y crea la ventana   

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
		_Ventana = SDL_CreateWindow( "Tetris Udacity", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO, ALTO, SDL_WINDOW_SHOWN );
		if( _Ventana == NULL ){
			std::cout<< "SDL_CreateWindow Error: "<< SDL_GetError()  <<std::endl;
			correcto = false;
		}
		else{
			_Render = SDL_CreateRenderer( _Ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( _Render == NULL )
			{
				std::cout<< "SDL_CreateRenderer Error: " << SDL_GetError() <<std::endl;
				correcto = false;
			}
			else
			{
				SDL_SetRenderDrawColor( _Render, 0xFF, 0xFF, 0xFF, 0xFF );
			}
		}
	}

	if( TTF_Init() == -1 ){
		std::cout<<"No se ha podido inicializar TTF_Init() "<< TTF_GetError() <<std::endl;
		correcto = false;
	}

	return correcto;
}

void Game::cerrar(){
		//Libera los recursos de ventanas	
	SDL_DestroyRenderer( _Render );
	SDL_DestroyWindow( _Ventana );
	_Ventana = NULL;
	_Render = NULL;
	
	//Cierra Componentes de SDL
	SDL_Quit();
	TTF_Quit();

	std::cout<<"GAME FINALIZADO CORRECTAMENTE"<<std::endl;
} 



//Mueve la pieza si no choca con bordes u otras piezas
void Game::Mueve_Pieza_Si_Se_Puede(const SDL_Keycode& tecla, Pieza &pieza, Tablero &tablero){
	
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


void Game::Actualiza_Pantalla(Pieza &pieza, Tablero &tablero_estatico, Pieza &siguiente_pieza){
	
	SDL_SetRenderDrawColor( _Render, 200, 200, 200, 0xFF ); //Colores de la pantalla
	SDL_RenderClear( _Render ); //Limpia la pantalla

	Coordenada coord_mapeada = Mapeado_Coord_Tablero(pieza.coordenada);
	//Renderiza la pieza recorriendo todas sus casillas
    for(int i = 0; i < pieza.posiciones.size() ; i++){	
    	for(int j = 0; j<  pieza.posiciones[0].size(); j++){
			if (pieza.posiciones[i][j]==true){
				SDL_Rect fillRect = { coord_mapeada.x_columna+j*REJILLA, coord_mapeada.y_fila+i*REJILLA, REJILLA, REJILLA};
				SDL_SetRenderDrawColor( _Render, pieza.get_r(), pieza.get_g(), pieza.get_b(), 0xFF );
				SDL_RenderFillRect( _Render, &fillRect );
			}
		}
	}

	//! PASAR LOS DOS SIGUIENTES BUCLES A FUNCION QUE ACEPTE UNA TABLA DE BOOLEANOS
	//Renderizado de la pieza siguiente
	for(int i = 0; i < siguiente_pieza.posiciones.size() ; i++){	
    	for(int j = 0; j<  siguiente_pieza.posiciones[0].size(); j++){
			if (siguiente_pieza.posiciones[i][j]==true){
				SDL_Rect fillRect = { ANCHO - 6*REJILLA+j*REJILLA, 8*REJILLA+i*REJILLA, REJILLA, REJILLA};
				SDL_SetRenderDrawColor( _Render,  siguiente_pieza.get_r(), siguiente_pieza.get_g(), siguiente_pieza.get_b(), 0xFF );
				SDL_RenderFillRect( _Render, &fillRect );
			}
		}
	}

	//Renderizado de las posiciones ocupadas del tablero
	for(int i = 1; i < (tablero_estatico._tablero.size()-1) ; i++){	
    	for(int j = 1; j<  (tablero_estatico._tablero[0].size()-1); j++){
			if (tablero_estatico._tablero[i][j]==true){
				SDL_Rect fillRect = {j*REJILLA, i*REJILLA, REJILLA, REJILLA};
				SDL_SetRenderDrawColor( _Render, colores[0][0], colores[0][1], colores[0][2], 0xFF );		
				SDL_RenderFillRect( _Render, &fillRect );
			}
		}
	}

	//Actualiza el texto de la puntuación
	if(!_Valor_Puntuacion->cargar_texto_renderizado(std::to_string(_puntuacion))){
		std::cout<< "No se ha podido renderizar el texto de la puntuación" <<std::endl;
	}
	if(nivel_previo!=_nivel){
		if(!_Valor_Nivel->cargar_texto_renderizado( std::to_string(_nivel))){
			std::cout<< "No se ha podido renderizar el texto del nivel" <<std::endl;
			nivel_previo = _nivel;
		}
	}

	// Renderiza el texto
	//Fila 1
	_Texto_Jugador->renderizar( ANCHO - 8*REJILLA, REJILLA );
	//Fila 2
	_Nombre_Jugador->renderizar(ANCHO - _Nombre_Jugador->get_ancho()-5, 2*REJILLA );
	//Fila 3
	_Texto_Puntuacion->renderizar(ANCHO - 8*REJILLA, 4*REJILLA); //5 pixeles de separación del borde superior y derecho de la ventana
	_Valor_Puntuacion->renderizar(ANCHO - _Valor_Puntuacion->get_ancho()-5, 4*REJILLA);
	//Fila 4
	_Texto_Nivel->renderizar( ANCHO - 8*REJILLA,  5*REJILLA); //5 Pixeles de separacion de la anterior linea
	_Valor_Nivel->renderizar( ANCHO - _Valor_Nivel->get_ancho()-5,  5*REJILLA);

	Dibuja_tablero();//Dibuja Tablero
	SDL_RenderPresent( _Render ); //Actualiza la pantalla	
}

void Game::Actualiza_Tablero_Dinamico(Pieza &pieza, Tablero &tablero_din){

		//if((pieza.coordenada.y_fila!=pieza.coordenada_previa.y_fila)||
	//	(pieza.coordenada.x_columna!=pieza.coordenada_previa.x_columna)){ //si la pieza se mueve se actualiza posición
		tablero_din.borra_coord_tabla(pieza); //borra la posición obsoleta de la tabla
		pieza.pieza_a_coordenadas(); //Actualiza el set de coordenadas
		tablero_din.intro_coord_tabla(pieza); //Introduce la pieza en la tabla
	//}
	
}

void Game::Actualiza_Tablero_Estatico(Pieza &pieza, Tablero &tablero){

	pieza.pieza_a_coordenadas(); //Actualiza el set de coordenadas
	tablero.intro_coord_tabla(pieza); //Introduce la pieza en la tabla
	tablero.eliminar_filas_llenas();
	
}

Coordenada Game::Mapeado_Coord_Tablero(Coordenada &coord){
	
	Coordenada coord_rejilla;
	coord_rejilla.x_columna = coord.x_columna*(REJILLA); //x
	coord_rejilla.y_fila = coord.y_fila*(REJILLA);//y
	return coord_rejilla;
}



void Game::game_run(){


	Pieza * pieza;
	Pieza * siguiente_pieza;				  
	Uint32 target_frame_duration = kMsPerFrame;
				
	SDL_Event eventos;   // Gestor (cola) de eventos
	SDL_RendererFlip flipType = SDL_FLIP_NONE;

	pieza = new Pieza;//Crear e inicializar pieza
		
	while(true){
	
		//!Crear mecanismo para impedir repetición de piezas consecutivas
		siguiente_pieza = new Pieza;
		pieza_bloqueada = false;

  		Uint32 frame_start, frame_end, frame_duration; //Variables para gestionar la tasa de refresco

		while(true){

			frame_start = SDL_GetTicks();//Registro del tiempo de inicio del frame
			while( SDL_PollEvent( &eventos ) != 0 ){ //Cola de eventos	
				if( eventos.type == SDL_QUIT ){ //Para cerrar (pulsando X de ventana)
					cerrar_programa = true;
					std::cout<<"TERMINASTE EL VIDEOJUEGO"<<std::endl;
					break;
				}
				else if( eventos.type == SDL_KEYDOWN ){
					Mueve_Pieza_Si_Se_Puede(eventos.key.keysym.sym, *pieza, *_tablero_estatico);
				}
			}// No sale del bucle hasta que la cola de eventos es 0		
			if(pieza_bloqueada){
				std::cout<<"LA PIEZA HA SIDO BLOQUEADA"<<std::endl;					
				delete pieza; //no funciona si la borro en el callback
				pieza = siguiente_pieza;
				break;
			}
			if(cerrar_programa)
				break;
			if(tablero_lleno)
				break;
			if(*_bajar_pieza){
				*_bajar_pieza = false;
				bajar_pieza_si_puede(pieza);
			}
				Actualiza_Pantalla(*pieza, *_tablero_estatico, *siguiente_pieza); //renderizado de tablero con piezas fijas y actual pieza moviéndose
				
			// Para asegurar un refresco máximo de 60Hz
			frame_end = SDL_GetTicks();
    		frame_duration = frame_end - frame_start;
			if (frame_duration < target_frame_duration) {
      			SDL_Delay(target_frame_duration - frame_duration);
    		}
		}
		if(cerrar_programa)
			break;
		if(tablero_lleno)
			break;

		pieza = siguiente_pieza;
    }
}

void Game::bajar_pieza_si_puede(Pieza* p_pieza){
	
	if(p_pieza!=nullptr){
		if(_tablero_estatico->Comprueba_bajada(*p_pieza)){ //Si puede bajar

			p_pieza->coordenada.y_fila = p_pieza->coordenada.y_fila + 1;
			std::cout<< "PIEZA BAJADA AUTOMÁTICAMENTE "<<std::endl;
			Actualiza_Tablero_Dinamico(*p_pieza, *_tablero_dinamico);
			std::cout<< "TABLERO DINAMICO  "<<std::endl;
			_tablero_dinamico->imprime_tabla();//para debug en consola
			std::cout<< "TABLERO ESTATICO "<<std::endl;
			_tablero_estatico->imprime_tabla();//para debug en consola
		}
		else{
			// Cuando no se puede bajar, aquí se pasa la pieza al tablero estático
			Actualiza_Tablero_Estatico(*p_pieza, *_tablero_estatico);//borra filas ocupadas

			std::cout<< "TABLERO ESTATICO COPIADO AL DINAMICO. ELIMINADO DE HUECOS "<<std::endl;
			//! ERROR: !Hace que el puntero apunte a la misma tabla en ambas variables
			*_tablero_dinamico = *_tablero_estatico; //! MOVE SEMANTICS
			_tablero_estatico->imprime_tabla();//para debug en consola
			pieza_bloqueada = true;
			
			if(p_pieza->coordenada.y_fila<=1){
				std::cout<<"FIN DEL JUEGO"<<std::endl;
				tablero_lleno=true;
			}
		}
	}
}

void Game::Dibuja_tablero(){

	SDL_Rect cuadrado = { REJILLA, REJILLA, ANCHO_TABLERO* REJILLA , ALTO_TABLERO* REJILLA};
	SDL_SetRenderDrawColor( _Render, 0x00, 0x00, 0x00, 0x00 );   //Borde tablero en negro    
	SDL_RenderDrawRect( _Render, &cuadrado );
}