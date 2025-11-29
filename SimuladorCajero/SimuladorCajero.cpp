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

class Banco{
    private:
        map<string, Cuenta*> cuentas;
    
    public:
        void agregarCuenta(Cuenta* cuenta){
            cuentas[cuenta->obtenerNumeroCuenta()] = cuenta;
        }

        Cuenta* obtenerCuenta(string numeroCuenta){
            if (cuentas.find(numeroCuenta) != cuentas.end()){
                return cuentas[numeroCuenta];
            }
            return nullptr;
        }

        bool transferir(string cuentaOrigen, string cuentaDestino, double cantidad){
            Cuenta* origen = obtenerCuenta(cuentaOrigen);
            Cuenta* destino = obtenerCuenta(cuentaDestino);

            if (!origen || !destino){
                cout << "Error: Cuenta no encontrada\n";
                return false;
            }

            if (origen->retirar(cantidad)){
                destino->depositar(cantidad);
                return true;
            }
            return false;
        }
};

int main(){
    return 0;
}