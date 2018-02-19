#include <iostream>
#include <vector>
#include "vaya.h"

using namespace std;

int main()
{

  string dic="abcdefghijklmnopqrstuvwxyz ";
  bool ver=true;
  while(ver)
  {
    int op;
    cout<<"Ingrese una opcion: \n[1] Encriptar \n[2] Desencriptar \n[0] Salir"<<endl;
    cin>>op;
    if(op == 1)
    {
      string mensaje,Emensaje;
      int clave;
      cout<<"Ingrese la clave: ";
      cin>>clave;
      cout<<"Ingrese el mensaje: ";
      getline(cin,mensaje);
      getline(cin,mensaje);
      vaya A(dic,clave);
      Emensaje = A.encriptar(mensaje);
      cout<<Emensaje<<endl;

    }
     else if(op == 2)
    {
      string Emensaje,mensaje;
      int clave;
      cout<<"Ingrese la clave: ";
      cin>>clave;
      cout<<"Ingrese el mensaje: ";
      getline(cin,Emensaje);
      getline(cin,Emensaje);
      vaya B(dic,clave);
      mensaje = B.desencriptar(Emensaje);
      cout<<mensaje<<endl;
    }
     else if(op==0)
    {
      ver=false;
    }
  }

  cout<<"Finalizado!!!"<<endl;
  return 0;
}
