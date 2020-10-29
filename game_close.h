#ifndef GAME_CLOSE_H
#define GAME_CLOSE_H

#include "texto.h"
#include <SDL.h>
#include <memory>

class Game;
class Game_Init;

class Game_Close{

    public:

        Game_Close(Game * game,  Game_Init * game_init);

        void registar_puntuacion();
        void mostrar_puntuacion();

        ~Game_Close();

    private:
        SDL_Event* _eventos;
        Texto* _Texto_Jugador;
        Texto* _Nombre_Jugador;
        Texto* _Texto_Puntuacion;
        Texto* _Valor_Puntuacion;
        Texto* _Texto_Nivel;
        Texto* _Valor_Nivel;
        Texto* _pulsa_intro_continuar;

        const int * _puntuacion;
        const int * _nivel;
        std::string _nombre;
        
        // https://stackoverflow.com/questions/48672399/is-it-possible-to-use-sdl2-with-smart-pointers
        //SDL_Window*   _Ventana;     // Ventana`
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _Ventana;
        //SDL_Renderer* _Render; // Elementos a renderizar en interior
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _Render;

        void _cerrar();

};

#endif