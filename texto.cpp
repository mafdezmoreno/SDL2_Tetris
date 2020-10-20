#include "main.h"
#include <iostream>

TTF_Font* Fuente_TTF = NULL;

Texto::Texto()
{
	_Textura = nullptr;
	_ancho = 0;
	_alto = 0;
}

Texto::~Texto()
{
	liberar();
}

bool Texto::cargar_texto_renderizado( std::string texto_renderizar)
{

	_cadena_texto = texto_renderizar;
	liberar();
	SDL_Surface* Texto_Surface = TTF_RenderText_Blended( Fuente_TTF, texto_renderizar.c_str(),  {0,0,0});
	
	if( Texto_Surface == nullptr )
	{
		std::cout<< "TTF_RenderText_Blended Error: " << TTF_GetError() << std::endl;
	}
	else
	{
        _Textura = SDL_CreateTextureFromSurface( Render, Texto_Surface );
		if( _Textura == nullptr )
		{
			std::cout<< "SDL_CreateTextureFromSurface Error: " <<  SDL_GetError() << std::endl;
		}
		else
		{
			_ancho = Texto_Surface->w;
			_alto = Texto_Surface->h;
		}

		SDL_FreeSurface( Texto_Surface );
	}
	
	return _Textura != nullptr;
}

void Texto::liberar()
{
	if( _Textura != nullptr )
	{
		SDL_DestroyTexture( _Textura );
		_Textura = nullptr;
		_ancho = 0;
		_alto = 0;
	}
}

//void Texto::renderizar( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
void Texto::renderizar( int x, int y)
{
	SDL_Rect renderQuad = { x, y, _ancho, _alto };
	//if( clip != nullptr )
	//{
	//	renderQuad.w = clip->w;
	//	renderQuad.h = clip->h;
	//}
	SDL_RenderCopyEx( Render, _Textura, nullptr, &renderQuad, 0, nullptr, SDL_FLIP_NONE );
}

int Texto::get_ancho()
{
	return _ancho;
}

int Texto::get_alto()
{
	return _alto;
}

std::string Texto::get_cadena_texto(){

	return _cadena_texto;
}