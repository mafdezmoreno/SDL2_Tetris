#include "constantes.h"
#include <iostream>
#include "texto.h"
#include <memory>
#include <thread>
#include <mutex>


void Texto::init(std::shared_ptr<SDL_Renderer> ext_render) // sin llamar a la función cargar texto
{
	_ancho = 0;
	_alto = 0;
	static std::mutex mi_mutex;
    std::lock_guard<std::mutex> mi_guard(mi_mutex);
	_Render = ext_render;

}

void Texto::init_full(std::string texto_renderizar, std::shared_ptr<SDL_Renderer> ext_render) // con llamada a la función cargar texto
{
	_ancho = 0;
	_alto = 0;
	static std::mutex mi_mutex;
    std::lock_guard<std::mutex> mi_guard(mi_mutex);
	_Render = ext_render;
	cargar_texto(texto_renderizar);
}

//!Default Constructor
Texto::Texto():
_Textura (nullptr, SDL_DestroyTexture),
_Render (nullptr),
_ancho (0),
_alto (0)
{
	std::cout << "Default Texto Constructor " << this << ": "<<std::endl;
}

//! Constructor II
Texto::Texto(std::shared_ptr<SDL_Renderer> ext_render):
_Textura (nullptr, SDL_DestroyTexture)
{
	_Render = ext_render;
	_ancho = 0;
	_alto = 0;
	std::cout << "Text Constructor II" << this << ": "<<std::endl;
}

//! Constructor III
Texto::Texto(std::string texto_renderizar, std::shared_ptr<SDL_Renderer> ext_render):
_Textura (nullptr, SDL_DestroyTexture)
{
	_ancho = 0;
	_alto = 0;

	static std::mutex mi_mutex;
    std::lock_guard<std::mutex> mi_guard(mi_mutex);
	_Render = ext_render;
	cargar_texto(texto_renderizar);
	std::cout << "Text Constructor III" << this << ": ";
	std::cout << _cadena_texto <<" "<<_Textura.get() <<std::endl;
}

// Rule of five implementation: https://cpppatterns.com/patterns/rule-of-five.html#line7
//! Copy Costructor
Texto::Texto(const Texto& original):
_Textura(nullptr, SDL_DestroyTexture)
{
	
	_Render = original._Render;
	_cadena_texto = original._cadena_texto;
	_ancho = original._ancho;
	_alto = original._alto;

	cargar_texto(_cadena_texto);
}

//! Copy assignment operator
Texto& Texto::operator=(const Texto& original){
	
	if (this == &original)  // self-assignment protection
    	return *this;

	_Render = original._Render;
	_cadena_texto = original._cadena_texto;
	_ancho = original._ancho;
	_alto = original._alto;

	cargar_texto(_cadena_texto);

	return *this;
}

//! Move constructor
Texto::Texto(Texto&& original)  noexcept:
_Textura(nullptr, SDL_DestroyTexture)
{
	
	_Render = std::move(original._Render);
	_Textura = std::move(original._Textura);
	_cadena_texto = std::move(original._cadena_texto);
	_ancho = std::move(original._ancho);
	_alto = std::move(original._alto);
}

//! Move assignment operator
Texto& Texto::operator=(Texto&& original) noexcept{
	
	if (this == &original)  // self-assignment protection
    	return *this;

	_Render = std::move(original._Render);
	_Textura = std::move(original._Textura);
	_cadena_texto = std::move(original._cadena_texto);
	_ancho = std::move(original._ancho);
	_alto = std::move(original._alto);

	return *this;
}

//! Destructor
Texto::~Texto()
{
	std::cout << "DESTRUCTOR TEXTO " << this << std::endl;
}

int Texto::get_ancho()
{
	return _ancho;
}

std::string Texto::get_cadena_texto(){

	return _cadena_texto;
}

// Store the text string to be rendered later
void Texto::_set_cadena_texto(std::string texto){

	std::cout<<"setted "<< texto << " on " <<this<< std::endl;
	_cadena_texto = texto;
}


// Converts the input string into rendered text for display in our game
bool Texto::cargar_texto(std::string inputText)
{

	static std::mutex mi_mutex;
    std::lock_guard<std::mutex> mi_guard(mi_mutex);

    //static std::unique_ptr<TTF_Font, std::function<void(TTF_Font*)>> Fuente_TTF(TTF_OpenFont("/System/Library/Fonts/Supplemental/Arial Unicode.ttf", 18), [](TTF_Font* puntero)
	static std::unique_ptr<TTF_Font, std::function<void(TTF_Font*)>> Fuente_TTF(TTF_OpenFont("../FreeSansBold.ttf", 18), [](TTF_Font* puntero)
	{
		std::cout << "No need to call deleter in a static uniquer pointer (avoid semgentation fault).\n";
	});

	if( Fuente_TTF == NULL ){
		std::cout<< "Error en la carga de la fuente. SDL_ttf Error: " << TTF_GetError()  <<std::endl;
		return false;
	}

	_set_cadena_texto(inputText);
	
	std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface*)>> 
	Texto_Surface(TTF_RenderText_Blended(Fuente_TTF.get(), inputText.c_str(), {0,0,0}), [](SDL_Surface* puntero)
	{
		SDL_FreeSurface(puntero);
	});
	
	
	if( Texto_Surface == nullptr )
	{
		std::cout<< "TTF_RenderText_Blended Error: " << TTF_GetError() << std::endl;
		return false;
	}

	_Textura.reset(SDL_CreateTextureFromSurface( _Render.get(), Texto_Surface.get()));
	if( _Textura == nullptr )
	{
		std::cout<< "SDL_CreateTextureFromSurface Error: " <<  SDL_GetError() << std::endl;
		return false;
	}

	_ancho = Texto_Surface->w;
	_alto = Texto_Surface->h;

	std::cout<< "Cadena de texto a RENDERIZADO: " << _cadena_texto <<std::endl;
	
	return true;
}
