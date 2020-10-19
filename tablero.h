#ifndef TABLERO_H
#define TABLERO_H

#include "pieza.h"
#include <SDL_thread.h>

//Initialize semaphore

class Tablero{
	public:

		Tablero();  //Inicializa la tabla
        ~Tablero(); //Destruye la tabla

        //Funciones de modificacion
        int set_cuadro (Coordenada &coordenada, bool tipo); //cambia el valor de la casilla
        void intro_coord_tabla(Pieza &pieza); //ocupa el espacio de la tabla con las coordenadas de la pieza
        void borra_coord_tabla(Pieza &pieza); //libera el hueco tras el movimiento de la pieza

        void imprime_tabla();   //imprime la tabla completa, con un "1" en casilla ocupada

        //Comprobaciones de cabida/movimiento
        bool comprueba_cabe_pieza(Pieza &pieza);  //actualiza posición de pieza y comprueba si cabe en nueva posición
        bool Comprueba_bajada(Pieza &pieza);
        bool Comprueba_derecha(Pieza &pieza);
        bool Comprueba_izquierda(Pieza &pieza);
        bool Comprueba_giro(Pieza &pieza);

        //Compactado tabla
        void eliminar_filas_llenas(); //función a llamar en el código
        //La anterior función usa estas funciones:
            bool comprobar_fila_llena(int fila);
            bool comprobar_fila_vacia(int fila);
            std::vector<int> comprobar_filas_tabla();
            void compactar_filas_tabla(int fila);
            void copiado_filas(int fila);
        
        //Variables
        //! TO DO: INCLUIR CÓDIGO COLOR A CADA POSICIÓN
		std::vector<std::vector<bool>> _tablero; //Posiciones ocupadas del tablero
        
        SDL_sem* gDataLock = NULL;
};

#endif