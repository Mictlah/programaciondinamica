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

class GestorInventario{
    private:
        vector<Producto> productos;
        int siguienteId;

    public:
        GestorInventario() : siguienteId(1) {}

    void agregarProducto(string nombre, double precio, int cantidad){
        productos.push_back(Producto(siguienteId++, nombre, precio, cantidad));
        cout << "Producto agregado exitosamente!" << endl;
    }

    void mostrarInventario(){
        if (productos.empty()){
            cout << "El inventario esta vacio." << endl;
            return;
        }
        cout << "\n" << setw(5) << "ID" << setw(20) << "Nombre" << setw(10) << "Precio" << setw(10) << "Cantidad" << endl;
        cout << string(45, '-') << endl;
        for (const auto &p : productos)
        {
            p.mostrar();
        }
        cout << endl;
    }

    Producto *buscarPorId(int id)
    {
        for (auto &p : productos)
        {
            if (p.getId() == id)
                return &p;
        }
        return nullptr;
    }

    void buscarPorNombre(string nombre)
    {
        bool encontrado = false;
        for (const auto &p : productos)
        {
            if (p.getNombre().find(nombre) != string::npos)
            {
                if (!encontrado)
                {
                    cout << "\n"
                         << setw(5) << "ID" << setw(20) << "Nombre"
                         << setw(10) << "Precio" << setw(10) << "Cantidad" << endl;
                    cout << string(45, '-') << endl;
                    encontrado = true;
                }
                p.mostrar();
            }
        }
        if (!encontrado)
        {
            cout << "No se encontraron productos con ese nombre." << endl;
        }
    }

    void actualizarProducto(int id, double nuevoPrecio, int nuevaCantidad)
    {
        Producto *p = buscarPorId(id);
        if (p)
        {
            p->setPrecio(nuevoPrecio);
            p->setCantidad(nuevaCantidad);
            cout << "Producto actualizado exitosamente!" << endl;
        }
        else
        {
            cout << "Producto no encontrado." << endl;
        }
    }

    void eliminarProducto(int id)
    {
        auto it = find_if(productos.begin(), productos.end(),
                          [id](const Producto &p)
                          { return p.getId() == id; });
        if (it != productos.end())
        {
            productos.erase(it);
            cout << "Producto eliminado exitosamente!" << endl;
        }
        else
        {
            cout << "Producto no encontrado." << endl;
        }
    }

    void ordenarPorPrecio(bool ascendente = true)
    {
        sort(productos.begin(), productos.end(),
             [ascendente](const Producto &a, const Producto &b)
             {
                 return ascendente ? a.getPrecio() < b.getPrecio()
                                   : a.getPrecio() > b.getPrecio();
             });
        cout << "Productos ordenados por precio." << endl;
    }

    void ordenarPorNombre()
    {
        sort(productos.begin(), productos.end(),
             [](const Producto &a, const Producto &b)
             {
                 return a.getNombre() < b.getNombre();
             });
        cout << "Productos ordenados por nombre." << endl;
    }

    void ordenarPorCantidad(bool ascendente = true)
    {
        sort(productos.begin(), productos.end(),
             [ascendente](const Producto &a, const Producto &b)
             {
                 return ascendente ? a.getCantidad() < b.getCantidad()
                                   : a.getCantidad() > b.getCantidad();
             });
        cout << "Productos ordenados por cantidad." << endl;
    }
};

int main(){
    GestorInventario inventario;
    int opcion;

    do
    {
        cout << "\n=== GESTOR DE INVENTARIO ===" << endl;
        cout << "1. Agregar producto" << endl;
        cout << "2. Mostrar inventario" << endl;
        cout << "3. Buscar por ID" << endl;
        cout << "4. Buscar por nombre" << endl;
        cout << "5. Actualizar producto" << endl;
        cout << "6. Eliminar producto" << endl;
        cout << "7. Ordenar por precio" << endl;
        cout << "8. Ordenar por nombre" << endl;
        cout << "9. Ordenar por cantidad" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            string nombre;
            double precio;
            int cantidad;
            cout << "Nombre: ";
            cin.ignore();
            getline(cin, nombre);
            cout << "Precio: ";
            cin >> precio;
            cout << "Cantidad: ";
            cin >> cantidad;
            inventario.agregarProducto(nombre, precio, cantidad);
            break;
        }
        case 2:
            inventario.mostrarInventario();
            break;
        case 3:
        {
            int id;
            cout << "ID del producto: ";
            cin >> id;
            Producto *p = inventario.buscarPorId(id);
            if (p)
            {
                cout << "\n"
                     << setw(5) << "ID" << setw(20) << "Nombre"
                     << setw(10) << "Precio" << setw(10) << "Cantidad" << endl;
                cout << string(45, '-') << endl;
                p->mostrar();
            }
            else
            {
                cout << "Producto no encontrado." << endl;
            }
            break;
        }
        case 4:
        {
            string nombre;
            cout << "Nombre del producto: ";
            cin.ignore();
            getline(cin, nombre);
            inventario.buscarPorNombre(nombre);
            break;
        }
        case 5:
        {
            int id, cantidad;
            double precio;
            cout << "ID del producto: ";
            cin >> id;
            cout << "Nuevo precio: ";
            cin >> precio;
            cout << "Nueva cantidad: ";
            cin >> cantidad;
            inventario.actualizarProducto(id, precio, cantidad);
            break;
        }
        case 6:
        {
            int id;
            cout << "ID del producto: ";
            cin >> id;
            inventario.eliminarProducto(id);
            break;
        }
        case 7:
        {
            int orden;
            cout << "1. Ascendente  2. Descendente: ";
            cin >> orden;
            inventario.ordenarPorPrecio(orden == 1);
            break;
        }
        case 8:
            inventario.ordenarPorNombre();
            break;
        case 9:
        {
            int orden;
            cout << "1. Ascendente  2. Descendente: ";
            cin >> orden;
            inventario.ordenarPorCantidad(orden == 1);
            break;
        }
        }
    } while (opcion != 0);
    
    return 0;
}