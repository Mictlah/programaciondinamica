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

        bool depositar(double cantidad) {
            if (cantidad <= 0) {
                cout << "Error: Cantidad invalida\n";
                return false;
            }
            saldo += cantidad;
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

class CajeroAutomatico{
    private:
        Banco* banco;
        Cuenta* cuentaActual;

        void mostrarMenu(){
        cout << "\n=== CAJERO AUTOMATICO ===\n";
        cout << "1. Consultar saldo\n";
        cout << "2. Retirar efectivo\n";
        cout << "3. Depositar efectivo\n";
        cout << "4. Transferir entre cuentas\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        }

        void consultarSaldo(){
            cout << fixed << setprecision(2);
            cout << "\nSaldo Actual: $" << cuentaActual->consultarSaldo() << "\n";
        }

        void retirarEfectivo(){
            double cantidad;
            cout << "\nIngrese cantidad a retirar: $";
            cin >> cantidad;

            if (cuentaActual->retirar(cantidad)){
                cout << "Retiro exitoso. Nuevo saldo: $" << cuentaActual->consultarSaldo() << "\n";
            }
        }

        void depositarEfectivo(){
            double cantidad;
            cout << "\nIngrese cantidad a depositar: $";
            cin >> cantidad;
            
            if (cuentaActual->depositar(cantidad)){
                cout << "Deposito exitoso. Nuevo saldo: $" << cuentaActual->consultarSaldo() << "\n";
            }
        }

        void transferirDinero(){
            string cuentaDestino;
            double cantidad;

            cout << "\nIngrese numero de cuenta destino: ";
            cin >> cuentaDestino;
            cout << "Ingrese cantidad a transferir: $";
            cin >> cantidad;

            if (banco->transferir(cuentaActual->obtenerNumeroCuenta(), cuentaDestino, cantidad)){
                cout << "Transferencia exitosa. Nuevo saldo: $" << cuentaActual->consultarSaldo() << "\n";
            }
        }

    public:
        CajeroAutomatico(Banco* b) : banco(b), cuentaActual(nullptr) {}

         bool autenticar(){
            string numeroCuenta, pin;
            int intentos = 3;

        cout << "=== BIENVENIDO ===\n";
        cout << "Ingrese numero de cuenta: ";
        cin >> numeroCuenta;
        
        Cuenta* cuenta = banco->obtenerCuenta(numeroCuenta);
        if (!cuenta) {
            cout << "Cuenta no encontrada\n";
            return false;
        }
        
        while (intentos > 0) {
            cout << "Ingrese su PIN: ";
            cin >> pin;
            
            if (cuenta->verificarPIN(pin)) {
                cuentaActual = cuenta;
                cout << "Autenticacion exitosa\n";
                return true;
            }
            
            intentos--;
            if (intentos > 0) {
                cout << "PIN incorrecto. Intentos restantes: " << intentos << "\n";
            }
        }
        
        cout << "Tarjeta bloqueada por seguridad\n";
        return false;
    }
    
    void ejecutar() {
        if (!autenticar()) return;
        
        int opcion;
        do {
            mostrarMenu();
            cin >> opcion;
            
            switch(opcion) {
                case 1:
                    consultarSaldo();
                    break;
                case 2:
                    retirarEfectivo();
                    break;
                case 3:
                    depositarEfectivo();
                    break;
                case 4:
                    transferirDinero();
                    break;
                case 5:
                    cout << "Gracias por usar nuestro servicio\n";
                    break;
                default:
                    cout << "Opcion invalida\n";
            }
        } while (opcion != 5);
    }
};

int main(){
    Banco banco;

    Cuenta* cuenta1 = new Cuenta("1001", "1234", 5000.00);
    Cuenta* cuenta2 = new Cuenta("1002", "5678", 3000.00);
    Cuenta* cuenta3 = new Cuenta("1003", "9012", 7500.00);
    
    banco.agregarCuenta(cuenta1);
    banco.agregarCuenta(cuenta2);
    banco.agregarCuenta(cuenta3);

    CajeroAutomatico cajero(&banco);
    cajero.ejecutar();
    
    delete cuenta1;
    delete cuenta2;
    delete cuenta3;
    return 0;
}