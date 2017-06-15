
#include <cstdlib>
#include <iostream>
#include <queue>

using namespace std;

int costo(char caracter)
{
	if (caracter == 'b')
	{
		return 1;
	}
	if (caracter == 'm')
	{
		return 1;
	}
	if (caracter == '.')
	{
		return 1;
	}
	if (caracter == 'o')
	{
		return 5;
	}
	if (caracter == 'O')
	{
		return 15;
	}
	if (caracter == '0')
	{
		return 15;
	}
	if (caracter == 'x')
	{
		return 100000; //Debido a que no se puede pasar por aqui
	}
	return 0;
}

void pasar_m_ady(char matriz[][100],int filas,int columnas, int ady[][100*100])
{
	int peaje;
	int nodos = filas*columnas;
	for (int i = 0; i < nodos; i++)
	{
		for (int j = 0; j < nodos; j++)
		{
			ady[i][j]=100000;
		}
	}
	for (int i = 0; i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			if (j < columnas-1)
			{
				peaje = costo(matriz[i][j]);
				ady[i*filas+j+1][j+i*columnas] = peaje;
				peaje = costo(matriz[i][j+1]);
				ady[j+i*columnas][i*filas+j+1] = peaje;
			}
			if (i < filas-1)
			{
				peaje = costo(matriz[i][j]);
				ady[i*filas+j+1+columnas-1][j+i*columnas] = peaje;
				peaje = costo(matriz[i+1][j]);
				ady[j+i*columnas][i*filas+j+1+columnas-1] = peaje;
			}
			
		}
	}
}

int main()
{
	int filas,columnas;
	cin >> filas >> columnas;
	char matriz[filas][100];
	for (int i = 0; i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			cin >> matriz[i][j];
		}
	}
	int ady[filas*columnas][10000];
	for (int i = 0; i < filas*columnas; i++)
	{
		for (int j = 0; j < filas*columnas; j++)
		{
			ady[i][j]=100000;
		}
	}
	pasar_m_ady(matriz,filas,columnas,ady);
	for (int i = 0; i < filas*columnas; i++)
	{
		for (int j = 0; j < filas*columnas; j++)
		{
			cout << ady[i][j]<<" ";
		}
		cout << endl;
	}
}