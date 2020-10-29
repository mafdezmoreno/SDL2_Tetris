#include "game_init.h"
#include "constantes.h"
#include <iostream>

Game_Init::Game_Init()
	: _Ventana(nullptr, SDL_DestroyWindow) , _Render (nullptr, SDL_DestroyRenderer) { //Constructor

	std::cout<<"\nGame Init Constructor" << this <<std::endl; 
    if(inicializar()){
		_pedir_nombre_jugador = new Texto("Introduce tu nombre:", _Render.get());
		_Nombre_Jugador_Temp = new Texto("Jugador 1", _Render.get());
		_pulsa_intro_continuar = new Texto("Pulsa Enter para continuar",_Render.get());
		pantalla_pedir_nombre();
	}
}



Game_Init::~Game_Init(){

    delete _pedir_nombre_jugador;
    delete _Nombre_Jugador_Temp;
    delete _pulsa_intro_continuar;
	std::cout<<"Game Init Destructor Called " << this<< "\n" <<std::endl;
}

Texto * Game_Init::get_nombre_jugador(){

	return _Nombre_Jugador_Temp;
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
						_Nombre_Jugador_Temp->cargar_texto_renderizado( inputText.c_str());
			}
			else
			{
						_Nombre_Jugador_Temp->cargar_texto_renderizado( " ");
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor( _Render.get(), 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( _Render.get() );

		//Render text textures
		_pedir_nombre_jugador->renderizar( (ANCHO - _pedir_nombre_jugador->get_ancho())/2, REJILLA );
		_Nombre_Jugador_Temp->renderizar ( (ANCHO - _Nombre_Jugador_Temp->get_ancho())/2 , 3*REJILLA );
		_pulsa_intro_continuar->renderizar ( (ANCHO - _pulsa_intro_continuar->get_ancho())/2 , 5*REJILLA );

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
		_Nombre_Jugador_Temp->cargar_texto_renderizado(inputText);
		//_Nombre_Jugador_Temp->set_cadena_texto(&inputText);
	}
	//Text is empty
	else
	{
		//Render space texture
		inputText = "Jugador 1";
		_Nombre_Jugador_Temp->cargar_texto_renderizado(inputText);
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
		_Ventana.reset(SDL_CreateWindow( "Tetris Udacity", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO, ALTO, SDL_WINDOW_SHOWN ));
		if( _Ventana == NULL )
		{
			std::cout<< "SDL_CreateWindow Error: "<< SDL_GetError()  <<std::endl;
			correcto = false;
		}
		else
		{
			_Render.reset(SDL_CreateRenderer( _Ventana.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC ));
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