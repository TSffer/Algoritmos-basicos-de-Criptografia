#ifndef CMODIFICADO_H
#define CMODIFICADO_H
#include <iostream>
#include <string>

using namespace std;

class CModificado
{
  private:
    string clave;
    string Alfabeto;
  public:
    CModificado(string);
    string Encriptar(string);
    string Desencriptar(string);
    int modulo(int, int);
};
#endif
