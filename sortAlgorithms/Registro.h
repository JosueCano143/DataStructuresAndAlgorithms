/* Actividad integral 1.3: Conceptos Básicos y Algoritmos Fundamentales (Evidencia Competencia)
   Equipo 1:
      Alejandra Guadalupe Olivas Altamirano.       Matrícula: A01741389
      Carolina Gómez Manzano.                      Matrícula: A01632229
      Guillermo Andrés Castillo Chapa.             Matrícula: A01720388
      Josue Salvador Cano Martinez.                Matrícula: A00829022.
   Fecha: 08/09/2020 */
   
#include <iostream>
#include <vector>

using namespace std;

class Registro {
    private: 
        string mes = " ", informacion = " ", entrada = " ";
        int mesN = 0, dia = 0;
    public:
        Registro(string entrada);

        string getEntrada();
        string getMes();
        int getDia();
        int getMesN();

        void separarEntrada(string entrada);
        void asignarMes(string mes);

        bool operator<=(Registro &registro);
        bool operator!=(Registro &registro);
};

// Objetos a partir del archivo
Registro::Registro(string entrada) { 
    this-> entrada = entrada;
    separarEntrada(this->entrada);
}

// Entrada del archivo se separa en atributos
void Registro::separarEntrada(string entrada) { 
    char espacio = 0;
    this->mes = entrada.substr(0,3);
    asignarMes(this->mes);

    if(isblank(entrada[5]) ==  false)
        espacio = 1;
    
    this->dia = stoi(entrada.substr(4, 1 + espacio));
    this->informacion = entrada.substr(6 + espacio);
}

// Sobrecarga de operadores
bool Registro::operator<=(Registro &registro) { 
    if (this->mesN != registro.getMesN()) 
        return this->mesN <= registro.getMesN();
    else if (this->dia != registro.getDia()) 
        return this->dia <= registro.getDia();

    return true; 
}

bool Registro::operator!=(Registro &registro) { 
    if (this->mesN != registro.getMesN()) 
        return true;
    else if (this->dia != registro.getDia()) 
        return true;

    return false; 
}

// Se asigna un número a cada mes
void Registro::asignarMes(string mes) { 
    if(mes == "Jun")
        this->mesN = 0;
    else if(mes == "Jul")
        this->mesN = 1;
    else if(mes == "Aug")
        this->mesN = 2;
    else if(mes == "Sep") 
        this->mesN = 3;
    else if(mes == "Oct")
        this->mesN = 4;
}

// Getters
string Registro::getEntrada() { return this-> entrada;}
string Registro::getMes() { return this-> mes;}
int Registro::getDia() { return this->dia; }
int Registro::getMesN() { return this->mesN;}