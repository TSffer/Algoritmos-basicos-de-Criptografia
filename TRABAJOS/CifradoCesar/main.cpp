#include <iostream>
#include <string>
#include "cesar.cpp"

using namespace std;

int main()
{
  int op;
  while(1)
  {
    cout<<"Ingrese una opcion:"<<endl;
    cout<<"[1] Encriptar"<<endl;
    cout<<"[2] Desencriptar"<<endl;
    cout<<"[0] Salir"<<endl;
    cin>>op;
    if(op==1)
    {
      string NMensaje;
      int NewKey;
      cout<<"Ingrese el mensaje a Codificar: ";
      getline(cin,NMensaje);
      getline(cin,NMensaje);
      cout<<"Ingrese la Clave: ";
      cin>>NewKey;
      cesar Persona(NewKey);
      cout<<Persona.Cifrar(NMensaje)<<endl;
    }
    else if(op==2)
    {
      string CMensaje;
      int NewKey1;
      cout<<"Ingrese el mensaje a Decodificar: ";
      getline(cin,CMensaje);
      getline(cin,CMensaje);
      cout<<"Ingrese la Clave: ";
      cin>>NewKey1;
      cesar Persona1(NewKey1);
      cout<<Persona1.Descifrar(CMensaje)<<endl;
    }
    else
    {
      break;
    }
  }

  return 0;

}
