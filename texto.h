#ifndef TEXTO_H
#define TEXTO_H

#include "SDL2/SDL.h"
//#include "SDL2_ttf/SDL_ttf.h" // Mac
#include "SDL2/SDL_ttf.h" // Linux
#include <string>
#include <memory>
#include <future>
#include <thread>
#include <utility>

// To render text on the screen
class Texto
{
	public:
				
		//https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
		template <class T> void renderizar(const T &x, const T &y)
		{
			SDL_Rect Cuadrado = { (int)x, (int)y, _ancho, _alto };
			SDL_RenderCopyEx( _Render.get(), _Textura.get(), nullptr, &Cuadrado, 0, nullptr, SDL_FLIP_NONE );
		}

		int get_ancho();  // Returns the width in pixels of the rendered text
		std::string get_cadena_texto(); // Returns the text string rendered
		bool cargar_texto(std::string inputText); // Render the text (to show it graphically in the window)
		void init_full(std::string texto_renderizar, std::shared_ptr<SDL_Renderer> ext_render); // Includes a call to the "cargar_texto" function
		void init(std::shared_ptr<SDL_Renderer> ext_render);
		
		// Default Constructor
		Texto();
		// Constructor II
		Texto(std::shared_ptr<SDL_Renderer> ext_render);
		// Constructor III
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
		void _set_cadena_texto(std::string texto); // Store the text string

		std::shared_ptr<SDL_Renderer> _Render;
		std::string _cadena_texto; // Text string rendered
		std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> _Textura;

		int _ancho{0}; 	// Width in pixels of the rendered text
		int _alto{0};	// Height in pixels of the rendered text
};

#endif

