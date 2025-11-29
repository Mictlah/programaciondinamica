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
        throw invalid_argument("División por cero no permitida");
    return a / b;
}

int main(){
    return 0;
}