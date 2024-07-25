#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

// Variables compartidas
atomic<bool> flag[2];
atomic<int> turn(0); // Variable para controlar el turno
int buildingStatus = 1; // Estado inicial del edificio (ejemplo)

// Inicializar las variables atómicas
void initFlags() {
    flag[0] = false;
    flag[1] = false;
}

// Función que simula la tarea de revisar el edificio
void reviewBuilding(int buildingNumber) {
    cout << "Becario revisando el estado del edificio " << buildingNumber << endl;
    // Simulación de revisión del estado del edificio
    // Puede incluir lógica para cambiar el estado del edificio
    this_thread::sleep_for(chrono::seconds(1)); // Simulación de tiempo de revisión
    cout << "Revisión del edificio " << buildingNumber << " completada." << endl;
}

// Función que simula la asignación de tareas por el jefe
void assignTask(int becarioId) {
    // Tareas posibles
    string tasks[] = { "reparar hardware", "revisión de redes", "revisión de equipo" };
    int buildingNumber = becarioId + 1; // Número de edificio asignado (simplificado)

    // Simulación de asignación de tarea aleatoria
    int taskIndex = rand() % 3; // Se elige una tarea al azar
    string task = tasks[taskIndex];
    cout << "Jefe asigna tarea al becario " << becarioId << ": " << task << endl;

    // Entrar a la sección crítica (revisión del edificio) usando el algoritmo de Peterson
    flag[becarioId] = true;
    turn = 1 - becarioId;
    while (flag[1 - becarioId] && turn == 1 - becarioId) {
        // Esperar a que sea el turno del becario actual
    }

    // Sección crítica
    reviewBuilding(buildingNumber);

    // Salir de la sección crítica
    flag[becarioId] = false;
}

int main() {
    // Inicializar las flags
    initFlags();

    // Ejemplo con dos becarios (procesos)
    thread becario1(assignTask, 0);
    thread becario2(assignTask, 1);

    becario1.join();
    becario2.join();

    return 0;
}
