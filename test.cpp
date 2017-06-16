
#include <cstdlib>
#include <iostream>
#include <queue>

using namespace std;

void modificar_matriz(int filas, int columnas, int bot, int margarina, char tablero[][100], int matrizcamino[][10000])
{
	//Debemos recorrer la matriz de caminos buscando en la fila del bot y fijandonos
	bool falta_camino_por_recorrer=true;
	while (falta_camino_por_recorrer)
	{

		int n_de_dato = 0;
		if (matrizcamino[bot][margarina]==bot || matrizcamino[bot][margarina]==margarina)
		{
			break;
		}
		for (int i = 0; i < filas; i++)
		{
			for (int j = 0; j < columnas; j++)
			{
				
				if (n_de_dato == matrizcamino[bot][margarina])
				{
					tablero[i][j] = '+';
					i=filas;
					break;
				}
				n_de_dato++;
			}
		}
		margarina = matrizcamino[bot][margarina];
	}

}

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
	//Dado que es un tablero, iremos agregando los datos a la matriz de adyacencia.
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
//Se a modificado para que, ademas de generar la matriz con los caminos mas baratos, cree
//la matriz con los padres de cada casilla, para asi poder obtener el camino luego.
void floyd(int n, int matrizbarata[][10000],int matrizcamino[][10000], int ady[][10000])
{	
	//Variables para recorrer la matriz.
	int i,j,k;

	//Recorremos la matriz que almacenara los caminos mas cortos.
	for(i = 0; i < n; i++)
   		for(j = 0; j < n; j++)
   			//En caso de estar en la diagonal el valor es 0.
      		if(i == j)	matrizbarata[i][i]=0;
      		//Si no, agregamos su valor correspondiente.
			else	matrizbarata[i][j]=ady[i][j];
			//Una vez agregado debemos verificar si por algun camino
			//podemos llegar a el con un menor costo, por lo que se recorre
			//la matriz nuevamente para identificarlo.
			for(k = 0; k < n; k++)
			{	for(i = 0; i < n; i++)
         			for(j = 0; j < n; j++)
         				//En el caso de que la suma de los dos costes sea menor
            			if((matrizbarata[i][k] + matrizbarata[k][j]) < matrizbarata[i][j])
            			{
            				//Se reemplazara el valor del camino
            				matrizbarata[i][j] = matrizbarata[i][k]+matrizbarata[k][j];
            				//Se anexa a la matriz que almacenara el camino el valor de k
            				//ya que este corresponde al numero del dato que es por el cual
            				//se llega a la casilla.
            				matrizcamino[i][j] = k;
            			}
			}
}



int main()
{
	//Variables de las dimensiones de la matriz.
	int filas,columnas;
	cin >> filas >> columnas;

	//Variables para almacenar el numero de dato que es el bot y la mantequilla
	int bot,mantequilla;
	int contador = 0;

	//Tablero.
	char matriz[filas][100];
	//Matriz de adyacencia/costos.
	int ady[filas*columnas][10000];
	//Matriz que almacenara los costes de los caminos mas baratos luego de aplicar el algoritmo de floyd.
	int matrizbarata[filas*columnas][10000];
	//Matriz que almacenara los indices de los padres de cada casilla (almacena el padre por el cual es mas barato llegar)-
	int matrizcamino[filas*columnas][10000];

	//Definimos la segunda dimension de los arreglos como el valor maximo que podian llegar a tener
	//debido a que, de otra forma, no podiamos pasarlas como parametro a las funciones.

	//Se le asignan como valores iniciales a nuestra matriz de padres
	//el valor correspondiente a la columna en que estan, ya que de momento
	//todos se tienen como padre a ellos mismos.
	for (int i = 0; i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			matrizcamino[i][j] = j;
		}
	}

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
			//En caso de estar en la diagonal es 0.
			if (i == j)
			{
				ady[i][j] = 0;
			}
		}
	}

	//Se llama a la funcion para cambiar los valores de la matriz de adyacencia.
	pasar_m_ady(matriz,filas,columnas,ady);
	
	//Llamamos a la funcion que ejecuta el algoritmo de floyd en la matriz de adyacencia.
	floyd(filas*columnas,matrizbarata,matrizcamino, ady);

	//Una vez listas las matrices, podemos obtener el coste de llegar desde el bot a la mantequilla
	cout << matrizbarata[bot][mantequilla]<<endl;

	for (int i = 0; i < filas*columnas; i++)
	{
		for (int j = 0; j < filas*columnas; j++)
		{
			cout << matrizcamino[i][j]<<" ";
		}
		cout << endl;
	}
	modificar_matriz(filas,columnas,bot,mantequilla,matriz,matrizcamino);

	for (int i = 0; i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			cout << matriz[i][j]<<" ";
		}
		cout << endl;
	}
	return 0;
}