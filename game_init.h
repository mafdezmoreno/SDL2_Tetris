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
        std::unique_ptr<Texto> get_nombre_jugador();
        std::unique_ptr<Texto> get_pulsa_intro_continuar();

        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _Ventana;
        
        //std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _Render;
        
        std::shared_ptr<SDL_Renderer> _Render;


    private:

        std::unique_ptr<Texto> _pedir_nombre_jugador;
        std::unique_ptr<Texto>  _Nombre_Jugador_Temp;
        std::unique_ptr<Texto> _pulsa_intro_continuar;

        static constexpr std::size_t _kFramesPerSecond{30};
        static constexpr std::size_t _kMsPerFrame{1000 / _kFramesPerSecond};

};

#endif