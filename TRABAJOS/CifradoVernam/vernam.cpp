#include  "vernam.h"
#include <string>
#include <bitset>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstddef>
#include <fstream>

using namespace std;
string controlChar[128] = {"NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL", "BS", "TAB",
"LF", "VT", "FF", "CR", "SO", "SI", "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB", "CAN",
"EM", "SUB", "ESC", "FS", "GS", "RS", "US"};

Vernam::Vernam()
{
  cipherkey = "1011011";
}

void Vernam::decrypt(controller chr[], int size){

    bitset<7> finalBit[size];
    bitset<7> e;
    string final;
    for (int i = 0; i < size; i++)
    {
      finalBit[i] = chr[i].get_binary();
      cout  << finalBit[i] << endl;

      e = finalBit[i];
      for (int j = 0; j < sizeof(finalBit[i]); j++)
      {

          if (cipherkey[j] == '1' && e.test(j) == true)
          {
            e[j] = false;
          }

          else if (cipherkey[j] == '1' && e.test(j) == false)
          {
            e[j] = true;
          }

          else if (cipherkey[j] == '0' && e.test(j) == true)
          {
            e[j] = true;
          }

          else
          {
            continue;
          }

      }
      finalBit[i] = e;
      unsigned char r = finalBit[i].to_ulong();
      cout << "Convertido en ascii char " << r << " De bitset " << finalBit[i] << endl;
      final += r;
    }

    cout << "CADENA FINAL! " << final << endl;
    ofstream myfile;
    myfile.open ("plain.txt");
    myfile << final << endl;
    myfile.close();
}

void Vernam::readFromFile()
{
  ifstream infile;
  infile.open("cipher.txt");
  int numlines = 0;
  string line;
  while (std::getline(infile, line))
  ++numlines;

  infile.close();
  infile.open("cipher.txt");

  string str;
  controller readControl[numlines];
  int index = 0;
  while (getline(infile, str) && index < numlines - 1)
  {
    bitset<7> newB = bitset<7>(str);
    readControl[index].set_bin(newB);
    cout << readControl[index].get_binary() << endl;
    index++;
  }
  infile.close();
  decrypt(readControl, numlines - 1);
}

void Vernam::convertToString(bitset<7> bit[], int size)
{
  string final;
  unsigned char d;
  string control;
  controller controls[size];

  ofstream myfile;
  myfile.open ("cipher.txt");

  for (int i = 0; i < size; i++)
  {

    myfile << bit[i] << endl;
    long t = bit[i].to_ulong();
    if (iscntrl(t)){
      cout << "CONTROL CHAR DETECTEDO" << endl;
      if (t < 32)
      {

          control = controlChar[t];
          final += control;
          controls[i].set_string(control);
          controls[i].set_bin(bit[i]);
          //controls[i] = c;
          cout << "Sustituyendo cadena " << controls[i].get_string() <<" Para el carácter de control con el valor ascii "  << t << endl;
          continue;
      }
      else
      {
        control = "DEL";
        final += control;
        controls[i].set_string(control);
        controls[i].set_bin(bit[i]);
        //controls[i] = c;
        cout << "Sustituyendo la cadena " << controls[i].get_string() <<" Para el carácter de control con el valor ascii "  << t << endl;
        continue;
      }
    }
    d = bit[i].to_ulong();
    controls[i].set_bin(bit[i]);
    controls[i].set_char(d);
    cout << "BIT EN ASCII " << d << endl;
    final += d;
  }

  cout << "CADENA FINAL EN EL ARCHIVO " << final << endl;
  myfile << "Texto Cifrado: " << final << endl;
  myfile.close();

  cmd:
  string decryptAns = "";
  cout << "Quieres descifrar (si/no)" << endl;
  getline(cin, decryptAns);

  if (decryptAns == "si")
  {
      decrypt(controls, size);
  }
  else if (decryptAns == "no")
  {
      exit(0);
  }
  else {
      goto cmd;
  }
}

void Vernam::operationXOR(bitset<7>  bit[], int size){

  bitset<7> currBitset;
  for (size_t i = 0; i < size; i++){

      currBitset = bit[i];
      for (int j = 0; j < sizeof(bit[i]); j++){



          if (cipherkey[j] == '1' && currBitset.test(j) == true)
          {
            currBitset[j] = false;
          }

          else if (cipherkey[j] == '1' && currBitset.test(j) == false)
          {
            currBitset[j] = true;
          }

          else if (cipherkey[j] == '0' && currBitset.test(j) == true)
          {
            currBitset[j] = true;
          }

          else
          {
            continue;
          }

      }
      cout << bit[i] << "Aplicando XOR " << currBitset << endl;
      bit[i] = currBitset;
  }

  convertToString(bit, size);
}



string Vernam::convertToBinary(string plaintext)
{

  int n = plaintext.size();

  bitset<7>  bit[n];
  for (size_t i = 0; i < n; ++i)
  {
    bit[i] = bitset<7>(plaintext[i]);
    cout << "Bit de bits original " << bit[i] << " Convertido de ascii char " << plaintext[i] << endl;
  }
  operationXOR(bit, n);
  return "";
}
