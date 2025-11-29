#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;

class Producto{
    private:
        int id;
        string nombre;
        double precio;
        int cantidad;
    
    public:
        Producto(int id=0, string nombre = "", double precio = 0.0, int cantidad = 0)
            : id(id), nombre(nombre), precio(precio), cantidad(cantidad) {}

        int getId() const {return id;}
        string getNombre() const {return nombre;}
        double getPrecio() const {return precio;}
        int getCantidad() const {return cantidad;}

        void setPrecio(double p) {precio = p;}
        void setCantidad(int c) {cantidad = c;}

        void mostrar() const {
            cout << setw(5) << id << setw(20) << nombre
                 << setw(10) << fixed << setprecision(2) << precio
                 << setw(10) << cantidad << endl;
        }
};

int main(){
    return 0;
}