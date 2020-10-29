#include "tablero.h"
#include "constantes.h"


Tablero::Tablero(){ //! Default Constructor
	
    _init_tablero();
}

Tablero::Tablero(std::shared_ptr<Interrupt_Param> param){ //! Constructor
	
    _init_tablero();
    _incrementar_puntuacion = param;
}

Tablero::~Tablero(){ //! Destructor

    std::cout << "Tablero "<< this << " Destruido" <<std::endl;
}


Tablero::Tablero(Tablero& original)  //! Copy constructor
{
    //Deep copy
    copiar_tableros(_tablero, original._tablero);
}


Tablero::Tablero(Tablero&& original) noexcept //! Move constructor
{
    _tablero = original._tablero;
    //https://stackoverflow.com/questions/13679635/how-to-properly-destroy-c-vector-of-vectors-and-release-memory
    std::vector<std::vector<bool>> empty_vector;
    original._tablero.swap(empty_vector); //swap whit empty vector to clear
    original._tablero.clear();
}

Tablero& Tablero::operator=(Tablero& original){ //! Copy Assignment operator

    if (this == &original) return *this; //protección autocopia

    //Deep copy
    copiar_tableros(_tablero, original._tablero);
  
    return *this;
}

Tablero& Tablero::operator=(Tablero&& original) noexcept{ //! Move Assignmet operator

 
    if (this == &original) return *this; //protección automovimiento

    std::vector<std::vector<bool>> empty_vector;
    _tablero.swap(empty_vector); //swap whit empty vector to clear
    _tablero.clear();
            
    _tablero = original._tablero;

    original._tablero.swap(empty_vector); //swap whit empty vector to clear
    original._tablero.clear();

    return *this;
}


void Tablero::copiar_tableros(std::vector<std::vector<bool>> &dinamico, std::vector<std::vector<bool>> &estatico){
    
    bool fila_contenido = true;
    for (int fila = 1 ; fila < (FILAS+1) ; fila++){
        for( int columna = 1 ; columna < (COLUMNAS+1) ; columna++){
            dinamico[fila][columna] = estatico[fila][columna];
            if(estatico[fila][columna]==1){
                fila_contenido = true;
            }
            else
            {
                fila_contenido = false;
            }
        }
        if(fila_contenido)
            break; //Termina el bucle si ya no tiene más contenido la tabla
    }
}

bool Tablero::Comprueba_bajada(Pieza &pieza){
    
    Pieza buffer = pieza; //el compilador se encarga de hacer la copia (más adelante implementar move semantics)
    buffer.coordenada.y_fila = buffer.coordenada.y_fila + 1; //bajo la pieza copiada
    buffer.pieza_a_coordenadas(); //actualizo el set de coordenadas de la pieza
    if(comprueba_cabe_pieza(buffer) == true){//compruebo si cabe la pieza
        //std::cout<<"La pieza " << &pieza << " puede bajar "<<std::endl;
        //SDL_SemPost( gDataLock );
        return true;
    }
    std::cout<<"La pieza " << &pieza <<" no puede bajar "<<std::endl;
    return false;

}

bool Tablero::Comprueba_derecha(Pieza &pieza){
    
    Pieza buffer = pieza;
    buffer.coordenada.x_columna = buffer.coordenada.x_columna + 1; //bajo la pieza copiada
    buffer.pieza_a_coordenadas(); //actualizo el set de coordenadas de la pieza
    if(comprueba_cabe_pieza(buffer) == true){//compruebo si cabe la pieza
        std::cout<<"La pieza " << &pieza << " puede ir a la derecha"<<std::endl;
        return true;
    }
    std::cout<<"La pieza " << &pieza <<" no puede ir a la derecha"<<std::endl;
    return false;
}

bool Tablero::Comprueba_izquierda(Pieza &pieza){
    
    Pieza buffer = pieza; //crea una nueva pieza
    buffer.coordenada.x_columna = buffer.coordenada.x_columna - 1; //bajo la pieza copiada
    buffer.pieza_a_coordenadas(); //actualizo el set de coordenadas de la pieza
    if(comprueba_cabe_pieza(buffer) == true){//compruebo si cabe la pieza
        //std::cout<<"La pieza " << &pieza << " puede ir a la derecha"<<std::endl;
        return true;
    }
    std::cout<<"La pieza " << &pieza <<" no puede ir a la izquierda"<<std::endl;
    return false;
}

bool Tablero::Comprueba_giro(Pieza &pieza){
    
    Pieza buffer = pieza; //crea una nueva pieza
    buffer.Gira_Pieza_90();
    buffer.pieza_a_coordenadas(); //actualizo el set de coordenadas de la pieza
    if(comprueba_cabe_pieza(buffer) == true){//compruebo si cabe la pieza
       
        return true;
    }
    std::cout<<"La pieza " << &pieza <<" no puede girar"<<std::endl;
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
    //std::cout<<"La pieza " << &pieza <<" cabe en el tablero"<<std::endl;
    return true;
}

void Tablero::imprime_tabla(){
    		
    std::cout<<"Tablero "<<this<<std::endl;
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

    _tablero[coordenada.y_fila][coordenada.x_columna] = tipo;
    return 0;
}

void Tablero::intro_coord_tabla(Pieza &pieza){
    std::cout<<"Pieza "<< &pieza <<" introducida en la tabla "<< this <<std::endl;
    for ( int i = 0 ; i < pieza.set_coordenadas.size() ; i++)     //vertical
        set_cuadro (pieza.set_coordenadas[i] , true);
}

void Tablero::borra_coord_tabla(Pieza &pieza){
    std::cout<<"Pieza "<< &pieza <<" borrada de la tabla "<< this <<std::endl;
    for ( int i = 0 ; i < pieza.set_coordenadas.size() ; i++)     //vertical
        set_cuadro (pieza.set_coordenadas[i] , false);
}


bool Tablero::comprobar_fila_llena(int fila){

    for(int i = 1; i<(_tablero[fila].size()-1); i++){
        if(_tablero[fila][i]==false)
            return false;
    }
std::cout<<"fila "<< fila << " llena"<<std::endl;
return true;
}

bool Tablero::comprobar_fila_vacia(int fila){
    
    for(int i = 1; i<(_tablero[fila].size()-1); i++){
        if(_tablero[fila][i]==true){
            std::cout<<"fila "<< fila << " con contenido"<<std::endl;
            return false;
        }
    }
    std::cout<<"fila "<< fila << " vacia"<<std::endl;
    return true;
}

std::vector<int> Tablero::comprobar_filas_tabla(){

    std::cout<<"comprobacion de las filas de la tabla"<<std::endl;
    std::vector<int> filas_llenas;
    for(int i = (_tablero.size()-2); i>1; i--){
        if(comprobar_fila_llena(i)){
            filas_llenas.push_back(i);
        }
        else if(comprobar_fila_vacia(i))
            break;
    }
    return filas_llenas; //vector con las filas ocupadas
}

void Tablero::copiado_filas(int fila){
    for(int i = 1; i<(_tablero[0].size()-1); i++){
        _tablero[fila][i]=_tablero[fila-1][i];
        std::cout<<  _tablero[fila][i] << " " << _tablero[fila-1][i] <<std::endl;
    }
}

void Tablero::compactar_filas_tabla(int fila){

    //bool fila_vacia = false;
    std::cout<<"Compactado de fila "<< fila <<std::endl;
    int i;
    for(i=fila; i > 1; i--){
        std::cout<< i <<std::endl;
        copiado_filas(i);
        if(comprobar_fila_vacia(i)){
            //std::cout<<"Fila vacia"<< std::endl;
            //fila_vacia = true;
            break;
        }
    }
    if(i==1){ //elimina la fila superior si tiene algún contenido tras el compactado
        int j = i;
        for(int i = 1; i<(_tablero[0].size()-1); i++)
            _tablero[j][i]=0;
    }
    std::cout<<std::endl;
    imprime_tabla();
}

void Tablero::eliminar_filas_llenas(){

    imprime_tabla();
    std::vector<int> filas_llenas = comprobar_filas_tabla();
    if(filas_llenas.size()>0){
        std::cout<<"Eliminado de filas llenas: " <<std::endl;
        int contador_filas_eliminadas = 0;
        for(int i = 0 ; i<filas_llenas.size(); i++){
            compactar_filas_tabla(filas_llenas[i]+contador_filas_eliminadas);
            contador_filas_eliminadas++;
        }
        
        _incrementar_puntuacion->puntuacion = _incrementar_puntuacion->puntuacion + contador_filas_eliminadas;

        std::cout<<"Puntuacion: "<< _incrementar_puntuacion->puntuacion <<std::endl;
        if(((int)(_incrementar_puntuacion->puntuacion/10))>(_incrementar_puntuacion->nivel)){
            _incrementar_puntuacion->nivel = _incrementar_puntuacion->nivel + 1;
            std::cout<<"Has subido al nivel: "<< _incrementar_puntuacion->nivel <<std::endl;
            
        }
    }
    else
    {
        std::cout<<"Ninguna fila completa: " <<std::endl;
    }
    
}

void Tablero::_init_tablero(){

    _tablero.resize(FILAS+2);
	for (int fila = 0 ; fila < (FILAS+2) ; fila++){
				_tablero[fila].resize(COLUMNAS+2);
				for( int columna = 0 ; columna < (COLUMNAS+2) ; columna++){
					if(fila == 0 || fila == FILAS +1 || columna == 0 || columna == COLUMNAS+1)
						_tablero[fila][columna] = true;
					else
						_tablero[fila][columna] = false;
				}
	}
}

bool Tablero::get_position(int fila, int columna){

    return _tablero[fila][columna];
}