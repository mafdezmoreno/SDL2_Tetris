#ifndef GAME_H
#define GAME_H


#include "pieza.h"
#include "tablero.h"
#include "constantes.h"
#include <SDL.h>
#include <SDL_thread.h>
#include "texto.h"
#include "game_init.h"
#include <memory>


class Tablero;
class Pieza;

Uint32 interrupcion(Uint32 interval, void *param);

class Interrupt_Param
{
	public:
        Interrupt_Param(){
            nivel = 0;
        }
		bool interrupt_control;
		int nivel;
};


class Game{

    public:

        Game(Game_Init * game_start);//, Interrupt_Param * param);
        //Game(Game_Init * game_start, bool * param);
        ~Game();
        
        void Mueve_Pieza_Si_Se_Puede(const SDL_Keycode& tecla, Pieza &pieza, Tablero &tablero);
        void Actualiza_Pantalla(Pieza &pieza, Tablero &tablero_estatico, Pieza &siguiente_pieza);
        void Actualiza_Tablero_Dinamico(Pieza &pieza, Tablero &tablero);
        void Actualiza_Tablero_Estatico(Pieza &pieza, Tablero &tablero);
        Coordenada Mapeado_Coord_Tablero(Coordenada &coord);
        void bajar_pieza_si_puede(Pieza* p_pieza);
        bool cargar_texto();
        void game_run();
        const int * get_puntuacion();
        const int * get_nivel();

        bool * _bajar_pieza;
    
        Texto * _Texto_Puntuacion;
        Texto * _Texto_Nivel;
        Texto * _Valor_Nivel;
        Texto * _Texto_Jugador;
        Texto * _Nombre_Jugador;
        Texto * _Valor_Puntuacion;
    
        // https://stackoverflow.com/questions/48672399/is-it-possible-to-use-sdl2-with-smart-pointers
        //SDL_Window*   _Ventana;     // Ventana`
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _Ventana;
        //SDL_Renderer* _Render; // Elementos a renderizar en interior
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _Render;
    
    private:



        Tablero* _tablero_dinamico; //Para comprobar los movimientos de las piezas
        Tablero* _tablero_estatico; //Para guardar las piezas fijas.


        //SDL_TimerCallback _interrupcion(Uint32 interval, void *param);
        bool _inicializar(); // Inicializa SDL y crea la ventana
        bool _init_timer(); // Inicializa SDL y crea la ventana
        void Dibuja_tablero();

        // VARIABLES GLOBALES
       
        bool pieza_bloqueada;
        bool tablero_lleno = false;
        bool cerrar_programa = false;

        int _puntuacion = 0;
        int * _nivel;	//1	//2	 //3  //4  //5  //6  //7  //8  //9 //10
        int _nivel_previo = -1;
        int puntuacion_previa = -1;


        static constexpr std::size_t _kFramesPerSecond{60};
        static constexpr std::size_t _kMsPerFrame{1000 / _kFramesPerSecond};

        std::shared_ptr<Interrupt_Param> _params;

};


#endif