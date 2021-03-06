#include "game_close.h"
#include "game.h"
#include <chrono>
#include <ctime>  
#include <iostream>
#include <fstream>
#include <sstream>

Game_Close::Game_Close(Game& game, Game_Init& game_init)
	: _Ventana(nullptr, SDL_DestroyWindow) ,
	  _Render (nullptr, SDL_DestroyRenderer){

	std::cout<<"Game_Close Construido "<<this<< std::endl;
	
	//move all the rendered text from game
	_Texto_Jugador = game.get_Texto_Jugador();
    _Nombre_Jugador = game.get_nombre_jugador();
    _Texto_Puntuacion = game.get_Texto_Puntuacion();
    _Valor_Puntuacion = game.get_Valor_Puntuacion();
    _Texto_Nivel = game.get_Texto_Nivel();
    _Valor_Nivel = game.get_Valor_Nivel();
	_pulsa_intro_continuar = game_init.get_pulsa_intro_continuar();
	
	//move window and render
	_Ventana = std::move(game._Ventana);
	_Render = std::move(game._Render);
	
	//get info to write into .txt
	_puntuacion = game.get_puntuacion();
	_nivel = game.get_nivel();
	_nombre = _Nombre_Jugador->get_cadena_texto();

	mostrar_puntuacion();
	registar_puntuacion();
}


Game_Close::~Game_Close(){
	_cerrar();
	std::cout<<"Game_Close Destruido "<<this<< std::endl;
}

void Game_Close::mostrar_puntuacion(){

	bool quit = false;

	SDL_Event eventos;

	//Creation of new window
	SDL_SetRenderDrawColor( _Render.get(), 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( _Render.get() );

	_Texto_Jugador->renderizar ( 3*REJILLA , 2*REJILLA );
	_Nombre_Jugador->renderizar ( ANCHO - _Nombre_Jugador->get_ancho() - 3*REJILLA, 3*REJILLA );

	_Texto_Puntuacion->renderizar ( 3*REJILLA , 5*REJILLA );
	_Valor_Puntuacion->renderizar ( ANCHO - _Valor_Puntuacion->get_ancho() - 3*REJILLA , 6*REJILLA );

	_Texto_Nivel->renderizar ( 3*REJILLA , 8*REJILLA );
	_Valor_Nivel->renderizar ( ANCHO - _Valor_Nivel->get_ancho() - 3*REJILLA , 9*REJILLA );

	_pulsa_intro_continuar->renderizar( (ANCHO - _pulsa_intro_continuar->get_ancho())/2 , 11*REJILLA );

	SDL_RenderPresent( _Render.get() ); // Refresh the window


	while( !quit )
	{
		bool renderText = false;
		while( SDL_PollEvent( &eventos ) != 0 )
		{
			if(eventos.type == SDL_QUIT)
			{
				quit = true;
				break;
			}

			else if( eventos.type == SDL_KEYDOWN )
			{	// It allows to end the game by pressing enter
				if(eventos.key.keysym.scancode == SDL_SCANCODE_RETURN)
				{
					quit = true;
					break;
				}	
			}
		}
      	SDL_Delay(200); //ms
	}
}

void Game_Close::registar_puntuacion(){

    //https://stackoverflow.com/questions/11108238/adding-text-and-lines-to-the-beginning-of-a-file-c
    //https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c

    const std::string fileName = "historico_puntuacion.txt";
    std::fstream processedFile(fileName.c_str());
    std::stringstream fileData;

    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    fileData <<"Nombre: " << _nombre<< ", Nivel: "<< *_nivel  
			<< ", Puntuacion: "<<*_puntuacion 
			<< ", Fecha: "<<std::ctime(&time) << std::endl;
  
	std::cout<< "Almacenado en historico: " << std::endl;
	std::cout<< "Nombre: " << _nombre<< ", Nivel: "<< *_nivel  
			<< ", Puntuacion: "<<*_puntuacion 
			<< ", Fecha: "<<std::ctime(&time) << std::endl;

    fileData << processedFile.rdbuf();
    processedFile.close();

    processedFile.open(fileName.c_str(), std::fstream::out | std::fstream::trunc); 
    processedFile << fileData.rdbuf();

}

void Game_Close::_cerrar(){

	//Releases the memory that some SDL components reserve
	SDL_Quit();
	TTF_Quit();

	std::cout<<"GAME FINALIZADO CORRECTAMENTE"<<std::endl;
} 
