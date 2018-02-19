#ifndef PLAYFAIR_H
#define PLAYFAIR_H
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class Playfair
{
  private:
    string key;
    string mensaje;
    bool d_e;
    char keyword[5][5] = {};
    string cipher;
  public:
    Playfair();
    string getKeyWord();
    string getMensaje();
    bool getMethod();

    string getCipher();
    void setKey(string);
    void setMensaje(string);
    void setMethod(bool);
    void setCipher(string);

    void inputInfo();
    void SortKeyWord();
    void prepMensaje();

    char getChar(int,int);
    void getCharPos(char,int &,int &);
    void  encry_decry();
    void output();
};
#endif
