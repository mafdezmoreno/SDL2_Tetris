#if defined(_GLIBCXX_HAS_GTHREADS) 
#defined(_GLIBCXX_USE_C99_STDINT_TR1)
#endif

#include <SDL.h>
#include <SDL_thread.h>
#include "apilado.h"
#include "tablero.h"
#include <iostream>
#include <Windows.h> //Sleep
#include <stdlib.h>  //cls
#include "main.h"
#include <thread>         // std::thread, std::thread::id, std::this_thread::get_id
#include <chrono>         // std::chrono::seconds
#include <fstream>
#include <string>
#include <sstream>
#include <ctime> 

//! Mejoras:
// Crear una nueva clase: juego. Almacenar en ella todas las funciones de los ficheros apilado
// Renderizar solo zonas concretas de la pantalla, sin limpiar el contenido anterior
// Color en las piezas del tablero estático
// Crear una clase para guardar el color de las casillas del tablero
// Bajar partes de tablero estático cuando ya no están adheridas a nada y no tienen nada debajo
// Crear mecanismo para impedir repetición de piezas consecutivas y del mismo color
// Rendereizar game over en la pantalla final
// Permitir que se vea el tablero de fondo, tras una transparencia
// Bajar la pieza completamente pulsando enter
// Ordenar el hitorico de puntuaciones. Quedarme con las 5 más altas, mostrarlas por pantalla y si se superan estas puntuaciones, almacenar la nueva puntuacion

//! Object Oriented Programming:
	//! incluir las funciones de main sin clase en una clase GAME (que se inicializará en main())
	//! hacer algún overload de alguna función (quizás los mas fácil sea hacerlo de un constructor)
	//! Derived class functions override virtual base class functions: One member function in an inherited class overrides a virtual base class member function.
	//! One function is declared with a template that allows it to accept a generic parameter.

//!Memory Management
	//! The project makes use of references in function declarations: At least two variables are defined as references, or two functions use pass-by-reference in the project code.
	//! The project uses destructors appropriately: At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor.
	//! The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate: The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.
	//! The project follows the Rule of 5: For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.
	//! The project uses move semantics to move data, instead of copying it, where possible: For classes with move constructors, the project returns objects of that class by value, and relies on the move constructor, instead of copying the object.
	//! The project uses smart pointers instead of raw pointers: The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers.
	
//!Concurrency
	//! The project uses multithreading. The project uses multiple threads in the execution.
	//! A promise and future is used in the project. A promise and future is used to pass data from a worker thread to a parent thread in the project code.
	//! A mutex or lock is used in the project. A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code.
	//! A condition variable is used in the project. A std::condition_variable is used in the project code to synchronize thread execution.

// VARIABLES GLOBALES
int nivel = 0;	//1	//2	 //3  //4  //5  //6  //7  //8  //9 //10
Uint32 MS_Nivel[] = {2000, 1000, 900, 800, 700, 600, 500, 450, 400, 350, 300, 250}; //ms para cada intervalo


//Inicializa tableros lógico
Tablero tablero_dinamico; //Para comprobar los movimientos de las piezas
Tablero tablero_estatico; //Para guardar las piezas fijas.

Uint32 interrupcion(Uint32 interval, void *param);
void bajar_pieza_si_puede(Pieza* p_pieza);

bool bajar_pieza = false;
bool pieza_bloqueada;
bool tablero_lleno = false;
bool cerrar_programa = false;

int puntuacion = 0;

constexpr std::size_t kFramesPerSecond{60};
constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};

void pedir_nombre();
void mostrar_puntuacion();
void registar_puntuacion();

Texto pedir_nombre_jugador;
Texto Nombre_Jugador_Temp;
Texto pulsa_intro_continuar;



int main( int argc, char* args[] )
{


	if( !inicializar() ) // SDL (renderizado, ttf, timer)
		printf( "ERROR!\n" );
	else{

		Uint32 delay = MS_Nivel[0];
		Pieza * pieza;
		Pieza * siguiente_pieza;
		SDL_TimerID timerID = SDL_AddTimer(delay, interrupcion, (void *)nullptr);

		Uint32 target_frame_duration = kMsPerFrame;
				
		SDL_Event eventos;   // Gestor (cola) de eventos
		SDL_RendererFlip flipType = SDL_FLIP_NONE;

		pieza = new Pieza;//Crear e inicializar pieza
		SDL_Delay(100);//Espero unos ms para evitar que la primera y la segunda pieza sean iguales
	
		//!Pedir nombre de usuario
		pedir_nombre();
		
		while(true){
	
			//!Crear mecanismo para impedir repetición de piezas consecutivas
			siguiente_pieza = new Pieza;
			std::cout<< "PIEZA "<< pieza << " CREADA "<< std::endl;
			pieza_bloqueada = false;

			//Uint32 title_timestamp = SDL_GetTicks();
  			Uint32 frame_start;
  			Uint32 frame_end;
			Uint32 frame_duration;


			while(true){
				frame_start = SDL_GetTicks();
				while( SDL_PollEvent( &eventos ) != 0 ){ //Cola de eventos	
					if( eventos.type == SDL_QUIT ){ //Para cerrar (pulsando X de ventana)
						cerrar_programa = true;
						std::cout<<"TERMINASTE EL VIDEOJUEGO"<<std::endl;
						break;
					}
					else if( eventos.type == SDL_KEYDOWN ){
						Mueve_Pieza_Si_Se_Puede(eventos.key.keysym.sym, *pieza, tablero_estatico);
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
				if(bajar_pieza){
					bajar_pieza = false;
					bajar_pieza_si_puede(pieza);
				}
				Actualiza_Pantalla(*pieza, tablero_estatico, *siguiente_pieza); //renderizado de tablero con piezas fijas y actual pieza moviéndose
				
				frame_end = SDL_GetTicks();

    			// Keep track of how long each loop through the input/update/render cycle
    			// takes.

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
		mostrar_puntuacion();
	} 

	registar_puntuacion();
	cerrar(); //Liberar recursos reservados
	
	return 0;
}

void bajar_pieza_si_puede(Pieza* p_pieza){
	
	if(p_pieza!=nullptr){
		if(tablero_estatico.Comprueba_bajada(*p_pieza)){ //Si puede bajar

			p_pieza->coordenada.y_fila = p_pieza->coordenada.y_fila + 1;
			std::cout<< "PIEZA BAJADA AUTOMÁTICAMENTE "<<std::endl;
			Actualiza_Tablero_Dinamico(*p_pieza, tablero_dinamico);
			tablero_dinamico.imprime_tabla();//para debug en consola
		}
		else{
			// Cuando no se puede bajar, aquí se pasa la pieza al tablero estático
			Actualiza_Tablero_Estatico(*p_pieza, tablero_estatico);//borra filas ocupadas

			std::cout<< "TABLERO ESTATICO COPIADO AL DINAMICO. ELIMINADO DE HUECOS "<<std::endl;
			tablero_dinamico = tablero_estatico;
			tablero_estatico.imprime_tabla();//para debug en consola
			pieza_bloqueada = true;
			
			if(p_pieza->coordenada.y_fila<=1){
				std::cout<<"FIN DEL JUEGO"<<std::endl;
				tablero_lleno=true;
			}
		}
	}
}

Uint32 interrupcion(Uint32 interval, void *param)
{
	bajar_pieza = true;
    return MS_Nivel[nivel]; //devuelve la velocidad para la siguiente ejecución
}

void pedir_nombre(){

	pedir_nombre_jugador.cargar_texto_renderizado( "Introduce tu nombre:");
	std::string inputText =  "Jugador 1";
	Nombre_Jugador_Temp.cargar_texto_renderizado( inputText.c_str());
	pulsa_intro_continuar.cargar_texto_renderizado( "Pulsa Enter para continuar");

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	SDL_StartTextInput(); //! HABILITA LA ENTRADA DE TEXTO

	//Para gestionar la tasa de refresco
  	Uint32 frame_start;
  	Uint32 frame_end;
	Uint32 frame_duration;
	Uint32 target_frame_duration = kMsPerFrame/2; //No hace falta tanta velocidad

	//While application is running
	while( !quit )
	{
		frame_start = SDL_GetTicks();
		
		//Control del renderizado
		bool renderText = false;


		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
				//User requests quit
				if(e.type == SDL_QUIT)
				{
						quit = true;
						break;
				}
				if(( e.type == SDL_KEYDOWN)&&(e.key.keysym.scancode == SDL_SCANCODE_RETURN))
				{
						quit = true;
						break;
				}
				//! Condicionante para gestionar la escritura
				//Special key input
				else if( e.type == SDL_KEYDOWN )
				{
					if(e.key.keysym.scancode == SDL_SCANCODE_RETURN)
					{
						quit = true;
						break;
					}
					//Handle backspace
					if( e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
					{
						//lop off character
						inputText.pop_back();
						renderText = true;
					}
					//Handle copy
					else if( e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
					{
							SDL_SetClipboardText( inputText.c_str() );
					}
					//Handle paste
					else if( e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
					{
							inputText = SDL_GetClipboardText();
							renderText = true;
					}
					}
					//Special text input event
					else if( e.type == SDL_TEXTINPUT )
					{
						//Not copy or pasting
						if( !( SDL_GetModState() & KMOD_CTRL && ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' || e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) ) )
						{
							//Append character
							inputText += e.text.text;
							renderText = true;
						}
					}
				}

				//Renderizado si es necesario
				if( renderText )
				{
					//Text is not empty
					if( inputText != "" )
					{
						//Render new text
						Nombre_Jugador_Temp.cargar_texto_renderizado( inputText.c_str());
					}
					//Text is empty
					else
					{
						//Render space texture
						Nombre_Jugador_Temp.cargar_texto_renderizado( " ");
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor( Render, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( Render );

				//Render text textures
				pedir_nombre_jugador.renderizar( (ANCHO - pedir_nombre_jugador.get_ancho())/2, REJILLA );
				Nombre_Jugador_Temp.renderizar ( (ANCHO - Nombre_Jugador_Temp.get_ancho())/2 , 3*REJILLA );
				pulsa_intro_continuar.renderizar ( (ANCHO - pulsa_intro_continuar.get_ancho())/2 , 5*REJILLA );

				//Update screen
				SDL_RenderPresent( Render );

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
		Nombre_Jugador.cargar_texto_renderizado( inputText.c_str());
	}
	//Text is empty
	else
	{
		//Render space texture
		inputText = "Jugador 1";
		Nombre_Jugador.cargar_texto_renderizado(inputText.c_str());
	}

			
}

void mostrar_puntuacion(){

	bool quit = false;

	SDL_Event e;

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
		while( SDL_PollEvent( &e ) != 0 )
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

void registar_puntuacion(){


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