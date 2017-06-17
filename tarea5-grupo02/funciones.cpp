#include <iostream>
#include "funciones.h"

using namespace std;

//Funcion para calcular el costo de avanzar esa casilla.
int costo(char caracter)
{
	//Recibe el caracter y dependiendo de este devuelve valor.
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
		//Debido a que no se puede pasar por aqui elegimos un valor muy grande para el costo de este camino.
		return 200000;
	}
	return 0;
}

//Recibe un trablero y genera la matriz de adyacencia de este.
void pasar_m_ady(char matriz[][100],int filas,int columnas, int ady[][10000])
{
	//Variable que almacenara el costo de moverse hacia aqui.
	int peaje;
	//Recorremos el arreglo.
	//Dado que es un tablero, iremos agregando los datos a la matriz de adyacencia,
	//mirando la casilla derecha y la que esta debajo de la cual estamos actualmente.
	for (int i = 0; i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			//Si aun tiene casillas a su lado derecho.
			if (j < columnas-1)
			{
				//Calculamos el costo de ir a la casilla en la que estamos.
				peaje = costo(matriz[i][j]);
				//Ahora debemos añadir el costo a la casilla correspondiente en la matriz de adyacencia.
				//La posicion de la casilla actual del tablero corresponde a i*columnas+j
				//mientras que la posicion de la casilla a su derecha corresponde a i*columnas+j+1.
				//Asignamos su costo a la casilla correspondiente
				ady[i*columnas+j+1][i*columnas+j] = peaje;
				//Ahora calculamos el costo de ir a la casilla a su derecha.
				peaje = costo(matriz[i][j+1]);
				//Le asignamos el costo en la casilla que corresponde en la matriz de adyacencia.
				ady[i*columnas+j][i*columnas+j+1] = peaje;
			}
			//Si aun tiene casillas debajo.
			if (i < filas-1)
			{
				//Calculamos el costo de ir a la casilla en la que estamos.
				peaje = costo(matriz[i][j]);
				//La posicion de la casilla actual en la matriz de adyacencia esta dada por i*columnas+j
				//mientras que la de la casilla debajo de esta corresponde a (i+1)*columnas+j.
				//Asignamos su costo a la casilla correspondiente.
				ady[(i+1)*columnas+j][i*columnas+j] = peaje;
				//Calculamos el costo de ir a la casilla de abajo.
				peaje = costo(matriz[i+1][j]);
				//Asignamos su costo a la casilla correspondiente.
				ady[i*columnas+j][(i+1)*columnas+j] = peaje;
			}			
		}
	}
	//Una vez terminado esto se obtiene la matriz de costos inicial.
}


//Algoritmo de floyd extraido del apartado de material complementario del curso en Moodle.
//Se ha modificado para que, ademas de generar la matriz con los caminos mas baratos, cree
//la matriz con los predecesores de cada casilla, para asi poder obtener el camino luego.
void floyd(int n,int matrizcamino[][10000], int matrizbarata[][10000])
{	
	//Variables para recorrer la matriz.
	int i,j,k;

	//Recorremos la matriz que almacenara los caminos mas cortos.
	for(i = 0; i < n; i++)
   		for(j = 0; j < n; j++)matrizcamino[i][j] = i;
   			//En un principio a la matrizcamino se le asigna el indice de la fila.
   			//Luego este sera modificado de ser necesario, para que sea el
   			//correspondiente a la casilla por la cual se llega a la casilla actual mas rapido. 
   			for(k = 0; k < n; k++)
			{	for(i = 0; i < n; i++)
         			for(j = 0; j < n; j++)
         				//En el caso de que la suma de los dos costes sea menor al valor actual de la casilla.
            			if((matrizbarata[i][k] + matrizbarata[k][j]) < matrizbarata[i][j])
            			{
            				//Se reemplazara el valor del camino.
            				matrizbarata[i][j] = matrizbarata[i][k]+matrizbarata[k][j];
            				//Se modifica el valor del predecesor del dato ingresado en el
            				//j-esimo lugar, por el que esta mas proximo a el.
            				matrizcamino[i][j] = matrizcamino[k][j];
            			}
			}
}

//Tiene la funcion de obtener el camino a partir de la matrizcamino y modificar los valores en el tablero segun corresponda.
void modificar_matriz(int filas, int columnas, int bot, int margarina, char tablero[][100], int matrizcamino[][10000])
{
	bool falta_camino_por_recorrer = true;

	while (falta_camino_por_recorrer)
	{
		//Variable que corresponde al numero de dato que es cada casilla.
		//Ejemplo:
		// b o 
		// . m
		//b posicion = (0,0) numero de dato = 0
		//o posicion = (0,1) numero de dato = 1
		//. posicion = (1,0) numero de dato = 2
		//m posicion = (1,1) numero de dato = 3 
		int n_de_dato = 0;

		//En el caso de que el predecesor corresponda al numero de dato del bot.
		if (matrizcamino[bot][margarina] == bot)
		{
			//Significa que terminamos de recorrer el camino y no hay nada mas que cambiar.
			//Rompemos el ciclo while.
			break;
		}

		//En caso contrario debemos recorrer el tablero y comparando el numero de dato de
		//cada casilla con el predecesor de la mantequilla.
		for (int i = 0; i < filas; i++)
		{
			for (int j = 0; j < columnas; j++)
			{
				//En el caso de que el numero de dato sea el predecesor de la mantequilla.
				if (n_de_dato == matrizcamino[bot][margarina])
				{
					//Significa que es parte del camino
					tablero[i][j] = '+';
					//Dado que no es necesario seguir recorriendo el tablero para buscar el predecesor.
					//Rompemos el for anidado.
					i = filas;
					break;
				}
				//Verificado esto actualizamos el numero de dato, ya que avanzaremos a la siguiente casilla.
				n_de_dato++;
			}
		}
		//Luego de cambiar la casilla correspondiente por '+'
		//debemos actualizar la casilla que debemos buscar.
		//Ahora margarina, que es la casilla a la que le buscamos predecesor,
		//debe ser el predecesor del cual ya encontramos.
		margarina = matrizcamino[bot][margarina];
	}
}