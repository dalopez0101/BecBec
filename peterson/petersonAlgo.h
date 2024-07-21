#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

std::atomic<bool> flag[2];
int turn;
int counter = 0;

void peterson_algorithm(int id) {
    int other = 1 - id;  // El otro proceso
    for (int i = 0; i < 10; ++i) {
        // Entrada a la secci�n cr�tica
        flag[id] = true;
        turn = other;
        while (flag[other] && turn == other) {
            // Esperar
        }

        // Secci�n cr�tica
        counter++;
        std::cout << "Proceso " << id << " en la secci�n cr�tica. Contador: " << counter << std::endl;

        // Salida de la secci�n cr�tica
        flag[id] = false;

        // Simular alg�n trabajo fuera de la secci�n cr�tica
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    // Inicializaci�n
    flag[0] = false;
    flag[1] = false;
    turn = 0;

    // Creaci�n de los hilos
    std::thread t1(peterson_algorithm, 0);
    std::thread t2(peterson_algorithm, 1);

    // Esperar a que los hilos terminen
    t1.join();
    t2.join();

    std::cout << "Valor final del contador: " << counter << std::endl;
    return 0;
}
