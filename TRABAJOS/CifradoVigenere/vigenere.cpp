#include "vigenere.h"
#include <iostream>
#include <string>

using namespace std;

Vigenere::Vigenere(string nClave)
{
  Clave = nClave;
  Alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz ,.";
}

string Vigenere::Cifrar(string Mensaje)
{
  string encriptado="";
  int resultado;
  int posT,posC;
  if(Mensaje.size() > Clave.size())
  {
    for(int i=0;i<Mensaje.size();i++)
    {
      Clave+=Clave.at(i);
    }
    for(int j=0;j<Mensaje.size();j++)
    {
      posT = Alfabeto.find(Mensaje.at(j));
      posC = Alfabeto.find(Clave.at(j));
      encriptado+=Alfabeto.at((posT+posC)%Alfabeto.size());
    }
  }else
  {
      for(int i =0;i< Mensaje.size();i++)
      {
        posT = Alfabeto.find(Mensaje.at(i));
        posC = Alfabeto.find(Clave.at(i));
        encriptado +=Alfabeto.at((posT + posC)% Alfabeto.size());
      }
  }
  return encriptado;
}

string Vigenere::Descifrar(string D_Mensaje)
{
  string descodificado;
  int resultado,posT,posC;

  if(D_Mensaje.size() > Clave.size())
  {
    for(int i=0 ; i<D_Mensaje.size();i++)
    {
      posT = Alfabeto.find(D_Mensaje.at(i));
      posC = Alfabeto.find(Clave.at(i));
      resultado = posT - posC;
      if(resultado < 0)
      {
        resultado = Alfabeto.size() + resultado;
        descodificado += Alfabeto.at(resultado%Alfabeto.size());
      }else
      {
        descodificado += Alfabeto.at(resultado%Alfabeto.size());
      }
    }
  }else
  {
    for(int i = 0;i<D_Mensaje.size();i++)
    {
      posT = Alfabeto.find(D_Mensaje.at(i));
      posC = Alfabeto.find(Clave.at(i));
      resultado = posT - posC;
      if(resultado < 0)
      {
        resultado = Alfabeto.size() + resultado;
        descodificado +=Alfabeto.at(resultado%Alfabeto.size());
      }else
      {
        descodificado += Alfabeto.at(resultado%Alfabeto.size());
      }
    }
  }
  return descodificado;
}
