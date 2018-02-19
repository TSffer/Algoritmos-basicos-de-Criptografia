#include <iostream>
#include <string>
#include "vernam.cpp"

using namespace std;

int main(){

    string answer = "";
    Vernam Emisor;
    cout << "Encriptar/Desencriptar" << endl;
    getline(cin, answer);
    if (answer == "Encriptar") {
          cout << "Encriptar!" << endl;
          string input = "";
      	  cout<<"Ingrese el mensaje"<<endl;
          getline(cin, input);
          cout<<"Ingreso " << input << endl;
          Emisor.convertToBinary(input);
          return 0;
    }

    else if (answer == "Desencriptar"){
      string input = "";
      Emisor.readFromFile();
      return 0;

    }



    else {
      cout << "Ingrese un comando valido (Encriptar/Desencriptar)" << endl;
      exit(0);
    }
}
