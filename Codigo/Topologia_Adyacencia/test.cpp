#include <iostream>
#include <fstream> //Permite la lectura de archivos
#include <vector> //Permite la creación de vectores y matrices

using namespace std;

vector<vector<bool>> leerMatriz(ifstream& file){ //Función para crear la matriz y llenarla con los datos del archivo. Toma una variable ifstream y retorna una matriz
   int n; //Crea la variable para guardar el tamaño de la matriz
   file >> n; //Se lee el tamaño de la matriz, que siempre es el primer número del archivo "1.txt"
   
   vector<vector<bool>> Mat_Ady(n, vector<bool>(n)); //Creamos una matriz de booleanos de tamaño nxn
   
   for(int i=0; i<=n-1; i++){ //Se llena la matriz Mat_Ady con los datos de "1.txt"
      for(int j=0; j<=n-1; j++){
         bool valor;
         file >> valor;
         Mat_Ady[i][j] = valor;
      }
   }
   return Mat_Ady;
}

void imprMatriz(vector<vector<bool>> Mat_Ady){ //Función para imprimir la matriz que se pasa como argumento
   for(int i=0; i<=Mat_Ady.size()-1; i++){
      for(int j=0; j<=Mat_Ady.size()-1; j++){
         cout << Mat_Ady[i][j] << "\t";
      }
      cout << endl;
   }
}

void Adyacencias(vector<vector<bool>> Mat_Ady){
   for(int i=0; i<=Mat_Ady.size()-1; i++){
      //Imprimimos A_{v_i+1}
      cout << "A_{v_" << i+1 << "} = {";
      for(int j=0; j<=Mat_Ady.size()-1; j++){
         if(Mat_Ady[i][j]){
            cout << "v_" << j+1 << "\t";
         }
      }
      cout << "}" << endl;
   }
}

int main(){
   ifstream file("1.txt"); //Guarda la información de "1.txt" en la variable "file" de tipo ifstream
   
   vector<vector<bool>> Mat_Ady = leerMatriz(file); //Creamos la matriz de adyacencia llamando la función "leerMatriz" que toma como argumento la variable file
   
   Adyacencias(Mat_Ady);

   return 0;
}
