#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

// Variables compartidas
atomic<bool> flag[2];
atomic<int> turn(0); // Variable para controlar el turno
int buildingStatus = 1; // Estado inicial del edificio (ejemplo)

// Inicializar las variables at�micas
void initFlags() {
    flag[0] = false;
    flag[1] = false;
}

// Funci�n que simula la tarea de revisar el edificio
void reviewBuilding(int buildingNumber) {
    cout << "Becario revisando el estado del edificio " << buildingNumber << endl;
    // Simulaci�n de revisi�n del estado del edificio
    // Puede incluir l�gica para cambiar el estado del edificio
    this_thread::sleep_for(chrono::seconds(1)); // Simulaci�n de tiempo de revisi�n
    cout << "Revisi�n del edificio " << buildingNumber << " completada." << endl;
}

// Funci�n que simula la asignaci�n de tareas por el jefe
void assignTask(int becarioId) {
    // Tareas posibles
    string tasks[] = { "reparar hardware", "revisi�n de redes", "revisi�n de equipo" };
    int buildingNumber = becarioId + 1; // N�mero de edificio asignado (simplificado)

    // Simulaci�n de asignaci�n de tarea aleatoria
    int taskIndex = rand() % 3; // Se elige una tarea al azar
    string task = tasks[taskIndex];
    cout << "Jefe asigna tarea al becario " << becarioId << ": " << task << endl;

    // Entrar a la secci�n cr�tica (revisi�n del edificio) usando el algoritmo de Peterson
    flag[becarioId] = true;
    turn = 1 - becarioId;
    while (flag[1 - becarioId] && turn == 1 - becarioId) {
        // Esperar a que sea el turno del becario actual
    }

    // Secci�n cr�tica
    reviewBuilding(buildingNumber);

    // Salir de la secci�n cr�tica
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
