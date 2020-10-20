#ifndef TEXTO_H
#define TEXT0_H

#include <SDL.h>
#include <SDL_ttf.h> //! Necesaria
//#include <stdio.h>
#include <string>

//Clase para el renderizado del texto
class Texto
{
	public:
		Texto();
		~Texto();
		bool cargar_texto_renderizado( std::string texto_renderizar);
		void renderizar ( int x, int y);
		int get_ancho();
		int get_alto();
		std::string get_cadena_texto();

	private:
		void liberar();	//libera los recursos reservados
		std::string _cadena_texto;
		SDL_Texture* _Textura;
		int _ancho;
		int _alto;
};
#endif

