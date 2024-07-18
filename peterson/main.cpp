#include "Jefe.h"
#include "Becario.h"
#include <vector>
#include <thread>

using namespace std;

int main() {
    const int numBecarios = 5;
    vector<Becario> becarios(numBecarios);
    Jefe jefe(1, becarios);  // Crear una instancia de Jefe

    // Crear hilos para asignar tareas a cada becario
    vector<thread> threads;
    for (int i = 0; i < numBecarios; ++i) {
        threads.emplace_back(jefe.asignarTarea(i, becarios));  // Llamar a asignarTarea para cada becario
    }

    // Esperar a que todos los hilos terminen
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
