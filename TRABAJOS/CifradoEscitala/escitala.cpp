#include "escitala.h"
#include <iostream>
#include <string>
using namespace std;

Escitala::Escitala(int nClave)
{
    Clave = nClave;
}

int Escitala::modulo(int a , int b)
{
    int q,r;
    q=a/b;
    r=a-(b*q);
    if(r<0)
        return (b+r);
    else
        return r;
}

string Escitala::Codificador(string Mensaje)
{
    string _codificado="";
    int tam = Mensaje.size();

    int Col = tam/Clave;
    int mod = modulo(tam,Clave);
    if(mod>0){
        Col++;
    }
    int temp;
    for (int i = 0;i<Clave;i++)
    {
            for(int j=0;j<Col;j++)
            {
                temp = i+(Clave*j);
                if(temp >= tam)
                {
                    _codificado += '-';
                }else{
                    _codificado +=Mensaje.at(temp);
                }
            }
    }
      return _codificado;
}

string Escitala::Descodificador(string  t_ci)
{
    string t_desc="";
	int r = t_ci.size()/Clave;
	for(int i=0;i<r;i++)
  {
		for(int j=0;j<Clave;j++)
    {
			if(t_ci.at(i+(j*r))=='-');
			else	t_desc = t_desc + t_ci.at(i+(j*r));
		}
	}
	return t_desc;
}
