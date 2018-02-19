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
#include "miller_rabin.h"
#include "bbs.h"
int tam=512;
#include "gordon.h"
#include "pollar.h"
#include "gamal.h"

string diccionario=" ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890 ,.";

int main(){
  SeedXorShift();
  SeedBBS();

  Gamal A(diccionario);
  ZZ e_1,e_2,p_a;
  e_1 = A.e1;
  e_2 = A.e2;
  p_a = A.p;

  cout <<"e1: "<< e_1 << endl;
  cout <<"e2: "<< e_2 << endl;
  cout <<"p: "<< p_a << endl;


  string mensaje;
  cout<<"Ingrese el mensaje: ";
  getline(cin,mensaje);

  string encriptar=A.encriptar(mensaje,e_1,e_2,p_a);
  cout <<"Mensaje encriptado: "<< encriptar << endl;
	string des =  A.desencriptar(encriptar) ;
  cout <<"Mensaje desencriptado: "<<des<< endl;
  return 0;
}
