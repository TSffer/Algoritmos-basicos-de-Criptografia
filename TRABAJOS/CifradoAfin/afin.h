#ifndef AFIN_H
#define AFIN_H
#include <NTL/ZZ.h>
#include <string>
#include <iostream>
using namespace std;
using namespace NTL;

class Afin
{
  private:
    string alfa;
    int nbit;
    ZZ A,A1;
    ZZ desp;
  public:
    Afin(int);
    Afin(ZZ,ZZ);
    ZZ euclides(ZZ,ZZ);
    ZZ inverso(ZZ,ZZ);
    string cifrado(string);
    string descifrado(string);
};

#endif
