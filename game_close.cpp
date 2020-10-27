#include "game_close.h"
#include "game.h"

Game_Close::Game_Close(Game game){


	/*
	Texto Texto_Jugador, 
                   Texto Nombre_Jugador, 
                   Texto Texto_Puntuacion,
                   Texto Valor_Puntuacion,
                   Texto Texto_Nivel,
                   Texto Valor_Nivel,
                   Texto pulsa_intro_continuar,
				   SDL_Event eventos*/
	
}


Game_Close::~Game_Close(){
    
    registar_puntuacion();
}

void Game_Close::mostrar_puntuacion(){

	bool quit = false;

	SDL_Event eventos;

	//Reinicia la ventana
	SDL_SetRenderDrawColor( Render, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( Render );
		
	Texto_Jugador.renderizar ( 3*REJILLA , 2*REJILLA );
	Nombre_Jugador.renderizar ( ANCHO - Nombre_Jugador.get_ancho() - 3*REJILLA, 3*REJILLA );
		
	Texto_Puntuacion.renderizar ( 3*REJILLA , 5*REJILLA );
	Valor_Puntuacion.renderizar ( ANCHO - Valor_Puntuacion.get_ancho() - 3*REJILLA , 6*REJILLA );

	Texto_Nivel.renderizar ( 3*REJILLA , 8*REJILLA );
	Valor_Nivel.renderizar ( ANCHO - Valor_Nivel.get_ancho() - 3*REJILLA , 9*REJILLA );

	pulsa_intro_continuar.renderizar( (ANCHO - pulsa_intro_continuar.get_ancho())/2 , 11*REJILLA );

	SDL_RenderPresent( Render );//Actualiza la pantalla

	//Para reducir carga de trabajo
  	Uint32 frame_start;
  	Uint32 frame_end;
	Uint32 frame_duration;
	Uint32 target_frame_duration = kMsPerFrame/4; //No hace falta tanta velocidad

	while( !quit )
	{
		bool renderText = false;
		while( SDL_PollEvent( &eventos ) != 0 )
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
				break;
			}

			else if( e.type == SDL_KEYDOWN )
			{	//para finalizar pulsando enter tmb
				if(e.key.keysym.scancode == SDL_SCANCODE_RETURN)
				{
					quit = true;
					break;
				}	
			}
		}
		frame_end = SDL_GetTicks();
    	frame_duration = frame_end - frame_start;
		if (frame_duration < target_frame_duration) {
      		SDL_Delay(target_frame_duration - frame_duration);
    	}	
	}
}

void Game_close::registar_puntuacion(){

    //https://stackoverflow.com/questions/11108238/adding-text-and-lines-to-the-beginning-of-a-file-c
    //https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c

    std::string nombre = Nombre_Jugador.get_cadena_texto();

    const std::string fileName = "historico_puntuacion.txt";
    std::fstream processedFile(fileName.c_str());
    std::stringstream fileData;

    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    fileData <<"Nombre: " <<nombre<< ", Nivel: "<< nivel  
			<< ", Puntuacion: "<<puntuacion 
			<< ", Fecha: "<<std::ctime(&time) << std::endl;
  
    fileData << processedFile.rdbuf();
    processedFile.close();

    processedFile.open(fileName.c_str(), std::fstream::out | std::fstream::trunc); 
    processedFile << fileData.rdbuf();

}