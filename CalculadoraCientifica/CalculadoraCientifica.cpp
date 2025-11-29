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
        throw invalid_argument("Factorial de numero negativo no definido.")
    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n-1);
}

double potencia(dobuel base, int exponente = 2){
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
    return 0;
}