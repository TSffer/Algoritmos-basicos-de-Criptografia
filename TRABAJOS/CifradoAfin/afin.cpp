#include "afin.h"
#include <stdio.h>
#include <sys/time.h>
#include <NTL/ZZ.h>
#include <iostream>
#include <string>

using namespace std;
using namespace NTL;

Afin::Afin(int bits)
{
  alfa = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789,. ";
  nbit = bits;
  ZZ clave,Desclave;

  RandomBits(desp,10);

  bool ver = false;
  while(ver == false)
  {
    RandomBits(clave,nbit);
    if(euclides(clave,ZZ(alfa.size())) == 1)
    {
      Desclave = inverso(ZZ(clave),ZZ(alfa.size()));
      ver = true;
    }else{
      ver = false;
    }
  }
  A = clave;
//  A1 = Desclave;
  cout<< "La clave de Cifrado es: "<<clave<<" La clave de Descifrado es: "<<Desclave<<endl;
  cout<< "Numero de desplazamiento es: "<<desp<<endl;
  cout<<endl;
  cout<<"\n";
}

Afin::Afin(ZZ clave,ZZ desplazamiento)
{
  A1 = clave;
  desp = desplazamiento;
}
ZZ modulo(ZZ a , ZZ b)
{
  int mod  = a - b*(a/b);
  if(mod>=0)
  {
    return mod;
  }
  mod = mod + b;
  return mod;
}

ZZ Afin::euclides(ZZ A , ZZ B)
{
      ZZ a , b , r;
      a = A;
      b = B;

      if(a < b)
      a^=b;b^=a;a^=b;

      r = a % b;
      while(r > 0)
      {
        a = b;
        b = r;
        r = modulo(a,b);
      }
      return b;
}

ZZ Afin::inverso(ZZ number, ZZ modulo)
{
  ZZ b = number;
  ZZ a = modulo;

  ZZ u , v , r , q , x , y , x_tmp , y_tmp;
  x = 1 , v = 1 , y = 0, u = 0;

  do{
    q = a/b;
    r = modulo(a,b);
    a = b; b = r;
    x_tmp = x; y_tmp = y;
    x = u; y = v;
    u = x_tmp - q*u;
    v = y_tmp - q*v;
  } while(b > 0);
  while(y < 0){
    y +=modulo;
  }
  return y;
}

string Afin::cifrado(string mensaje)
{
  string enc;
  for(int i =0; i<mensaje.size();i++)
  {
    int aux = alfa.find(mensaje[i]);
    enc += alfa.at(modulo((A*aux + desp),alfa.size()));
  }
  return enc;
}

string Afin::descifrado(string mensaje)
{
  string mns;
  for(int i =0;i<mensaje.size();i++)
  {
    int aux = alfa.find(mensaje[i]);
    mns +=alfa.at(modulo((A1*(aux-desp)),alfa.size()));
  }
  return mns;
}
