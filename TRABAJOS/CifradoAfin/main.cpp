#include <iostream>
#include "afin.cpp"
#include <string>
#include <fstream>

using namespace std;

int main()
{
  int op;
  bool ver=true;
  while(ver)
  {

    cout<<"Ingrese una opcion: \n [1] Encriptar \n [2] Desencriptar \n [0] Salir"<<endl;
    cin>>op;
    if(op==1)
    {
      int bi;
      string mensaje;
      cout<<"Ingrese el numero de bits: ";
      cin>>bi;
      ifstream ficheroEntrada;
      ficheroEntrada.open("texto.txt");
      getline(ficheroEntrada,mensaje);
      ficheroEntrada.close();
      Afin A(bi);
      string ME=A.cifrado(mensaje);
      cout<<ME<<endl;

      ofstream ficheroSalida;
      ficheroSalida.open("ficheroTexto.txt");
      ficheroSalida<<ME;
    }
    else if(op==2)
    {
      ZZ clave;
      ZZ desp;
      string mensaje;
      cout<<"Ingrese la clave: ";
      cin>>clave;
      cout<<"Ingrese el desplazamiento: ";
      cin>>desp;
      cout<<"Ingrese el mensaje: ";
      getline(cin,mensaje);
      getline(cin,mensaje);
      /*ifstream ficheroEntrada;
      ficheroEntrada.open("ficheroTexto.txt");
      getline(ficheroEntrada,mensaje);
      ficheroEntrada.close();
      cout<<"Mensaje";*/
      Afin B(clave,desp);

      cout<<"Mensaje Original:   "<<B.descifrado(mensaje)<<endl;
    }
    else if(op==0)
    {
      ver=false;
    }


  }
}
