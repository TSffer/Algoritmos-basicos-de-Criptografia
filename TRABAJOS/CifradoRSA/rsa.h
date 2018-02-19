#ifndef RSA_H
#define RSA_H

#include <iostream>
#include <vector>
#include <string>
#include <NTL/ZZ.h>
using namespace std;
using namespace NTL;

typedef long long int ll;

class rsa
{
	private:
		ZZ p;
		ZZ q;
		ZZ n;
		ZZ fn;
		ZZ d;
		ZZ e;
	public:
		string alfabeto ="0123456789,abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ-.";

		long long   size = alfabeto.size();
		rsa(int nbits);
		rsa(ZZ nn, ZZ ee);
		rsa(ZZ pp, ZZ qq,ZZ ee);

		void generarClaves(int nbits);

    void cifrar();
		ZZ cLetra(string posPlano);

		void descifrar();
		ZZ dLetra(ZZ cifrado);

		ZZ MultMod(ZZ a,ZZ b,ZZ c);

		bool find(vector<ll>& lista,ll inicio,ll fin,ll& elemento);

		ZZ tRestoChino(ZZ posCifrado);
		ZZ get_q_inicial(ZZ P, ZZ p_or_q);

		ZZ mod(ZZ a , ZZ b );
		ZZ exp(ZZ a , ZZ b, ZZ m);
		ZZ pow(ZZ a , ZZ b,  ZZ MOD );
		ZZ modInversa(ZZ a, ZZ m);

		vector<ll> cribaEratostenes(ll inicio, ll final);

		bool millerRabin(ZZ n);
		bool fermat(ZZ n);
		ZZ expoBits(ZZ nbits);
		ZZ mcd(ZZ a,ZZ b);
		ZZ eExtendido(ZZ a,ZZ b);
		ZZ Inversa(ZZ , ZZ);
		ZZ euler_fi_N(ZZ , ZZ , ZZ);

		string get_file_contents(const char* filename);

			/*		CONVERSIONESS 		*/
		string ZZtos(ZZ num);
		ZZ stoZZ(string str);
		bool ZZtoBool(ZZ number);

		string convertirRellenarCeros(string cadenaString);
		string rellenarCeros(string cadena,long long cantidad);

		ZZ NumeroAleatorio(int);

    ZZ resto_chino_G(ZZ zz);
    ZZ resto_chino(ZZ num);

};

#endif
