
#include <cstdlib>
#include <iostream>
#include <queue>

using namespace std;

char dev_antecesor(char indicado)
{
	if (indicado == 'R')
	{
		return 'I';
	}
	if (indicado == 'I')
	{
		return 'R';
	}
	if (indicado == 'D')
	{
		return 'U';
	}
	if (indicado == 'U')
	{
		return 'D';
	}
	return ' ';
}

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
	return 0;
}

void algoritmo(char matriz[][100],char matriz_padres[][100],int matriz_costos[][100], char matriz_pasados[][100],int cord_x,int cord_y,int filas,int columnas,char antecesor)
{
	cout << "asd"<<endl;
	//Si ya llegamos a la mantequilla
	if(matriz[cord_x][cord_y]=='m')
	{
		return;
	}
	int maximo = 10000; //maximo costo
	char indicado;
	//Si se puede mover a la izquierda
	if(antecesor != 'L')
	{
		if ( cord_y-1 >= 0)
		{
			
			if (matriz_pasados[cord_x][cord_y-1] == 'D')
			{
				//Si ya lo ha visto debemos comparar su costo actual con el anterior, en el caso de ser mayor lo reemplazamos
				if (matriz_costos[cord_x][(cord_y-1)] > (matriz_costos[cord_x][cord_y]+costo(matriz[cord_x][(cord_y-1)])))
				{
					//Se llama a la funcion costo para saber cuando vale cruzar hacia el
					//Actualizamos su costo
					matriz_costos[cord_x][(cord_y-1)] = (matriz_costos[cord_x][cord_y]+costo(matriz[cord_x][(cord_y-1)]));
					//Actualizamos su padre
					matriz_padres[cord_x][(cord_y-1)]='R';
				}
			}
			//Si es igual a I significa que su costo aun es infinito
			if (matriz_pasados[cord_x][(cord_y-1)] == 'I')
			{
				//Como ya pasamos por el lo cambiamos a D de definitivo
				matriz_pasados[cord_x][(cord_y-1)] = 'D';
				//Dado que su costo es infinito debemos reemplazar su costo por la suma del suyo mas el actual obligatoriamente
				//Actualizamos costo		
				matriz_costos[cord_x][(cord_y-1)] = matriz_costos[cord_x][(cord_y-1)]+matriz_costos[cord_x][cord_y];
				//Tambien debemos actualizar su padre
				matriz_padres[cord_x][(cord_y-1)] = 'R';
			}	
			if (matriz_costos[cord_x][(cord_y-1)] < maximo)
			{
				maximo = matriz_costos[cord_x][(cord_y-1)];
				indicado = 'L'	;	
			}
		}
	}
	if (antecesor != 'R')
	{
		//Si se puede mover a la Derecha
		if (cord_y+1 <= columnas-1)
		{		
					
			if (matriz_pasados[cord_x][cord_y+1] == 'D')
			{
				//Si ya lo ha visto debemos comparar su costo actual con el anterior, en el caso de ser mayor lo reemplazamos
				if (matriz_costos[cord_x][(cord_y+1)] > (matriz_costos[cord_x][cord_y]+costo(matriz[cord_x][(cord_y+1)])))
				{
					//Se llama a la funcion costo para saber cuando vale cruzar hacia el
					//Actualizamos su costo
					matriz_costos[cord_x][(cord_y+1)] = (matriz_costos[cord_x][cord_y]+costo(matriz[cord_x][(cord_y+1)]));
					//Actualizamos su padre
					matriz_padres[cord_x][(cord_y+1)]='L';
				}
			}
			//Si es igual a I significa que su costo aun es infinito
			if (matriz_pasados[cord_x][(cord_y+1)] == 'I')
			{
				//Como ya pasamos por el lo cambiamos a D de definitivo
				matriz_pasados[cord_x][(cord_y+1)] = 'D';
				//Dado que su costo es infinito debemos reemplazar su costo por la suma del suyo mas el actual obligatoriamente
				//Actualizamos costo		
				matriz_costos[cord_x][(cord_y+1)] = matriz_costos[cord_x][(cord_y+1)]+matriz_costos[cord_x][cord_y];
				//Tambien debemos actualizar su padre
				matriz_padres[cord_x][(cord_y+1)] = 'L';
			}
			if (matriz_costos[cord_x][(cord_y+1)] < maximo)
			{
				maximo = matriz_costos[cord_x][(cord_y+1)];
				indicado = 'R';
			}
		}
	}
	if (antecesor != 'U')
	{
		//Si se puede mover a hacia Arriba
		if (cord_x-1 >= 0)
		{	
			if (matriz_pasados[cord_x-1][cord_y] == 'D')
			{
				//Si ya lo ha visto debemos comparar su costo actual con el anterior, en el caso de ser mayor lo reemplazamos
				if (matriz_costos[(cord_x-1)][(cord_y)] > (matriz_costos[cord_x][cord_y]+costo(matriz[(cord_x-1)][cord_y])))
				{
					//Se llama a la funcion costo para saber cuando vale cruzar hacia el
					//Actualizamos su costo
					matriz_costos[(cord_x-1)][cord_y] = (matriz_costos[cord_x][cord_y]+costo(matriz[(cord_x-1)][cord_y]));
					//Actualizamos su padre
					matriz_padres[(cord_x-1)][cord_y]='D';
				}
			}
			//Si es igual a I significa que su costo aun es infinito
			if (matriz_pasados[(cord_x-1)][cord_y] == 'I')
			{
				//Como ya pasamos por el lo cambiamos a D de definitivo
				matriz_pasados[(cord_x-1)][cord_y] = 'D';
				//Dado que su costo es infinito debemos reemplazar su costo por la suma del suyo mas el actual obligatoriamente
				//Actualizamos costo		
				matriz_costos[(cord_x-1)][cord_y] = matriz_costos[cord_x-1][cord_y]+matriz_costos[cord_x][cord_y];
				//Tambien debemos actualizar su padre
				matriz_padres[(cord_x-1)][cord_y] = 'D';
			}
			if (matriz_costos[(cord_x-1)][cord_y] < maximo)
			{
				maximo = matriz_costos[(cord_x-1)][cord_y];
				indicado = 'U';
			}
		}
	}
	if (antecesor != 'D')
	{
		//Si se puede mover hacia Abajo
		if (cord_x+1 <= filas-1)
		{
			if (matriz_pasados[cord_x+1][cord_y] == 'D')
			{
				//Si ya lo ha visto debemos comparar su costo actual con el anterior, en el caso de ser mayor lo reemplazamos
				if (matriz_costos[(cord_x+1)][cord_y] > (matriz_costos[cord_x][cord_y]+costo(matriz[(cord_x+1)][cord_y-1])))
				{
					//Se llama a la funcion costo para saber cuando vale cruzar hacia el
					//Actualizamos su costo
					matriz_costos[(cord_x+1)][cord_y] = (matriz_costos[cord_x][cord_y]+costo(matriz[(cord_x+1)][cord_y]));
					//Actualizamos su padre
					matriz_padres[(cord_x+1)][cord_y]='U';
				}
			}
			//Si es igual a I significa que su costo aun es infinito
			if (matriz_pasados[(cord_x+1)][cord_y] == 'I')
			{
				//Como ya pasamos por el lo cambiamos a D de definitivo
				matriz_pasados[(cord_x+1)][cord_y] = 'D';
				//Dado que su costo es infinito debemos reemplazar su costo por la suma del suyo mas el actual obligatoriamente
				//Actualizamos costo		
				matriz_costos[(cord_x+1)][cord_y] = matriz_costos[(cord_x+1)][cord_y]+matriz_costos[cord_x][cord_y];
				//Tambien debemos actualizar su padre
				matriz_padres[(cord_x+1)][cord_y] = 'U';
			}		
			if (matriz_costos[(cord_x+1)][cord_y] < maximo)
			{
				maximo = matriz_costos[(cord_x+1)][cord_y];
				indicado = 'D';
			}
		}
	}
	cout << maximo << " " << indicado<< dev_antecesor(indicado) <<endl;
	//Una vez actualizada la matriz de costos, y teniendo el costo minimo, debemos llamar a la funcion con este nodo.
	if(indicado == 'I')
	{
		algoritmo(matriz,matriz_padres,matriz_costos,matriz_pasados,cord_x,(cord_y-1),filas,columnas,antecesor);	
	}
	if(indicado == 'R')
	{
		algoritmo(matriz,matriz_padres,matriz_costos,matriz_pasados,cord_x,(cord_y+1),filas,columnas,antecesor);	
	}
	if(indicado == 'U')
	{
		algoritmo(matriz,matriz_padres,matriz_costos,matriz_pasados,(cord_x-1),cord_y,filas,columnas,antecesor);	
	}
	if(indicado == 'D')
	{
		algoritmo(matriz,matriz_padres,matriz_costos,matriz_pasados,(cord_x+1),cord_y,filas,columnas,antecesor);	
	}
	
	for(int i = 0;i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			cout << matriz_padres[i][j];
		}
		cout << endl;
	}
	for(int i = 0;i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			cout << matriz_pasados[i][j];
		}
		cout << endl;
	}
	for(int i = 0;i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			cout << matriz_costos[i][j]<< " ";
		}
		cout << endl;
	}
}

int main()
{
	int filas, columnas;
	int cord_x, cord_y;
	int cord_x_m, cord_y_m;
	char dato; 
	char antecesor = ' ';
	cin >> filas >> columnas;
	//es 100 las columnas por un tema de que para pasar la matriz debiamos definir sus dimensiones excepto la primera
	char matriz[filas][100];
	char matriz_padres[filas][100]; //Left Right Up Down
	int matriz_costos[filas][100]; //Almacena costos
	char matriz_pasados[filas][100]; //dEfinitivo, dIsponible
	for (int i = 0; i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			cin >> dato;
			matriz[i][j] = dato;
			matriz_padres[i][j] = 'N';
			matriz_costos[i][j] = costo(dato);
			matriz_pasados[i][j] = 'I';
			if (dato == 'b')
			{
				matriz_pasados[i][j] = 'X';
				cord_y = j;
				cord_x = i;
			}
			if (dato == 'm')
			{
				cord_x_m = i;
				cord_y_m = j;
			}
		}
	}	
	algoritmo(matriz,matriz_padres,matriz_costos,matriz_pasados,cord_x,cord_y,filas,columnas,antecesor);
	return 0;
}