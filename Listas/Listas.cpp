#include <iostream>
#include <locale>
using namespace std;

int main(){
	setlocale(LC_ALL, "es_ES.UTF-8");
	// Tamaño del arreglo
	const int TAM = 10;
	double numeros[TAM];
	double suma = 0;
	double promedio = 0;
	double maximo, minimo;

	cout << "=== Calculamos la suma, promedio, mínimo y máximo ===" << endl;
	cout << "Ingrese el número 1: ";
	cin >> numeros[0];
	suma += numeros[0];
	minimo = maximo = numeros[0];
	// Primero tenemos que leer los valores del Arreglo
	for (int i = 1; i < TAM; i++) {
		cout << "Ingrese el número " << (i + 1) << ": ";
		cin >> numeros[i];
		suma += numeros[i];
		if (numeros[i] > maximo) {
			maximo = numeros[i];
		}
		if (numeros[i] < minimo) {
			minimo = numeros[i];
		}
	}
	promedio = suma / TAM;
	cout << "=== Resultados ===" << endl;
	cout << "Promedio: " << promedio << endl;
	cout << "Mínimo: " << minimo << endl;
	cout << "Máximo: " << maximo << endl;
	return 0;
}