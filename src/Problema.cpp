#include "../includes/Problema.h"

Problema::Problema(){

}
Problema::~Problema(){
    
}

/**
Función booleana que nos devolverá verdadero si el array que recibe tiene todos sus valores a cero y falso en caso contrario. con esto sabremos que tenemos visitados
a todos los clientes y debemos volver al depósito. 
*/
bool Problema::isZero(std::vector<int> array){

    for (int i = 1; i < array.size(); i++) {
    if (array[i] != 0) {
      return false;
    }
  }
  return true;
}

/**
Función que recibe una de las filas de la matriz, las RLC tanto de ruta como de valor y el tamaño de la RLC y genera la RLC correspondiente dependiendo de la fila y del tamaño
escogiendo los valores mas pequeños que representarán las menores distancias hasta el siguietne vecino.
*/
void Problema::generateRLC(std::vector<int>& RLCR, std::vector<int>& RLCV, std::vector<int> fila, int size_RLC){
    int elemento;
  std::vector<int> matrix = fila;
  for (int i = 0; i < size_RLC; i++) {
    int minimo = 999999;
    for (int j = 1; j < matrix.size(); j++) {
      if ((minimo > matrix[j]) && (matrix[j] != 0)) {
        elemento = j;
        minimo = matrix[j];
      }
    }

    matrix[elemento] = 0;
    if (RLCR.size() < size_RLC) {
      RLCR.push_back(elemento);
      RLCV.push_back(minimo);
    }
  }
}

bool Problema::isEmpty(std::vector<std::vector<int> > matrix){
    for (int i = 0; i < matrix.size(); i++) {
    for(int j = 1; j < matrix.size(); j++){
    if (matrix[i][j] != 0) {
      return false;
    }
  }
  }
  return true;
}

/**
Función donde conseguiremos el número de iteraciones que llevará a cabo nuestro algoritmo Grasp antes de terminar su ejecución. Este número será una de nuestras condiciones
de parada en el bucle while perteneciente al algoritmo Grasp.
*/
int Problema::getNumberIterations(){
    	std::string input = "";
	while (true) {
		std::cout << "Introduzca el número de iteraciones que llevará a cabo el algoritmo Grasp: " << std::endl << "\t>> ";
		std::cin >> input;
		if (input.find_first_not_of("0123456789") == std::string::npos) {
			return stoi(input);
		} else {
			std::cout << std::endl << "Introduzca un numero entero." << std::endl << std::endl;
			input = "";
		}
	}
}

/**
Función para conseguir el tamaño deseado para la RLC a la hora de ejecutar nuestro algoritmo Grasp. Pedimos al usuario que introduzca un número entero que será
el tamaño del vector que contendrá nuestra RLC.
*/
int Problema::getRLCVectorSize(){
      std::string input = "";
	while (true) {
		std::cout << "Introduzca el tamaño deseado para la RLC: " << std::endl << "\t>> ";
		std::cin >> input;
		if (input.find_first_not_of("0123456789") == std::string::npos) {
			return stoi(input);
		} else {
			std::cout << std::endl << "Introduzca un numero entero." << std::endl << std::endl;
			input = "";
		}
	}
}

/**
Función para conseguir la segunda condición de parada de nuestro bucle While para la ejecución del algoritmo Grasp. En este caso necesitaremos conseguir por parte del usuario
un número entero que ejemplifique el número de iteraciones seguidas sin que se mejore la solución obtenida previamente antes de parar la ejecución.
*/
int Problema::getTimesWithoutImprove(){
    std::string input = "";
	while (true) {
		std::cout << "Introduzca el número de iteraciones antes de parar la ejecución, sin una mejora en la solución: " << std::endl << "\t>> ";
		std::cin >> input;
		if (input.find_first_not_of("0123456789") == std::string::npos) {
			return stoi(input);
		} else {
			std::cout << std::endl << "Introduzca un numero entero." << std::endl << std::endl;
			input = "";
		}
	}
}

/**
Función para conseguir el tiempo actual, que usaremos en los algoritmos, para conseguir el tiempo de ejecución para ambos.
*/
long Problema::getCurrentTime(){
      struct timeval tv;
  gettimeofday(&tv, NULL);
  return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
