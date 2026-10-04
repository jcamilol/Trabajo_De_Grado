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

vector<vector<bool>> llenarMatriz_U(vector<vector<bool>> Mat_Ady){
   vector<vector<bool>> Mat_U(Mat_Ady.size(), vector<bool>(Mat_Ady.size()));
   for(int i=0; i<=Mat_U.size()-1; i++){
      int piv = 0; //v_piv será el primer vértice con el que v_i sea adyacente (primer vértice que pertenezca a A_{v_i})
      for(int j=0; j<=Mat_Ady.size()-1; j++){
         if(Mat_Ady[i][j]){
            piv = j;
            break;
         }
      }
      for(int k=0; k<=Mat_U.size()-1; k++){ //k recorrerá los elementos de A_{v_piv}
         bool pertenencia = Mat_Ady[piv][k]; //Determina si v_k \in A_{v_piv}
         if(pertenencia){ //Si sí se tiene revisa si v_k \in A_{v_l} para todo v_l \in A_{v_i} con l empezando en piv+1 (pues ya se tiene que v_k \in A_{v_piv})
            for(int l=piv+1; l<=Mat_Ady.size()-1; l++){
               if(Mat_Ady[i][l]){ //Determina si v_l \in A_{v_i}
                  if(!Mat_Ady[l][k]){ //Si sí se tiene revisa si v_k \notin A_{v_l} y cambia la pertenencia a 0. Si v_k \in A_{v_l} deja la pertenencia en 1
                     pertenencia = 0;
                     break; //No hace falta revisar si v_k \in A_{v_l} en los demás l, pues ya no pertenecerá a la intersección de todos ellos
                  }

               }
            }
         }
         Mat_U[i][k] = pertenencia; //Ya se pasó por todos los A_{v_l} con v_l \in A_{v_i} para determinar si v_k \in \bigcap_{v_l \in A_{v_i} A_{v_i}}; pertenencia = 1 ssi esto se cumple   
      }
   }
   return Mat_U;
}

void imprVecindadesMinimales(vector<vector<bool>> Mat_U){ //Esta función imprime todos las vecindades minimales U_{v_i} del grafo
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

   imprAdyacencias(Mat_Ady); //Imprimimos todos los A_{v_i}
   cout << endl;
   imprMatriz(Mat_U); //Imprimimos la Matriz U
   cout << endl;
   imprVecindadesMinimales(Mat_U); //Imprimimos todas los U_{v_i}

   return 0;
}
