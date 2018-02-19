#include "CModificado.h"
#include <iostream>
#include <string>

using namespace std;

CModificado::CModificado(string nClave)
{
  clave = nClave;
  Alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz ,.";
}

string CModificado::Encriptar(string Mensaje)
{
  string _codificado = "";
  int con=0,longi_Cla=0;

  for(int i=0; i<Mensaje.size();i++)
  {
    con=Alfabeto.find(clave.at(longi_Cla)) - Alfabeto.find(Mensaje.at(i));
    if(con<0)
      con=Alfabeto.size() + (con%(int)Alfabeto.size());
      _codificado+=Alfabeto.at(con);
    if(longi_Cla++>=clave.size()-1)
      longi_Cla=0;

  }return _codificado;
}

string CModificado::Desencriptar(string Mensaje)
{
  string _descodificado="";
  int con=0,longi_Cla=0;
  for(int i=0; i<Mensaje.size();i++)
  {
    con=Alfabeto.find(clave.at(longi_Cla)) - Alfabeto.find(Mensaje.at(i));
    if(con<0)
    con=Alfabeto.size()+(con%(int)Alfabeto.size());
    _descodificado+=Alfabeto.at(con);
    if(longi_Cla++>=clave.size()-1)
      longi_Cla=0;

  }return _descodificado;
}
