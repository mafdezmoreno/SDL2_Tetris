#include "game_init.h"
#include "game.h"
#include "game_close.h"
#include <iostream>

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
	//! Derived class functions override virtual base class functions: One member function in an inherited class overrides a virtual base class member function.

//!Concurrency

	//- [] The project uses multithreading. The project uses multiple threads in the execution.
	//- [] A condition variable is used in the project. A ```std::condition_variable``` is used in the project code to synchronize thread execution.

int main( int argc, char* args[] )
{

	Game_Init game_init; //crea ventana, render y pide nombre
	
	Game game(game_init);
	
	game.game_run();
	
	Game_Close game_close(game, game_init); //debe adquirir ventana, render, nivel, puntuacion
	
	return 0;
}




