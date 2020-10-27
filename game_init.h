#ifndef GAME_INIT_H
#define GAME_INIT_H

#include "texto.h"
#include <SDL.h>

class Game_Init{

    public:
        Game_Init();
        ~Game_Init();
        void pantalla_pedir_nombre();
        bool inicializar();
        Texto * get_nombre_jugador();

        SDL_Window*   _Ventana = NULL;     // Ventana
        SDL_Renderer* _Render = NULL; // Elementos a renderizar en interior

    private:

        Texto * _pedir_nombre_jugador;
        Texto * _Nombre_Jugador_Temp;
        Texto * _pulsa_intro_continuar;


        static constexpr std::size_t _kFramesPerSecond{30};
        static constexpr std::size_t _kMsPerFrame{1000 / _kFramesPerSecond};

};

#endif