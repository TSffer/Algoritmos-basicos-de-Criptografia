#include <iostream>
#include <time.h>
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


ZZ n_bbs;
ZZ xi_bbs;
ZZ MAX=conv<ZZ> (1000000000);

ZZ GPrimeXor()
{
  ZZ P,e;
  P = XorShift(MAX);
  e = P & 1;
  if(e==0) P++;
  while(!m_r(P,5))
  {
    P+=2;
  }
  return P;
}

void SeedBBS()
{
  ZZ p,q,seed;
  p = GPrimeXor();
  q = GPrimeXor();
  n_bbs = p*q;
  seed = XorShift(MAX);
  xi_bbs = MultMod(seed,seed,n_bbs);
}

ZZ BlumBlumShub(int tam)
{
  ZZ res,e,aux;
  aux = 1;
  res = 0;
  for(int i=tam-1;i>=0;i--)
  {
    xi_bbs = ExpMod(xi_bbs,conv<ZZ>(2),n_bbs);
    e = xi_bbs & 1;
    if(e==1) res+=aux;
    aux=aux<<1;
  }
  return res;
}
/*
int main()
{
    SeedXorShift();
    SeedBBS();
    ZZ a = BlumBlumShub(64);
    cout<<a<<endl;
    return 0;
}*/
