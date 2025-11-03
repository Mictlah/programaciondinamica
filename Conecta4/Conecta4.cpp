#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class Conecta4
{
private:
    vector<vector<char>> tablero;
    int filas;
    int columnas;
    int ultFila = -1., ultCol = -1;
    char jugadorActual;

    bool enRango(int r, int c) const{
        return r >= 0 && r < filas && c >= 0 && c < columnas;
    }

    int contar(int dr, int dc) const {
        if (ultFila < 0 || ultCol < 0) return 0;
        char f = tablero[ultFila][ultCol];
        int r = ultFila + dr, c = ultCol + dc, cnt = 0;
        while (enRango(r, c) && tablero[r][c] == f) {
            cnt++;
            r += dr;
            c += dc;
        }
        return cnt;
    }

public:
    Conecta4(int f, int c) : filas(f), columnas(c), jugadorActual('X')
    {
        tablero.resize(filas, vector<char>(columnas, ' '));
    }

    void mostrarTablero()
    {
        // Cabecera de columnas 1..columnas
        cout << " ";
        for (int j = 1; j <= columnas; ++j)
            cout << " " << j;
        cout << "\n";

        for (int i = 0; i < filas; i++)
        {
            cout << "|";
            for (int j = 0; j < columnas; j++)
            {
                cout << tablero[i][j] << "|";
            }
            cout << "\n";
        }
    }

    bool colocarFicha(int col)
    {
        col -= 1;
        if (col < 0 || col >= columnas)
            return false;
        for (int i = filas - 1; i >= 0; i--)
        {
            if (tablero[i][col] == ' ')
            {
                tablero[i][col] = jugadorActual;
                ultFila = i;
                ultCol = col;
                return true;
            }
        }
        return false;
    }

    void cambiarTurno()
    {
        jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
    }

    bool hay4EnLinea() const {
        if (ultFila < 0 || ultCol < 0) return false;
        const int D[4][2] = { {0,1}, {1,0}, {1,1}, {1,-1} };
        for (auto& d : D) {
            int total = 1 + contar(d[0], d[1] + contar(-d[0], -d[1]));
            if (total >= 4) return true;
        }
        return false;
    }
};

int main()
{
    Conecta4 juego(6, 7);
    juego.mostrarTablero();

    int col;
    cout << "Jugador X, elija la columna (1-7): ";
    while (!(cin >> col) || !juego.colocarFicha(col))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida. Por favor, elija una columna (1-7): ";
    }

    juego.cambiarTurno();
    cout << "Turno del otro jugador.\n";
    juego.mostrarTablero();

    cout << "Jugador O, elija la columna (1-7): ";
    while (!(cin >> col) || !juego.colocarFicha(col))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida. Por favor, elija una columna (1-7): ";
    }
    juego.mostrarTablero();
    return 0;
}
