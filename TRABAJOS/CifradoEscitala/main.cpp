#include <iostream>
#include "escitala.cpp"
#include <string>
#include <cmath>
using namespace std;

int main()
{
    int Clave;
    string Mensaje ="", cod , des;
    cout<<"Ingrese el Mensaje: ";
    getline(cin,Mensaje);
    cout<<"Ingrese la Clave: ";
    cin>>Clave;
    Escitala Emisor(Clave);
    cod=Emisor.Codificador(Mensaje);
    cout<<cod<<endl;
    cout<<"\n\n"<<endl;
    des=Emisor.Descodificador(cod);
    cout<<des<<endl;
    return 0;
}
