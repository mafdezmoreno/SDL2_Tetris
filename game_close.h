#ifndef GAME_CLOSE_H
#define GAME_CLOSE_H

#include "texto.h"
#include <SDL2/SDL.h>
#include <memory>

class Game;
class Game_Init;

class Game_Close{

    public:

        Game_Close(Game& game,  Game_Init& game_init);

        void registar_puntuacion(); // Register the score to a .txt
        void mostrar_puntuacion();  // Display a window with the game information

        ~Game_Close();

    private:
      
        std::unique_ptr<Texto> _Texto_Jugador;
        std::unique_ptr<Texto> _Nombre_Jugador;
        std::unique_ptr<Texto> _Texto_Puntuacion;
        std::unique_ptr<Texto> _Valor_Puntuacion;
        std::unique_ptr<Texto> _Texto_Nivel;
        std::unique_ptr<Texto> _Valor_Nivel;
        std::unique_ptr<Texto> _pulsa_intro_continuar;

        std::unique_ptr<const int> _puntuacion;
        std::unique_ptr<const int> _nivel;

        std::string _nombre;
        
        // https://stackoverflow.com/questions/48672399/is-it-possible-to-use-sdl2-with-smart-pointers
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _Ventana;
        std::shared_ptr<SDL_Renderer> _Render;

        void _cerrar();
};

#endif
