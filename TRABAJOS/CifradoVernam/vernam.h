#ifndef VERNAM_H
#define VERNAM_H
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

class controller
{
  private:

   string controlField;
   char ascii;
   bitset<7> binary;

  public:

   void set_char(char newChar)
   {
    ascii = newChar;
   }
   void set_string(string field)
  {
    controlField = field;
  }
  void set_bin(bitset<7> bit)
  {
      binary = bit;
  }
  string get_string()
  {
    return controlField;
  }
  char get_char()
  {
    return ascii;
  }
  bitset<7> get_binary()
  {
     return binary;
  }
};

class Vernam
{
  private:
    string cipherkey;
  public:
    Vernam();
    void decrypt(controller chr[],int size);
    void readFromFile();
    void convertToString(bitset<7> bit[],int size);
    void operationXOR(bitset<7> bit[],int size);
    string convertToBinary(string plaintext);


};
#endif
