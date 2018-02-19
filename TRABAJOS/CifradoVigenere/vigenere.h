#ifndef VIGENERE_H
#define VIGENERE_H
#include <iostream>
#include <string>

using namespace std;

class Vigenere
{
  private:
    string Clave;
    string Alfabeto;
  public:
    Vigenere(string);
    string Cifrar(string);
    string Descifrar(string);
};
#endif
