#include <iostream>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

class Cuenta{
    private: 
        string numeroCuenta;
        string pin;
        double saldo;

    public:
        Cuenta(string num, string p, double saldoInicial)
            : numeroCuenta(num), pin(p), saldo(saldoInicial){}
        
            bool verificarPIN(string pinIngresado){
                return pin == pinIngresado;
            }

        double consultarSaldo(){
            return saldo;
        }

        bool retirar(double cantidad){
            if (cantidad <= 0){
                cout << "Error: Cantidad Invalida\n";
                return false;
            }
            if (cantidad > saldo){
                cout << "Error: Fondos Insuficientes\n";
                return false;
            }
            saldo -= cantidad;
            return true;
        }

        string obtenerNumeroCuenta(){
            return numeroCuenta;
        }
};

int main(){
    return 0;
}