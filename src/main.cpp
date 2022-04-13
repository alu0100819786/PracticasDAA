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
long getCurrentTime();
std::string deleteWhiteSpacesSurround(std::string str);

void Greedy(int customers, int vehicles ,std::vector<std::vector<int>> matriz);
void Grasp(int customers, int vehicles ,std::vector<std::vector<int>> matriz);
bool isZeroVector(std::vector<int> array);
bool isInVector(int number, std::vector<int> vector);
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

  /*for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }*/

Grasp(n_customers, n_vehicles, matrix);
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
srand(time(NULL));
std::vector<std::vector<int>> matrix;
int RLCSize, iterations, noImprove, aux;
int elemento = 0;
int minimo = 999999;
int contador = 0;
int contruta = 0;
int size_route = 0;
int ind = 0;
if (customers % vehicles == 0){
      size_route = customers/vehicles;
  }
  else{
      size_route = customers / vehicles + 1;
  }

std::cout << "Introduzca el número de iteraciones que quiere llevar a cabo con el algoritmo Grasp: " << std::endl;
std::cin >> aux;
iterations = aux;
std::cout << "Introduzca el tamaño deseado para la RLC: " << std::endl;
std::cin >> aux;
RLCSize = aux;
std::cout << "Introduzca el número de iteraciones antes de parar la ejecución, sin que se encuentre una solución mejor que la guardada" << std::endl;
std::cin >> aux;
noImprove = aux;
std::vector<int> RLCRuta;
std::vector<int> RLCValor;
std::vector<int> rutaParcial;
std::vector<int> valorParcial; //Quitarlo, meterlo directamente en distancia
std::vector<int> rutafinal;
std::vector<int> rutaSolucion;

int distancia = 0;
int distanciaTotal = 0;
int mejorDistancia = 9999999;
int contadorIteraciones = 0;
int contadorNoImprove = 0;

while((contadorIteraciones < iterations) && (contadorNoImprove != noImprove)){
matrix = matriz;
rutafinal.push_back(0);
for(int i = 0; i < matrix.size(); i++){
        for (int j = 1; j < matrix.size(); j++){
          if(isZeroVector(matrix[i]) == true){
              elemento = 0;
              minimo = matrix[i][elemento];
              contador = size_route -1;
          }else{
            generateRLC(RLCRuta,RLCValor,matrix[i],RLCSize);
            ind = rand()%RLCRuta.size();
            elemento = RLCRuta[ind];//pillamos vecino
            minimo = RLCValor[ind];//Pillamos valor de distancia
          }
        }
        minimo = 999999;
        RLCRuta.clear();
        RLCValor.clear();
        //std::cout << "el menor elemento en la fila: " << i << ", es el: " << elemento << ", con valor: " << matrix[i][elemento] << std::endl;
        rutaParcial.push_back(elemento);
        valorParcial.push_back(matrix[i][elemento]);
        i = elemento -1;
        for (int k = 0; k <matrix.size(); k++){
            matrix[k][elemento] = 0;
        }
        contador++;
        std::cout << std::endl;
        if(contador == size_route){
            i = -1;
            rutaParcial.push_back(0);
            valorParcial.push_back(matrix[elemento][0]);
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
            if(mejorDistancia > distanciaTotal){
              mejorDistancia = distanciaTotal;
              distanciaTotal = 0;
              rutaSolucion = rutafinal;
              rutafinal.clear();
              contadorNoImprove = 0;
            }else{
              contadorNoImprove++;
            }
            std::cout << std::endl;
            std::cout << "Mejor Distancia Final: " <<std::endl << mejorDistancia << std::endl;
            std::cout << " --------------" << std::endl;
            std::cout << "Mejor Ruta Final: " << std::endl;
            std::cout << " --------------" << std::endl;
            for(int c = 0; c < rutaSolucion.size(); c++){
                std::cout << rutaSolucion[c] << "\t";
            }

                std::cout << std::endl;
                matrix.clear();
                contadorIteraciones++;
                contruta = 0;
                break;
            }
        }    
}
}
}


void generateRLC(std::vector<int>& RLCR, std::vector<int>& RLCV, std::vector<int> fila, int size_RLC){

std::vector<int> matrix = fila;

int elemento;
for(int z = 0; z < size_RLC ; z++){
int minimo = 999999;
for (int i = 1; i < matrix.size(); i++){
    if(minimo > matrix[i] && matrix[i] !=0){
      minimo = matrix[i];
      elemento = i;
    }
}
matrix[elemento] = 0;
if(RLCR.size() < size_RLC){
  RLCR.push_back(elemento);
  RLCV.push_back(minimo);
  }
}

//std::cout << "RLC: ";
//for(int j = 0; j < RLCR.size(); j++){
  //std::cout << RLCR[j] << " ";
//}
//std::cout << std::endl;


int ind = rand()%RLCR.size();
//std::cout << ind << std::endl;
//std::cout << RLCV[ind] << std::endl;
}


#endif
