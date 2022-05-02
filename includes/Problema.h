#ifndef PROBLEMA_H_
#define PROBLEMA_H_
#pragma once

#include <sys/time.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>

class Problema{

    private:

    public:
        Problema();
        ~Problema();
        bool isZero(std::vector<int> array);
        void generateRLC(std::vector<int>& RLCR, std::vector<int>& RLCV, std::vector<int> fila, int size_RLC);
        bool isEmpty(std::vector<std::vector<int> > matrix);
        int getNumberIterations();
        int getRLCVectorSize();
        int getTimesWithoutImprove();
        long getCurrentTime();


};
#endif /* PROBLEMA_H_ */