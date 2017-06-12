#include <iostream>

using namespace std;

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
	return 0;
}