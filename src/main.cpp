#ifndef MAIN_
#define MAIN_

#include <sys/time.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>

void help();
long getCurrentTime();
std::string deleteWhiteSpacesSurround(std::string str);

void Greedy(int customers, int vehicles ,std::vector<std::vector<int>> matriz);
void Grasp(int customers, int vehicles ,std::vector<std::vector<int>> matriz);
bool isZeroVector(std::vector<int> array);

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

  /*for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }*/

Greedy(n_customers, n_vehicles, matrix);
};

void help() {
	std::cout << std::endl << "Se requiere de 1 parámetro:" << std::endl;
	std::cout << "\t1º- Nombre del fichero de entrada." << std::endl;
	std::cout << "./vrp <input-file-name>" << std::endl;
}

long getCurrentTime() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000000) + tv.tv_usec;
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


void Greedy(int customers, int vehicles ,std::vector<std::vector<int>> matriz){
  int minimo = 999999;
  int elemento = 0;
  int contador = 0;
  int contruta = 0;
  int size_route = 0;
  std::vector<int> rutaParcial;
  std::vector<int> valorParcial;
  std::vector<int> rutafinal;
  rutafinal.push_back(0);
  int distancia = 0;
  int distanciaTotal = 0;

  if (customers % vehicles == 0){
      size_route = customers/vehicles;
  }
  else{
      size_route = customers / vehicles + 1;
  }

  for(int i = 0; i < matriz.size(); i++){
        for (int j = 0; j < matriz.size(); j++){

            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }

for(int i = 0; i < matriz.size(); i++){
        for (int j = 1; j < matriz.size(); j++){
          if(isZeroVector(matriz[i]) == true){
            elemento = 0;
            minimo = matriz[i][elemento];
            contador = size_route -1;
          }else{
            if(minimo > matriz[i][j] && matriz[i][j] != 0){
                minimo = matriz[i][j];
                elemento = j;
            }
          }
        }
        minimo = 999999;

        std::cout << "el menor elemento en la fila: " << i << ", es el: " << elemento << ", con valor: " << matriz[i][elemento] << std::endl;
        rutaParcial.push_back(elemento);
        valorParcial.push_back(matriz[i][elemento]);
        i = elemento -1;
        for (int k = 0; k <matriz.size(); k++){
            matriz[k][elemento] = 0;
        }
        contador++;
        std::cout << std::endl;

        for(int i = 0; i < matriz.size(); i++){
          for (int j = 0; j < matriz.size(); j++){

            std::cout << matriz[i][j] << " ";
          }
        std::cout << std::endl;
        }
        if(contador == size_route){
            i = -1;
            rutaParcial.push_back(0);
            valorParcial.push_back(matriz[elemento][0]);
            std::cout << "La mejor ruta es: " << std::endl;
            for(int n = 0; n < size_route + 1; n++){

                std::cout << rutaParcial[n] << " --> ";
                std::cout << valorParcial[n] << std::endl;
                rutafinal.push_back(rutaParcial[n]);
                distancia += valorParcial[n];
            }
            std::cout << std::endl;
            std::cout << "Distancia ruta: " << distancia << std::endl;
            rutaParcial.clear();
            valorParcial.clear();
            distanciaTotal += distancia;
            distancia = 0;
            contador = 0;
            
            contruta++;
            if (contruta == vehicles){
            std::cout << std::endl;
            std::cout << "Distancia total: " << distanciaTotal << std::endl;
            std::cout << " --------------" << std::endl;
            for(int z = 0; z < rutafinal.size(); z++){
                std::cout << rutafinal[z] << "\t";
            }
                std::cout << std::endl;
                exit(0);
            }
            
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


void Grasp(int customers, int vehicles ,std::vector<std::vector<int>> matriz){

int RLCSize, iterations, noImprove, aux;

std::cout << "Introduzca el número de iteraciones que quiere llevar a cabo con el algoritmo Grasp: " << std::endl;
std::cin >> aux;
iterations = aux;
std::cout << iterations;
std::cout << "Introduzca el tamaño deseado para la RLC: " << std::endl;
std::cin >> aux;
RLCSize = aux;
std::cout << RLCSize;
std::cout << "Introduzca el número de iteraciones antes de parar la ejecución, sin que se encuentre una solución mejor que la guardada" << std::endl;
std::cin >> aux;
noImprove = aux;
std::cout << noImprove;


}


#endif