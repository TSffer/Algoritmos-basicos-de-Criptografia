#ifndef ESCITALA_H
#define ESCITALA_H
#include <string>
#include <iostream>
using namespace std;
class Escitala
{
    private:
        int Clave;
    public:
        Escitala(int);
        string Codificador(string);
        string Descodificador(string);
        int modulo(int ,int);
};

#endif
