#include <iostream>
#include <ctime>
#include <map>
#include <math.h>
#include <chrono>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <sys/time.h>
#include <stdint.h>
#include <NTL/ZZ.h>
using namespace std;
using namespace NTL;
typedef long long ll;
typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;
typedef pair <ZZ,ZZ> pii;

#include "funciones.h"
#include "xorshift.h"
#include "mersenne_twister.h"
#include "miller_rabin.h"
#include "bbs.h"
#include "lfcr.h"
int tam=128;
#include "criba.h"
#include "pollar.h"
#include "rsa.h"


string diccionario;

int main()
{
  diccionario=leer("diccionario.txt");
  int encriptar;
  SeedXorShift();
  SeedBBS();
  RSA A(diccionario);

  A.dar_datos();
  cout << "Encriptar-Desencriptar" << endl;
  cin >> encriptar;
  while (encriptar)
  {
    if (encriptar==1)
    {
      ifstream leer ("encriptar.txt",ios::in);
      ZZ n;
      ZZ e;
      string mns;
      cin >> n >> e;
      getline(cin,mns);
      getline(cin,mns);
      cout << A.encriptar(mns,n,e) << endl;
      cout<<"Este es el encriptado"<<A.encriptar(mns,n,e)<<endl;
      leer.close();

    }
    if (encriptar==2)
    {
      string mns;
      getline(cin,mns);
      getline(cin,mns);
      cout << A.desencriptar(mns) << endl;

    }
    cout << "Encriptar-Desencriptar" << endl;
    cin >> encriptar;
  }
  return 0;
}
