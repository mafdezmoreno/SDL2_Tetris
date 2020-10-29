#ifndef TABLERO_H
#define TABLERO_H

#include "pieza.h"
#include <vector>
#include "game.h"
#include <memory>

class Interrupt_Param;

class Tablero{
	public:

        //Funciones de modificacion
        void intro_coord_tabla(Pieza &pieza); //ocupa el espacio de la tabla con las coordenadas de la pieza
        void borra_coord_tabla(Pieza &pieza); //libera el hueco tras el movimiento de la pieza. Solo necesario para una correcta visualización del tablero logico
        void imprime_tabla();   //imprime _tablero (lógico), con un "1" en casilla ocupada
        void copiar_tableros(std::vector<std::vector<bool>> &dinamico, std::vector<std::vector<bool>> &estatico);

        //Comprobaciones de cabida/movimiento
        bool comprueba_cabe_pieza(Pieza &pieza);  //actualiza posición de pieza y comprueba si cabe en nueva posición
        bool Comprueba_bajada(Pieza &pieza);
        bool Comprueba_derecha(Pieza &pieza);
        bool Comprueba_izquierda(Pieza &pieza);
        bool Comprueba_giro(Pieza &pieza);

        //Compactado tabla
        void eliminar_filas_llenas();

        //get value position
        bool get_position(int fila, int columna);

        //! Default constructor
        Tablero();
        //! Constructor
        Tablero(std::shared_ptr<Interrupt_Param> param);
        //! Destructor
        ~Tablero();
        //! Copy constructor
        Tablero(Tablero& original);
        //! Move constructor
        Tablero(Tablero&& original) noexcept;
        //! Copy Assignment operator
        Tablero& operator=(Tablero& original);
        //! Move Assignmet operator
        Tablero& operator=(Tablero&& original) noexcept;


    private:

        //Funciones que usa eliminar_filas_llenas();
        bool comprobar_fila_llena(int fila);
        bool comprobar_fila_vacia(int fila);
        std::vector<int> comprobar_filas_tabla();
        void compactar_filas_tabla(int fila);
        void copiado_filas(int fila);

        //Cambia el valor de una casilla de _tablero
        int set_cuadro (Coordenada &coordenada, bool tipo);
        void _init_tablero();

        //variables
        std::shared_ptr<Interrupt_Param> _incrementar_puntuacion;
        std::vector<std::vector<bool>> _tablero; //Posiciones ocupadas del tablero
};

#endif