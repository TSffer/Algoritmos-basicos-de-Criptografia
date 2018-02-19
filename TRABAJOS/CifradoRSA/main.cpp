#include "rsa.h"
#include "rsa.cpp"
#include <iostream>
#include <string>
#include <fstream>
#include <NTL/ZZ.h>
#include <regex>
using namespace std;
using namespace NTL;

ZZ stoZZ(string num)
{
	ZZ conv(INIT_VAL , num.c_str());
	return conv;
}
string get_file_contents(const char *filename)
{
 	ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    return(string( (std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>() ));
  }
}

int main()
{
	while(1){
	int opcion;

	cout <<" [1] Encriptar \n [2] Desencriptar \n [3] Generar Claves \n [0] Cerrar \n" <<endl;
	cout << "Elija una opcion :";
	cin >> opcion;

	if(opcion == 1)
	{
		ZZ n,e;
		n = stoZZ (get_file_contents("clave_n.txt") );
		e = stoZZ (get_file_contents("clave_e.txt") );
		rsa rsa(n,e);
		rsa.cifrar();
	}
	else if( opcion == 2)
	{
    ZZ  p,q,e;
		p = stoZZ(get_file_contents("p.txt"));
		q = stoZZ(get_file_contents("q.txt"));
		e = stoZZ(get_file_contents("clave_e.txt"));
		rsa l(p,q,e);
		l.descifrar();

	}
	else if (opcion ==3)
	{
		int numBits;
		cout << "Ingrese el numero de bits: " ;
		cin >> numBits;
		rsa l(numBits);
	}

	else if (opcion ==0)
	{
		break;
	}

	else
		cout << " Vuelva a ingresar otra opcion "<< endl;
}
	return 0;
}
