#include "game_init.h"
#include "game.h"
#include <iostream>

//! BUGs::
	// ALGUNA PIEZA INICIA FUERA DEL TABLERO!!!!
	// No incrementa el valor del nivel, ni lo renderiza en la pantalla

//! Mejoras:
//! Cambiar _tablero a dinamic raw pointer
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
	//! hacer algún overload de alguna función (quizás los mas fácil sea hacerlo de un constructor)
	//! Derived class functions override virtual base class functions: One member function in an inherited class overrides a virtual base class member function.

//!Memory Management
	//! The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate: The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.
	//! The project uses move semantics to move data, instead of copying it, where possible: For classes with move constructors, the project returns objects of that class by value, and relies on the move constructor, instead of copying the object.
	//! The project uses smart pointers instead of raw pointers: The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers.
	
//!Concurrency
	//! The project uses multithreading. The project uses multiple threads in the execution.
	//! A promise and future is used in the project. A promise and future is used to pass data from a worker thread to a parent thread in the project code.
	//! A mutex or lock is used in the project. A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code.
	//! A condition variable is used in the project. A std::condition_variable is used in the project code to synchronize thread execution.


Uint32 interrupcion(Uint32 interval, void *param)
{
	*(bool*)param = true;
	//_bajar_pieza = true;//Segmentación fault
	std::cout<< "INTERRUPCION"<<std::endl;
    return (Uint32)1000;
}  //devuelve la velocidad para la siguiente ejecución


//! Crear una clase de renderizado que se pase como parametro a las instancias de game

int main( int argc, char* args[] )
{
	bool interrupt_counter = false;
	std::cout<<"INIT"<<std::endl;  
	Game_Init game_init; //crea ventana, render y pide nombre
	
	Game game(&game_init, &interrupt_counter); //inicializa timer. //adquiere ventana, render y pide nombre
	
	//timer start
	SDL_TimerID timerID = SDL_AddTimer(500, interrupcion, (void *)(&interrupt_counter));
	
	game.game_run();


	//! Implementar
	//Game_End game_end(&game); //debe adquirir ventana, render, nivel, puntuacion
	//game_end;

	std::cout<<"JUEGO FINALIZADO"<<std::endl; 
	
	return 0;
}



