//	Universidad Tecnica Federico Santa Maria
//	Departamento de Informatica
//	Prof. Hubert Hoffmann N.
//	ILI-134 Estructura de Datos
//	Grafos: Algoritmo de Floyd

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <sys/stat.h>

using namespace std;

const int N=10;

ofstream resultados("g-floyd-out.txt");

int a[N][N], c[N][N], mini[N][N], ex[N];

bool existeArchivo(string nombreArchivo)
{	struct stat stArchivoInfo;
	if(stat(nombreArchivo.c_str(),&stArchivoInfo))
	{	cout << "No se puede abrir el archivo g-floyd-in.txt" << endl;
		exit(0);
	}
	return true;
}

void escribaMatriz(int n, int a[N][N])
{	for(int i=0; i<n; i++)
   	{	for(int j=0; j<n; j++)
      		resultados << setw(4) << a[i][j];
       	resultados << endl;
      }
}

void floyd(int n, int a[N][N], int c[N][N])
{	int i,j,k;
	for(i=0; i<n; i++)
   		for(j=0; j<n; j++)
      		if(i==j)	a[i][i]=0;
				else	a[i][j]=c[i][j];
			for(k=0; k<n; k++)
			{	for(i=0; i<n; i++)
         			for(j=0; j<n; j++)
            			if((a[i][k]+a[k][j])<a[i][j]) a[i][j]=a[i][k]+a[k][j];
				resultados << "Matriz " << k+1 << endl;
				escribaMatriz(n,a);
         		resultados << endl;
			}
}

int main(void)
{	int i, i1, i2, n, minEx, centro;
	existeArchivo("g-floyd-in.txt");
	ifstream datos("g-floyd-in.txt");
	datos >> n;
	for(i=0; i<n; i++)
   		for(int j=0; j<n; j++)
      		if(i==j)	c[i][i]=0;
			else		c[i][j]=999;
		while(datos)
		{	datos >> i1 >> i2;
      		datos >> c[i1-1][i2-1];
		}
	resultados << "Matriz de Costos" << endl;
	escribaMatriz(n,c);
    resultados << endl;

	floyd(n, mini, c);

	for(int j=0; j<n; j++)
	{	ex[j] = mini[0][j];
		for(i=1; i<n; i++)
      		if(ex[j] < mini[i][j]) ex[j] = mini[i][j];
	}

	resultados << "Excentricidades:" << endl;
	for(i=0; i<n; i++)
   		resultados << setw(4) << ex[i];
    	resultados << endl;
		minEx = ex[0];
     	centro = 0;

	for(i=0; i<n; i++)
		if(minEx>ex[i]) {centro=i; minEx=ex[i];}

	resultados << endl <<"Centro es el nodo con la minima excentricidad: nodo " << centro+1;
	cout << "Ver los resultados en el archivo floyd-out.txt" << endl << endl;

	resultados.close();
	datos.close();
}