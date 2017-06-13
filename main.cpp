
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
		return 8953; //Debido a que no se puede pasar por aqui
	}
}


int pasar_a_matriz_ady(char arreglo[][], filas, columnas)
{
	//Primero identificamos cuantos caracteres distintos de 'x' posee la matriz para saber el tamaño de esta
	int contador = 0;
	for (int i = 0; i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			if (arreglo[i][j] != 'x')
			{
				contador++;
			}
		}
	}
	//Una vez hecho esto procedemos a crear la matriz
	int matriz_ady[contador][contador];
	//Ahora debe ser rellenada

}

encontrar

int main()
{
	int filas, columnas;
	cin >> filas >> columnas;
	char matriz[filas][columnas];
	for (int i = 0; i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			cin >> matriz[i][j];
		}
	}
	matriz_ady=pasar_a_matriz_ady(matriz, filas, columnas)
	return 0;
}