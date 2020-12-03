#include "pieza.h"
#include <time.h> 
#include "constantes.h"
#include <vector>
#include <random>
#include <chrono>


void Pieza::Gira_Pieza_90(){
	
	std::vector<std::vector<bool>> pieza_plus_90; //defino el vector a devolver
	
	//inicializo el vector con la dimensión necesaria
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
    
    //std::cout<< "Actualizadas coordenadas de la pieza: "<< this <<std::endl;  
    //std::cout<< "{y_fila,  x_columna}" <<std::endl; 
    set_coordenadas.clear(); //borra contenido anterior
    Coordenada buffer;
    for (int i = 0; i< posiciones.size(); i++){
        for (int j = 0; j<posiciones[0].size(); j++){
            if(posiciones[i][j]==true){
                buffer.y_fila = i + coordenada.y_fila;
                buffer.x_columna = j + coordenada.x_columna; 
                //std::cout<< "columna: " <<buffer.x_columna  << "  fila: "<< buffer.y_fila <<std::endl;
                //std::cout<< "{" <<buffer.y_fila   << ", "<< buffer.x_columna << "}  ";
                set_coordenadas.emplace_back(buffer);
            }
            //else
                //std::cout<< "   _    ";
        }
        //std::cout<<std::endl;
    } 
   // std::cout<<std::endl;  
}

void Pieza::imprime_set_coordenadas(){
    std::cout<< "El set de coordenadas de la pieza " << this << " a imprmir es: "<<std::endl;
    //std::cout<< "{y_fila,  x_columna}" <<std::endl; 
    for ( int i = 0 ; i < set_coordenadas.size() ; i++) {
        std::cout<< "{" <<set_coordenadas[i].y_fila   << ", "<< set_coordenadas[i].x_columna << "}  ";
        //std::cout<< "columna: " << set_coordenadas[i].x_columna<<std::endl;
        //std::cout<< "   fila: " << set_coordenadas[i].y_fila<<std::endl;
    }
    std::cout <<std::endl; 
    std::cout <<std::endl;
}

void Pieza::_inicializacion_pieza(){

    generador_aleatorio_pieza();

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


    //Mejora la aleatoriedad
    std::mt19937 gen1(seed); // seed the generator
    std::uniform_int_distribution<> distr1(2, COLUMNAS-2-posiciones[0].size()); // define the range
    coordenada.x_columna = distr1(gen1);

    std::mt19937 gen2(seed); // seed the generator
    std::uniform_int_distribution<> distr2(3, 15); //evito los tres primeros colores (0,1,2)
    cod_color = distr2(gen2);

    pieza_a_coordenadas();
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
    //Para evitar que las primera y la segunda pieza sean iguales
    std::uniform_int_distribution<> distr(0, 6); // define the range
    //srand (time(NULL)); //semilla para generación aleatoria
    posiciones = tipos_piezas[distr(gen)]; //copia una pieza aleatoria de las posibles
}

//obtener colores de la pieza
int Pieza::get_r(){return colores[cod_color][0];}
int Pieza::get_g(){return colores[cod_color][1];}
int Pieza::get_b(){return colores[cod_color][2];}
