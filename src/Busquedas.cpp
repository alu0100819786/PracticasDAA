#include "../includes/Busquedas.h"


Busquedas::Busquedas(std::vector<std::vector<int> > matriz, std::vector<int> inputRuta, int inputDistancia, int vehiculos, int clientes){

        matrix = matriz;
        ruta = inputRuta;
        distancia = inputDistancia;
        vehicles = vehiculos;
        customers = clientes;
        mejorRuta=inputRuta;
        rutaGVNS = inputRuta;
}

Busquedas::Busquedas(){

}
Busquedas::~Busquedas(){
    matrix.clear();
    ruta.clear();
    distancia = 0;
    vehicles = 0;
    customers = 0;
    mejorRuta.clear();
    rutaGVNS.clear();
}

void Busquedas::IntercambioIntraRuta(){

  /*for(int l = 0; l < ruta.size(); l ++){
    std::cout << ruta[l] << " ";
  }
  std::cout << std::endl;
  std::cout << distancia << std::endl;
*/
//for( int x = 0; x < vehicles ; x++){}
std::vector<int> copia_ruta;
std::vector<int> ruta_final;
std::vector<int> copia_resultado;
ruta_final = ruta;
int distancia_GVNS = Evaluate(ruta);
int distancia_final;
distancia_final = distancia_GVNS;
copia_ruta = ruta;
int contador = 0;
int aux = 0;
int resultadoIntermedio = 0;
int resta = 0;
int suma = 0;
int copia_distancia = 0;
copia_distancia = distancia_GVNS;

//std::cout << "Distancia antes de mejorar: " << distancia << std::endl;
for(int i = 1; i < copia_ruta.size(); i++){
  copia_ruta = ruta;
  if(copia_ruta[i] == 0){
    i++;
    contador++;
    if(contador == vehicles){
      break;
    }
  }
  for(int j = i+1; j < copia_ruta.size(); j++){
    copia_ruta = ruta;
    if(copia_ruta[j] == 0){
      break;
    }else{
      //std::cout <<"cambio: " << copia_ruta[i] << " por: " << copia_ruta[j] << std::endl;
      if(copia_ruta[i+1] == copia_ruta[j]){
        //resta = 0;
        //resta = matrix[copia_ruta[i-1]][copia_ruta[i]] + matrix[copia_ruta[i]][copia_ruta[j]] + matrix[copia_ruta[j]][copia_ruta[j+1]];
        //std::cout << "resta: " << resta << std::endl;
        aux = copia_ruta[i];
        copia_ruta[i] = copia_ruta[j];
        copia_ruta[j] = aux;
        //suma = 0;
        //suma = matrix[copia_ruta[i-1]][copia_ruta[i]] + matrix[copia_ruta[i]][copia_ruta[j]] + matrix[copia_ruta[j]][copia_ruta[j+1]];
        //std::cout << "suma: " << suma << std::endl;
          //for(int l = 0; l < copia_ruta.size(); l ++){
            //std::cout << copia_ruta[l] << " ";
          //}
        //std::cout << std::endl;
      }
      if(copia_ruta[i+1] != copia_ruta[j]){
        //resta = 0;
        //resta = matrix[copia_ruta[i-1]][copia_ruta[i]] + matrix[copia_ruta[i]][copia_ruta[i+1]] + matrix[copia_ruta[j-1]][copia_ruta[j]] + matrix[copia_ruta[j]][copia_ruta[j+1]];
        //std::cout << "resta: " << resta << std::endl;
        aux = copia_ruta[i];
        copia_ruta[i] = copia_ruta[j];
        copia_ruta[j] = aux;
        //suma = 0;
        //suma = matrix[copia_ruta[i-1]][copia_ruta[i]] + matrix[copia_ruta[i]][copia_ruta[i+1]] + matrix[copia_ruta[j-1]][copia_ruta[j]] + matrix[copia_ruta[j]][copia_ruta[j+1]];
        //std::cout << "suma: " << suma << std::endl;
          //for(int l = 0; l < copia_ruta.size(); l ++){
            //std::cout << copia_ruta[l] << " ";
          //}
        //std::cout << std::endl;
      }
  //std::cout << "aaaa: " << copia_distancia<< std::endl;
  //resultadoIntermedio = suma - resta;
  //copia_distancia = copia_distancia + (suma - resta);
  int auxEvalute = 0;
  auxEvalute = Evaluate(copia_ruta);
  copia_distancia = auxEvalute;
  //std::cout << "pepe: " << copia_distancia << std::endl;
  if(copia_distancia < distancia_final){
    distancia_final = copia_distancia;
    ruta_final = copia_ruta;
    copia_distancia = distancia_GVNS;
    copia_ruta = ruta;
  }else{
    copia_distancia = distancia_GVNS;
    copia_ruta = ruta;
  }
    }
    
  }
}

//std::cout << "Distancia Inicial: " << distancia << std::endl;
//std::cout << "Distancia Mejorada: " << distancia_final << std::endl;
if(distancia_final < distancia_GVNS){
  
  ruta = ruta_final;
  distancia_GVNS = distancia_final;
  //std::cout << "Nueva distancia: " <<  distancia << std::endl;
  IntercambioIntraRuta();
}
else{
  
std::cout << "La nueva mejor ruta (óptimo Local) conseguida con Intercambio IntraRuta es: " << std::endl;
for(int m = 0; m < ruta_final.size(); m ++){
    std::cout << ruta_final[m] << " ";
  }
std::cout << std::endl;
std::cout << "Con una distancia de: " << distancia_final << std::endl;
std::cout << "-----------------------------------------------------" << std::endl;
setMejorRuta(ruta_final);
}

//Hacerla al final paso por referencia la ruta y la distancia para que al volver al grasp la devuelva modificada y poder aplicarla en las demás funciones.
}

void Busquedas::IntercambioEntreRutas(){

std::vector<int> copia_ruta;
std::vector<int> ruta_final;
ruta_final = ruta;
int distancia_final;
int distancia_GVNS = Evaluate(ruta);
distancia_final = distancia_GVNS;
copia_ruta = ruta;
int contador = 0;
int aux = 0;
int resultadoIntermedio = 0;
int resta = 0;
int suma = 0;
int copia_distancia = 0;
copia_distancia = distancia_GVNS;
int conthastacero = 1;
int contj = 0;
//std::cout << "Distancia antes de mejorar: " << distancia << std::endl;
  for(int i = 1; i < copia_ruta.size(); i ++){
    copia_ruta = ruta;
    if(copia_ruta[i] == 0){
      i++;
      contador++;
    }
    if(contador == vehicles){
      break;
    }
    for(int z=i+1;z<copia_ruta.size();z++){
      if(copia_ruta[z] != 0){
        conthastacero++;
      }
      if(copia_ruta[z] == 0){
        break;
      }
    }
    contj = i + conthastacero + 1;
    //std::cout << "Posicion i: " << i << std::endl;
    //std::cout << "Contador J: " << contj << std::endl;
    if(contj == copia_ruta.size()){
      //std::cout << "estamos en la misma ruta" << std::endl;
      break;
    }
    
    
    conthastacero = 1;
  for(int j=contj; j<copia_ruta.size()-1;j++){
    copia_ruta = ruta;
    if(copia_ruta[j] == 0 && copia_ruta[j+1] == 0){
      break;
    }
    if(copia_ruta[j] == 0){
        j++;
    }
    
      //std::cout <<"cambio: " << copia_ruta[i] << " por: " << copia_ruta[j] << std::endl;
      //resta = 0;
        //resta = matrix[copia_ruta[i-1]][copia_ruta[i]] + matrix[copia_ruta[i]][copia_ruta[i+1]] + matrix[copia_ruta[j-1]][copia_ruta[j]] + matrix[copia_ruta[j]][copia_ruta[j+1]];
        //std::cout << "resta: " << resta << std::endl;
        aux = copia_ruta[i];
        copia_ruta[i] = copia_ruta[j];
        copia_ruta[j] = aux;
        //suma = 0;
        //suma = matrix[copia_ruta[i-1]][copia_ruta[i]] + matrix[copia_ruta[i]][copia_ruta[i+1]] + matrix[copia_ruta[j-1]][copia_ruta[j]] + matrix[copia_ruta[j]][copia_ruta[j+1]];
        //std::cout << "suma: " << suma << std::endl;
          //for(int l = 0; l < copia_ruta.size(); l ++){
            //std::cout << copia_ruta[l] << " ";
          //}
        //std::cout << std::endl;
        //std::cout << "aaaa: " << copia_distancia<< std::endl;
  //resultadoIntermedio = suma - resta;
  //copia_distancia = copia_distancia + (suma - resta);
   int auxEvalute = 0;
  auxEvalute = Evaluate(copia_ruta);
  copia_distancia = auxEvalute;
  //std::cout << "pepe: " << copia_distancia << std::endl;
  if(copia_distancia < distancia_final){
    //std::cout << "Intercambio con Mejora:" << copia_ruta[i] << ", " << copia_ruta[j] << std::endl;
    distancia_final = copia_distancia;
    ruta_final = copia_ruta;
    copia_distancia = distancia_GVNS;
    copia_ruta = ruta;
  }else{
    copia_distancia = distancia_GVNS;
    copia_ruta = ruta;
  }
  }
  }
//std::cout << "Distancia Inicial: " << distancia << std::endl;
//std::cout << "Distancia Mejorada: " << distancia_final << std::endl;
if(distancia_final < distancia_GVNS){
  ruta = ruta_final;
  distancia_GVNS = distancia_final;
//std::cout << "Nueva distancia: " <<  distancia << std::endl;
  IntercambioEntreRutas();
}
else{
std::cout << "La nueva mejor ruta (óptimo Local) conseguida con Intercambio Entre Rutas es: " << std::endl;
for(int m = 0; m < ruta_final.size(); m ++){
    std::cout << ruta_final[m] << " ";
  }
std::cout << std::endl;
std::cout << "Con una distancia de: " << distancia_final << std::endl;
std::cout << "-----------------------------------------------------" << std::endl;
setMejorRuta(ruta_final);
}
//Hacerla al final paso por referencia la ruta y la distancia para que al volver al grasp la devuelva modificada y poder aplicarla en las demás funciones.
}

void Busquedas::InsercionIntraRuta(){

std::vector<int> copia_ruta;
std::vector<int> vector_erased;
std::vector<int> ruta_final;
ruta_final = ruta;
int distancia_final;
int distancia_GVNS = Evaluate(ruta);
distancia_final = distancia_GVNS;
copia_ruta = ruta;
int contador = 0;
int aux = 0;
int resultadoIntermedio = 0;
int resta = 0;
int suma = 0;
int copia_distancia = 0;
copia_distancia = distancia_GVNS;
int indice = 0;
int inicio = 1;

/*
std::cout << copia_ruta[3] << std::endl;
copia_ruta.erase(copia_ruta.begin() + 3);
std::cout << copia_ruta[3] << std::endl;
for(int l = 0; l < copia_ruta.size(); l ++){
            std::cout << copia_ruta[l] << " ";
          }
          std::cout << std::endl;
copia_ruta.insert(copia_ruta.begin() +1, 2);
for(int l = 0; l < copia_ruta.size(); l ++){
            std::cout << copia_ruta[l] << " ";
          }

  */ 
//std::cout << "Distancia antes de mejorar: " << distancia << std::endl;       
for(int i = 1; i < copia_ruta.size(); i++){
  copia_ruta = ruta;
  if(copia_ruta[i] == 0){
    i++;
    contador++;
    inicio = i;
    if(contador == vehicles){
      break;
    }
  }
  indice = copia_ruta[i];
  //std::cout << "erased: " << indice << std::endl;
  copia_ruta.erase(copia_ruta.begin() + i);
  vector_erased = copia_ruta;
  for(int j = inicio; j < vector_erased.size(); j++){
      if( j != inicio && vector_erased[j-1] == 0){
        break;
      }
      //std::cout << "insert: " << j << std::endl;
      if(i==j){
        //std::cout << "(i=j)quitamos: " << ruta[i-1] << "-" << ruta[i] << " luego " << ruta[i] << "-" << ruta[i+1] << " por ultimo: " << ruta[j-1]<< "-" << ruta[j] << std::endl;
        //resta = matrix[ruta[i-1]][ruta[i]] + matrix[ruta[i]][ruta[i+1]] + matrix[ruta[j-1]][ruta[j]];
      }
      if(i<j){
        //std::cout << "(i<j)quitamos: " << ruta[i-1] << "-" << ruta[i] << " luego " << ruta[i] << "-" << ruta[i+1] << " por ultimo: " << ruta[j]<< "-" << ruta[j+1] << std::endl;
        //resta = matrix[ruta[i-1]][ruta[i]] + matrix[ruta[i]][ruta[i+1]] + matrix[ruta[j]][ruta[j+1]];
      //std::cout << "Resta:" << resta << std::endl;
      }
      if(i>j){
        //std::cout << "(i>j)quitamos: " << ruta[i-1] << "-" << ruta[i] << " luego " << ruta[i] << "-" << ruta[i+1] << " por ultimo: " << ruta[j-1]<< "-" << ruta[j] << std::endl;
        //resta = matrix[ruta[i-1]][ruta[i]] + matrix[ruta[i]][ruta[i+1]] + matrix[ruta[j-1]][ruta[j]]; 
      }
      vector_erased.insert(vector_erased.begin() +j, indice);
      if(i==j){
        //std::cout << "(i=j)ponemos: " << vector_erased[j-1] << "-" << vector_erased[j] << " luego " << vector_erased[j] << "-" << vector_erased[j+1] << " por ultimo: " << vector_erased[i-1]<< "-" << vector_erased[i] << std::endl;
        //suma = matrix[vector_erased[j-1]][vector_erased[j]] + matrix[vector_erased[j]][vector_erased[j+1]] + matrix[vector_erased[i-1]][vector_erased[i]];
       }
      if(i<j){
        //std::cout << "(i<j)ponemos: " << vector_erased[j-1] << "-" << vector_erased[j] << " luego " << vector_erased[j] << "-" << vector_erased[j+1] << " por ultimo: " << vector_erased[i-1]<< "-" << vector_erased[i] << std::endl;
        //suma = matrix[vector_erased[j-1]][vector_erased[j]] + matrix[vector_erased[j]][vector_erased[j+1]] + matrix[vector_erased[i-1]][vector_erased[i]];
       //std::cout << "Suma:" << suma << std::endl;
       }
      if(i>j){
        //std::cout << "(i>j)ponemos: " << vector_erased[j-1] << "-" << vector_erased[j] << " luego " << vector_erased[j] << "-" << vector_erased[j+1] << " por ultimo: " << vector_erased[i]<< "-" << vector_erased[i+1] << std::endl;
        //suma = matrix[vector_erased[j-1]][vector_erased[j]] + matrix[vector_erased[j]][vector_erased[j+1]] + matrix[vector_erased[i]][vector_erased[i+1]];
      }
      
//resultadoIntermedio = suma - resta;
//vector_erased = copia_ruta;
//std::cout << "Distancia Pre Intercambio: " << copia_distancia << std::endl;
//std::cout << "Resultado Intermedio: " << resultadoIntermedio << std::endl;
      //for(int l = 0; l < vector_erased.size(); l ++){
            //std::cout << vector_erased[l] << " ";
          //}
          //std::cout << std::endl;
//int pruebita = 0;
//int auxprueba = 0;
      //for(int n = 1; n < vector_erased.size(); n ++){
           // auxprueba = matrix[vector_erased[n-1]][vector_erased[n]];
            //pruebita += auxprueba;
          //}

          
//copia_distancia = copia_distancia + resultadoIntermedio;
 int auxEvalute = 0;
  auxEvalute = Evaluate(vector_erased);
  copia_distancia = auxEvalute;
//copia_distancia = pruebita;
//std::cout << "Resultado esperado: " << pruebita << std::endl;
//auxprueba = 0;
//pruebita = 0;
//std::cout << "Distancia Post Intercambio: " << copia_distancia << std::endl;
//std::cout << std::endl;
if(copia_distancia < distancia_final){
  distancia_final = copia_distancia;
  ruta_final = vector_erased;
  copia_distancia = distancia_GVNS;
  vector_erased = copia_ruta;
}else{
  copia_distancia = distancia_GVNS;
  vector_erased = copia_ruta;
}

  }
}

//std::cout << "Distancia Inicial: " << distancia << std::endl;
//std::cout << "Distancia Mejorada: " << distancia_final << std::endl;
if(distancia_final < distancia_GVNS){
  //for(int n = 0; n < ruta.size(); n ++){
    //std::cout << ruta[n] << " ";
 // }
//std::cout << std::endl;
//for(int m = 0; m < ruta_final.size(); m ++){
   // std::cout << ruta_final[m] << " ";
  //}
//std::cout << std::endl;
  distancia_GVNS = distancia_final;
  ruta = ruta_final;
//std::cout << "Nueva distancia: " <<  distancia << std::endl;
//contadorintra++;
//if(contadorintra == 3){
  //exit(0);
//}
  InsercionIntraRuta();
}
else{
std::cout << "La nueva mejor ruta (óptimo Local) conseguida con Inserción IntraRuta es: " << std::endl;
for(int m = 0; m < ruta_final.size(); m ++){
    std::cout << ruta_final[m] << " ";
  }
std::cout << std::endl;
std::cout << "Con una distancia de: " << distancia_final << std::endl;
std::cout << "-----------------------------------------------------" << std::endl;
setMejorRuta(ruta_final);
}

//Hacerla al final paso por referencia la ruta y la distancia para que al volver al grasp la devuelva modificada y poder aplicarla en las demás funciones.   
}

void Busquedas::InsercionEntreRutas(){
  std::cout << "Entramos" << std::endl;
  std::vector<int> copia_ruta = ruta;
  std::vector<int> ruta_final = ruta;
  int distancia_GVNS = Evaluate(ruta);
  int distancia_final = distancia_GVNS;
  int contador = 0;
  int aux = 0;
  int resultadoIntermedio = 0;
  int resta = 0;
  int suma = 0;
  int copia_distancia = distancia_GVNS;
  int conthastacero = 1;
  int contj = 0;
  int size_route = 0;
  float prueba = 0;
  prueba = (customers / vehicles) + (customers * 0.1);
  size_route = ceil(prueba);
  int MovimientoNoPermitido = 0;
  int contadorCeroPermitido = 0;
  //std::cout << "tamaño maximo " << size_route <<std::endl;

//std::cout << "Distancia antes de mejorar: " << distancia << std::endl;
  for(int i = 1; i < copia_ruta.size(); i ++){
    copia_ruta = ruta;
    if (copia_ruta[i] == 0) {
      i++;
      contador++;
    }
    if (contador == vehicles) {
      break;
    }
    for (int z=i+1; z<copia_ruta.size(); z++) {
      if(copia_ruta[z] != 0){
        conthastacero++;
      }
      if(copia_ruta[z] == 0){
        break;
      }
    }
    contj = i + conthastacero + 1;
    conthastacero = 1;
    for (int j=contj; j<copia_ruta.size(); j++) {
      copia_ruta = ruta;
      //std::cout <<"cambio: " << copia_ruta[i] << " en: " << j << std::endl;
      //resta = matrix[copia_ruta[i-1]][copia_ruta[i]] + matrix[copia_ruta[i]][copia_ruta[i+1]] + matrix[copia_ruta[j-1]][copia_ruta[j]];
      /*std::cout << "resta= ";
      std::cout << matrix[copia_ruta[i-1]][copia_ruta[i]] << "(" << copia_ruta[i-1] << "," << copia_ruta[i] << ")";
      std::cout << " + " << matrix[copia_ruta[i]][copia_ruta[i+1]] << "(" << copia_ruta[i] << "," << copia_ruta[i+1] << ")";
      std::cout << " + " << matrix[copia_ruta[j-1]][copia_ruta[j]] << "(" << copia_ruta[j-1] << "," << copia_ruta[j] << ")";
      std::cout << " = " << resta << std::endl;*/
        
      aux = copia_ruta[i];
      copia_ruta.erase(copia_ruta.begin() + i);
      copia_ruta.insert(copia_ruta.begin() + j - 1, aux);

      //suma = matrix[copia_ruta[i-1]][copia_ruta[i]] + matrix[copia_ruta[j-2]][copia_ruta[j-1]] + matrix[copia_ruta[j-1]][copia_ruta[j]];
      /*std::cout << "suma= ";
      std::cout << matrix[copia_ruta[i-1]][copia_ruta[i]] << "(" << copia_ruta[i-1] << "," << copia_ruta[i] << ")";
      std::cout << " + " << matrix[copia_ruta[j-2]][copia_ruta[j-1]] << "(" << copia_ruta[j-2] << "," << copia_ruta[j-1] << ")";
      std::cout << " + " << matrix[copia_ruta[j-1]][copia_ruta[j]] << "(" << copia_ruta[j-1] << "," << copia_ruta[j] << ")";
      std::cout << " = " << suma << std::endl;
      for(int l = 0; l < copia_ruta.size(); l ++){
        std::cout << copia_ruta[l] << " ";
      }
      std::cout << std::endl;*/
      //std::cout << "aaaa: " << copia_distancia<< std::endl;
      //resultadoIntermedio = suma - resta;
      //copia_distancia = copia_distancia + (suma - resta);
      //std::cout << "pepe: " << copia_distancia << std::endl;
       int auxEvalute = 0;
  auxEvalute = Evaluate(copia_ruta);
  copia_distancia = auxEvalute;
      //std::cout << "Evaluate pepe: " << auxdistancia << std::endl;
      if(copia_distancia < distancia_final){
        //Meter aquí la comprobación de que el movimiento sea posible.

          for(int i = 1; i < copia_ruta.size(); i++){
            if(MovimientoNoPermitido == 1){
              break;
            }
            for(int j = i; j < copia_ruta.size(); j++){
                if(copia_ruta[j] != 0){
                  contadorCeroPermitido++;
                }
                if(copia_ruta[j] == 0){
                  break;
                }
            }
            std::cout << "ContadorCeroPermitido: " << contadorCeroPermitido << std::endl;
            if(contadorCeroPermitido > size_route){
              MovimientoNoPermitido = 1;
            }else{
              i= i + contadorCeroPermitido + 1;
              contadorCeroPermitido = 0;
            }

          }
        if(MovimientoNoPermitido == 1){
          std::cout << "Movimiento No Permitido" << std::endl;
          copia_distancia = distancia_GVNS;
          copia_ruta = ruta;
        }
        if(MovimientoNoPermitido == 0){
          std::cout << "Movimiento Permitido" << std::endl;
          distancia_final = copia_distancia;
          ruta_final = copia_ruta;
          copia_distancia = distancia_GVNS;
          copia_ruta = ruta;
        }
        /*
        distancia_final = copia_distancia;
        ruta_final = copia_ruta;
        copia_distancia = distancia_GVNS;
        copia_ruta = ruta;*/
        
      }else{
        //std::cout << "Movimiento de Peora" << std::endl;
        copia_distancia = distancia_GVNS;
        copia_ruta = ruta;
      }
    }
  }
//std::cout << "Distancia Inicial: " << distancia << std::endl;
//std::cout << "Distancia Mejorada: " << distancia_final << std::endl;
  if(distancia_final < distancia_GVNS){
    distancia_GVNS = distancia_final;
    ruta = ruta_final;
    //std::cout << "Nueva distancia: " <<  distancia << std::endl;
    InsercionEntreRutas();
  }
  else{
  std::cout << "La nueva mejor ruta (óptimo Local) conseguida con Inserción EntreRutas es: " << std::endl;
  for(int m = 0; m < ruta_final.size(); m ++){
    std::cout << ruta_final[m] << " ";
  }
  std::cout << std::endl;
  std::cout << "Con una distancia de: " << distancia_final << std::endl;
  std::cout << "-----------------------------------------------------" << std::endl;
  setMejorRuta(ruta_final);
  }
  
  //Hacerla al final paso por referencia la ruta y la distancia para que al volver al grasp la devuelva modificada y poder aplicarla en las demás funciones.    
}

void Busquedas::setMejorRuta(std::vector<int> ruta){
for(int m = 0; m < ruta.size(); m ++){
    mejorRuta[m] = ruta[m];
  }
}

std::vector<int> Busquedas::getMejorRuta(){

  return mejorRuta;
}

int Busquedas::Evaluate(std::vector<int> rutita){
int resultado = 0;
int aux = 0;
      for(int i = 1; i < rutita.size(); i ++){
            aux = matrix[rutita[i-1]][rutita[i]];
            resultado += aux;
          }
      return resultado;
}

void Busquedas::GVNS(){

int saltos = 0;
int contador = 0;
int distancia_GVNS = 0;
std::vector<int> ruta_Intermedia = ruta;

while(saltos <5){//Este es el Shaking.

InsercionEntreRutasAleatorio();
std::cout << "Ruta Despues del Shaking: " << std::endl;
for(int m = 0; m < ruta.size(); m ++){
    std::cout << ruta[m] << " ";
  }
  std::cout << std::endl;

ruta_Intermedia = ruta;
for(int m = 0; m < ruta_Intermedia.size(); m ++){
    std::cout << ruta_Intermedia[m] << " ";
}
  std::cout << std::endl;
  std::cout << "Evaluate del Shaking: " << Evaluate(ruta) << " " << Evaluate(ruta_Intermedia) << std::endl;
  while(contador < 4){ //Este While es el VND.
    if(contador == 0){
      std::cout << "Entramos a Contador = 0 con: "<< Evaluate(ruta) << std::endl;
      std::cout << "Miramos La Ruta de Antes: " << std::endl;
      for(int m = 0; m < ruta_Intermedia.size(); m ++){
    std::cout << ruta_Intermedia[m] << " ";
  }
  std::cout << std::endl;
      //InsercionEntreRutas();
      
  std::cout << "Miramos La Ruta Nueva: " << std::endl;
  for(int m = 0; m < ruta.size(); m ++){
    std::cout << ruta[m] << " ";
  }
  std::cout << std::endl;
      std::cout << Evaluate(ruta_Intermedia) << " " << Evaluate(ruta)<< std::endl;
      if(Evaluate(ruta_Intermedia) <= Evaluate(ruta)){
        contador = 1;
      }
      else{
        contador = 0;
        ruta_Intermedia = ruta;
      }
    }
    if(contador == 1){
      std::cout << "Entramos a Contador = 1 con: "<< Evaluate(ruta) << std::endl;
      InsercionIntraRuta();
      std::cout << Evaluate(ruta_Intermedia) << " " << Evaluate(ruta)<< std::endl;
      if(Evaluate(ruta_Intermedia) <= Evaluate(ruta)){
        contador = 2;
      }
      else{
        contador = 0;
        ruta_Intermedia = ruta;
      }
    }
    if(contador == 2){
      std::cout << "Entramos a Contador = 2 con: "<< Evaluate(ruta) << std::endl;
      IntercambioEntreRutas();
      std::cout << Evaluate(ruta_Intermedia) << " " << Evaluate(ruta)<< std::endl;
      if(Evaluate(ruta_Intermedia) <= Evaluate(ruta)){
        contador = 3;
      }
      else{
        contador = 0;
        ruta_Intermedia = ruta;
      }
    }
    if(contador == 3){
      std::cout << "Entramos a Contador = 3 con: "<< Evaluate(ruta) << std::endl;
      IntercambioIntraRuta();
      std::cout << Evaluate(ruta_Intermedia) << " " << Evaluate(ruta)<< std::endl;
      if(Evaluate(ruta_Intermedia) <= Evaluate(ruta)){
        contador = 4;
      }
      else{
        contador = 0;
        ruta_Intermedia = ruta;
      }
    }
  }
  if(Evaluate(rutaGVNS) > Evaluate(ruta)){
    rutaGVNS = ruta;
  }
  saltos++;
  contador = 0;
}
std::cout << "El óptimo local Conseguido con GVNS es: "<< std::endl;
  for(int m = 0; m < rutaGVNS.size(); m ++){
    std::cout << rutaGVNS[m] << " ";
  }
  std::cout << std::endl;
  distancia_GVNS = Evaluate(rutaGVNS);
  std::cout << "Con distancia: " << distancia_GVNS << std::endl;
}

void Busquedas::InsercionEntreRutasAleatorio(){
  //std::cout << "----------------------------------" << std::endl;

  //for(int m = 0; m < ruta.size(); m ++){
    //std::cout << ruta[m] << " ";
  //}
  //std::cout << std::endl;

int MovimientoI = 0;
int MovimientoCont = 0;
int MovimientoJ = 0;
int contador = 0;
int contJ = 0;
int contZ = 0;
int posErased = 0;
int posInserted = 0;
int contadorhastasiguienteruta = 0;
int conthastacero = 0;
int size_route = 0;
int contadorMov = 0;
  float prueba = 0;
  prueba = (customers / vehicles) + (customers * 0.1);
  size_route = ceil(prueba);

  for(int i = 1; i < ruta.size(); i++){
    if(contadorMov == 1){
      break;
    }
    contadorhastasiguienteruta = 0;
    conthastacero = 0;
    if(ruta[i] == 0 || (ruta[i-1] == 0 && ruta[i+1] == 0)){
      i++;
      contador++;
    }
    if(contador >= vehicles){
      break;
    }
    for( int x = i; x < ruta.size(); x++){
      if(ruta[x] != 0){
        contadorhastasiguienteruta++;
      }
      if(ruta[x] == 0){
        contadorhastasiguienteruta+=2;
        break;
      }
    }
contZ = contadorhastasiguienteruta + i -1;
//std::cout << "Con i en: " << i <<", La siguiente ruta empieza en: " << contadorhastasiguienteruta << std::endl;
    for(int z = contZ; z<ruta.size(); z++){
      if(contadorMov == 1){
        break;
      }
      if(ruta[z] != 0){
        conthastacero++;
      }
      
      if(ruta[z] == 0 && conthastacero < size_route){
        if(ruta[i-1] == 0 && ruta[i+1] == 0){
          //std::cout << "Contador hasta cero: " << conthastacero << std::endl;
          //std::cout << "No podemos insertar en esta ruta, miramos la siguiente" <<std::endl;
          conthastacero = 0;
        }else{
          //std::cout << "Contador hasta cero: " << conthastacero << std::endl;
          //std::cout << "Podemos Insertar" <<std::endl;
          contJ = z - conthastacero;
          contadorMov = 1;
          //std::cout << "Empezamos J en la posición: " << contJ << std::endl;
          MovimientoJ = contJ;
          MovimientoI = i;
          MovimientoCont = contadorhastasiguienteruta-2;
          break;
        }
        
      }
      if(ruta[z] == 0 && conthastacero == size_route || (ruta[i-1] == 0 && ruta[i+1] == 0)){
        //std::cout << "Contador hasta cero: " << conthastacero << std::endl;
        //std::cout << "No podemos insertar en esta ruta, miramos la siguiente" <<std::endl;
        conthastacero = 0;
      }
      
    }
    
    
  }

  if(contadorMov == 1){
    //std::cout << "La ruta empieza en: " << MovimientoI << std::endl;
    //std::cout << "Dura: " << MovimientoCont << std::endl;
    //std::cout << "La siguiente ruta empieza en: " << MovimientoJ << std::endl;
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(MovimientoI, MovimientoCont);
    posErased = distr(eng);


    conthastacero = 0;
    //std::cout<< "MovimientoJ " << MovimientoJ << std::endl;
    //std::cout<< "Ruta Size " << ruta.size() << std::endl;
    for(int j = MovimientoJ; j<ruta.size(); j++){
      if(MovimientoJ == ruta.size() -2){
      break;
      }
      if(ruta[j] != 0){
        conthastacero++;
        //std::cout << "pepe" << std::endl;
      }
      if(ruta[j] == 0){
        break;
      }
}
MovimientoJ = MovimientoJ -1;
conthastacero += MovimientoJ;
std::uniform_int_distribution<int> distrJ(MovimientoJ, conthastacero);
posInserted = distrJ(eng);
int auxMovimiento = 0;
auxMovimiento = ruta[posErased];
    //std::cout << posErased << std::endl;
    //std::cout << posInserted << std::endl;
//for(int m = 0; m < ruta.size(); m ++){
    //std::cout << ruta[m] << " ";
  //}
  //std::cout << std::endl;
ruta.erase(ruta.begin()+ posErased);
ruta.insert(ruta.begin()+ posInserted, auxMovimiento);

//for(int m = 0; m < ruta.size(); m ++){
    //std::cout << ruta[m] << " ";
  //}
  //std::cout << std::endl;
  }
if(contadorMov == 2){
    contador = 0;
    contJ = 0;
    contZ = 0;
    contadorhastasiguienteruta = 0;
    conthastacero = 0;

    std::cout << "peep" << std::endl;
      int pene = ruta.size() -2;
      for(int y = pene ; y >= 0; y--){
        contadorhastasiguienteruta = 0;
        conthastacero = 0;
        //std::cout << ruta[y] << " ";
        if(ruta[y] == 0){
          y--;
          contador++;
        }
        if(contador == vehicles){
          break;
        }
        for(int x = y; x >= 0; x--){
          if(ruta[x] != 0){
            contadorhastasiguienteruta++;
          }
          if(ruta[x] == 0){
            contadorhastasiguienteruta+=2;
            break;
          }
        }
      contZ = y - contadorhastasiguienteruta +1;
      std::cout << "Con y en: " << y <<", La siguiente ruta empieza en: " << y - contadorhastasiguienteruta +1 << std::endl;
      for (int z = contZ; z >= 0; z--){
        if(ruta[z] != 0){
          conthastacero++;
        }
        if(ruta[z] == 0 && conthastacero < size_route){
          std::cout << "Contador hasta cero: " << conthastacero << std::endl;
          std::cout << "Podemos Insertar" <<std::endl;
          contJ = z + conthastacero;
          contadorMov = 1;
          std::cout << "Empezamos J en la posición: " << contJ << std::endl;
          break;
        }
        if(ruta[z] == 0 && conthastacero == size_route){
          std::cout << "Contador hasta cero: " << conthastacero << std::endl;
          std::cout << "No podemos insertar en esta ruta, miramos la siguiente" <<std::endl;
          conthastacero = 0;
        }
      }
      }
      std::cout << std::endl;
    
  }
}

void Busquedas::IPrueba(){
  std::cout << "----------------------------------" << std::endl;

  for(int m = 0; m < ruta.size(); m ++){
    std::cout << ruta[m] << " ";
  }
  std::cout << std::endl;

int MovimientoI = 0;
int MovimientoCont = 0;
int MovimientoJ = 0;
int contador = 0;
int contJ = 0;
int contZ = 0;
int posErased = 0;
int posInserted = 0;
int contadorhastasiguienteruta = 0;
int conthastacero = 0;
int size_route = 0;
int contadorMov = 0;
  float prueba = 0;
  prueba = (customers / vehicles) + (customers * 0.1);
  size_route = ceil(prueba);

  for(int i = 1; i < ruta.size(); i++){
    if(contadorMov == 1){
      break;
    }
    contadorhastasiguienteruta = 0;
    conthastacero = 0;
    if(ruta[i] == 0 || (ruta[i-1] == 0 && ruta[i+1] == 0)){
      i++;
      contador++;
    }
    if(contador >= vehicles){
      break;
    }
    for( int x = i; x < ruta.size(); x++){
      if(ruta[x] != 0){
        contadorhastasiguienteruta++;
      }
      if(ruta[x] == 0){
        contadorhastasiguienteruta+=2;
        break;
      }
    }
contZ = contadorhastasiguienteruta + i -1;
std::cout << "Con i en: " << i <<", La siguiente ruta empieza en: " << contadorhastasiguienteruta << std::endl;
    for(int z = contZ; z<ruta.size(); z++){
      if(contadorMov == 1){
        break;
      }
      if(ruta[z] != 0){
        conthastacero++;
      }
      
      if(ruta[z] == 0 && conthastacero < size_route){
        if(ruta[i-1] == 0 && ruta[i+1] == 0){
          std::cout << "Contador hasta cero: " << conthastacero << std::endl;
          std::cout << "No podemos insertar en esta ruta, miramos la siguiente" <<std::endl;
          conthastacero = 0;
        }else{
          std::cout << "Contador hasta cero: " << conthastacero << std::endl;
          std::cout << "Podemos Insertar" <<std::endl;
          contJ = z - conthastacero;
          contadorMov = 1;
          std::cout << "Empezamos J en la posición: " << contJ << std::endl;
          MovimientoJ = contJ;
          MovimientoI = i;
          MovimientoCont = contadorhastasiguienteruta-2;
          break;
        }
        
      }
      if(ruta[z] == 0 && conthastacero == size_route || (ruta[i-1] == 0 && ruta[i+1] == 0)){
        std::cout << "Contador hasta cero: " << conthastacero << std::endl;
        std::cout << "No podemos insertar en esta ruta, miramos la siguiente" <<std::endl;
        conthastacero = 0;
      }
      
    }
    
    
  }

  if(contadorMov == 1){
    std::cout << "La ruta empieza en: " << MovimientoI << std::endl;
    std::cout << "Dura: " << MovimientoCont << std::endl;
    std::cout << "La siguiente ruta empieza en: " << MovimientoJ << std::endl;
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(MovimientoI, MovimientoCont);
    posErased = distr(eng);


    conthastacero = 0;
    std::cout<< "MovimientoJ " << MovimientoJ << std::endl;
    std::cout<< "Ruta Size " << ruta.size() << std::endl;
    for(int j = MovimientoJ; j<ruta.size(); j++){
      if(MovimientoJ == ruta.size() -2){
      break;
      }
      if(ruta[j] != 0){
        conthastacero++;
        std::cout << "pepe" << std::endl;
      }
      if(ruta[j] == 0){
        break;
      }
}
MovimientoJ = MovimientoJ -1;
conthastacero += MovimientoJ;
std::uniform_int_distribution<int> distrJ(MovimientoJ, conthastacero);
posInserted = distrJ(eng);
int auxMovimiento = 0;
auxMovimiento = ruta[posErased];
    std::cout << posErased << std::endl;
    std::cout << posInserted << std::endl;
for(int m = 0; m < ruta.size(); m ++){
    std::cout << ruta[m] << " ";
  }
  std::cout << std::endl;
ruta.erase(ruta.begin()+ posErased);
ruta.insert(ruta.begin()+ posInserted, auxMovimiento);

for(int m = 0; m < ruta.size(); m ++){
    std::cout << ruta[m] << " ";
  }
  std::cout << std::endl;
  }
if(contadorMov == 2){
    contador = 0;
    contJ = 0;
    contZ = 0;
    contadorhastasiguienteruta = 0;
    conthastacero = 0;

    std::cout << "peep" << std::endl;
      int pene = ruta.size() -2;
      for(int y = pene ; y >= 0; y--){
        contadorhastasiguienteruta = 0;
        conthastacero = 0;
        //std::cout << ruta[y] << " ";
        if(ruta[y] == 0){
          y--;
          contador++;
        }
        if(contador == vehicles){
          break;
        }
        for(int x = y; x >= 0; x--){
          if(ruta[x] != 0){
            contadorhastasiguienteruta++;
          }
          if(ruta[x] == 0){
            contadorhastasiguienteruta+=2;
            break;
          }
        }
      contZ = y - contadorhastasiguienteruta +1;
      std::cout << "Con y en: " << y <<", La siguiente ruta empieza en: " << y - contadorhastasiguienteruta +1 << std::endl;
      for (int z = contZ; z >= 0; z--){
        if(ruta[z] != 0){
          conthastacero++;
        }
        if(ruta[z] == 0 && conthastacero < size_route){
          std::cout << "Contador hasta cero: " << conthastacero << std::endl;
          std::cout << "Podemos Insertar" <<std::endl;
          contJ = z + conthastacero;
          contadorMov = 1;
          std::cout << "Empezamos J en la posición: " << contJ << std::endl;
          break;
        }
        if(ruta[z] == 0 && conthastacero == size_route){
          std::cout << "Contador hasta cero: " << conthastacero << std::endl;
          std::cout << "No podemos insertar en esta ruta, miramos la siguiente" <<std::endl;
          conthastacero = 0;
        }
      }
      }
      std::cout << std::endl;
    
  }
}