
# SDL2_Tetris

Juego de tetris creado empleando SDL2

## Rubric Points

### TO DO

- [] Imprimir puntuación en la ventana al lado del tablero.
- [] Imprimir el nivel del juego al lado del tablero
- [] Generar la pieza siguiente, y renderizarla al lado del tablero
- [] Implementar incremento automático de la velocidad
- [] Color en las piezas del tablero estático
- [] Crear una clase para guardar el color de las casillas del tablero
- [] Implementar refresco de la pantalla y eliminar los sleep introducidos
- [] Leer de un archivo de texto y escribir en el mismo (los nombres y puntuaciones de jugadores)
- [] Pedir en nombre de usuario y renderizarlo en el borde, bajo la generación de las piezas

### Object Oriented Programming

- [] Clasificar los miembro de las clases como: public, protected, or private, según interese
- [] Revisar los constructores de funciones
- [] incluir las funciones de main sin clase en una clase GAME
- [] hacer algún overload de alguna función (quizás los mas fácil sea hacerlo de un constructor)
- [] Derived class functions override virtual base class functions: One member function in an inherited class overrides a virtual base class member function.
- [] One function is declared with a template that allows it to accept a generic parameter.

### Memory Management

- [] The project makes use of references in function declarations: At least two variables are defined as references, or two functions use pass-by-reference in the project code.
- [] The project uses destructors appropriately: At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor.
- [] The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate: The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.
- [] The project follows the Rule of 5: For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.
- [] The project uses move semantics to move data, instead of copying it, where possible: For classes with move constructors, the project returns objects of that class by value, and relies on the move constructor, instead of copying the object.
- [] The project uses smart pointers instead of raw pointers: The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers.

### Concurrency

- [] The project uses multithreading. The project uses multiple threads in the execution.
- [] A promise and future is used in the project. A promise and future is used to pass data from a worker thread to a parent thread in the project code
- [] A mutex or lock is used in the project. A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code.
- [] A condition variable is used in the project. A std::condition_variable is used in the project code to synchronize thread execution.
