#ifndef GAME_H
#define GAME_H


#include "pieza.h"
#include "tablero.h"
#include "constantes.h"
#include "SDL2/SDL.h"
#include "texto.h"
#include "game_init.h"
#include <memory>


class Tablero;
class Pieza;

// Interrupt function to activate the descent of the part
Uint32 interrupcion(Uint32 interval, void *param);

// Class that stores the basic management parameters of the game
class Interrupt_Param
{
	public:
        Interrupt_Param(){
            nivel = 0;
            puntuacion = 0;
            nivel_previo = -1;
            puntuacion_previa = -1;
        }
		bool interrupt_control; // To manage when the part can be moved down
		int nivel;
        int puntuacion;
        int nivel_previo;
        int puntuacion_previa;
};


class Game{

    public:

        Game(Game_Init& game_start);
        ~Game();
        
        void Mueve_Pieza_Si_Se_Puede(const SDL_Keycode& tecla, Pieza &pieza, Tablero &tablero);
        void Actualiza_Pantalla(Pieza &pieza, Pieza &siguiente_pieza);
        void Actualiza_Tablero_Dinamico(Pieza &pieza, Tablero &tablero);
        void Actualiza_Tablero_Estatico(Pieza &pieza, Tablero &tablero);
        Coordenada Mapeado_Coord_Tablero(Coordenada &coord);
        void bajar_pieza_si_puede(Pieza* p_pieza);
        bool cargar_texto();
        void game_run();

        std::unique_ptr<const int> get_puntuacion();
        std::unique_ptr<const int>  get_nivel();

        std::unique_ptr<Texto> get_nombre_jugador();
        std::unique_ptr<Texto> get_Texto_Puntuacion();
        std::unique_ptr<Texto> get_Texto_Nivel();
        std::unique_ptr<Texto> get_Valor_Nivel();
        std::unique_ptr<Texto> get_Texto_Jugador();
        std::unique_ptr<Texto> get_Valor_Puntuacion();
    
        // https://stackoverflow.com/questions/48672399/is-it-possible-to-use-sdl2-with-smart-pointers
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _Ventana;
        std::shared_ptr<SDL_Renderer> _Render;

    
    private:

        bool _inicializar();   // Initialize SDL and create the window
        void Dibuja_tablero(); // Draw the edges of the board

        bool pieza_bloqueada;
        bool tablero_lleno = false;
        bool cerrar_programa = false;

        static constexpr std::size_t _kFramesPerSecond{60};
        static constexpr std::size_t _kMsPerFrame{1000 / _kFramesPerSecond};

        std::shared_ptr<Interrupt_Param> _params;

        std::unique_ptr<Texto> _Nombre_Jugador;
        std::unique_ptr<Texto> _Texto_Puntuacion;
        std::unique_ptr<Texto> _Texto_Nivel;
        std::unique_ptr<Texto> _Valor_Nivel;
        std::unique_ptr<Texto> _Texto_Jugador;
        std::unique_ptr<Texto> _Valor_Puntuacion;

        std::unique_ptr<Tablero> _tablero_dinamico; // To check the movements of the parts
        std::unique_ptr<Tablero> _tablero_estatico; // To store the locked parts

};


#endif
