#include "game.h"
#include "texto.h"
#include "tablero.h"
#include <SDL2/SDL.h>
#include <sstream>
#include <string>
#include <iostream>
#include <future>
#include <thread>
#include <utility>
#include <chrono>

Game::Game(Game_Init& game_start)
	: _Ventana(nullptr, SDL_DestroyWindow), 
	_Render (nullptr, SDL_DestroyRenderer){

	if(_inicializar()){
		_Ventana = std::move(game_start._Ventana); // Window
        _Render = std::move(game_start._Render); // Elementos a renderizar en interior
		_Nombre_Jugador = game_start.get_nombre_jugador();

		//std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    	//std::chrono::duration<float> duration;
    	//start = std::chrono::high_resolution_clock::now();

		//The following lines takes ~0.14 - 0.07 s 
		/*
		_Texto_Puntuacion = std::make_unique<Texto>("Puntuacion: ", _Render);
		_Texto_Nivel = std::make_unique<Texto>("Nivel: ", _Render);
		_Texto_Jugador = std::make_unique<Texto>("Jugador: ", _Render);		
		*/

		//The same code, with this three treads reduces until ~0.05s or less 
		/*
		_Texto_Puntuacion = std::make_unique<Texto>(_Render);
		std::thread t1(&Texto::cargar_texto, _Texto_Puntuacion.get(), "Puntuacion: ");
		_Texto_Nivel = std::make_unique<Texto>( _Render);
		std::thread t2(&Texto::cargar_texto, _Texto_Nivel.get(), "Nivel: ");
		_Texto_Jugador = std::make_unique<Texto>(_Render);
		std::thread t3(&Texto::cargar_texto, _Texto_Jugador.get(), "Jugador: ");
		_Valor_Puntuacion = std::make_unique<Texto>( _Render);
		_Valor_Nivel = std::make_unique<Texto>( _Render);
		*/

		//This version reduces until ~0.012s or less 
		_Texto_Puntuacion = std::make_unique<Texto>();
		std::thread t1(&Texto::init_full, _Texto_Puntuacion.get(), "Puntuacion: ", _Render);
		_Texto_Nivel = std::make_unique<Texto>();
		std::thread t2(&Texto::init_full, _Texto_Nivel.get(), "Nivel: ", _Render);
		_Texto_Jugador = std::make_unique<Texto>();
		std::thread t3(&Texto::init_full, _Texto_Jugador.get(), "Jugador: ", _Render);
		_Valor_Puntuacion = std::make_unique<Texto>();
		std::thread t4(&Texto::init, _Valor_Puntuacion.get(),  _Render);
		_Valor_Nivel = std::make_unique<Texto>();
		std::thread t5(&Texto::init, _Valor_Nivel.get(), _Render);

		//end = std::chrono::high_resolution_clock::now();
		//duration = end-start;

		_params = std::make_shared<Interrupt_Param>();
		_tablero_dinamico = std::make_unique<Tablero>();
		_tablero_estatico = std::make_unique<Tablero>(_params);

		t1.join(); t2.join(); t3.join(); t4.join(); t5.join();
		
		//std::cout<<"\nTIEMPO QUE HA TARDADO LA CONSTRUCCION: "<< duration.count() <<" \n"<<std::endl;
		//system("pause");
		std::cout << "GAME CONSTRUCTOR " << this << ": "<<std::endl;

	}
	else
		std::cout<<"Error Init_timer Constructor Game"<<std::endl;
	
}

Game::~Game(){

	std::cout << "GAME DESTRUCTOR " << this << ": "<<std::endl;
}

bool Game::_inicializar()
{ // Loads the timer function from the SDL module
	if( SDL_Init( SDL_INIT_TIMER ) < 0 ) 
	{
		std::cout<<"SDL_INIT_TIMER Error: " << SDL_GetError() <<std::endl;
		return false;
	}
	return true;
}

// Move the part if it does not hit the edge of the board or other parts
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
							
		case SDLK_SPACE: //Rotate the part
			if(tablero.Comprueba_giro(pieza))
				pieza.Gira_Pieza_90();

		break;
	}
}


void Game::Actualiza_Pantalla(Pieza &pieza, Pieza &siguiente_pieza){
	
	SDL_SetRenderDrawColor( _Render.get(), 200, 200, 200, 0xFF ); // Background color of the window
	SDL_RenderClear( _Render.get() ); // Removes all the graphics of the window

	Coordenada coord_mapeada = Mapeado_Coord_Tablero(pieza.coordenada);
	
	// Render the part (inside the board)
    for(int i = 0; i < pieza.posiciones.size() ; i++){	
    	for(int j = 0; j<  pieza.posiciones[0].size(); j++){
			if (pieza.posiciones[i][j]==true){
				SDL_Rect fillRect = { coord_mapeada.x_columna+j*REJILLA, coord_mapeada.y_fila+i*REJILLA, REJILLA, REJILLA};
				SDL_SetRenderDrawColor( _Render.get(), pieza.get_r(), pieza.get_g(), pieza.get_b(), 0xFF );
				SDL_RenderFillRect( _Render.get(), &fillRect );
			}
		}
	}

	// Render the following part
	for(int i = 0; i < siguiente_pieza.posiciones.size() ; i++){	
    	for(int j = 0; j<  siguiente_pieza.posiciones[0].size(); j++){
			if (siguiente_pieza.posiciones[i][j]==true){
				SDL_Rect fillRect = { ANCHO - 6*REJILLA+j*REJILLA, 8*REJILLA+i*REJILLA, REJILLA, REJILLA};
				SDL_SetRenderDrawColor( _Render.get(),  siguiente_pieza.get_r(), siguiente_pieza.get_g(), siguiente_pieza.get_b(), 0xFF );
				SDL_RenderFillRect( _Render.get(), &fillRect );
			}
		}
	}

	// Render the occupied spaces in the board
	for(int i = FILAS; i >0  ; i--){	
		bool fila_vacia = true;
    	for(int j = 1; j<(COLUMNAS+1); j++){
			if ((_tablero_estatico.get())->get_position(i,j)){			
				SDL_Rect fillRect = {j*REJILLA, i*REJILLA, REJILLA, REJILLA};
				SDL_SetRenderDrawColor( _Render.get(), colores[0][0], colores[0][1], colores[0][2], 0xFF );		
				SDL_RenderFillRect( _Render.get(), &fillRect );
				fila_vacia = false;
			}
		}
		if(fila_vacia)
			break;
	}

	// Reload score text if it has changed
	if(_params->puntuacion_previa!=_params->puntuacion){
		if(!_Valor_Puntuacion->cargar_texto(std::to_string(_params->puntuacion))){
			std::cout<< "No se ha podido cargar el texto de la puntuación" <<std::endl;
		}
		if(_params->nivel_previo!=_params->nivel){

			if(!_Valor_Nivel->cargar_texto(std::to_string(_params->nivel))){
				std::cout<< "No se ha podido cargar el texto del nivel" <<std::endl;
			}
			_params->nivel_previo = _params->nivel;
		}
		_params->puntuacion_previa = _params->puntuacion;
	}

	// Render the text
	// Row 1
	_Texto_Jugador->renderizar( ANCHO - 8*REJILLA, REJILLA );
	// Row 2
	_Nombre_Jugador->renderizar(ANCHO - _Nombre_Jugador->get_ancho()-5, 2*REJILLA );
	// Row 3
	_Texto_Puntuacion->renderizar(ANCHO - 8*REJILLA, 4*REJILLA);
	_Valor_Puntuacion->renderizar(ANCHO - _Valor_Puntuacion->get_ancho()-5, 4*REJILLA);
	// Row 4
	_Texto_Nivel->renderizar( ANCHO - 8*REJILLA,  5*REJILLA);
	_Valor_Nivel->renderizar( ANCHO - _Valor_Nivel->get_ancho()-5,  5*REJILLA);

	Dibuja_tablero(); //Re-draw the board-game
	SDL_RenderPresent( _Render.get() ); // Update the window	
}

// Update the table with the filled positions of the table

void Game::Actualiza_Tablero_Dinamico(Pieza &pieza, Tablero &tablero_din){

		tablero_din.borra_coord_tabla(pieza); // Deletes the obsolete position from the table
		pieza.pieza_a_coordenadas(); // Update the coordinates
		tablero_din.intro_coord_tabla(pieza); // Enter the part on the table
}

// Update the table with the filled positions of the table
// Contains only the occupied positions (squares) (not the moving parts)
void Game::Actualiza_Tablero_Estatico(Pieza &pieza, Tablero &tablero){

	pieza.pieza_a_coordenadas(); // Update the coordinates
	tablero.intro_coord_tabla(pieza); // Enter the part on the table
	tablero.eliminar_filas_llenas(); // Clears the full rows of the table
}

// Translates between coordinates and filled positions
Coordenada Game::Mapeado_Coord_Tablero(Coordenada &coord){
	
	Coordenada coord_rejilla;
	coord_rejilla.x_columna = coord.x_columna*(REJILLA); //x
	coord_rejilla.y_fila = coord.y_fila*(REJILLA);//y
	return coord_rejilla;
}



void Game::game_run(){

	std::unique_ptr<Pieza> pieza(new Pieza); 
	std::unique_ptr<Pieza> siguiente_pieza;				  
	Uint32 target_frame_duration = _kMsPerFrame;
				
	SDL_Event eventos;   // Events queue
	SDL_TimerID timerID = SDL_AddTimer(500, interrupcion, (void *)(_params.get())); //timer start
		
	while(true){
	
		siguiente_pieza.reset(new Pieza);
		pieza_bloqueada = false;

  		Uint32 frame_start, frame_end, frame_duration; // Variables to manage the refreshing rate

		while(true){

			frame_start = SDL_GetTicks();// Start of frame
			while( SDL_PollEvent( &eventos ) != 0 ){ // while there are events in queue
				if( eventos.type == SDL_QUIT ){ // To close (by pressing X in the window)
					cerrar_programa = true;
					std::cout<<"TERMINASTE EL VIDEOJUEGO"<<std::endl;
					break;
				}
				else if( eventos.type == SDL_KEYDOWN ){
					Mueve_Pieza_Si_Se_Puede(eventos.key.keysym.sym, *pieza, *_tablero_estatico);
				}
			}

			if(pieza_bloqueada){
				std::cout<<"LA PIEZA HA SIDO BLOQUEADA"<<std::endl;					
				pieza = std::move(siguiente_pieza);
				break;
			}
			if(cerrar_programa || tablero_lleno)
				break;
			if((_params.get())->interrupt_control){
				(_params.get())->interrupt_control = false;
				bajar_pieza_si_puede(pieza.get());
			}
			Actualiza_Pantalla(*pieza, *siguiente_pieza); // Render the board (parts and occupied positions)

			// To guarantee a refreshment rate of 60Hz
			frame_end = SDL_GetTicks();
    		frame_duration = frame_end - frame_start;
			if (frame_duration < target_frame_duration) {
      			SDL_Delay(target_frame_duration - frame_duration);
    		}
		}
        
        if(cerrar_programa || tablero_lleno)
            break;
    }
	SDL_RemoveTimer(timerID); //To stop the timer
}

void Game::bajar_pieza_si_puede(Pieza* p_pieza){
	
	if(p_pieza!=nullptr){
		
		//if the part can go down, the board is updated
		if(_tablero_estatico->Comprueba_bajada(*p_pieza)){
			p_pieza->coordenada.y_fila = p_pieza->coordenada.y_fila + 1;
			std::cout<< "PIEZA BAJADA AUTOMÁTICAMENTE "<<std::endl;
			Actualiza_Tablero_Dinamico(*p_pieza, *_tablero_dinamico);

		}

		//When the part can' t go down, here the part is moved to the static board
		else{
			Actualiza_Tablero_Estatico(*p_pieza, *_tablero_estatico); //borra filas ocupadas
			std::cout<< "TABLERO ESTATICO COPIADO AL DINAMICO. ELIMINADO DE HUECOS "<<std::endl;
			*_tablero_dinamico = *_tablero_estatico; //	Deep Copy (copy assignment)
			_tablero_estatico->imprime_tabla(); // to debug
			pieza_bloqueada = true;
			
			if(p_pieza->coordenada.y_fila<=1){
				std::cout<<"FIN DEL JUEGO"<<std::endl;
				tablero_lleno=true;
			}
		}
	}
}

void Game::Dibuja_tablero(){

	SDL_Rect cuadrado = { REJILLA, REJILLA, COLUMNAS* REJILLA , FILAS* REJILLA};
	SDL_SetRenderDrawColor( _Render.get(), 0x00, 0x00, 0x00, 0x00 );   //Set in black the borders of the board
	SDL_RenderDrawRect( _Render.get(), &cuadrado );
}


std::unique_ptr<const int> Game::get_puntuacion(){

	return std::make_unique<const int>((_params->puntuacion_previa));;
}

std::unique_ptr<const int> Game::get_nivel(){

	return std::make_unique<const int>((_params.get())->nivel);;
}


// Returns the velocity of movement for the next level
Uint32 interrupcion(Uint32 interval, void *param)
{
	static const int niveles[12] = {1500, 1000, 900, 800, 700, 600, 500, 450, 400, 350, 300, 250}; //ms for each level
	((Interrupt_Param*)param)->interrupt_control = true;  // Automated part descent
	std::cout<< "INTERRUPCION"<<std::endl;
	std::cout<< "velocidad de movimiento: "<< niveles[((Interrupt_Param*)param)->nivel] <<std::endl;
	return (Uint32)niveles[((Interrupt_Param*)param)->nivel];
}  

std::unique_ptr<Texto> Game::get_nombre_jugador(){

	return std::move(_Nombre_Jugador);
}

std::unique_ptr<Texto> Game::get_Texto_Puntuacion(){
	
	return std::move(_Texto_Puntuacion);
}

std::unique_ptr<Texto> Game::get_Texto_Nivel(){
	
	return std::move(_Texto_Nivel);
}

std::unique_ptr<Texto> Game::get_Valor_Nivel(){
	
	return std::move(_Valor_Nivel);
}

std::unique_ptr<Texto> Game::get_Texto_Jugador(){
	
	return std::move(_Texto_Jugador);
}

std::unique_ptr<Texto> Game::get_Valor_Puntuacion(){
	
	return std::move(_Valor_Puntuacion);
}
