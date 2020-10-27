#ifndef TEXTO_H
#define TEXTO_H

#include <SDL.h>
#include <SDL_ttf.h> //! Necesaria
#include <string>

extern SDL_Renderer* Render;  //! Destruir en la proxima clase Game a crear



//Clase para el renderizado del texto
class Texto
{
	public:
		
		
		bool cargar_texto_renderizado(std::string texto_renderizar);
		
		//https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
		template <class T> void renderizar(const T &x, const T &y)
		{
			SDL_Rect Cuadrado = { (int)x, (int)y, _ancho, _alto };
			SDL_RenderCopyEx( _Render, _Textura, nullptr, &Cuadrado, 0, nullptr, SDL_FLIP_NONE );
		}

		
		int get_ancho();
		//int get_alto();
		std::string * get_cadena_texto();
		void cargar_texto(std::string inputText);

	// Rule of five implementation: https://cpppatterns.com/patterns/rule-of-five.html#line7
		
		//! Default Constructor
		Texto(SDL_Renderer* ext_render);
		//! Constructor
		Texto(std::string &&texto_renderizar, SDL_Renderer* ext_render);
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
		SDL_Renderer* _Render = NULL;
		TTF_Font * Fuente_TTF = TTF_OpenFont("FreeSansBold.ttf", 16);
		void liberar();	//libera los recursos reservados
		std::string* _cadena_texto;
		//const char* _cadena_texto;
		SDL_Texture* _Textura;
		int _ancho;
		int _alto;
		
};


#endif

