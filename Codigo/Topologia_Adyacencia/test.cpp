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

void imprMatriz(vector<vector<bool>> Mat){ //Función para imprimir la matriz que se pasa como argumento
   for(int i=0; i<=Mat.size()-1; i++){
      for(int j=0; j<=Mat.size()-1; j++){
         cout << Mat[i][j] << "\t";
      }
      cout << endl;
   }
}

void imprAdyacencias(vector<vector<bool>> Mat_Ady){ //Esta función imprime todos los conjuntos de adyacencia A_{v_i} del grafo
   for(int i=0; i<=Mat_Ady.size()-1; i++){
      //Imprimimos A_{v_i+1}
      cout << "A_{v_" << i+1 << "} = {";
      bool aux_coma = 0; //Usamos esta variable para ayudarnos a imprimir bien las comas que separan elementos del conjunto
      for(int j=0; j<=Mat_Ady.size()-1; j++){
         if(Mat_Ady[i][j]){
            if(aux_coma){
               cout << ", ";
            }
            cout << "v_" << j+1;
            aux_coma = 1;
         }
      }
      cout << "}" << endl;
   }
}

vector<bool> inter(vector<bool> vect1, vector<bool> vect2){
   for(int i=0; i<=vect1.size()-1; i++){
      vect1[i] = vect1[i] && vect2[i];
   }
   return vect1;
}

vector<vector<bool>> llenarMatriz_U(vector<vector<bool>> Mat_Ady){
   vector<vector<bool>> Mat_U(Mat_Ady.size(), vector<bool>(Mat_Ady.size(),true));
   for(int i=0; i<=Mat_Ady.size()-1; i++){
      for(int j=0; j<=Mat_Ady.size()-1; j++){
         if(Mat_Ady[i][j]){
            Mat_U[i] = inter(Mat_U[i], Mat_Ady[j]);
         }
      }
   }
   return Mat_U;
}

void imprVecindadesMinimas(vector<vector<bool>> Mat_U){ //Esta función imprime todos las vecindades minimales U_{v_i} del grafo
   for(int i=0; i<=Mat_U.size()-1; i++){
      //Imprimimos U_{v_i+1}
      cout << "U_{v_" << i+1 << "} = {";
      bool aux_coma = 0; //Usamos esta variable para ayudarnos a imprimir bien las comas que separan elementos del conjunto
      for(int j=0; j<=Mat_U.size()-1; j++){
         if(Mat_U[i][j]){
            if(aux_coma){
               cout << ", ";
            }
            cout << "v_" << j+1;
            aux_coma = 1;
         }
      }
      cout << "}" << endl;
   }
}

int main(){
   ifstream file("../Matrices/Mat_Ady_1.txt"); //Guarda la información de "1.txt" en la variable "file" de tipo ifstream
   
   vector<vector<bool>> Mat_Ady = leerMatriz(file); //Creamos la matriz de adyacencia llamando la función "leerMatriz" que toma como argumento la variable file
   vector<vector<bool>> Mat_U = llenarMatriz_U(Mat_Ady); //Llenamos Mat_U de nxn con la información de Mat_ady. En ella guardamos la información de los U_{v_i} mediante (Mat_U)_{i,j}=1 ssi v_j \in U_{v_i}
   cout << "A = " << endl;
   imprMatriz(Mat_Ady);
   cout << endl;
   imprAdyacencias(Mat_Ady); //Imprimimos todos los A_{v_i}
   cout << endl;
   cout << "U = " << endl;
   imprMatriz(Mat_U); //Imprimimos la Matriz U
   cout << endl;
   imprVecindadesMinimas(Mat_U); //Imprimimos todas los U_{v_i}

   return 0;
}
