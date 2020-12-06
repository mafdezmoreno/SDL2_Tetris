#include "game_init.h"
#include "constantes.h"
#include <iostream>
#include <future>
#include <thread>
#include <utility>

void pruebas(std::promise<Texto*>&& Promesa, std::string texto_renderizar, std::shared_ptr<SDL_Renderer> ext_render){

	Promesa.set_value(new Texto(texto_renderizar, ext_render));
}

Game_Init::Game_Init()
	: _Ventana(nullptr, SDL_DestroyWindow),
	  _Render (nullptr, SDL_DestroyRenderer)
{//Constructor

    if(inicializar()){
	
		// In this case, it is not more efficient to use future and promise, but I did it to to fulfill the requirements of the capstone
		///* //future and promise: https://www.modernescpp.com/index.php/promise-and-future
		std::promise<Texto*> p_1, p_2, p_3;
		std::future<Texto*>  f_1 = p_1.get_future();
		std::future<Texto*>  f_2 = p_2.get_future();
		std::future<Texto*>  f_3 = p_3.get_future();
		
		std::thread mi_hilo_1(pruebas, std::move(p_1),"Introduce tu nombre:", _Render);
		std::thread mi_hilo_2(pruebas, std::move(p_2),"Pulsa Enter para continuar", _Render);
		std::thread mi_hilo_3(pruebas, std::move(p_3),"Jugador 1", _Render);
		
		_pedir_nombre_jugador = std::make_unique<Texto>(std::move(*(f_1.get())));
		_pulsa_intro_continuar = std::make_unique<Texto>(std::move(*(f_2.get())));
		_Nombre_Jugador_Temp = std::make_unique<Texto>(std::move(*(f_3.get())));
		mi_hilo_1.join(); mi_hilo_2.join(); mi_hilo_3.join();
		//*/
		
		/*
		_pulsa_intro_continuar = std::make_unique<Texto> ("Pulsa Enter para continuar",_Render);
		_pedir_nombre_jugador = std::make_unique<Texto>("Introduce tu nombre:",_Render);
		_Nombre_Jugador_Temp = std::make_unique<Texto>("Jugador 1", _Render);
		*/

		pantalla_pedir_nombre();
	}
	//std::cout<< "_Render.use_count() = "<<_Render.use_count() << std::endl;
}



Game_Init::~Game_Init(){

	std::cout<<"Game Init Destructor Called " << this<< "\n" <<std::endl;
}

std::unique_ptr<Texto> Game_Init::get_nombre_jugador(){

	return std::move(_Nombre_Jugador_Temp);
}

std::unique_ptr<Texto> Game_Init::get_pulsa_intro_continuar(){
	
	return std::move(_pulsa_intro_continuar);
}

void Game_Init::pantalla_pedir_nombre(){

	std::string inputText = "Jugador 1";
	bool quit = false;
	SDL_Event eventos;
	SDL_StartTextInput(); //Habilita la entrada de texto
	
    //Para gestionar la tasa de refresco
  	Uint32 frame_start, frame_end, frame_duration;
	Uint32 target_frame_duration = _kMsPerFrame;

	//While application is running
	while( !quit )
	{
		frame_start = SDL_GetTicks();
		bool renderText = false;
		while( SDL_PollEvent( &eventos ) != 0 )
		{
			if(eventos.type == SDL_QUIT)
			{//para salir si se pulsa x de la ventana
				quit = true;
				break;
			}

			else if( eventos.type == SDL_KEYDOWN )
			{
				if(eventos.key.keysym.scancode == SDL_SCANCODE_RETURN)
				{//para salir si pulsamos enter
					quit = true;
					break;
				}
				
				if( eventos.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
				{// backspace
					inputText.pop_back();
					renderText = true;
				}
			}
					
			else if( eventos.type == SDL_TEXTINPUT ) //si se teclean letras se añaden
			{
						inputText += eventos.text.text;
						renderText = true;
			}
		}
		//Renderizado si es necesario
		if( renderText )
		{
			if( inputText != "" )
			{
						_Nombre_Jugador_Temp->cargar_texto( inputText.c_str());
			}
			else
			{
						_Nombre_Jugador_Temp->cargar_texto( " ");
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor( _Render.get(), 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( _Render.get() );

		//Render text textures
		//!implementar multi-hilo
		_pedir_nombre_jugador->renderizar ( (ANCHO - _pedir_nombre_jugador->get_ancho())/2, REJILLA );
		_Nombre_Jugador_Temp->renderizar  ( (ANCHO - _Nombre_Jugador_Temp->get_ancho())/2 , 3*REJILLA );
		_pulsa_intro_continuar->renderizar( (ANCHO - _pulsa_intro_continuar->get_ancho())/2 , 5*REJILLA );

		//Update screen
		SDL_RenderPresent( _Render.get() );

		frame_end = SDL_GetTicks();
    	frame_duration = frame_end - frame_start;
		if (frame_duration < target_frame_duration) {
      		SDL_Delay(target_frame_duration - frame_duration);
    	}
	}

			
	//Disable text input
	SDL_StopTextInput();


	//Text is not empty
	if( inputText != "" )
	{
		//Render new text
		_Nombre_Jugador_Temp->cargar_texto(inputText);
		//_Nombre_Jugador_Temp->set_cadena_texto(&inputText);
	}
	//Text is empty
	else
	{
		//Render space texture
		inputText = "Jugador 1";
		_Nombre_Jugador_Temp->cargar_texto(inputText);
		//_Nombre_Jugador_Temp->set_cadena_texto(&inputText);
	}	

	std::cout<< "Nombre del jugador: "<< inputText << std::endl;
}


bool Game_Init::inicializar()
{
	bool correcto = true;

	if( SDL_Init(SDL_INIT_VIDEO) < 0 ) 
	{
		std::cout<<"SDL_Init Error: " << SDL_GetError() <<std::endl;
		correcto = false;
	}
	else
	{

		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) //https://wiki.libsdl.org/SDL_HINT_RENDER_SCALE_QUALITY
			std::cout<<"SDL_SetHint Error"<<std::endl;

		// Creación de la ventana
		_Ventana.reset(SDL_CreateWindow( "Tetris Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO, ALTO, SDL_WINDOW_SHOWN ));
		if( _Ventana == NULL )
		{
			std::cout<< "SDL_CreateWindow Error: "<< SDL_GetError()  <<std::endl;
			correcto = false;
		}
		else
		{
			//shared pointer. Incluye el tipo de deleter															//deleter
			_Render.reset(SDL_CreateRenderer( _Ventana.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC ), SDL_DestroyRenderer);
			
			if( _Render == NULL )
			{
				std::cout<< "SDL_CreateRenderer Error: " << SDL_GetError() <<std::endl;
				correcto = false;
			}
			else
			{
				SDL_SetRenderDrawColor( _Render.get(), 0xFF, 0xFF, 0xFF, 0xFF );
			}
		}
	}

	if( TTF_Init() == -1 ){ //para renderizado de texto
		std::cout<<"No se ha podido inicializar TTF_Init() "<< TTF_GetError() <<std::endl;
		correcto = false;
	}

	return correcto;
}
