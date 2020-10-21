#ifndef TEXTO_H
#define TEXT0_H

#include <SDL.h>
#include <SDL_ttf.h> //! Necesaria
#include <string>
#include "main.h"

extern SDL_Renderer* Render;  //! Destruir en la proxima clase Game a crear

//Clase para el renderizado del texto
class Texto
{
	public:
		Texto();
		
		bool cargar_texto_renderizado( std::string &&texto_renderizar);
		template <class T> void renderizar( const T &x, const T &y);
		int get_ancho();
		//int get_alto();
		std::string get_cadena_texto();

	// Rule of five implementation: https://cpppatterns.com/patterns/rule-of-five.html#line7
		//Copy Costructor
	    Texto(const Texto& original);
		//Copy assignment operator
		Texto& operator=(const Texto& original);
		//Destructor
		~Texto();
		//Move constructor
		Texto(Texto&& original)  noexcept;
		//Move assignment operator
		Texto& operator=(Texto&& original) noexcept;


	private:
		void liberar();	//libera los recursos reservados
		std::string* _cadena_texto;
		//const char* _cadena_texto;
		SDL_Texture* _Textura;
		int _ancho;
		int _alto;
};

//https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
template <class T> void Texto::renderizar(const T &x, const T &y)
{
	SDL_Rect Cuadrado = { (int)x, (int)y, _ancho, _alto };
	SDL_RenderCopyEx( Render, _Textura, nullptr, &Cuadrado, 0, nullptr, SDL_FLIP_NONE );
}

#endif

