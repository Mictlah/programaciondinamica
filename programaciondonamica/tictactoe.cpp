#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <thread>
#include <chrono>

using namespace std;

class TicTacToe {
private:
    vector<vector<char>> tablero;
    char jugadorActual;
    int movimientos;
    bool contraPC;
    char simboloJugador;
    char simboloPC;

public:
    TicTacToe() {
        tablero = vector<vector<char>>(3, vector<char>(3, ' '));
        jugadorActual = 'X';
        movimientos = 0;
        contraPC = false;
        simboloJugador = 'X';
        simboloPC = 'O';
    }

    void configurarModo(bool esContraPC) {
        contraPC = esContraPC;
        if (contraPC) {
            simboloJugador = 'X';
            simboloPC = 'O';
        }
    }

    void mostrarTablero() {
        cout << "\n";
        for (int i = 0; i < 3; i++) {
            cout << "  ";
            for (int j = 0; j < 3; j++) {
                cout << " " << tablero[i][j];
                if (j < 2) cout << " |";
            }
            cout << "\n";
            if (i < 2) cout << "  ---+---+---\n";
        }
        cout << "\n";
    }

    void mostrarPosiciones() {
        cout << "\nPosiciones del tablero:\n";
        cout << "  1 | 2 | 3\n";
        cout << "  --+---+--\n";
        cout << "  4 | 5 | 6\n";
        cout << "  --+---+--\n";
        cout << "  7 | 8 | 9\n\n";
    }

    bool realizarMovimiento(int posicion) {
        if (posicion < 1 || posicion > 9) {
            cout << "Posición inválida. Debe ser entre 1 y 9.\n";
            return false;
        }

        int fila = (posicion - 1) / 3;
        int col = (posicion - 1) % 3;

        if (tablero[fila][col] != ' ') {
            cout << "Esa posición ya está ocupada. Intenta otra.\n";
            return false;
        }

        tablero[fila][col] = jugadorActual;
        movimientos++;
        return true;
    }

    bool verificarGanador() {
        // Verificar filas
        for (int i = 0; i < 3; i++) {
            if (tablero[i][0] == jugadorActual &&
                tablero[i][1] == jugadorActual &&
                tablero[i][2] == jugadorActual) {
                return true;
            }
        }

        // Verificar columnas
        for (int j = 0; j < 3; j++) {
            if (tablero[0][j] == jugadorActual &&
                tablero[1][j] == jugadorActual &&
                tablero[2][j] == jugadorActual) {
                return true;
            }
        }

        // Verificar diagonal principal
        if (tablero[0][0] == jugadorActual &&
            tablero[1][1] == jugadorActual &&
            tablero[2][2] == jugadorActual) {
            return true;
        }

        // Verificar diagonal secundaria
        if (tablero[0][2] == jugadorActual &&
            tablero[1][1] == jugadorActual &&
            tablero[2][0] == jugadorActual) {
            return true;
        }

        return false;
    }

    bool verificarPosibleGanador(char simbolo) {
        char temp = jugadorActual;
        jugadorActual = simbolo;
        bool resultado = verificarGanador();
        jugadorActual = temp;
        return resultado;
    }

    bool esEmpate() {
        return movimientos == 9;
    }

    void cambiarJugador() {
        jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
    }

    char getJugadorActual() {
        return jugadorActual;
    }

    bool esContraPC() {
        return contraPC;
    }

    char getSimboloJugador() {
        return simboloJugador;
    }

    char getSimboloPC() {
        return simboloPC;
    }

    // Movimiento inteligente de la PC
    int obtenerMovimientoPC() {
        // 1. Intentar ganar
        for (int i = 1; i <= 9; i++) {
            int fila = (i - 1) / 3;
            int col = (i - 1) % 3;
            if (tablero[fila][col] == ' ') {
                tablero[fila][col] = simboloPC;
                if (verificarPosibleGanador(simboloPC)) {
                    tablero[fila][col] = ' ';
                    return i;
                }
                tablero[fila][col] = ' ';
            }
        }

        // 2. Bloquear al jugador
        for (int i = 1; i <= 9; i++) {
            int fila = (i - 1) / 3;
            int col = (i - 1) % 3;
            if (tablero[fila][col] == ' ') {
                tablero[fila][col] = simboloJugador;
                if (verificarPosibleGanador(simboloJugador)) {
                    tablero[fila][col] = ' ';
                    return i;
                }
                tablero[fila][col] = ' ';
            }
        }

        // 3. Tomar el centro si está disponible
        if (tablero[1][1] == ' ') {
            return 5;
        }

        // 4. Tomar una esquina
        vector<int> esquinas = { 1, 3, 7, 9 };
        vector<int> esquinasDisponibles;
        for (int esquina : esquinas) {
            int fila = (esquina - 1) / 3;
            int col = (esquina - 1) % 3;
            if (tablero[fila][col] == ' ') {
                esquinasDisponibles.push_back(esquina);
            }
        }
        if (!esquinasDisponibles.empty()) {
            return esquinasDisponibles[rand() % esquinasDisponibles.size()];
        }

        // 5. Tomar cualquier posición disponible
        vector<int> disponibles;
        for (int i = 1; i <= 9; i++) {
            int fila = (i - 1) / 3;
            int col = (i - 1) % 3;
            if (tablero[fila][col] == ' ') {
                disponibles.push_back(i);
            }
        }
        if (!disponibles.empty()) {
            return disponibles[rand() % disponibles.size()];
        }

        return -1;
    }

    void reiniciar() {
        tablero = vector<vector<char>>(3, vector<char>(3, ' '));
        jugadorActual = 'X';
        movimientos = 0;
    }
};

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void mostrarMenu() {
    cout << "\n=================================\n";
    cout << "    BIENVENIDO AL JUEGO DEL GATO    \n";
    cout << "=================================\n\n";
    cout << "Selecciona el modo de juego:\n";
    cout << "1. Jugador vs Jugador\n";
    cout << "2. Jugador vs PC\n";
    cout << "3. Salir\n";
    cout << "\nOpción: ";
}

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
    srand(time(0));
    TicTacToe juego;
    bool salir = false;

    while (!salir) {
        mostrarMenu();
        int opcion;
        cin >> opcion;

        if (cin.fail()) {
            limpiarBuffer();
            cout << "Opción inválida. Intenta de nuevo.\n";
            continue;
        }

        if (opcion == 3) {
            cout << "\n¡Gracias por jugar! ¡Hasta pronto!\n";
            salir = true;
            continue;
        }

        if (opcion != 1 && opcion != 2) {
            cout << "Opción inválida. Por favor selecciona 1, 2 o 3.\n";
            continue;
        }

        bool contraPC = (opcion == 2);
        juego.configurarModo(contraPC);

        char jugarOtraVez;

        do {
            juego.reiniciar();
            juego.mostrarPosiciones();

            bool juegoTerminado = false;

            while (!juegoTerminado) {
                juego.mostrarTablero();

                if (contraPC && juego.getJugadorActual() == juego.getSimboloPC()) {
                    // Turno de la PC
                    cout << "Turno de la PC (" << juego.getSimboloPC() << ")...\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    int movimientoPC = juego.obtenerMovimientoPC();
                    juego.realizarMovimiento(movimientoPC);
                    cout << "La PC eligió la posición: " << movimientoPC << "\n";
                }
                else {
                    // Turno del jugador humano
                    if (contraPC) {
                        cout << "Tu turno (Jugador " << juego.getSimboloJugador() << ")\n";
                    }
                    else {
                        cout << "Turno del jugador " << juego.getJugadorActual() << "\n";
                    }
                    cout << "Ingresa la posición (1-9): ";

                    int posicion;
                    cin >> posicion;

                    if (cin.fail()) {
                        limpiarBuffer();
                        cout << "Entrada inválida. Por favor ingresa un número.\n";
                        continue;
                    }

                    if (!juego.realizarMovimiento(posicion)) {
                        continue;
                    }
                }

                if (juego.verificarGanador()) {
                    juego.mostrarTablero();
                    if (contraPC && juego.getJugadorActual() == juego.getSimboloPC()) {
                        cout << "La PC ha ganado. ¡Mejor suerte la próxima vez!\n";
                    }
                    else if (contraPC) {
                        cout << "¡¡¡FELICIDADES!!! ¡Has ganado contra la PC!\n";
                    }
                    else {
                        cout << "¡¡¡FELICIDADES!!! El jugador " << juego.getJugadorActual() << " ha ganado!\n";
                    }
                    juegoTerminado = true;
                }
                else if (juego.esEmpate()) {
                    juego.mostrarTablero();
                    cout << "¡Es un empate! El tablero está lleno.\n";
                    juegoTerminado = true;
                }
                else {
                    juego.cambiarJugador();
                }
            }

            cout << "\n¿Quieres jugar otra vez en este modo? (s/n): ";
            cin >> jugarOtraVez;
            cout << "\n";

        } while (jugarOtraVez == 's' || jugarOtraVez == 'S');
    }

    return 0;
}