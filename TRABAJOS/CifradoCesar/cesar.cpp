#include "cesar.h"
#include <string>
#include <iostream>
using namespace std;


int modulo(int a , int b)
{
  int mod  = a - b*(a/b);
  if(mod>=0)
  {
    return mod;
  }
  mod = mod + b;
  return mod;
}

cesar::cesar(int key)
{
  this->Alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz ";
  this->clave = key;

}


string cesar::Cifrar(string Mensaje)
{
  string New="";
  int pos;
  for(int i = 0; i<Mensaje.size();i++)
  {
    pos = modulo((Alfabeto.find(Mensaje[i]) + clave) , Alfabeto.size());
    New += Alfabeto.at(pos);
  }
  return New;
}

string cesar::Descifrar(string MensajeCifrado)
{
  string New="";
  int pos;
  for(int i = 0; i<MensajeCifrado.size();i++)
  {
    pos = modulo((Alfabeto.find(MensajeCifrado[i]) - clave) , Alfabeto.size());
    New += Alfabeto.at(pos);
  }
  return New;
}

cesar::~cesar(){}
