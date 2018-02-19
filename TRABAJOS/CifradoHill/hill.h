#ifndef HILL_H
#define HILL_H

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <iomanip>
#include <cmath>

using namespace std;

class Hill
{
  private:
    int SIZE;
  public:
    Hill();
    void inputMessage(string& message, int& length);
    void standardizeMessage(int length, int& columns, string& message);
    void characterMatrix(vector<vector<char> >& char_matrix, string message, int columns);
    void integerMatrix(vector<vector<double> >& int_matrix, string message, int columns);
    void encodingMatrix(double encoder[][3], int size);
    void encryptMatrix(vector<vector<double> >& resultantMatrix, vector<vector<double> >& startingMatrix, double coder[][3], int size, int columns);
    void decodingMatrix(double decoder[][3], double encoder[][3], int size);
    vector<vector<int> > decryptMatrix(vector<vector<double> >& resultantMatrix, vector<vector<double> > startingMatrix, double coder[][3], int size, int columns);
    void finalMessage(vector<vector<int> > int_matrix, vector<vector<char> > char_matrix, int size, int columns);
    void Operar();
};

#endif
