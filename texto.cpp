#include "constantes.h"
#include <iostream>
#include "texto.h"


//!Default Constructor
Texto::Texto(SDL_Renderer* ext_render)
{
	_Render = ext_render;
	_Textura = nullptr;
	_cadena_texto = nullptr;
	_ancho = 0;
	_alto = 0;
	std::cout << "Texto Default Constructor " << this << ": "<<std::endl;

}


//! Constructor
Texto::Texto(std::string &&texto_renderizar, SDL_Renderer* ext_render)
{
	_Render = ext_render;
	_Textura = nullptr;
	_cadena_texto = nullptr;
	_ancho = 0;
	_alto = 0;
	cargar_texto(texto_renderizar);
	std::cout << "Texto Constructor " << this << ": ";
	std::cout << texto_renderizar <<std::endl;

}

void Texto::cargar_texto(std::string inputText)
{
	if( Fuente_TTF == NULL ){
		std::cout<< "Error en la carga de la fuente. SDL_ttf Error: " << TTF_GetError()  <<std::endl;
	}
	else{
		if(!cargar_texto_renderizado(inputText)){
			std::cout<< "No se ha podido renderizar la textura del texto: "<< "<<"<< inputText << ">>" <<std::endl;
		}
	}
}

// Rule of five implementation: https://cpppatterns.com/patterns/rule-of-five.html#line7
//! Copy Costructor
Texto::Texto(const Texto& original){
	
	_Textura = original._Textura;
	_cadena_texto = original._cadena_texto;
	_ancho = original._ancho;
	_alto = original._alto;
	std::cout << "Texto Copy Costructor " << this << ": ";
	std::cout << _cadena_texto <<std::endl;
}

//! Copy assignment operator
Texto& Texto::operator=(const Texto& original){
	
	if (this == &original)  // prevención auto asignación
    	return *this;

	_cadena_texto = original._cadena_texto;
	_ancho = original._ancho;
	_alto = original._alto;

	std::cout << "Texto Copy assignment operator " << this << ": ";
	std::cout << _cadena_texto <<std::endl;

	return *this;
}

//! Move constructor
Texto::Texto(Texto&& original)  noexcept{
	
	_cadena_texto = original._cadena_texto;
	_ancho = original._ancho;
	_alto = original._alto;

	original._cadena_texto = nullptr;

	std::cout << "Texto Move constructor " << this << ": ";
	std::cout << _cadena_texto <<std::endl;
}

//! Move assignment operator
Texto& Texto::operator=(Texto&& original) noexcept{
	
	if (this == &original)  // prevención auto asignación
    	return *this;
	
	if(!_cadena_texto)
		delete _cadena_texto;

	_cadena_texto = original._cadena_texto;
	_ancho = original._ancho;
	_alto = original._alto;

	original._cadena_texto = nullptr;


	std::cout << "Texto Move assignment operator " << this << ": ";
	std::cout << _cadena_texto <<std::endl;

	return *this;
}

//! Destructor
Texto::~Texto()
{
	std::cout << "Texto DESTRUCTOR TEXTO " << this << ": ";
	
	if( _cadena_texto != nullptr )
	{
		//std::cout << *_cadena_texto <<std::endl;	
	}
	
	liberar();
}
void Texto::liberar() //Reinicia el contenido para el siguiente renderizado
{
	if( _Textura != nullptr )
	{
		SDL_DestroyTexture( _Textura );
		_Textura = nullptr;
		_ancho = 0;
		_alto = 0;
	}
	if( _cadena_texto != nullptr )
	{
		_cadena_texto = nullptr;
	}
	
}

bool Texto::cargar_texto_renderizado(std::string texto_renderizar)
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
        _Textura = SDL_CreateTextureFromSurface( _Render, Texto_Surface );
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

std::string * Texto::get_cadena_texto(){

	return _cadena_texto;
}