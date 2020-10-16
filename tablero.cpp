#include "tablero.h"
#include "apilado.h"

Tablero::Tablero(){ //Inicializa la tabla
			_tablero.resize(FILAS+2);
			for (int fila = 0 ; fila < (FILAS+2) ; fila++){
				_tablero[fila].resize(COLUMNAS+2);
				for( int columna = 0 ; columna < (COLUMNAS+2) ; columna++){
					if(fila == 0 || fila == FILAS +1 || columna == 0 || columna == COLUMNAS+1)
						_tablero[fila][columna] = true;
					else
						_tablero[fila][columna] = false;
				}
				std::cout<< std::endl;
			}
			std::cout<< "\nTabla inicializada\n" << std::endl;
			//imprime_tabla();
}

Tablero::~Tablero(){ //Destruye la tabla

			std::cout<< "Tabla "<< this << " destruida" << std::endl;
			//imprime_tabla();
}


bool Tablero::Comprueba_bajada(Pieza &pieza){
    
    Pieza buffer = pieza; //el compilador se encarga de hacer la copia (más adelante implementar move semantics)
    buffer.coordenada.y_fila = buffer.coordenada.y_fila + 1; //bajo la pieza copiada
    buffer.pieza_a_coordenadas(); //actualizo el set de coordenadas de la pieza
    if(comprueba_cabe_pieza(buffer) == true){//compruebo si cabe la pieza
        std::cout<<"La pieza " << &buffer << " puede bajar "<<std::endl;
        return true;
    }
    std::cout<<"La pieza " << &buffer <<" no puede bajar "<<std::endl;
    return false;
}

bool Tablero::Comprueba_derecha(Pieza &pieza){
    
    Pieza buffer = pieza;
    buffer.coordenada.x_columna = buffer.coordenada.x_columna + 1; //bajo la pieza copiada
    buffer.pieza_a_coordenadas(); //actualizo el set de coordenadas de la pieza
    if(comprueba_cabe_pieza(buffer) == true){//compruebo si cabe la pieza
        std::cout<<"La pieza " << &buffer << " puede ir a la derecha"<<std::endl;
        return true;
    }
    std::cout<<"La pieza " << &buffer <<" no puede ir a la derecha"<<std::endl;
    return false;
}

bool Tablero::Comprueba_izquierda(Pieza &pieza){
    
    Pieza buffer = pieza;
    buffer.coordenada.x_columna = buffer.coordenada.x_columna - 1; //bajo la pieza copiada
    buffer.pieza_a_coordenadas(); //actualizo el set de coordenadas de la pieza
    if(comprueba_cabe_pieza(buffer) == true){//compruebo si cabe la pieza
        std::cout<<"La pieza " << &buffer << " puede ir a la derecha"<<std::endl;
        return true;
    }
    std::cout<<"La pieza " << &buffer <<" no puede ir a la izquierda"<<std::endl;
    return false;
}

bool Tablero::comprueba_cabe_pieza(Pieza &pieza){ //devuelve true si cabe y false si no cabe
    //pieza.imprime_set_coordenadas();
    for ( int i = 0 ; i < pieza.set_coordenadas.size() ; i++) {    //vertical
        if(_tablero[pieza.set_coordenadas[i].y_fila][pieza.set_coordenadas[i].x_columna]== true){ //Si está ocupado la pieza no cabe
            std::cout<<"La pieza " << &pieza <<" no cabe"<<std::endl;
            return false;
        }
    }
    std::cout<<"La pieza " << &pieza <<" cabe en el tablero"<<std::endl;
    return true;
}

void Tablero::imprime_tabla(){
    		
            std::cout<<"   ";
    		for ( int i = 0 ; i < COLUMNAS+2 ; i++){
        		if (i<10)
            		std::cout<<"  "<<i;
        		else
            		std::cout<<" "<<i; 
    		}
			std::cout<<std::endl;
			std::cout<<"   ";
			for ( int i = 0 ; i < COLUMNAS+2 ; i++)
            		std::cout<<"___";
    		std::cout<<std::endl;
   			for ( int fila = 0 ; fila < _tablero.size() ; fila++){ 
        		if (fila<10)
            		std::cout<<" "<< fila <<"|";
        	else
            	std::cout<< fila  <<"|";

        	for ( int columna = 0 ; columna < _tablero[fila].size() ; columna++){
            	//std::cout<<"  "<<_tablero[fila][columna];
                if(_tablero[fila][columna])
                    std::cout<<"  1";
                else
                    std::cout<<"   ";
            }
        	std::cout<<std::endl;
   			}
}



int Tablero::set_cuadro (Coordenada &coordenada, bool tipo){ // horizontal (fila) // vertical (columna)

    if (coordenada.x_columna>COLUMNAS){
        std::cout<<"Te sales del ancho"<<std::endl;
        return 1;
    }
    if (coordenada.y_fila>FILAS){
        std::cout<<"Te sales del alto"<<std::endl;
        return 2;
    }
    _tablero[coordenada.y_fila][coordenada.x_columna] = tipo;
    //std::cout<< "Tabla actualizada en {y_fila, x_columna}: {"<< coordenada.y_fila << ",  "<<coordenada.x_columna<<"}"<<std::endl;

    return 0;
}

void Tablero::intro_coord_tabla(Pieza &pieza){
    std::cout<<"Pieza "<< &pieza <<" introducida en la tabla"<<std::endl;
    for ( int i = 0 ; i < pieza.set_coordenadas.size() ; i++)     //vertical
        set_cuadro (pieza.set_coordenadas[i] , true);
}

void Tablero::borra_coord_tabla(Pieza &pieza){
    std::cout<<"Pieza "<< &pieza <<" borrada de la tabla "<< this <<std::endl;
    for ( int i = 0 ; i < pieza.set_coordenadas.size() ; i++)     //vertical
        set_cuadro (pieza.set_coordenadas[i] , false);
}
