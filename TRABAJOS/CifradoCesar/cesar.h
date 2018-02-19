#ifndef CESAR_H
#define CESAR_H
#include <string>
using namespace std;

class cesar
{
  private:
    int clave;
    string Alfabeto;
  public:
    cesar(int);
    string Cifrar(string);
    string Descifrar(string);
    ~cesar();
};

#endif
