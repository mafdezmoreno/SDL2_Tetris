#ifndef TABLERO_H
#define TABLERO_H

#include "pieza.h"
#include <vector>
#include "game.h"
#include <memory>

class Interrupt_Param;

class Tablero{
	public:

        // Board Modification Functions
        void intro_coord_tabla(Pieza &pieza); // Fill the space of the part on the board
        void borra_coord_tabla(Pieza &pieza); // Releases the space of the part on the board.
        void imprime_tabla();   // Print the logic board. For debugging purposes
        void copiar_tableros(std::vector<std::vector<bool>> &dinamico, std::vector<std::vector<bool>> &estatico);

        // Checking parts fitting/motion
        bool comprueba_cabe_pieza(Pieza &pieza);    // Check if the part fits in a new position
        bool Comprueba_bajada(Pieza &pieza);        // Check the descent of the piece
        bool Comprueba_derecha(Pieza &pieza);       // Check the movement to the right
        bool Comprueba_izquierda(Pieza &pieza);     // Check the movement to the left
        bool Comprueba_giro(Pieza &pieza);          // Check the possibility of rotation

        // To remove the filled rows of the board
        void eliminar_filas_llenas();

        // To obtain the cell value in a particular position
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

        // Funtions called by eliminar_filas_llenas();
        bool comprobar_fila_llena(int fila);
        bool comprobar_fila_vacia(int fila);
        std::vector<int> comprobar_filas_tabla(); // Returns a vector that contains the filled rows
        void compactar_filas_tabla(int fila);
        void copiado_filas(int fila);

        // To change the value of the cells of the boards
        int set_cuadro (Coordenada &coordenada, bool tipo);
        
        // Set the boolean board to 0 and the borders to 1
        void _init_tablero();

        // Variables
        std::shared_ptr<Interrupt_Param> _incrementar_puntuacion;
        std::vector<std::vector<bool>> _tablero; // Store the filled cells of the board
};

#endif