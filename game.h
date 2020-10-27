#ifndef GAME_H
#define GAME_H


#include "pieza.h"
#include "tablero.h"
#include "constantes.h"
#include <SDL.h>
#include <SDL_thread.h>
#include "texto.h"
#include "game_init.h"

constexpr std::size_t kFramesPerSecond{60};
constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};

class Tablero;
class Pieza;
//class Game_Init;

class Game{

    public:

        Game(Texto * nombre_jugador, bool * counter);
        Game(Game_Init * game_start, bool * counter);
        ~Game();
        
        void cerrar();      // Libera recursos previamente reservados
        //void Mueve_Pieza_Si_Se_Puede(SDL_Keycode tecla, Pieza &pieza, Tablero &tablero); //Mueve la pieza si no choca con bordes u otras piezas
        void Mueve_Pieza_Si_Se_Puede(const SDL_Keycode& tecla, Pieza &pieza, Tablero &tablero);
        void Actualiza_Pantalla(Pieza &pieza, Tablero &tablero_estatico, Pieza &siguiente_pieza);
        void Actualiza_Tablero_Dinamico(Pieza &pieza, Tablero &tablero);
        void Actualiza_Tablero_Estatico(Pieza &pieza, Tablero &tablero);
        Coordenada Mapeado_Coord_Tablero(Coordenada &coord);
        void bajar_pieza_si_puede(Pieza* p_pieza);
        bool cargar_texto();
        void game_run();

        //Uint32 _interrupcion(Uint32 interval, void *param);
        //SDL_TimerID timerID;
        bool * _bajar_pieza;

        int _nivel = 0;	//1	//2	 //3  //4  //5  //6  //7  //8  //9 //10
        int _niveles[12] = {2000, 1000, 900, 800, 700, 600, 500, 450, 400, 350, 300, 250}; //ms para cada intervalo
    
    private:

        SDL_Window*   _Ventana = NULL;     // Ventana
        SDL_Renderer* _Render = NULL; // Elementos a renderizar en interior

        Tablero* _tablero_dinamico; //Para comprobar los movimientos de las piezas
        Tablero* _tablero_estatico; //Para guardar las piezas fijas.

        Texto * _Texto_Puntuacion;
        Texto * _Texto_Nivel;
        Texto * _Valor_Nivel;
        Texto * _Texto_Jugador;
        Texto * _Nombre_Jugador;
        Texto * _Valor_Puntuacion;
        
        int nivel_previo = -1;

        //SDL_TimerCallback _interrupcion(Uint32 interval, void *param);
        bool _inicializar(); // Inicializa SDL y crea la ventana
        bool _init_timer(); // Inicializa SDL y crea la ventana
        void Dibuja_tablero();

        // VARIABLES GLOBALES
       


        
        bool pieza_bloqueada;
        bool tablero_lleno = false;
        bool cerrar_programa = false;

        int _puntuacion = 0;

};


#endif