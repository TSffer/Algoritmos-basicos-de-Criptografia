#include <iostream>
#include <string>
#include "playfair.cpp"

using namespace std;

int main()
{
  Playfair Emisor;
  Emisor.inputInfo();
  Emisor.SortKeyWord();
  Emisor.prepMensaje();
  Emisor.encry_decry();
  Emisor.output();
  return 0;
}
