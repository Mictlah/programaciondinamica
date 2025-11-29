#include <iostream>
#include <stdexcept>
#include <cmath>
using namespace std;

double suma(double a, double b)
{
    return a + b;
}

double resta(double a, double b)
{
    return a - b;
}

double multiplicacion(double a, double b)
{
    return a * b;
}

double division(double a, double b)
{
    if (b == 0)
        throw invalid_argument("Division por cero no permitida");
    return a / b;
}

int factorial(int n) {
    if (n < 0)
        throw invalid_argument("Factorial de numero negativo no definido.");
    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n-1);
}

double potencia(double base, int exponente = 2){
    return pow(base, exponente);
}

double potencia(double base, double exponente){
    return pow(base, exponente);
}

double raiz(double x){
    if (x < 0)
        throw invalid_argument("Raiz de numero negativo no permitido.");
    return sqrt(x);
}

int main(){
    int opcion;
    double n1, n2;
    cout << "CALCULADORA MULTIFUNCION\n";
    cout << "1. Suma\n2. Resta\n3. Multiplicacion\n4. Division\n5. Factorial\n6. Potencia\n7. Raoz cuadrada\n";
    cout << "Seleccione una opcion: ";
    cin >> opcion;

    try
    {
        switch (opcion)
        {
        case 1:
            cout << "Ingrese dos numeros: ";
            cin >> n1 >> n2;
            cout << "Resultado: " << suma(n1, n2) << endl;
            break;
        case 2:
            cout << "Ingrese dos numeros: ";
            cin >> n1 >> n2;
            cout << "Resultado: " << resta(n1, n2) << endl;
            break;
        case 3:
            cout << "Ingrese dos numeros: ";
            cin >> n1 >> n2;
            cout << "Resultado: " << multiplicacion(n1, n2) << endl;
            break;
        case 4:
            cout << "Ingrese dos numeros: ";
            cin >> n1 >> n2;
            cout << "Resultado: " << division(n1, n2) << endl;
            break;
        case 5:
            cout << "Ingrese un numero: ";
            cin >> n1;
            cout << "Resultado: " << factorial((int)n1) << endl;
            break;
        case 6:
            cout << "Ingrese base y exponente: ";
            cin >> n1 >> n2;
            cout << "Resultado: " << potencia(n1, (int)n2) << endl;
            break;
        case 7:
            cout << "Ingrese un número: ";
            cin >> n1;
            cout << "Resultado: " << raiz(n1) << endl;
            break;
        default:
            cout << "Opción no válida.\n";
        }
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}