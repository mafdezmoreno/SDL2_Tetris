#ifndef GAME_CLOSE_H
#define GAME_CLOSE_H

#include "texto.h"
#include <SDL.h>

class Game_Close{

    public:

        Game_Close(Game game);

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

};

#endif