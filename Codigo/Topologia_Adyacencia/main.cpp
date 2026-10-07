#include <iostream>
#include <fstream> //Permite la lectura de archivos
#include <vector> //Permite la creación de vectores y matrices
#include <cmath> //Necesario para la función pow                

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
      for(int j=0; j<=Mat[0].size()-1; j++){
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

vector<bool> inter(vector<bool> vect1, vector<bool> vect2){ //Esta función realiza la "intersección" de dos vectores
   for(int i=0; i<=vect1.size()-1; i++){
      vect1[i] = vect1[i] && vect2[i];
   }
   return vect1;
}

vector<vector<bool>> llenarMatriz_U(vector<vector<bool>> Mat_Ady){
   vector<vector<bool>> Mat_U(Mat_Ady.size(), vector<bool>(Mat_Ady.size(),true));
   for(int i=0; i<=Mat_Ady.size()-1; i++){
      for(int j=0; j<=Mat_Ady.size()-1; j++){ // Para cada i \in \{1,\dots, n\} se hace la intersección \bigcap_{v_j \in A_{v_i}} A_{v_j} variando j de 1 a n

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
vector<vector<bool>> llenarMatriz_Preuniones(int n){//Esta matriz se usa para hacer todas las posibles uniones de una familia de n conjuntos: por cada fila i pone 1 en la columna j si, y solo si, el conjunto U_j se debe incluir en la unión
   int m = 1 << n; // 2^n equivalente en enteros
   vector<vector<bool>> Mat_Preuniones(m, vector<bool>(n, false)); //La matriz tendrá 2^n filas y n columnas
   for(int j=0; j<=n-1; j++){ //Llenamos la matriz como en una tabla de verdad
      bool pert = 1; //La primera fila siempre es 1; ponemos 1 cada 2^(n-i) elementos
      for(int i=0; i<=m-1; i++){
         Mat_Preuniones[i][j] = pert;
         if( ((i+1) % (1 << (n-(j+1)))) == 0){ //Cambiamos la pertenencia cada 2^(n-j) elementos
            pert = !pert;
         }
      }
   }
   return Mat_Preuniones;
}

vector<bool> unir(vector<bool> vect1, vector<bool> vect2){ //Esta función realiza la unión de dos conjuntos
   for(int i=0; i<=vect1.size()-1; i++){
      vect1[i] = vect1[i] || vect2[i];
   }
   return vect1;
}

bool igualdadVectores(vector<bool> vect1, vector<bool> vect2){ //Esta función determina si dos vectores son iguales
   for(int i=0; i<=vect1.size()-1; i++){
      if(vect1[i] != vect2[i]){
         return false;
      }
   }         
   return true;
}

vector<vector<bool>> limpiarMatriz(vector<vector<bool>> Mat_tau){ //Esta función llena de ceros las versiones repetidas de una fila
   int m = Mat_tau.size();
   for(int i=0; i<=m-1; i++){
      for(int j=i+1; j<=m-1; j++){
         if(igualdadVectores(Mat_tau[i], Mat_tau[j])){
            Mat_tau[j].assign(Mat_tau[j].size(), false); //Si el vector es repetido, lo llena de ceros
         }
      }
   }
   return Mat_tau;
}

int card(vector<bool> vect){ //Esta función determina cuántas entradas no nulas tiene el vector
   int card_vect = 0;
   for(int i=0; i<=vect.size()-1; i++){
      if(vect[i]){
         card_vect++;
      }
   }
   return card_vect;
}

bool pivSet(vector<bool> vect1, vector<bool> vect2){ //Esta función determina si vect2 tiene un "orden horizontal" inferior a vect1 (si i es la menor posición tal que vect1[i] != vect2[i] entonces vect2[i]=1), donde se asume que vect2 y vect1 tienen el mismo "cardinal" pero son distintos
   for(int i=0; i<=vect1.size()-1; i++){
      if(vect1[i]!=vect2[i] && vect2[i]){
         return true;
      }
      if(vect1[i]!=vect2[i] && vect1[i]){
         return false;
      }
   }
   return false;
}

vector<vector<bool>> sort(vector<vector<bool>> Mat_tau){
   int m = Mat_tau.size();
   for(int i=0; i<=m-1; i++){
      for(int j=i+1; j<=m-1; j++){
         if( ( (card(Mat_tau[i])!=0 && card(Mat_tau[j])!=0) && ( (card(Mat_tau[i])>card(Mat_tau[j])) || ( (card(Mat_tau[i]) == card(Mat_tau[j])) && pivSet(Mat_tau[i],Mat_tau[j])==1) ) )  ||  (card(Mat_tau[i])==0 && card(Mat_tau[j])!=0) ){ 
            //Primero miramos si ambas filas son no nulas. Si |tau_i|>|tau_j| entonces se intercambian. Si |tau_i|=|tau_j| pero tau_j tiene menor orden horizontal que tau_j entonces se intercambian. Segundo miramos si tau_i es nula y tau_j no lo es; en dado caso intercambiamos las filas. Esto último hace que las filas vacías queden abajo.
            vector<bool> temp = Mat_tau[i];
            Mat_tau[i] = Mat_tau[j];
            Mat_tau[j] = temp;
         }
      }
   }
   return Mat_tau;
}

vector<vector<bool>> llenarMatriz_tau(vector<vector<bool>> Mat_U){ //Esta función devuelve una matriz tau que contiene la información de todos los abiertos de la topología de adyacencia, en tanto que las filas forman la colección de todos los conjuntos abiertos
   vector<vector<bool>> Mat_Preuniones = llenarMatriz_Preuniones(Mat_U.size());
   int m = 1 << Mat_U.size();
   vector<vector<bool>> Mat_tau(m, vector<bool>(Mat_U.size(), false)); //La matriz tendrá 2^n filas y n columnas (n=número de vértices)
   for(int i=0; i<= m-1; i++){ //Hacemos la unión de los U_{v_i} que indica cada fila de Mat_Preuniones
      for(int j=0; j<= Mat_U.size()-1; j++){
         if(Mat_Preuniones[i][j]){
            Mat_tau[i] = unir(Mat_tau[i],Mat_U[j]);
         }
      }
   }
   Mat_tau = limpiarMatriz(Mat_tau); //Quitamos los abiertos repetidos
   Mat_tau = sort(Mat_tau); //Ordenamos los conjuntos por cardinal y también "horizontalmente"
   return Mat_tau;
}

void imprAbiertos(vector<vector<bool>> Mat_tau){
   int m = Mat_tau.size();
   int n = Mat_tau[0].size();
   cout << "tau_{mathcal{A},G} = { vacío"; //Siempre imprimimos el vacío primero
   for(int i=0; i<=m-1; i++){
      bool aux_coma = 0; //Ayuda a imprimir bien las comas que separan conjuntos
      if(card(Mat_tau[i])!=0){ //Solo imprimimos los conjuntos no vacíos
         cout << ", {";
         bool aux_coma_int = 0; //Ayuda a imprimir bien las comas que separan elementos
         for(int j=0; j<=n-1; j++){
            if(Mat_tau[i][j]){
               if(aux_coma_int){
                  cout << ", ";
               }
               cout << "v_" << j+1;
               aux_coma_int = 1;
            }
         }
         cout << "}";
      }
   }
   cout << " }";  
}

int main(){
   ifstream file("5_Mat_Ady.txt"); //Guarda la información de "1.txt" en la variable "file" de tipo ifstream
   
   vector<vector<bool>> Mat_Ady = leerMatriz(file); //Creamos la matriz de adyacencia llamando la función "leerMatriz" que toma como argumento la variable file
   vector<vector<bool>> Mat_U = llenarMatriz_U(Mat_Ady); //Llenamos Mat_U de nxn con la información de Mat_ady. En ella guardamos la información de los U_{v_i} mediante (Mat_U)_{i,j}=1 ssi v_j \in U_{v_i}
   vector<vector<bool>> Mat_Preuniones = llenarMatriz_Preuniones(Mat_Ady.size());
   vector<vector<bool>> Mat_tau = llenarMatriz_tau(Mat_U);

   cout << "A = " << endl;
   imprMatriz(Mat_Ady);
   cout << endl;
   imprAdyacencias(Mat_Ady); //Imprimimos todos los A_{v_i}
   cout << endl;
   cout << "U = " << endl;
   imprMatriz(Mat_U); //Imprimimos la Matriz U
   cout << endl;
   imprVecindadesMinimas(Mat_U); //Imprimimos todas los U_{v_i}
   cout << endl;
   imprAbiertos(Mat_tau);

   return 0;
}
