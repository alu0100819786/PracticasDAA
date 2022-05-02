#ifndef ALGORITMO_H_
#define ALGORITMO_H_
#pragma once
#include "Problema.h"
#include "Busquedas.h"

#include <sys/time.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>


class Algoritmo : public Problema, public Busquedas{

    private:
        int customers;
        int vehicles;
        std::vector<std::vector<int> > matriz;


    public:
        Algoritmo(int customers, int vehicles,std::vector<std::vector<int> > matriz);
        ~Algoritmo();
       
        void Greedy();
        void Grasp();
        


};
#endif /* ALGORITMO_H_ */