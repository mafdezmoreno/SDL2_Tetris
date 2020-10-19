#ifndef TEXTO_H
#define TEXT0_H

#include <SDL.h>
#include <SDL_ttf.h> //! Necesaria
#include <stdio.h>
#include <string>

//Clase para el renderizado del texto
class Texto
{
	public:
		Texto();
		~Texto();
		bool cargar_texto_renderizado( std::string texto_renderizar);
		void liberar();		
		void renderizar( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
		int get_ancho();
		int get_alto();

	private:

		SDL_Texture* _Textura;
		int _ancho;
		int _alto;
};
#endif

