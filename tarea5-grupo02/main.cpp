#include <iostream>
#include "funciones.h"

using namespace std;

int main()
{
	//Variables de las dimensiones de la matriz.
	int filas,columnas;
	cin >> filas >> columnas;

	//Variables para almacenar el numero de dato que es el bot y la mantequilla.
	int bot,mantequilla;
	int contador = 0;

	//Tablero.
	char matriz[filas][100];
	//Matriz de adyacencia/costos, luego de aplicar el algoritmo de floyd almacenara los costes de los caminos mas baratos.
	int ady[filas*columnas][10000];
	//Matriz que almacenara los indices de los predecesores de cada casilla (almacena el predecesor por el cual es mas barato llegar).
	int matrizcamino[filas*columnas][10000];

	//Definimos la segunda dimension de los arreglos como el valor maximo que podian llegar a tener
	//debido a que, de otra forma, no podiamos pasarlas como parametro a las funciones.

	//Agregamos los valores al tablero.
	for (int i = 0; i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			cin >> matriz[i][j];
			//En el caso de que sea el bot igualamos su valor al contador.
			if ( matriz[i][j] =='b')
			{
				bot = contador;
			}
			//Realizamos lo mismo si es la mantequilla.
			if (matriz[i][j] == 'm')
			{
				mantequilla = contador;
			}
			contador++;
		}
	}

	//Rellenamos la matriz de adyacencia, en un principio, con valores muy grandes
	//con excepcion de la diagonal principal, ya que corresponde al costo de moverse
	//de una casilla a ella misma, y dado que eso no ocurrira, su coste es 0.
	for (int i = 0; i < filas*columnas; i++)
	{
		for (int j = 0; j < filas*columnas; j++)
		{
			//Se agrega el valor.
			ady[i][j]=200000;
			//En caso de estar en la diagonal, es 0.
			if (i == j)
			{
				ady[i][j] = 0;
			}
		}
	}

	//Se llama a la funcion para cambiar los valores de la matriz de adyacencia.
	pasar_m_ady(matriz, filas, columnas, ady);
	
	//Llamamos a la funcion que ejecuta el algoritmo de floyd en la matriz de adyacencia junto con la matriz camino.
	floyd(filas*columnas, matrizcamino, ady);

	//Una vez listas las matrices, podemos obtener el coste de llegar desde el bot a la mantequilla.
	cout << ady[bot][mantequilla] << endl;

	//Se llama a la funcion que modificara el tablero en funcion de los resultados obtenidos en la matriz camino.
	modificar_matriz(filas, columnas, bot, mantequilla, matriz, matrizcamino);

	//Finalmente se imprime la nueva matriz.
	for (int i = 0; i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}