#ifndef FUNCIONES_h
#define FUNCIONES_h

using namespace std;

int costo(char caracter);
void pasar_m_ady(char matriz[][100],int filas,int columnas, int ady[][10000]);
void floyd(int n,int matrizcamino[][10000], int matrizbarata[][10000]);
void modificar_matriz(int filas, int columnas, int bot, int margarina, char tablero[][100], int matrizcamino[][10000]);

#endif