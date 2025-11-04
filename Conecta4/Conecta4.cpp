#include <cstdlib>
#include <iostream>
#include <limits>
#include <locale>
#include <vector>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

using namespace std;

class Conecta4
{
private:
    vector<vector<char>> tablero;
    int filas;
    int columnas;
    int ultFila = -1, ultCol = -1;
    char jugadorActual;

    bool enRango(int r, int c) const {
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

    void animacionCaida(char ficha, int filaFinal, int col) {
        system("cls");
        for (int i = 0; i <= filaFinal; i++) {
            tablero[i][col] = ficha;
            mostrarTablero();
            tablero[i][col] = ' ';
            Sleep(200);
            system("cls");
        }
    }

public:
    Conecta4(int f, int c) : filas(f), columnas(c), jugadorActual('X')
    {
        tablero.resize(filas, vector<char>(columnas, ' '));
    }

    void mostrarTablero()
    {
        cout << "  ";
        for (int j = 1; j <= columnas; ++j)
            cout << " " << j << " ";
        cout << "\n";

        for (int i = 0; i < filas; i++)
        {
            cout << i + 1 << " "; // <-- Cambiamos para no mostrar 0
            for (int j = 0; j < columnas; j++)
            {
                cout << " " << tablero[i][j] << " ";
                if (j < columnas - 1)
                    cout << "|";
            }
            cout << "\n";
            if (i < filas - 1)
            {
                cout << "  ";
                for (int j = 0; j < columnas; j++)
                {
                    cout << "---";
                    if (j < columnas - 1)
                        cout << "+";
                }
                cout << "\n";
            }
        }
    }

    bool colocarFicha(int col, bool conAnimacion = true) {
        col -= 1;
        if (col < 0 || col >= columnas)
            return false;

        for (int i = filas - 1; i >= 0; i--) {
            if (tablero[i][col] == ' ') {
                if (conAnimacion) {
                    animacionCaida(jugadorActual, i, col);
                }
                tablero[i][col] = jugadorActual;
                ultFila = i;
                ultCol = col;
                return true;
            }
        }
        return false;
    }

    char getJugadorActual() const {
        return jugadorActual;
    }

    void cambiarTurno()
    {
        jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
    }

    bool hay4EnLinea() const {
        if (ultFila < 0 || ultCol < 0) return false;
        const int D[4][2] = { {0,1}, {1,0}, {1,1}, {1,-1} };
        for (auto& d : D) {
            int total = 1 + contar(d[0], d[1]) + contar(-d[0], -d[1]);
            if (total >= 4) return true;
        }
        return false;
    }

    bool tableroLleno() const {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                if (tablero[i][j] == ' ')
                    return false;
            }
        }
        return true;
    }

    void limpiarTablero() {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                tablero[i][j] = ' ';
            }
        }
        ultFila = -1;
        ultCol = -1;
        jugadorActual = 'X';
    }
};

int mostrarMenu() {
    int opc;
    while (true) {
        cout << "=========================================\n";
        cout << "         BIENVENIDO A CONECTA 4          \n";
        cout << "=========================================\n";
        cout << " Un juego de estrategia para dos jugadores\n";
        cout << " Gana quien conecte 4 fichas iguales      \n";
        cout << " en linea horizontal, vertical o diagonal \n";
        cout << "-----------------------------------------\n";
        cout << " 1. Iniciar nuevo juego                   \n";
        cout << " 2. Salir                                 \n";
        cout << "=========================================\n";
        cout << " Selecciona una opcion: ";
        cin >> opc;

        if (cin.fail() || opc < 1 || opc > 2) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Opcion incorrecta, vuelve a seleccionar.\n\n";
        }
        else {
            return opc;
        }
    }
}

void felicitarGanador(char jugador) {
    cout << "\n==============================\n";
    cout << "   Felicidades Jugador " << (jugador == 'X' ? "1 (X)" : "2 (O)") << "! \n";
    cout << "   Has logrado conectar 4!\n";
    cout << "==============================\n\n";
}

void mensajeEmpate() {
    cout << "\n===============================" << endl;
    cout << "|                             |" << endl;
    cout << "|         EMPATE!            |" << endl;
    cout << "|                             |" << endl;
    cout << "|   El tablero esta lleno     |" << endl;
    cout << "|   y nadie logro ganar.      |" << endl;
    cout << "|                             |" << endl;
    cout << "|   Gran juego de ambos!     |" << endl;
    cout << "|                             |" << endl;
    cout << "===============================" << endl << endl;
}

char jugarPartida(Conecta4& juego) {
    int col;

    while (true) {
        char jugadorActual = juego.getJugadorActual();
        int numJugador = (jugadorActual == 'X') ? 1 : 2;

        cout << "Jugador " << numJugador << " (" << jugadorActual
            << "), elija la columna (1-7): ";

        while (!(cin >> col) || !juego.colocarFicha(col)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("cls");
            juego.mostrarTablero();
            cout << "Entrada invalida o columna llena. ";
            cout << "Jugador " << numJugador << " (" << jugadorActual
                << "), elija la columna (1-7): ";
        }

        system("cls");
        juego.mostrarTablero();

        if (juego.hay4EnLinea()) {
            return jugadorActual;
        }

        if (juego.tableroLleno()) {
            return 'E';
        }

        juego.cambiarTurno();
    }
}

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
    Conecta4 juego(6, 7);
    int opc, volverJugar;

    while (true) {
        opc = mostrarMenu();
        system("cls");

        if (opc == 2) {
            cout << "Gracias por jugar! Hasta pronto.\n";
            break;
        }

        juego.limpiarTablero();
        juego.mostrarTablero();

        char resultado = jugarPartida(juego);

        system("cls");
        juego.mostrarTablero();

        if (resultado == 'E') {
            mensajeEmpate();
        }
        else {
            felicitarGanador(resultado);
        }

        cout << "Quieres volver a jugar? (1-Si, 2-No): ";
        while (!(cin >> volverJugar) || (volverJugar != 1 && volverJugar != 2)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Opcion invalida. Quieres volver a jugar? (1-Si, 2-No): ";
        }

        if (volverJugar == 2) {
            cout << "Gracias por jugar! Hasta pronto.\n";
            break;
        }

        system("cls");
    }

    return 0;
}