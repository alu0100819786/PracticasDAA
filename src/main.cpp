#ifndef MAIN_
#define MAIN_

#include <sys/time.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>

void help();
bool isGreedy();
long getCurrentTime();
int askForRLCVectorSize();
int askForNumberIterations();
int askForTimesTryingImprove();
bool isZeroVector(std::vector<int> array);
std::string deleteWhiteSpacesSurround(std::string str);
void Greedy(int customers, int vehicles, std::vector<std::vector<int> > matriz);
void Grasp (int customers, int vehicles, std::vector<std::vector<int> > matriz);
void generateRLC(std::vector<int>& RLCR, std::vector<int>& RLCV, std::vector<int> fila, int size_RLC);

int main(int argc, char *argv[]) {
  int n_customers = 0;
  int n_vehicles = 0;
  std::vector<std::vector<int> > matrix = std::vector<std::vector<int> >();

	if (argc != 2) {
		std::cerr << "Numero incorrecto de argumentos." << std::endl;
		help();
		return 1;
	}

	std::string fileName = argv[1];
  std::ifstream input(fileName.c_str());
  if (input.is_open()) {
    int lineCounter = 1;
    std::string line;
    while (std::getline(input, line)) {
      int found;
      if ((found = line.find("n_clientes:")) != std::string::npos) {
        line = line.substr(found + 11);
        line = deleteWhiteSpacesSurround(line);
        if (line.find_first_not_of("0123456789") != std::string::npos) {
          std::cerr << "Ha introducido caracteres en vez de numeros." << std::endl;
          return 1;
        }
        n_customers = std::stoi(line);
      } else if ((found = line.find("n_vehiculos:")) != std::string::npos) {
        line = line.substr(found + 12);
        line = deleteWhiteSpacesSurround(line);
        if (line.find_first_not_of("0123456789") != std::string::npos) {
          std::cerr << "Ha introducido caracteres en vez de numeros." << std::endl;
          return 1;
        }
        n_vehicles = std::stoi(line);
      } else if (lineCounter > 3) {
        std::vector<int> row = std::vector<int>();
        line = deleteWhiteSpacesSurround(line);
        while (!line.empty()) {
          found = line.find_first_of(" \t");
          std::string aux = line.substr(0, found);

          if (aux.find_first_not_of("0123456789") != std::string::npos) {
            std::cerr << "Ha introducido caracteres en vez de numeros." << std::endl;
            return 1;
          }
          row.push_back(std::stoi(aux));

          line.erase(0, aux.size());
          line = deleteWhiteSpacesSurround(line);
        }
        matrix.push_back(row);
      }

      lineCounter++;
    }
  } else {
    std::cerr << "No se ha podido abrir el fichero de entrada " << fileName << std::endl;
    return 1;
  }

  long start, end, total;

  if (isGreedy()) {
    start = getCurrentTime();
    Greedy(n_customers, n_vehicles, matrix);
    end = getCurrentTime();
  } else {
    start = getCurrentTime();
    Grasp(n_customers, n_vehicles, matrix);
    end = getCurrentTime();
  }

  total = end - start;
};

void help() {
	std::cout << std::endl << "Se requiere de 1 parámetro:" << std::endl;
	std::cout << "\t1º- Nombre del fichero de entrada." << std::endl;
	std::cout << "./vrp <input-file-name>" << std::endl;
}

bool isGreedy() {
  std::string inputString = "";
	while (true) {
		std::cout << "¿Desea ejecutar el algoritmo greedy (si/no)?: " << std::endl << "\t>> ";
		std::cin >> inputString;
		if ((inputString == "si") || (inputString == "SI") || (inputString == "Si")) {
			return true;
		} else if ((inputString == "no") || (inputString == "NO") || (inputString == "No")) {
      return false;
    } else {
			std::cout << std::endl << "Elija una opcion correcta." << std::endl << std::endl;
			inputString = "";
		}
	}
}

long getCurrentTime() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int askForRLCVectorSize() {
  std::string inputString = "";
	while (true) {
		std::cout << "Introduzca el tamaño deseado para la RLC: " << std::endl << "\t>> ";
		std::cin >> inputString;
		if (inputString.find_first_not_of("0123456789") == std::string::npos) {
			return stoi(inputString);
		} else {
			std::cout << std::endl << "Elija un numero entero." << std::endl << std::endl;
			inputString = "";
		}
	}
}

int askForNumberIterations() {
	std::string inputString = "";
	while (true) {
		std::cout << "Introduzca el número de iteraciones que quiere llevar a cabo con el algoritmo Grasp: " << std::endl << "\t>> ";
		std::cin >> inputString;
		if (inputString.find_first_not_of("0123456789") == std::string::npos) {
			return stoi(inputString);
		} else {
			std::cout << std::endl << "Elija un numero entero." << std::endl << std::endl;
			inputString = "";
		}
	}
}

int askForTimesTryingImprove() {
  std::string inputString = "";
	while (true) {
		std::cout << "Introduzca el número de iteraciones antes de parar la ejecución, sin que se encuentre una solución mejor que la guardada: " << std::endl << "\t>> ";
		std::cin >> inputString;
		if (inputString.find_first_not_of("0123456789") == std::string::npos) {
			return stoi(inputString);
		} else {
			std::cout << std::endl << "Elija un numero entero." << std::endl << std::endl;
			inputString = "";
		}
	}
}

bool isZeroVector(std::vector<int> array) {
  for (int i = 1; i < array.size(); i++) {
    if (array[i] != 0) {
      return false;
    }
  }
  return true;
}

std::string deleteWhiteSpacesSurround(std::string str) {
  while (!str.empty()) {
    if ((str[0] == ' ') || (str[0] == '\t') || ((int)str[0] == 13)) {
      str.erase(str.begin());
    } else if ((str[str.size() - 1] == ' ')  || (str[str.size() - 1] == '\t') || ((int)str[str.size() - 1] == 13)) {
      str.erase(str.size() - 1);
    } else {
      break;
    }
  }
  return str;
}

void Greedy(int customers, int vehicles ,std::vector<std::vector<int> > matriz) {
  int size_route = 0;
  if ((customers % vehicles) == 0) {
    size_route = customers / vehicles;
  } else {
    size_route = customers / vehicles + 1;
  }

  /*for (int i = 0; i < matriz.size(); i++) {
    for (int j = 0; j < matriz.size(); j++) {
      std::cout << matriz[i][j] << " ";
    }
    std::cout << std::endl;
  }*/

  int contruta = 0;
  int contador = 0;//Quizas se puede quitar y reemplazar por el tamaño del vector ruta parcial
  int distanciaTotal = 0;
  std::vector<int> rutaParcial;
  std::vector<int> valorParcial;
  std::vector<int> rutafinal(1,0);
  for (int i = 0; i < matriz.size(); i++) {
    int elemento = 0;
    int minimo = 999999;
    for (int j = 1; j < matriz.size(); j++) {
      if (isZeroVector(matriz[i]) == true) {
        elemento = 0;
        minimo = matriz[i][elemento];
        contador = size_route - 1;
      } else if (minimo > matriz[i][j] && matriz[i][j] != 0) {
        elemento = j;
        minimo = matriz[i][j];
      }
    }

    //std::cout << "El menor elemento en la fila: " << i << ", es el: " << elemento << ", con valor: " << matriz[i][elemento] << std::endl;
    valorParcial.push_back(matriz[i][elemento]);
    rutaParcial.push_back(elemento);
    for (int j = 0; j < matriz.size(); j++) {
      matriz[j][elemento] = 0;
    }

    
    i = elemento - 1;
    contador++;//

    //std::cout << std::endl;
    /*for (int j = 0; j < matriz.size(); j++) {
      for (int k = 0; k < matriz.size(); k++) {
        std::cout << matriz[j][k] << " ";
      }
      std::cout << std::endl;
    }*/

    if (contador == size_route) {//
      i = -1;
      rutaParcial.push_back(0);
      valorParcial.push_back(matriz[elemento][0]);

      int distancia = 0;
      std::cout << "La mejor ruta es: " << std::endl;
      for (int j = 0; j < size_route + 1; j++) {
        std::cout << rutaParcial[j] << " --> " << valorParcial[j] << std::endl;
        rutafinal.push_back(rutaParcial[j]);
        distancia += valorParcial[j];
      }
      std::cout << std::endl << "Distancia ruta: " << distancia << std::endl;

      contruta++;
      rutaParcial.clear();
      valorParcial.clear();
      distanciaTotal += distancia;

      contador = 0;//

      if (contruta == vehicles) {
        std::cout << std::endl << "Distancia total: " << distanciaTotal << std::endl << " --------------" << std::endl << "Ruta: ";
        for (int j = 0; j < rutafinal.size(); j++){
          std::cout << rutafinal[j] << " ";
        }
        std::cout << std::endl;
        exit(0);
      }
    }
  }
}

void Grasp(int customers, int vehicles ,std::vector<std::vector<int> > matriz){
  srand(time(NULL));
  int size_route = 0;
  if ((customers % vehicles) == 0){
    size_route = customers / vehicles;
  } else {
    size_route = customers / vehicles + 1;
  }

  int iterations = askForNumberIterations();
  int RLCSize = askForRLCVectorSize();
  int noImprove = askForTimesTryingImprove();
  
  std::vector<int> valorParcial;
  std::vector<int> rutaSolucion;
  std::vector<int> rutaParcial;
  int mejorDistancia = 9999999;
  int contadorIteraciones = 0;
  int contadorNoImprove = 0;
  int distanciaTotal = 0;
  int contruta = 0;
  int contador = 0;//Quizas se puede quitar y reemplazar por el tamaño del vector ruta parcial
  while ((contadorIteraciones < iterations) && (contadorNoImprove != noImprove)) {
    std::vector<std::vector<int> > matrix = matriz;
    std::vector<int> rutafinal(1,0);
    for (int i = 0; i < matrix.size(); i++) {
      std::vector<int> RLCValor;
      std::vector<int> RLCRuta;
      int minimo = 999999;
      int elemento = 0;
      int ind = 0;
      for (int j = 1; j < matrix.size(); j++) {
        if (isZeroVector(matrix[i]) == true) {
          elemento = 0;
          minimo = matrix[i][elemento];
          contador = size_route - 1;
        } else {
          generateRLC(RLCRuta, RLCValor, matrix[i], RLCSize);
          elemento = RLCRuta[ind];
          minimo = RLCValor[ind];
          ind = rand() % RLCRuta.size();
        }
      }
      
      //std::cout << "el menor elemento en la fila: " << i << ", es el: " << elemento << ", con valor: " << matrix[i][elemento] << std::endl;
      valorParcial.push_back(matrix[i][elemento]);
      rutaParcial.push_back(elemento);
      for (int j = 0; j <matrix.size(); j++){
        matrix[j][elemento] = 0;
      }
      
      
      i = elemento -1;
      contador++;//
      
      //std::cout << std::endl;
      if (contador == size_route) {//
        i = -1;
        rutaParcial.push_back(0);
        valorParcial.push_back(matrix[elemento][0]);

        int distancia = 0;
        //std::cout << "La mejor ruta es: " << std::endl;
        for (int j = 0; j < size_route + 1; j++) {
          //std::cout << rutaParcial[j] << " --> " << valorParcial[j] << std::endl;
          rutafinal.push_back(rutaParcial[j]);
          distancia += valorParcial[j];
        }
        //std::cout << std::endl << "Distancia ruta: " << distancia << std::endl;

        distanciaTotal += distancia;
        valorParcial.clear();
        rutaParcial.clear();
        contador = 0;//
        contruta++;

        if (contruta == vehicles) {
          /*std::cout << std::endl << "Distancia total: " << distanciaTotal << std::endl << " --------------" << std::endl;
          for (int j = 0; j < rutafinal.size(); j++) {
            std::cout << rutafinal[j] << "\t";
          }*/

          if (mejorDistancia > distanciaTotal) {
            mejorDistancia = distanciaTotal;
            rutaSolucion = rutafinal;
            contadorNoImprove = 0;
            distanciaTotal = 0;
            rutafinal.clear();
          } else {
            contadorNoImprove++;
          }

          contadorIteraciones++;
          matrix.clear();
          contruta = 0;
          break;
        }
      }
    }
  }
  std::cout << std::endl << "Mejor Distancia Final: " << mejorDistancia << std::endl << " --------------";//Lo pongo por fuera del while para que cuando acabe muertre la mejor solo 1 vez
  std::cout << std::endl << "Mejor Ruta Final: " ;
  for (int i = 0; i < rutaSolucion.size(); i++) {
    std::cout << rutaSolucion[i] << " ";
  }
  std::cout << std::endl;
}

void generateRLC(std::vector<int>& RLCR, std::vector<int>& RLCV, std::vector<int> fila, int size_RLC) {
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

  int ind = rand() % RLCR.size();//no hace nada no?

  //std::cout << "RLC: ";
  //for(int j = 0; j < RLCR.size(); j++){
    //std::cout << RLCR[j] << " ";
  //}
  //std::cout << std::endl;
  //std::cout << ind << std::endl;
  //std::cout << RLCV[ind] << std::endl;
}

#endif