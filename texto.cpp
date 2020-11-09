#include "constantes.h"
#include <iostream>
#include "texto.h"
#include <memory>
#include <thread>
#include <mutex>

//! Crear un constructor vacío, para poder llamar a con std::thread a una función init de la clase que se encarge de la inicialización de las variables en paralelo:
// init(std::shared_ptr<SDL_Renderer> ext_render)
// init_full(std::string texto_renderizar, std::shared_ptr<SDL_Renderer> ext_render,) // con llamada a la función cargar texto

//!Default Constructor
Texto::Texto(std::shared_ptr<SDL_Renderer> ext_render)
{
	_Render = ext_render;
	_Textura = nullptr;
	_ancho = 0;
	_alto = 0;
	std::cout << "Texto Default Constructor " << this << ": "<<std::endl;

}

//! Constructor
Texto::Texto(std::string texto_renderizar, std::shared_ptr<SDL_Renderer> ext_render)
{
	static std::mutex mi_mutex;
    std::lock_guard<std::mutex> mi_guard(mi_mutex);
	_Render = ext_render;
	_Textura = nullptr;
	_ancho = 0;
	_alto = 0;

	cargar_texto(texto_renderizar);
	std::cout << "Texto Constructor " << this << ": ";
	std::cout << _cadena_texto <<" "<<_Textura <<std::endl;

}


std::unique_ptr<TTF_Font, std::function<void(TTF_Font*)>> 
assign_font(TTF_Font* Fuente_TTF) {
  		
	return std::unique_ptr<TTF_Font,std::function<void(TTF_Font*)>>(Fuente_TTF, [](TTF_Font* fnt) {
   		if (fnt != nullptr) 
			TTF_CloseFont(fnt); //Segmentation fault whit static variable
	});
}


bool Texto::cargar_texto(std::string inputText)
{

	static std::mutex mi_mutex;
    std::lock_guard<std::mutex> mi_guard(mi_mutex);
    static std::unique_ptr<TTF_Font, std::function<void(TTF_Font*)>> Fuente_TTF(TTF_OpenFont("FreeSansBold.ttf", 18), [](TTF_Font* puntero)
	{
		std::cout << "No need to call deleter in a static uniquer pointer (avoid semgentation fault).\n";
	});



	//! bug: Segmentation fault
	//static std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> Fuente_TTF(TTF_OpenFont("FreeSansBold.ttf", 18), &TTF_CloseFont);

	
	/*Works
    static std::unique_ptr<TTF_Font, std::function<void(TTF_Font*)>> Fuente_TTF(TTF_OpenFont("FreeSansBold.ttf", 18), [](TTF_Font* puntero)
        {
            std::cout << "destroying from a custom deleter...\n";
			//if (puntero != nullptr){
			//	TTF_CloseFont(puntero);//! segmentation fault: no deleter required whit static
			//}
        });
	*/

	/*Works removing deleter
	static std::unique_ptr<TTF_Font, std::function<void(TTF_Font*)>> Fuente_TTF;
		if(Fuente_TTF ==nullptr){
			std::cout<<"Test"<<std::endl;
    		Fuente_TTF = assign_font(TTF_OpenFont("FreeSansBold.ttf", 18));
		}
	*/

	if( Fuente_TTF == NULL ){
		std::cout<< "Error en la carga de la fuente. SDL_ttf Error: " << TTF_GetError()  <<std::endl;
		return false;
	}

	_cadena_texto = inputText;//! usar set cadena de texto

	//! pasar a smart pointer
	SDL_Surface* Texto_Surface = TTF_RenderText_Blended(Fuente_TTF.get(), inputText.c_str(), {0,0,0});
	if( Texto_Surface == nullptr )
	{
		std::cout<< "TTF_RenderText_Blended Error: " << TTF_GetError() << std::endl;
		return false;
	}

	_Textura = SDL_CreateTextureFromSurface( _Render.get(), Texto_Surface );
	if( _Textura == nullptr )
	{
		std::cout<< "SDL_CreateTextureFromSurface Error: " <<  SDL_GetError() << std::endl;
		return false;
	}

	_ancho = Texto_Surface->w;
	_alto = Texto_Surface->h;


	SDL_FreeSurface(Texto_Surface);

	std::cout<< "Cadena de texto a RENDERIZADO: " << _cadena_texto <<std::endl;
	
	return true;
}


// Rule of five implementation: https://cpppatterns.com/patterns/rule-of-five.html#line7
//! Copy Costructor
Texto::Texto(const Texto& original){
	
	_Render = original._Render;
	_Textura = original._Textura;
	_cadena_texto = original._cadena_texto;
	_ancho = original._ancho;
	_alto = original._alto;
	//std::cout << "Texto Copy Costructor " << this << ": ";
	//std::cout << _cadena_texto <<" "<<_Textura <<std::endl;
}

//! Copy assignment operator
Texto& Texto::operator=(const Texto& original){
	
	if (this == &original)  // prevención auto asignación
    	return *this;

	_Render = original._Render;
	_Textura = original._Textura;
	_cadena_texto = original._cadena_texto;
	_ancho = original._ancho;
	_alto = original._alto;

	//std::cout << "Texto Copy assignment operator " << this << ": ";
	//std::cout << _cadena_texto <<" "<<_Textura <<std::endl;

	return *this;
}

//! Move constructor
Texto::Texto(Texto&& original)  noexcept{
	
	_Render = std::move(original._Render);
	_Textura = std::move(original._Textura);
	_cadena_texto = std::move(original._cadena_texto);
	_ancho = std::move(original._ancho);
	_alto = std::move(original._alto);
	original._Textura = nullptr;
	original._Render = nullptr;
	//std::cout << "Texto Move constructor " << this << ": ";
	//std::cout << _cadena_texto <<" "<<_Textura <<std::endl;
}

//! Move assignment operator
Texto& Texto::operator=(Texto&& original) noexcept{
	
	if (this == &original)  // prevención auto asignación
    	return *this;

	_Render = original._Render;
	_Textura = original._Textura;
	_cadena_texto = original._cadena_texto;
	_ancho = original._ancho;
	_alto = original._alto;

	original._Textura = nullptr;
	original._Render = nullptr;

	//std::cout << "Texto Move assignment operator " << this << ": ";
	//std::cout << _cadena_texto <<" "<<_Textura <<std::endl;

	return *this;
}

//! Destructor
Texto::~Texto()
{
	std::cout << "DESTRUCTOR TEXTO " << this << std::endl;
}

/*
bool Texto::cargar_texto_renderizado(std::string texto_renderizar)
{
	_cadena_texto = texto_renderizar;
	std::cout<< "Cadena de texto a renderizar: " << _cadena_texto<<std::endl;
	SDL_Surface* Texto_Surface = TTF_RenderText_Blended(Fuente_TTF.get(), texto_renderizar.c_str(), {0,0,0});
	
	if( Texto_Surface == nullptr )
	{
		std::cout<< "TTF_RenderText_Blended Error: " << TTF_GetError() << std::endl;
	}
	else
	{
        _Textura = SDL_CreateTextureFromSurface( _Render.get(), Texto_Surface );
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
	std::cout<< "Cadena de texto a RENDERIZADO: " << _cadena_texto<<std::endl;
	return _Textura != nullptr;
}*/

int Texto::get_ancho()
{
	return _ancho;
}

std::string Texto::get_cadena_texto(){

	return _cadena_texto;
}
void Texto::set_cadena_texto(std::string texto){

	std::cout<<"setted "<< texto << " on " <<this<< std::endl;
	_cadena_texto = texto;
}