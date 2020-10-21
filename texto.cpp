#include "main.h"
#include <iostream>

TTF_Font* Fuente_TTF = NULL;

//! Constructor
Texto::Texto()
{
	_Textura = nullptr;
	//std::string * _cadena_texto = new std::string();
	_cadena_texto = nullptr;
	_ancho = 0;
	_alto = 0;
}


// Rule of five implementation: https://cpppatterns.com/patterns/rule-of-five.html#line7
//Copy Costructor
Texto::Texto(const Texto& original){
	
	_Textura = original._Textura;
	_cadena_texto =_cadena_texto;
	_ancho = original._ancho;
	_alto = original._alto;
}


//Copy assignment operator
Texto& Texto::operator=(const Texto& original){
	
	if (this == &original)  // prevención auto asignación
    	return *this;

	_cadena_texto = original._cadena_texto;
	_ancho = original._ancho;
	_alto = original._alto;

	return *this;
}
//Destructor
Texto::~Texto()
{
	liberar();
}
void Texto::liberar() //Reinicia el contenido para el siguiente renderizado
{
	if( _Textura != nullptr )
	{
		SDL_DestroyTexture( _Textura );
		_Textura = nullptr;
		delete _cadena_texto;
		_ancho = 0;
		_alto = 0;
	}
}


//Move constructor
Texto::Texto(Texto&& original)  noexcept{
	
	_cadena_texto = original._cadena_texto;
	_ancho = original._ancho;
	_alto = original._alto;

	original._cadena_texto = nullptr;
}


//Move assignment operator
Texto& Texto::operator=(Texto&& original) noexcept{
	
	if (this == &original)  // prevención auto asignación
    	return *this;
	
	if(!_cadena_texto)
		delete _cadena_texto;

	_cadena_texto = original._cadena_texto;
	_ancho = original._ancho;
	_alto = original._alto;

	original._cadena_texto = nullptr;
	return *this;
}


bool Texto::cargar_texto_renderizado( std::string &&texto_renderizar)
{

	_cadena_texto = &texto_renderizar;
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




int Texto::get_ancho()
{
	return _ancho;
}

/*
int Texto::get_alto()
{
	return _alto;
}*/

std::string Texto::get_cadena_texto(){

	return *_cadena_texto;
}