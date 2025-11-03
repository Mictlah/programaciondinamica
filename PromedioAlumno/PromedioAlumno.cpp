#include <iostream>
#include <string>
using namespace std;

struct Alumno {
	string nombre;
	int edad;
	float promedio;
};

int main() {
	const int TAM = 5;
	Alumno grupo[TAM]; // Arreglo de una estructura definida por el usuario
	cout << "=== Captura los datos del alumno ===" << endl;
	for (int i = 0; i < TAM; i++) {
		cout << "\nAlumno" << (i + 1) << ": ";
		getline(cin >> ws, grupo[i].nombre);
		cout << "Promedio: ";
		cin >> grupo[i].promedio;
		cout << "Edad: ";
		cin >> grupo[i].edad;
	}

	cout << "=== Listado de los alumnos ===" << endl;
	for (int i = 0; i < TAM; i++) {
		cout << "Alumno " << (i + 1) << ":\n";
		cout << "Nombre: " << grupo[i].nombre << endl;
		cout << "Edad: " << grupo[i].edad << endl;
		cout << "Promedio: " << grupo[i].promedio << endl;
	}

	cout << "\nPresione enter para continuar.";
	cin.ignore();
	cin.get();

	return 0;
}