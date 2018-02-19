#include "rsa.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <NTL/ZZ.h>
#include <regex>
#include <string>

using namespace std;
using namespace NTL;

typedef long long int ll;

rsa::rsa(int nbits)
{
  cout<<"# de "<<nbits<<" bits"<<endl;
  generarClaves(nbits);
}

rsa::rsa(ZZ nn , ZZ ee)
{
  long long   size = alfabeto.size();
	n = nn;
	e = ee;
}

rsa::rsa(ZZ pp,ZZ qq,ZZ ee)
{
  ofstream clave_fi;
	ofstream clave_d;
	clave_fi.open("clave_fi.txt",ifstream::binary);
	clave_d.open("d.txt", ifstream::binary);
	p = pp;
	q = qq;
	n = p*q;
	fn = (p-1)*(q-1);
	clave_fi<<fn;
	e = ee;
	d= Inversa(e,fn);
	clave_d<<d;
	clave_fi.close();
	clave_d.close();
}

void rsa::generarClaves(int nbits)
{
  ofstream Directorio ;
	ofstream clavesPrivadas;
	ofstream clave_e;
	ofstream clave_n;
	ofstream clave_p;
	ofstream clave_q;

  Directorio.open("Directorio publico.txt",ifstream::binary);
  clavesPrivadas.open("claves Privadas.txt",ifstream::binary);
  clave_e.open("clave_e.txt",ifstream::binary);
  clave_n.open("clave_n.txt",ifstream::binary);
  clave_p.open("p.txt",ifstream::binary);
  clave_q.open("q.txt",ifstream::binary);

  srand(time(0));
  while(true)
  {
    p = GenPrime_ZZ(nbits);
    if(MillerWitness(p,ZZ(200)) == 0)
      break;
  }

  cout<<"---------------------------"<<endl;
  while(true)
  {
    q = GenPrime_ZZ(nbits);
    if(MillerWitness(q,ZZ(200)) == 0)
      break;
  }
  n = p*q;
  fn = (p-1)*(q-1);
  while(true)
  {
    e = mod(RandomBits_ZZ(nbits),fn);
    if(mcd(e,fn)==ZZ(1))
      break;
  }
  d = mod(eExtendido(e,fn),fn);

  cout<<"  Claves Generadas " <<endl;
	Directorio << " \nClave n: "<< n << "\nClave e: "<< e << endl;
	clave_e << e;
	clave_n << n;
	clavesPrivadas << "p: "<< p <<"\n"<< "q: "<< q <<"\n"<< "n: "<< n <<"\n"<< "fn: "<< fn <<"\n"<< "e: "<< e <<"\n"<< "d: "<< d << endl ;
	clave_p<< p;
	clave_q << q;

  Directorio.close();
  clavesPrivadas.close();
  clave_e.close();
  clave_n.close();
  clave_p.close();
  clave_q.close();
}

void rsa::cifrar()
{
	long long tamBloque = ZZtos(n).size()-1; // tamaño de cada bloque
	cout << " tamBloques: " << tamBloque << endl;

	ll dZZ = to_string(alfabeto.size()-1).size(); // hallamos el tamaño de la letra mas significativa(ultimo elemento) del alfabeto
	cout << "dZZ: "<< dZZ << endl;

	string tPlanoZZstring;
	ll tPlanoZZ;

	string tPlano;// = get_file_contents("Mensaje Plano.txt");
	ifstream Plano;
	Plano.open("Mensaje.txt",ifstream::binary);
	getline(Plano,tPlano);

	long long aux;
	string auxS;

	int i=0;
	for(; i<tPlano.size() ;i++)
	{
		aux = alfabeto.find(tPlano[i]);
		auxS = to_string(aux);
		if ( auxS.size() < dZZ )
		{
			int j=0;
			for (; j< dZZ - auxS.size() ;j++)
				auxS = "0"+auxS;
		}
		cout << auxS << " " ;
		tPlanoZZstring += auxS ;
	}

	int contaux=0;
		while( mod(ZZ(tPlanoZZstring.size()),ZZ(tamBloque)) != 0 )
		{
			contaux++;
			tPlanoZZstring += to_string(alfabeto.size()-1);
		}

	cout << "agregamos "<<alfabeto.size()-1 <<" al final de la cadena "<< contaux <<" veces" << endl;

	cout << "tPlanoZZstring: "<< tPlanoZZstring << endl;
	cout << "tam texto a cifrar: "<<tPlanoZZstring.size()<< endl;


	//   CIFRADO

	ZZ posC=ZZ(0);
	string tmp;
	string tmp2;
	string posCstring="";
	ofstream archPlano;
	archPlano.open("Mensaje Cifrado.txt",std::ifstream::binary);
	ZZ tmpZZ ;
	long long cont ,k=0;
	if( archPlano.is_open())
	{
		for( ; k< tPlanoZZstring.size(); k+=tamBloque)
		{
			cont=0;
			for(long long a=k ; cont<tamBloque; a++)
			{
				tmp+=tPlanoZZstring[a];
				cont++;
			}

			tmpZZ = stoZZ(tmp);
			cout << "cifrar: "<< tmpZZ << endl;
			posC = cLetra(tmp);
			tmp ="";
			posCstring = ZZtos(posC);

			if( posCstring.size() < tamBloque+1 )
			{
				for (int l=0; l<(tamBloque+1)-posCstring.size(); l++ )
					tmp2+="0";

				posCstring = tmp2+posCstring;
				tmp2="";
			}
			cout <<"posCstring: "<<posCstring <<endl;
			archPlano << posCstring;
		}
	}
	else
	{
		cout << "Error: No se pudo crear Cifrado.txt " << endl;
		cout << "No se realizo el Cifrado Satisfactamente "<< endl;
	}
	archPlano.close();
	cout << " Cifrado Satisfactorio "<< endl;
}

ZZ rsa::cLetra(string Plano )
{
	ZZ posPlano = stoZZ(Plano);
	ZZ posC;
	ZZ posP, posF;
	ZZ x,ant=ZZ(1) ;
	ZZ j = ZZ(0);
	ZZ ee = ZZ(e);
	bool aux ;
	while(ee > 0){
		x = expoBits(j);
		aux = ZZtoBool( ee&1 );
		if( aux ){
			posP = exp(posPlano,x,n);
			posF = mod((posP*ant),n);
			ant = posF ;
		}
		j++;
		ee >>=1 ;
	}
	posC = posF;
	return posC;
}

void rsa::descifrar()
{
	cout << "\n\t *****************  Descifrado ************* "<< endl;
	ll nTam = ZZtos(n).size();
	cout << "Tamaño de clave n: "<<nTam << endl;
	int dZZ = to_string(alfabeto.size()-1).size();

	// 					DESCRIFRAMOS
	string tmp,aux1;
	string tDescifradoTmp;
	string tDescifrado;
	ll tDescifradoInt;

	ifstream archCifrado;
	ofstream archDescifrado;
	archCifrado.open("Mensaje Cifrado.txt",ifstream::binary);
	archDescifrado.open("Mensaje Descifrado.txt",ofstream::binary);

	if(archCifrado.is_open() and archDescifrado.is_open())
	{
		getline(archCifrado,tmp);
		cout <<" cadena a descifrar: "<< tmp << endl;
		int i=0;
		long long k,cont;
		for(; i<tmp.size(); i+=nTam)
		{
			cont =0;
			for(k=i; cont<nTam ; k++)
			{
				tDescifradoTmp+=tmp[k];
				cont++;
			}


			aux1 = ZZtos(dLetra(stoZZ(tDescifradoTmp)));
			tDescifradoTmp ="";
			for(int i=aux1.size(); i<nTam-1; i++ )
				tDescifrado += "0";
			tDescifrado += aux1;

		}


		string posD;
		char aux2[dZZ-1];
		int j=0;
		long long aa,cont2;
		for(; j<tDescifrado.size(); j+= dZZ)
		{
			tDescifrado.copy(aux2,dZZ,j);

			posD = alfabeto[stoi(aux2)];
			archDescifrado << posD;
		}
		cout << endl;
	}
	else
		cout << "ERROR: No se pudo abrir el archivo Cifrado.txt "<<endl;

	archCifrado.close();
	archDescifrado.close();
}

ZZ rsa::dLetra(ZZ posDescifrado)
{
	string tDescifrado;
	ZZ posD;
	ZZ posP, posF;
	ZZ x,ant=ZZ(1);
	ZZ j=ZZ(0);

	ZZ dd = d;
	while(dd>0){
		x = expoBits(j);
		if( mod(dd,ZZ(2))==ZZ(1) ){

			posP = resto_chino_G(posDescifrado);//euler_fi_N(posDescifrado,x,n);
			posF = mod((posP*ant),n);
			ant = posF ;
		}
		j++;
		dd >>=1 ;
	}
	posD = posF;
	return posP;
}

ZZ rsa::euler_fi_N(ZZ base , ZZ expo, ZZ modulo)
{
	if(fn == expo){
		return ZZ(1);
	}
	if(expo > fn){
		expo = abs(expo - fn);
		base = exp(base , expo , modulo);
		return base;
	}
	base = exp(base , expo , modulo);
	return base;
}

ZZ rsa::tRestoChino(ZZ posCifrado)
{
	ZZ d= ZZ(mod(eExtendido(e,fn),fn));
	ZZ dp = ZZ(mod(d, p-1));
	ZZ dq = ZZ(mod(d, q-1));

	ZZ P = ZZ(n) ;

	ZZ pi = ZZ(q);
	ZZ qi = ZZ(p);

	ZZ q_1 = get_q_inicial (pi , p);
	ZZ q_2 = get_q_inicial (qi , q);

	ZZ D_i = mod((exp(posCifrado,dp,P) * pi * q_1), P ) + mod( ( exp(posCifrado,dq,P) * qi * q_2),P);
	D_i = ZZ(mod (D_i,P));

	ZZ posD = ZZ(D_i);
	return posD;
}

ZZ rsa::get_q_inicial(ZZ P,ZZ p_or_q)
{
	ZZ q_i = eExtendido(p_or_q , P);
	return q_i;
}


ZZ rsa::resto_chino_G(ZZ zz)
{
  ZZ dp, dq, Dp, Dq, m1, m2;
  ZZ q1, q2, q11, q22;
  ZZ res1, res2, res, r1, r2;
  dp = mod(d,p-1);
  dq = mod(d,q-1);
  m1 = mod(zz,p);
  m2 = mod(zz,q);
  Dp = exp(m1,dp,p);
  Dq = exp(m2,dq,q);
  q1 = Inversa(q,p);
  q11 = mod(q1,p);
  q2 = Inversa(p,q);
  q22 = mod(q2,q);
  r1 = mod(Dp*q,n);
  res1 = mod(r1*q11,n);
  r2 = mod(Dq*p,n);
  res2 = mod(r2*q22,n);
  res = mod(res1+res2,n);
  return res;
}

ZZ rsa::resto_chino(ZZ num)
{
  ZZ dp=mod(d,p-1);
  ZZ dq=mod(d,q-1);
  ZZ a1=exp(mod(num,p),dp,p);
  ZZ a2=exp(mod(num,q),dq,q);
  ZZ p2=Inversa(q,p);
  ZZ q2=Inversa(p,q);
  ZZ a=mod(a1*q*p2,n);
  ZZ b=mod(a2*p*q2,n);
  num=mod(a+b,n);
  return num;
}

ZZ rsa::Inversa(ZZ n1 , ZZ n2 )
{
	ZZ ret = eExtendido(n1 , n2);
	if(ret < 0)
	{
		ret += n2;
	}
	return ret;
}

ZZ rsa::mod(ZZ D, ZZ d)
{
	ZZ q = ZZ(D/d);
	ZZ r = ZZ(D-(q*d));
	if ( r< ZZ(0))
	{
		q--;
		r += d;
	}
	return r;
}


ZZ rsa::exp(ZZ  a, ZZ p, ZZ n)
	{
	ZZ  y;
	y = ZZ(1);
	while (p!=ZZ(0))
	{
      if ((p&1)==1)
		y = mod((y * a) ,n);

      a = mod((a * a),n);
      p = p >> 1;
	}
	return y;
}

ZZ rsa::pow(ZZ a , ZZ b , ZZ MOD)
{
	ZZ x,y;
	x=1 ; y = a;
	while(b>0)
	{
		if(mod(b,ZZ(2)) == 1)
		{
			x = (x *y);
			if(x > MOD)
				x = mod(x,MOD);
		}
		y = (y * y);
		if(y > MOD)
			y = mod(y,MOD);
			b /=2;
	}
	return x;
}


ZZ rsa::modInversa(ZZ a , ZZ m)
{
	return pow(a , m - 2 , m);
}

ZZ rsa::expoBits(ZZ nbits)
{
	ZZ res=ZZ(1);
	ZZ i=ZZ(0);
	for(; i<nbits;i++)
		res <<= 1;
	return res;
}

ZZ rsa::mcd( ZZ a , ZZ b )
{
	ZZ aux = ZZ(1) ;
	ZZ tmp;

	while( mod(a,ZZ(2))==0 and mod(b,ZZ(2))==0 )
	{

		a >>= 1 ;
		b >>= 1 ;
		aux <<= 1 ;
	}

	while ( a != 0 )
	{
		if ( mod(a, ZZ(2)) == 0)
			a >>= 1 ;
		else if ( mod(b, ZZ(2)) == 0 )
			b >>= 1;
		else {
			tmp = abs(a-b);
			tmp >>= 1 ;
			if (a >= b )
				a = tmp;
			else
				b = tmp;
		}
	}
	return aux*b;
}

ZZ rsa::eExtendido(ZZ a ,ZZ b)
{
	ZZ r1 , r2, s1, s2 , t1, t2, r,s,t,q;
	r1=a ; r2=b ; s1 = ZZ(1) ; s2 = ZZ(0)  ; t1 = ZZ(0) ; t2 = ZZ(1) ;

	while( r2> ZZ(0))
	{
		q = r1/r2;
		r = r1 -(q*r2);
		r1 = r2 ; r2 = r ;

		s= s1 -(q*s2);
		s1 = s2 ; s2 = s ;

		t = t1 -(q*t2) ;
		t1 = t2 ; t2 = t ;
	}
	return s1;
}

string rsa::get_file_contents(const char *filename)
{
  ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    return(string( (std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>() ));
  }
}

	//		CONVERSIONES
string rsa::ZZtos(ZZ num)
{
	stringstream conv;
	conv << num;
	return conv.str();
}

ZZ rsa::stoZZ(string num)
{
	ZZ conv(INIT_VAL , num.c_str());
	return conv;
}

bool rsa::ZZtoBool(ZZ number)
{
	stringstream conv;
	conv << number;
	string tmp = conv.str();
	return stoi(tmp);
}
