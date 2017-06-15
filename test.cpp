
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
	for (int i = 0; i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			if (j < columnas-1)
			{
				peaje = costo(matriz[i][j]);
				ady[i*columnas+j+1][i*columnas+j] = peaje;
				peaje = costo(matriz[i][j+1]);
				ady[i*columnas+j][i*columnas+j+1] = peaje;
			}
			if (i < filas-1)
			{
				peaje = costo(matriz[i][j]);
				ady[(i+1)*columnas+j][i*columnas+j] = peaje;
				peaje = costo(matriz[i+1][j]);
				ady[i*columnas+j][(i+1)*columnas+j] = peaje;
			}			
		}
	}
}


void floyd(int n, int matrizbarata[][100*100],int matrizcamino[][100*100], int ady[][100*100])
{	int i,j,k;
	for(i=0; i<n; i++)
   		for(j=0; j<n; j++)
      		if(i==j)	matrizbarata[i][i]=0;
				else	matrizbarata[i][j]=ady[i][j];
			for(k=0; k<n; k++)
			{	for(i=0; i<n; i++)
         			for(j=0; j<n; j++)
            			if((matrizbarata[i][k]+matrizbarata[k][j])<matrizbarata[i][j])
            			{
            				matrizbarata[i][j]=matrizbarata[i][k]+matrizbarata[k][j];
            				matrizcamino[i][j]=k;
            			}
			}
}

int main()
{
	int filas,columnas;
	cin >> filas >> columnas;
	char matriz[filas][100];
	int ady[filas*columnas][10000];
	int matrizbarata[filas*columnas][10000];
	int matrizcamino[filas*columnas][10000];




	for (int i = 0; i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			matrizcamino[i][j]=j;
		}
	}




	for (int i = 0; i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			cin >> matriz[i][j];
		}
	}
	for (int i = 0; i < filas*columnas; i++)
	{
		for (int j = 0; j < filas*columnas; j++)
		{
			ady[i][j]=100000;
			if (i == j)
			{
				ady[i][j] = 0;
			}
		}
	}
	pasar_m_ady(matriz,filas,columnas,ady);
	for (int i = 0; i < filas*columnas; i++)
	{
		for (int j = 0; j < filas*columnas; j++)
		{
			cout << matrizcamino[i][j]<<" ";
		}
	}
		
	floyd(filas*columnas,matrizbarata,matrizcamino, ady);
	for (int i = 0; i < filas*columnas; i++)
	{
		for (int j = 0; j < filas*columnas; j++)
		{
			cout << matrizbarata[i][j]<<" ";
		}
		cout << endl;
	}
	for (int i = 0; i < filas*columnas; i++)
	{
		for (int j = 0; j < filas*columnas; j++)
		{
			cout << matrizcamino[i][j]<<" ";
		}
		cout << endl;
	}
	return 0;
}