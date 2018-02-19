#include "playfair.h"
#include <string>
#include <cctype>

using namespace std;

Playfair::Playfair()
{

}

string Playfair::getKeyWord()
{
  return key;
}

string Playfair::getMensaje()
{
  return mensaje;
}

bool Playfair::getMethod()
{
  return d_e;
}

string Playfair::getCipher()
{
  return cipher;
}

void Playfair::setKey(string k)
{
  key = k;
}

void Playfair::setMensaje(string m)
{
  mensaje = m;
}

void Playfair::setMethod(bool de)
{
  d_e = de;
}

void Playfair::setCipher(string c)
{
  cipher = c;
}

void Playfair::inputInfo()
{
  string keyford_e;
  string mensajefor_e;
  bool dec_enc;
  cout<<"Ingrese la clave: ";
  getline(cin,keyford_e);

  cout<<"Ingrese el mensaje a encriptar - desencriptar: ";
  getline(cin,mensajefor_e);

  cout<<"Ingrese 0 para encriptar o 1 para desencriptar: ";
  cin>>dec_enc;

  setKey(keyford_e);
  setMensaje(mensajefor_e);
  setMethod(dec_enc);
}

void Playfair::SortKeyWord()
{
  int i=0;
  string alpha = "abcdefghijklmnopqrstuvwxyz ";
  for(int i = 0;i<key.size();i++)
  {
    if(key[i] == ' ')
      key.erase(i,1);
  }
  key.append(alpha);

  for(int i=0;i<key.size();i++)
  {
    for(int j = i+1;j<key.size();j++)
    {
      if(key[i]==key[j])
        key.erase(j,1);
    }
  }

  for(int i =0;i<key.size();i++)
  {
    if(key[i]=='j')
      key.erase(i,1);
  }
  for(int r=0;r<5;r++)
  {
    for(int c =0;c<5;c++)
    {
      keyword[r][c] = key[i];
      i++;
    }
  }
}

void Playfair::prepMensaje()
{
  string mes;
  char filler;
  int testfillq = 0;
  int testfillx = 0;
  int testfillz = 0;

  for(int i=0;i<mensaje.size();i++)
  {
    if(mensaje[i] == ' ')
      mensaje.erase(i,1);
  }

  for(int i = 0;i<mensaje.size();i++)
  {
    if(mensaje[i]=='q')
      testfillq = 1;
    if(mensaje[i]=='x')
      testfillx = 1;
    if(mensaje[i]=='z')
      testfillz = 1;
  }
  if(testfillx ==0)
    filler = 'x';
  else if(testfillz ==0)
    filler = 'z';
  else if(testfillq ==0)
    filler = 'q';
  for(int i=0;i<mensaje.size();i+=2)
  {
    mes+=mensaje[i];
    if(i+1<mensaje.size())
    {
      if(mensaje[i]==mensaje[i+1])
      {
        mes+=filler;
      }
      mes+=mensaje[i+1];
    }
  }
    if(mes.size()%2==1)
      mes+=filler;
    mensaje = mes;
}

char Playfair::getChar(int row , int column)
{
  return keyword[(row + 5)%5][(column + 5)%5];
}

void Playfair::getCharPos(char ch,int &row,int &col)
{
  for(int i = 0;i<5;i++)
  {
    for(int j =0;j<5;j++)
    {
      if(keyword[i][j] == ch)
      {
        row = i;
        col = j;
      }
    }
  }
}

void Playfair::encry_decry()
{
  int row1 = 0, col1 = 0,row2 = 0,col2 = 0;
  int h = 0;
  int direccion;
  if(!d_e)
    direccion = 1;
  if(d_e)
    direccion = -1;

  for(h = 0;h<mensaje.size();h+=2)
  {
    getCharPos(mensaje[h],row1,col1);
    getCharPos(mensaje[h+1],row2,col2);

    if(row1 == row2)
    {
      cipher += getChar(row1,col1+direccion);
      cipher += getChar(row2,col2+direccion);
    }
    else if(col1 == col2)
    {
      cipher +=getChar(row1+direccion,col1);
      cipher +=getChar(row2+direccion,col1);
    }
    else
    {
      cipher += getChar(row1,col2);
      cipher += getChar(row2,col1);
    }
  }
}

void Playfair::output()
{
  if(!d_e)
  {
    for(int i =0;i<cipher.size();i+=3)
      cipher.insert(i," ");
    cout<<"El texto encriptardo es: "<<endl;

    for(int i=0; i<cipher.size();i++)
      cout<<static_cast<char>(toupper(cipher[i]));
  }
  if(d_e)
  {
    for(int i =0;i<cipher.size();i++)
    {
      if(cipher.find(i)=='x')
      cipher[i]+=' ';
    }
    cout<<"El texto descifardo es: "<<endl;
    cout<<cipher<<endl;
  }
}
