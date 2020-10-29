#ifndef GAME_INIT_H
#define GAME_INIT_H

#include "texto.h"
#include <SDL.h>
#include <memory>

class Game_Init{

    public:
        Game_Init();
        ~Game_Init();
        void pantalla_pedir_nombre();
        bool inicializar();
        Texto * get_nombre_jugador();

        // https://stackoverflow.com/questions/48672399/is-it-possible-to-use-sdl2-with-smart-pointers
        //SDL_Window*   _Ventana;     // Ventana`
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _Ventana;
        //SDL_Renderer* _Render; // Elementos a renderizar en interior
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _Render;

        

    private:

        Texto * _pedir_nombre_jugador;
        Texto * _Nombre_Jugador_Temp;
        Texto * _pulsa_intro_continuar;

        static constexpr std::size_t _kFramesPerSecond{30};
        static constexpr std::size_t _kMsPerFrame{1000 / _kFramesPerSecond};

};

#endif