/* Actividad integral 1.3: Conceptos Básicos y Algoritmos Fundamentales (Evidencia Competencia)
   Equipo 1:
      Alejandra Guadalupe Olivas Altamirano.       Matrícula: A01741389
      Carolina Gómez Manzano.                      Matrícula: A01632229
      Guillermo Andrés Castillo Chapa.             Matrícula: A01720388
      Josue Salvador Cano Martinez.                Matrícula: A00829022.
   Fecha: 08/09/2020 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Registro.h" 

using namespace std;

// FUNCIÓN PARA LECTURA DEL FICHERO: coloca cada registro en un vector de pointers
void leerArchivo(std::string archivo, std::vector<Registro*> &registros) {
    // Abre el archivo
    std::ifstream in(archivo.c_str());
    std::string str;

    // Lee el archivo linea por linea
    while (std::getline(in, str)) {
        // Si la linea contiene una string con tamaño > 0 se guarda en un vector
        if(str.size() > 0)
        registros.push_back(new Registro(str));
    }

    // Cierra el archivo
    in.close();
}

// FUNCIÓN DE ORDENAMIENTO
void merge(std::vector<Registro*> &vectorA, int izquierda, int medio, int derecha) {
   int i, j, k, nIzquierda, nDerecha;
   // Tamaño de los vectores de izquierda y derecha
   nIzquierda = medio - izquierda + 1; nDerecha = derecha - medio; 
 
    vector<Registro*> vectorIzquierda(nIzquierda);
    vector<Registro*> vectorDerecha(nDerecha);
   
   // Se llenan los vectores
   for(i = 0; i < nIzquierda; i++)
      vectorIzquierda[i] = vectorA[izquierda + i];
   for(j = 0; j < nDerecha; j++)
      vectorDerecha[j] = vectorA[medio + 1 + j];

   i = 0; j = 0; k = izquierda;
   
   // Se unen los vectores de izquierda y derecha al 'vectorA'
   while(i < nIzquierda && j < nDerecha) {
      if((*vectorIzquierda[i]) <= (*vectorDerecha[j])) { // Dos comparaciones debidas al operador
         vectorA[k] = vectorIzquierda[i];
         i++;
      }
      else {
         vectorA[k] = vectorDerecha[j];
         j++;
      }
      k++;
   }
   // En caso de que haya elementos extra del lado izquierdo
   while(i < nIzquierda) { 
      vectorA[k] = vectorIzquierda[i];
      i++; k++;
   }
   // En caso de que haya elementos extras del lado derecho
   while(j < nDerecha) {      
      vectorA[k] = vectorDerecha[j];
      j++; k++;
   }
}

void ordenaMerge(std::vector<Registro*> &vectorA, int izquierda, int derecha) {
   int medio;

   if(izquierda < derecha) {
      int medio = izquierda + (derecha - izquierda) / 2; 
      ordenaMerge(vectorA, izquierda, medio);  
      ordenaMerge(vectorA, medio + 1, derecha);  
      merge(vectorA, izquierda, medio, derecha);
   }
}

// BÚSQUEDA: Lee el archivo de índices y regresa el índice donde se encuentra la fecha ingresada
int leerIndices(std::string archivo, string fecha) {
   int indiceComa, indice;
   string fechaLinea;
   std::ifstream in(archivo.c_str());
   std::string str;
    
   while (std::getline(in, str)) {
      indiceComa = str.find(",");
      fechaLinea = str.substr(indiceComa + 1);
      if (fechaLinea == fecha)
         indice = stoi(str.substr(0,indiceComa));
   }

   in.close();
   return indice;
}

int main() {
   std::vector<Registro*> registros;

   // Guarda el contenido del archivo en un vector de pointers
   leerArchivo("bitacora.txt", registros);
   int n = registros.size();

   // Se ordenan por fecha
   ordenaMerge(registros, 0, n - 1);

   // Archivo donde se guardará el resultado de la búsqueda
   std::ofstream resultadoOrdenamiento; 

   resultadoOrdenamiento.open("resultadoOrdenamiento.txt", std::ofstream::out | std::ofstream::trunc);
   resultadoOrdenamiento.close();    
   resultadoOrdenamiento.open("resultadoOrdenamiento.txt", std::ios_base::app);
   
   for(int i = 0; i <= n - 1; i++)
      resultadoOrdenamiento << registros[i]->getEntrada() << endl;
   
   resultadoOrdenamiento.close(); 

   // Se crea un archivo que contiene el primer índice de cada fecha
   vector<int> indices = {0};
   std::ofstream resultadoIndices;

   for(int i = 1; i <= n - 1; i++) {
      if((*registros[i]) != (*registros[i - 1])) 
         indices.push_back(i);
   }

   resultadoIndices.open("resultadoIndice.txt", std::ofstream::out | std::ofstream::trunc);
   resultadoIndices.close();   
   resultadoIndices.open("resultadoIndice.txt", std::ios_base::app); 
   
   for(int i = 0; i <= indices.size()-1; i++)
      resultadoIndices << indices[i] << "," << registros[indices[i]]->getMes() << " " << registros[indices[i]]->getDia() << endl;

   resultadoIndices.close();  

   // Búsqueda por fecha
   string fecha, fechaFinal;
   int indiceInicio = 0, indiceFinal = 0;

   cout << "Ingresa la fecha donde deseas iniciar la busqueda en formato: Jun 16"<< endl;
   std::getline(std::cin, fecha);
   cout << "Ingresa la fecha donde deseas finalizar la busqueda en formado: Jun 21"<< endl;
   std::getline(std::cin, fechaFinal);
   
   indiceInicio = leerIndices("resultadoIndice.txt", fecha);
   indiceFinal = leerIndices("resultadoIndice.txt", fechaFinal);

   // Imprime los resultados de la búsqueda
   while(indiceInicio <= indiceFinal - 1) {
      cout << registros[indiceInicio]->getEntrada() << endl;
      indiceInicio++;
   }
}