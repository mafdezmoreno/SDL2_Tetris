#ifndef TEXTO_H
#define TEXTO_H

#include <SDL.h>
#include <SDL_ttf.h> //! Necesaria
#include <string>
#include "memory"
#include <future>
#include <thread>
#include <utility>



//Clase para el renderizado del texto
class Texto
{
	public:
		
		//bool cargar_texto_renderizado(std::string texto_renderizar);
		
		//https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
		template <class T> void renderizar(const T &x, const T &y)
		{
			SDL_Rect Cuadrado = { (int)x, (int)y, _ancho, _alto };
			SDL_RenderCopyEx( _Render.get(), _Textura.get(), nullptr, &Cuadrado, 0, nullptr, SDL_FLIP_NONE );
		}

		int get_ancho();
		std::string get_cadena_texto();
		void set_cadena_texto(std::string texto);
		bool cargar_texto(std::string inputText);

		//! Default Constructor
		Texto(std::shared_ptr<SDL_Renderer> ext_render);
		//! Constructor
		Texto(std::string texto_renderizar, std::shared_ptr<SDL_Renderer> ext_render);
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
		std::shared_ptr<SDL_Renderer> _Render;
		std::string _cadena_texto;

		//!convertir en smart pointer
		//SDL_Texture* _Textura;
		std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> _Textura;

		int _ancho{0};
		int _alto{0};
	
};

#endif

