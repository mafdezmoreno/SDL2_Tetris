#include "pieza.h"
#include <time.h> 
#include "constantes.h"
#include <vector>
#include <random>
#include <chrono>


void Pieza::Gira_Pieza_90(){
	
    // Initializes the new vector of the piece to be returned
	std::vector<std::vector<bool>> pieza_plus_90;
	
	// Resize the new vector of the part
    pieza_plus_90.resize(posiciones[0].size());        
    for (int8_t i = 0; i< pieza_plus_90.size(); i++)
    pieza_plus_90[i].resize(posiciones.size());
 	
    // Copio el vector trasponiendo los datos
    for(int i = 0; i < posiciones[0].size() ; i++){	   
        int x = posiciones.size()-1;
        for(int j = 0; j<  posiciones.size(); j++){
            pieza_plus_90[i][x] = posiciones[j][i];
            x--;
        }
    }
    posiciones = pieza_plus_90;
}

void Pieza::pieza_a_coordenadas(){
    
    //Update the coordinates of each of the squares that compose the part.
    set_coordenadas.clear(); // Delete the previous coordinates
    Coordenada buffer;
    for (int i = 0; i< posiciones.size(); i++){
        for (int j = 0; j<posiciones[0].size(); j++){
            if(posiciones[i][j]==true){
                buffer.y_fila = i + coordenada.y_fila;
                buffer.x_columna = j + coordenada.x_columna; 
                set_coordenadas.emplace_back(buffer);
            }
        }
    } 
}

void Pieza::imprime_set_coordenadas(){
    
    // Print the set of coordinates. Used to debug
    std::cout<< "El set de coordenadas de la pieza " << this << " a imprmir es: "<<std::endl;
    for ( int i = 0 ; i < set_coordenadas.size() ; i++) {
        std::cout<< "{" <<set_coordenadas[i].y_fila   << ", "<< set_coordenadas[i].x_columna << "}  ";
    }
    std::cout <<std::endl; 
}

void Pieza::_inicializacion_pieza(){

    generador_aleatorio_pieza(); // Random generator part

    //https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c
    std::random_device rd;
    std::mt19937::result_type seed = rd() ^ (
            (std::mt19937::result_type)
            std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()
            ).count() +
            (std::mt19937::result_type)
            std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()
            ).count() );


    // To improve randomness
    std::mt19937 gen1(seed); // seed the generator
    std::uniform_int_distribution<> distr1(2, COLUMNAS-2-posiciones[0].size()); // define the range
    coordenada.x_columna = distr1(gen1);

    std::mt19937 gen2(seed); // seed the generator
    std::uniform_int_distribution<> distr2(3, 15); // Choose the desired color range
    cod_color = distr2(gen2);

    pieza_a_coordenadas(); // Initializes the coordinates of the part
    std::cout<<"Pieza " << this << " inicializada"<<std::endl;
    std::cout <<std::endl;
}

void Pieza::generador_aleatorio_pieza(){


    //https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c
    std::random_device rd;
    std::mt19937::result_type seed = rd() ^ (
            (std::mt19937::result_type)
            std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()
            ).count() +
            (std::mt19937::result_type)
            std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()
            ).count() );

    std::mt19937 gen(seed);
    std::uniform_int_distribution<> distr(0, 6); // define the range
    posiciones = tipos_piezas[distr(gen)]; // obtains a copy of a random part from the possible
}

// To obtain the colors of the part
int Pieza::get_r(){return colores[cod_color][0];}
int Pieza::get_g(){return colores[cod_color][1];}
int Pieza::get_b(){return colores[cod_color][2];}
