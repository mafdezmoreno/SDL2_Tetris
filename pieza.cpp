#include "pieza.h"
#include <time.h>       /* time */
#include "main.h"

std::vector<std::vector<bool>> Pieza::Gira_Pieza_90(std::vector<std::vector<bool>> pieza){
	
	std::vector<std::vector<bool>> pieza_plus_90; //defino el vector a devolver
	
	//inicializo el vector con la dimensión necesaria
    pieza_plus_90.resize(pieza[0].size());        
    for (int8_t i = 0; i< pieza_plus_90.size(); i++)
    pieza_plus_90[i].resize(pieza.size());
 	
    // Copio el vector trasponiendo los datos
    for(int i = 0; i < pieza[0].size() ; i++){	   
        int x = pieza.size()-1;
        for(int j = 0; j<  pieza.size(); j++){
            pieza_plus_90[i][x] = pieza[j][i];
            x--;
        }
    }
	
    return pieza_plus_90;
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
    srand (time(NULL)); //semilla para generación aleatoria
    coordenada.x_columna = (rand() % (COLUMNAS-1-posiciones[0].size()))+1; // posiciona aleatoriamente la pieza en la primera fila
    pieza_a_coordenadas();

    cod_color = rand() % 13;

    std::cout<<"Pieza " << this << " inicializada"<<std::endl;
    std::cout <<std::endl;
}

void Pieza::generador_aleatorio_pieza(){

    srand (time(NULL)); //semilla para generación aleatoria
    posiciones = tipos_piezas[rand() % 6]; //copia una pieza aleatoria de las posibles
}