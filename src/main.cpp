/*=======================================================================================
=========================================================================================
    =                                                                              =
    =            Proyect:       Practica 7 VRP con Greedy y Grasp                  =
    =            File name:     main.cpp                                           =
    =            Author:        Gabriel Melián Hernández                           =
    =            Email:         alu0100819786@ull.edu.es                           =
    =                                                                              =
=========================================================================================
=======================================================================================*/
#include "../includes/Algoritmo.h"
#include "../includes/Busquedas.h"
#include "../includes/Problema.h"
#ifndef MAIN_
#define MAIN_

/*-----DECLARACIÓN DE LBIRERIAS-----*/

#include <sys/time.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
/*-----DECLARACIÓN DE FUNCIONES-----*/
void help();
bool useGreedy();
std::string deleteWhiteSpacesSurround(std::string str);

/**
Función main en la que vamos a recibir como argumentos en la llamada al programa, el fichero de entrada de datos, vamos a almacenar su contenido en las variables 
correspondientes, además de crear la matriz de distancias entre clientes. Por último llamaremos a la función "useGreedy" que devolverá true o false para conocer
que tipo de algoritmo tenemos que ejecutar.
*/
int main(int argc, char *argv[]) {
  int n_customers = 0;
  int n_vehicles = 0;
  std::vector<std::vector<int> > matrix = std::vector<std::vector<int> >();

	if (argc != 2) {
		std::cerr << "Numero de argumentos incorrecto." << std::endl;
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
    std::cerr << "No se ha podido abrir el fichero de entrada. " << fileName << std::endl;
    return 1;
  }

  if (useGreedy()) {
    Algoritmo *problema = new Algoritmo(n_customers, n_vehicles, matrix);
    problema -> Greedy();
  }else {
    Algoritmo *problema = new Algoritmo(n_customers, n_vehicles, matrix);
    problema -> Grasp();
  }
};

/**
Función de ayuda que devuelve diferentes mensajes de texto por pantalla, para ayudar al usuario a ejecutar de correcta forma nuestro
programa.
*/
void help() {
	std::cout << std::endl << "Se requiere de 1 parámetro:" << std::endl;
	std::cout << "\t1º- Nombre del fichero de entrada." << std::endl;
	std::cout << "./vrp <input-file-name>" << std::endl;
}

/**
Función booleana, que recibirá la respuesta del usuario al tipo de algoritmo que vamos a ejecutar, si la respuesta es Sí, se llamará y ejecutará el algoritmo Greedy, mientras
que en caso contrario, llamaríamos y ejecutaríamos el algoritmo Grasp.
*/
bool useGreedy() {
  std::string input = "";
	while (true) {
		std::cout << "¿Ejecutar el algoritmo greedy (si/no)?: " << std::endl << "\t>> ";
		std::cin >> input;
		if ((input == "si") || (input == "SI") || (input == "Si")) {
			return true;
		} else if ((input == "no") || (input == "NO") || (input == "No")) {
      return false;
    } else {
			std::cout << std::endl << "Escriba una opcion correcta." << std::endl << std::endl;
			input = "";
		}
	}
}

/**
Función que eliminará los espacios en blanco, tabulaciones y retornos de carro de nuestra entrada.
*/
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
#endif