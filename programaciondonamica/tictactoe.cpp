#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <thread>
#include <chrono>

using namespace std;

class TicTacToe
{
private:
    vector<vector<char>> tablero;
    vector<pair<int, int>> casillasGanadoras;
    char direccionGanadora;
    char jugadorActual;
    int movimientos;
    bool contraPC;
    char simboloJugador;
    char simboloPC;

public:
    TicTacToe()
    {
        tablero = vector<vector<char>>(3, vector<char>(3, ' '));
        jugadorActual = 'X';
        movimientos = 0;
        contraPC = false;
        simboloJugador = 'X';
        simboloPC = 'O';
        casillasGanadoras.clear();
        direccionGanadora = 'N';
    }

    void configurarModo(bool esContraPC)
    {
        contraPC = esContraPC;
        if (contraPC)
        {
            simboloJugador = 'X';
            simboloPC = 'O';
        }
    }

    void mostrarTablero()
    {
        auto esGanadora = [&](int i, int j)
            {
                for (auto& p : casillasGanadoras)
                    if (p.first == i && p.second == j)
                        return true;
                return false;
            };

        int winLen = (int)casillasGanadoras.size();

        auto celdaStr = [&](int i, int j) -> string
            {
                char c = tablero[i][j];
                string base = "   ";
                if (c != ' ')
                {
                    base[0] = ' ';
                    base[1] = c;
                    base[2] = ' ';
                }

                if (!esGanadora(i, j))
                    return base;

                if (direccionGanadora == 'H')
                {
                    char bord = (winLen >= 3 && winLen <= 7) ? '|' : '\\';

                    if (c == ' ')
                    {
                        string s(3, bord);
                        return s;
                    }

                    string s = "";
                    s += bord;
                    s += c;
                    s += bord;
                    return s;
                }
                else if (direccionGanadora == 'V')
                {
                    if (c == ' ')
                        return "   ";
                    string s = "";
                    s += '|';
                    s += c;
                    s += '|';
                    return s;
                }
                else if (direccionGanadora == 'D')                            
                {
                    if (c == ' ')
                        return "   ";
                    string s = "";
                    s += '\\';
                    s += c;
                    s += '\\';
                    return s;
                }
                else if (direccionGanadora == 'A')
                {
                    if (c == ' ')
                        return "   ";
                    string s = "";
                    s += '/';
                    s += c;
                    s += '/';
                    return s;
                    }

                    return base;
    };

        cout << "\n";
        for (int i = 0; i < 3; i++)
        {
            cout << "  ";
            for (int j = 0; j < 3; j++)
            {
                cout << celdaStr(i, j);
                if (j < 2)
                    cout << "|";
            }
            cout << "\n";
            if (i < 2)
                cout << "  ---+---+---\n";
        }
        cout << "\n";
    }

    void mostrarPosiciones()
    {
        cout << "\nPosiciones del tablero:\n";
        cout << "  1 | 2 | 3\n";
        cout << "  --+---+--\n";
        cout << "  4 | 5 | 6\n";
        cout << "  --+---+--\n";
        cout << "  7 | 8 | 9\n\n";
    }

    bool realizarMovimiento(int posicion)
    {
        if (posicion < 1 || posicion > 9)
        {
            cout << "Posición inválida. Debe ser entre 1 y 9.\n";
            return false;
        }

        int fila = (posicion - 1) / 3;
        int col = (posicion - 1) % 3;

        if (tablero[fila][col] != ' ')
        {
            cout << "Esa posición ya está ocupada. Intenta otra.\n";
            return false;
        }

        tablero[fila][col] = jugadorActual;
        movimientos++;
        return true;
    }

    bool verificarGanador()
    {
        casillasGanadoras.clear();
        direccionGanadora = 'N';

        for (int i = 0; i < 3; i++)
        {
            if (tablero[i][0] == jugadorActual &&
                tablero[i][1] == jugadorActual &&
                tablero[i][2] == jugadorActual)
            {
                casillasGanadoras = {{i, 0}, {i, 1}, {i, 2}};
                direccionGanadora = 'H';
                return true;
            }
        }

        for (int j = 0; j < 3; j++)
        {
            if (tablero[0][j] == jugadorActual &&
                tablero[1][j] == jugadorActual &&
                tablero[2][j] == jugadorActual)
            {
                casillasGanadoras = {{0, j}, {1, j}, {2, j}};
                direccionGanadora = 'V';
                return true;
            }
        }

        if (tablero[0][0] == jugadorActual &&
            tablero[1][1] == jugadorActual &&
            tablero[2][2] == jugadorActual)
        {
            casillasGanadoras = {{0, 0}, {1, 1}, {2, 2}};
            direccionGanadora = 'D';
            return true;
        }

        if (tablero[0][2] == jugadorActual &&
            tablero[1][1] == jugadorActual &&
            tablero[2][0] == jugadorActual)
        {
            casillasGanadoras = {{0, 2}, {1, 1}, {2, 0}};
            direccionGanadora = 'A';
            return true;
        }

        return false;
    }

    bool verificarPosibleGanador(char simbolo)
    {
        char temp = jugadorActual;
        jugadorActual = simbolo;
        bool resultado = verificarGanador();
        jugadorActual = temp;
        return resultado;
    }

    bool esEmpate()
    {
        return movimientos == 9;
    }

    void cambiarJugador()
    {
        jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
    }

    char getJugadorActual()
    {
        return jugadorActual;
    }

    bool esContraPC()
    {
        return contraPC;
    }

    char getSimboloJugador()
    {
        return simboloJugador;
    }

    char getSimboloPC()
    {
        return simboloPC;
    }

    int obtenerMovimientoPC()
    {
        for (int i = 1; i <= 9; i++)
        {
            int fila = (i - 1) / 3;
            int col = (i - 1) % 3;
            if (tablero[fila][col] == ' ')
            {
                tablero[fila][col] = simboloPC;
                if (verificarPosibleGanador(simboloPC))
                {
                    tablero[fila][col] = ' ';
                    return i;
                }
                tablero[fila][col] = ' ';
            }
        }

        for (int i = 1; i <= 9; i++)
        {
            int fila = (i - 1) / 3;
            int col = (i - 1) % 3;
            if (tablero[fila][col] == ' ')
            {
                tablero[fila][col] = simboloJugador;
                if (verificarPosibleGanador(simboloJugador))
                {
                    tablero[fila][col] = ' ';
                    return i;
                }
                tablero[fila][col] = ' ';
            }
        }

        if (tablero[1][1] == ' ')
        {
            return 5;
        }

        vector<int> esquinas = {1, 3, 7, 9};
        vector<int> esquinasDisponibles;
        for (int esquina : esquinas)
        {
            int fila = (esquina - 1) / 3;
            int col = (esquina - 1) % 3;
            if (tablero[fila][col] == ' ')
            {
                esquinasDisponibles.push_back(esquina);
            }
        }
        if (!esquinasDisponibles.empty())
        {
            return esquinasDisponibles[rand() % esquinasDisponibles.size()];
        }

        vector<int> disponibles;
        for (int i = 1; i <= 9; i++)
        {
            int fila = (i - 1) / 3;
            int col = (i - 1) % 3;
            if (tablero[fila][col] == ' ')
            {
                disponibles.push_back(i);
            }
        }
        if (!disponibles.empty())
        {
            return disponibles[rand() % disponibles.size()];
        }

        return -1;
    }

    void reiniciar()
    {
        tablero = vector<vector<char>>(3, vector<char>(3, ' '));
        jugadorActual = 'X';
        movimientos = 0;
        casillasGanadoras.clear();
        direccionGanadora = 'N';
    }
};

void limpiarBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void mostrarMenu()
{
    cout << "\n=================================\n";
    cout << "    BIENVENIDO AL JUEGO DEL GATO    \n";
    cout << "=================================\n\n";
    cout << "Selecciona el modo de juego:\n";
    cout << "1. Jugador vs Jugador\n";
    cout << "2. Jugador vs PC\n";
    cout << "3. Salir\n";
    cout << "\nOpción: ";
}

int main()
{
    setlocale(LC_ALL, "es_ES.UTF-8");
    srand(time(0));
    TicTacToe juego;
    bool salir = false;

    while (!salir)
    {
        mostrarMenu();
        int opcion;
        cin >> opcion;

        if (cin.fail())
        {
            limpiarBuffer();
            cout << "Opción inválida. Intenta de nuevo.\n";
            continue;
        }

        if (opcion == 3)
        {
            cout << "\n¡Gracias por jugar! ¡Hasta pronto!\n";
            salir = true;
            continue;
        }

        if (opcion != 1 && opcion != 2)
        {
            cout << "Opción inválida. Por favor selecciona 1, 2 o 3.\n";
            continue;
        }

        bool contraPC = (opcion == 2);
        juego.configurarModo(contraPC);

        int winsX = 0;
        int winsO = 0;
        int draws = 0;
        int winsO_PC = 0;

        char jugarOtraVez;

        do
        {
            juego.reiniciar();
            juego.mostrarPosiciones();

            bool juegoTerminado = false;

            while (!juegoTerminado)
            {
                juego.mostrarTablero();

                if (contraPC && juego.getJugadorActual() == juego.getSimboloPC())
                {
                    cout << "Turno de la PC (" << juego.getSimboloPC() << ")...\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    int movimientoPC = juego.obtenerMovimientoPC();
                    juego.realizarMovimiento(movimientoPC);
                    cout << "La PC eligió la posición: " << movimientoPC << "\n";
                }
                else
                {
                    if (contraPC)
                    {
                        cout << "Tu turno (Jugador " << juego.getSimboloJugador() << ")\n";
                    }
                    else
                    {
                        cout << "Turno del jugador " << juego.getJugadorActual() << "\n";
                    }
                    cout << "Ingresa la posición (1-9): ";

                    int posicion;
                    cin >> posicion;

                    if (cin.fail())
                    {
                        limpiarBuffer();
                        cout << "Entrada inválida. Por favor ingresa un número.\n";
                        continue;
                    }

                    if (!juego.realizarMovimiento(posicion))
                    {
                        continue;
                    }
                }

                if (juego.verificarGanador())
                {
                    juego.mostrarTablero();

                    char ganador = juego.getJugadorActual();

                    if (ganador == 'X')
                    {
                        winsX++;
                    }
                    else if (ganador == 'O')
                    {
                        winsO++;
                        if (contraPC && ganador == juego.getSimboloPC())
                        {
                            winsO_PC++;
                        }
                    }
                    else if(juego.esEmpate())
                    {
                            draws++;
                    }

                    if (contraPC && ganador == juego.getSimboloPC())
                    {
                        cout << "La PC ha ganado. ¡Mejor suerte la próxima vez!\n";
                    }
                    else if (contraPC && ganador == juego.getSimboloJugador())
                    {
                        cout << "¡¡¡FELICIDADES!!! ¡Has ganado contra la PC!\n";
                    }
                    else
                    {
                        cout << "¡¡¡FELICIDADES!!! El jugador " << ganador << " ha ganado!\n";
                    }

                    cout << "\n--- Marcador (modo ";
                    cout << (contraPC ? "Jugador vs PC" : "Jugador vs Jugador") << ") ---\n";
                    cout << "Ganadas X: " << winsX << "\n";
                    cout << "Ganadas O: " << winsO;
                    if (contraPC)
                        cout << "  (PC: " << winsO_PC << ")";
                    cout << "\n------------------------------------\n";

                    juegoTerminado = true;
                }
                else if (juego.esEmpate())
                {
                    juego.mostrarTablero();
                    cout << "¡Es un empate! El tablero está lleno.\n";

                    draws++;

                    cout << "\n--- Marcador (modo ";
                    cout << (contraPC ? "Jugador vs PC" : "Jugador vs Jugador") << ") ---\n";
                    cout << "Ganadas X: " << winsX << "\n";
                    cout << "Ganadas O: " << winsO;
                    if (contraPC) cout << "  (PC: " << winsO_PC << ")";
                    cout << "\nEmpates: " << draws << "\n";
                    cout << "------------------------------------\n";

                    juegoTerminado = true;
                }
                else
                {
                    juego.cambiarJugador();
                }
            }

            cout << "\n¿Quieres jugar otra vez en este modo? (s/n): ";
            cin >> jugarOtraVez;
            cout << "\n";

            if (jugarOtraVez == 'n' || jugarOtraVez == 'N')
            {
                winsX = 0;
                winsO = 0;
                draws = 0;
                winsO_PC = 0;
                cout << "Marcadores reiniciados.\n\n";
            }

        } while (jugarOtraVez == 's' || jugarOtraVez == 'S');
    }

    return 0;
}
