#include <iostream>
#include "vigenere.cpp"

using namespace std;

int main()
{
  string clave,Mensaje,t_c,t_d;
  cout<<"Ingrese la Clave para cifrar: ";
  getline(cin,clave);

  cout<<"Ingrese el mensaje a cifrar: ";
  getline(cin,Mensaje);

  Vigenere Emisor(clave);
  t_c=Emisor.Cifrar(Mensaje);
  cout<<t_c<<endl;
  cout<<"\n\n"<<endl;
  t_d=Emisor.Descifrar(t_c);
  cout<<t_d<<endl;
  return 0;
}
