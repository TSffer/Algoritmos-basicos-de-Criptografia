#include <iostream>
#include <string>
#include <stdio.h>
#include "CModificado.cpp"
using namespace std;

int main()
{
  string Clave,Mensaje;
  string codi,desco;

  cout<<"Introdusca la clave: "<<endl;
  getline(cin,Clave);
  CModificado Emisor(Clave);

  cout <<"Ingrese un nuevo mensaje: "<<endl;
  getline(cin,Mensaje);

  codi = Emisor.Encriptar(Mensaje);
  cout<<codi<<endl;
  cout<<"\n\n"<<endl;
  desco = Emisor.Desencriptar(codi);
  cout<<desco<<endl;
}
