#include "hill.h"
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <iomanip>
#include <cmath>

Hill::Hill()
{
  SIZE = 3;
}

void Hill::inputMessage(string& message, int& length)
{
	cout << "Escriba su mensaje para codificar:\n";
	getline(cin, message);
	length = message.length();
	cout << endl;
}


void Hill::standardizeMessage(int length, int& columns, string& message)
{
	columns = length/3;
	if (length % 3 > 0)
	{
		columns++;
		int extra = 3 - (length % 3);
		for (int i=0; i < extra; i++)
			message += " ";
	}
}


void Hill::characterMatrix(vector<vector<char> >& char_matrix, string message, int columns)
{
	cout << "Matriz de texto sin formato:\n";
	int count=0;
	for (int col=0; col < columns; col++)
	{
		for (int row=0; row < 3; row++)
		{
			char_matrix[row][col] = message[count];
			count++;
		}
	}
	for (int row=0; row < 3; row++)
	{
		cout << "[";
		for (int col=0; col < columns; col++)
			cout << setw(2) << char_matrix[row][col];
		cout << " ]" << endl;
	}
	cout << "\n\n";
}

void Hill::integerMatrix(vector<vector<double> >& int_matrix, string message, int columns)
{
	cout << "Matriz de texto sin formato convertido en un número Matriz:\n";
	int count=0;
	for (int col=0; col < columns; col++)
	{
		for (int row=0; row < 3; row++)
		{
			int number = static_cast<int>(message[count]);
			number = static_cast<double>(number);
			int_matrix[row][col] = number;
			count++;
		}
	}
	for (int row=0; row < 3; row++)
	{
		cout << "[";
		for (int col=0; col < columns; col++)
			cout << setw(4) << int_matrix[row][col];
		cout << " ]" << endl;
	}
	cout << "\n\n";
}

void Hill::encodingMatrix(double encoder[][3], int size)
{
	cout << "Cifrado (matriz de codificación):\n";
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
		{
			int temp = rand() % 10;
			encoder[i][j] = static_cast<double>(temp);
		}
	}

	for (int row=0; row < size; row++)
	{
		cout << "[";
		for (int col=0; col < size; col++)
			cout << setw(2) << encoder[row][col];
		cout << " ]" << endl;
	}
	cout << "\n\n";
}


void Hill::encryptMatrix(vector<vector<double> >& resultantMatrix, vector<vector<double> >& startingMatrix, double coder[][3], int size, int columns)
{
	for (int row=0; row < size; row++)
	{
		for (int col=0; col < columns; col++)
			resultantMatrix[row][col] = (coder[row][0] * startingMatrix[0][col]) + (coder[row][1] * startingMatrix[1][col]) + (coder[row][2] * startingMatrix[2][col]);
	}
	cout << " Cifrado de Texto Patrón Completo:\n";
	for (int row=0; row < 3; row++)
	{
		cout << "[";
		for (int col=0; col < columns; col++)
			cout << setw(5) << resultantMatrix[row][col];
		cout << " ]" << endl;
	}
	cout << "\n\n";

	for (int row=0; row < 3; row++)
	{
		for (int col=0; col < columns; col++)
			startingMatrix[row][col]=0;
	}
}

void Hill::decodingMatrix(double decoder[][3], double encoder[][3], int size)
{
	double identity[3][3]={1.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,1.0};

	for (int step=0; step < size; step++)
	{
		if (encoder[0+step][0+step] == 0)
		{
			for (int row=(1+step); row < size; row++)
			{
				if (encoder[row][0+step] != 0)
				{
					for (int col=0; col < size; col++)
					{
						double temp = encoder[row][col];
						encoder[row][col] = encoder[0+step][col];
						encoder[0+step][col] = temp;

						temp = identity[row][col];
						identity[row][col] = identity[0+step][col];
						identity[0+step][col] = temp;
					}
					break;
				}
			}
		}
		if (encoder[0+step][0+step] != 1)
		{
			double scalar = encoder[0+step][0+step];
			for (int col=0; col < size; col++)
			{
				encoder[0+step][col] = encoder[0+step][col] / scalar;
				identity[0+step][col] = identity[0+step][col] / scalar;
			}
		}
		for (int row=(1+step); row < size; row++)
		{
			if (encoder[row][0+step] != 0)
			{
				double scalar = encoder[row][0+step];
				for (int col=0; col < size; col++)
				{
					encoder[row][col] += (-(scalar))*(encoder[0+step][col]);
					identity[row][col] += (-(scalar))*(identity[0+step][col]);
				}
			}
		}
	}

	for (int step = 1; step < size; step++)
	{
		for (int row=(size-(step+1)); row >= 0; row--)
		{
			if (encoder[row][size-step] != 0)
			{
				double scalar = encoder[row][size-step];
				for (int col=0; col < size; col++)
				{
					encoder[row][col] += (-(scalar))*(encoder[size-step][col]);
					identity[row][col] += (-(scalar))*(identity[size-step][col]);
				}
			}
		}
	}


	for (int row=0; row < size; row++)
	{
		for (int col=0; col < size; col++)
			decoder[row][col] = identity[row][col];
	}

	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(1);

	cout << "Encontrando Inverso de Cifrado...\n";
	cin.get();

	cout << "\nEstado final de la matriz de cifrado (la Identidad):\n";
	for (int row=0; row < size; row++)
	{
		cout.precision(2);
		cout << "[";
		for (int col=0; col < size; col++)
		{
			if (encoder[row][col]==-0)
				encoder[row][col] = 0;
			cout << setw(6) << encoder[row][col];
		}
		cout << "  ]" << endl;
	}
	cout << "\n\n";

	cout << "\nClave de descifrado - Estado final de la matriz del decodificador (el inverso del codificador):\n";
	for (int row=0; row < size; row++)
	{
		cout << "[";
		for (int col=0; col < size; col++)
			cout << setw(6) << decoder[row][col];
		cout << "  ]" << endl;
	}
	cout << "\n\n";
}

vector <vector<int> > Hill::decryptMatrix(vector<vector<double> >& resultantMatrix, vector<vector<double> > startingMatrix, double coder[][3], int size, int columns)
{
	vector <vector<int> > temp_int_Matrix(3, vector<int>(columns));
	for (int row=0; row < size; row++)
	{
		for (int col=0; col < columns; col++)
			resultantMatrix[row][col] = (coder[row][0] * startingMatrix[0][col]) + (coder[row][1] * startingMatrix[1][col]) + (coder[row][2] * startingMatrix[2][col]);
	}

	for (int col=0; col < columns; col++)
	{
		for (int row=0; row < 3; row++)
		{
			if (ceil(resultantMatrix[row][col]) - resultantMatrix[row][col] < 0.1)
				resultantMatrix[row][col] = ceil(resultantMatrix[row][col]);

			temp_int_Matrix[row][col] = static_cast<int>(resultantMatrix[row][col]);
		}
	}

	cout << "Descifrado Patrón completo:\n";
	for (int row=0; row < 3; row++)
	{
		cout << "[";
		for (int col=0; col < columns; col++)
			cout << setw(4) << temp_int_Matrix[row][col];
		cout << " ]" << endl;
	}
	cout << "\n\n";

	return temp_int_Matrix;
}

void Hill::finalMessage(vector<vector<int> > int_matrix, vector<vector<char> > char_matrix, int size, int columns)
{
	string decodedMessage;
	int count=0;

	for (int col=0; col < columns; col++)
	{
		for (int row=0; row < size; row++)
		{
			char letter = static_cast<char>(int_matrix[row][col]);
			char_matrix[row][col] = letter;
			decodedMessage += char_matrix[row][col];
			count++;
		}
	}

	cout << "Matriz de texto sin formato descifrado:\n";
	for (int row=0; row < 3; row++)
	{
		cout << "[";
		for (int col=0; col < columns; col++)
			cout << setw(2) << char_matrix[row][col];
		cout << " ]" << endl;
	}
	cout << "\n\n";
	cout << "Mensaje descodificado:\n\n" << decodedMessage << "\n\n";
}
void Hill::Operar()
{
  srand(time(0));
	string message;
	int length, columns;
	double encoder[3][3];
	double decoder[3][3];

	inputMessage(message, length);
	standardizeMessage(length, columns, message);
	vector <vector<char> > char_matrix(3, vector<char>(columns));
	vector <vector<double> > int_matrix(3, vector<double>(columns));

	characterMatrix(char_matrix, message, columns);
	integerMatrix(int_matrix, message, columns);
	cin.get();
	encodingMatrix(encoder, SIZE);
	cin.get();

	vector <vector<double> > secrets(3, vector<double>(columns));

	encryptMatrix(secrets, int_matrix, encoder, 3, columns);
	cin.get();
	decodingMatrix(decoder, encoder, 3);
	cin.get();

	vector <vector<int> > final_int_matrix(3, vector<int>(columns));
	vector <vector<char> > final_char_matrix(3, vector<char>(columns));

	final_int_matrix = decryptMatrix(int_matrix, secrets, decoder, SIZE, columns);
	finalMessage(final_int_matrix, final_char_matrix, 3, columns);

}
