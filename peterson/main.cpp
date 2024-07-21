#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include <cstdlib> // Para rand y srand
#include <ctime>   // Para time

using namespace std;

const int NUM_BECARIOS = 6;
atomic<bool> flag[NUM_BECARIOS + 1]; // El índice 0 es para el jefe
int turn;
int task = 0;  //tarea actual
atomic<int> current_task[NUM_BECARIOS]; // Tareas actuales para becario

vector<string> tareas = { "trabajo a", "trabajo b", "trabajo c", "trabajo d" };

string almacen[20];

string tareaRand(int n) {
    string tarea_asignada = tareas[rand() % tareas.size()];
    almacen[n] = tarea_asignada;
    return tarea_asignada;
}

void jefe() {
    int id = 0;
    for (int i = 0; i < 10; ++i) {
        
        flag[id] = true;
        turn = 1;
        for (int j = 1; j <= NUM_BECARIOS; ++j) {
            while (flag[j] && turn == 1) {
                // Esperar
            }
        }

        for (int j = 0; j < NUM_BECARIOS; ++j) {
            task++;
            current_task[j] = task;
            cout << "Jefe: Asignando tarea " << tareaRand(j) << " al becario " << j + 1 << "." << endl;
        }

        // Salida de la sección crítica
        flag[id] = false;

        // Simular algún trabajo fuera de la sección crítica
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void becario(int id) {
    for (int i = 0; i < 10; ++i) {
        // Entrada a la sección crítica
        flag[id] = true;
        turn = 0;
        while (flag[0] && turn == 0) {
            // Esperar
        }

        // Sección crítica
        cout << "Becario " << id << ": Realizando tarea " << almacen[current_task[id - 1]] << " asignada por el jefe." << endl;

        flag[id] = false;

        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    // Inicialización
    srand(time(0));

    for (int i = 0; i <= NUM_BECARIOS; ++i) {
        flag[i] = false;
    }
    turn = 0;

    // Creación de hilos
    thread jefe_thread(jefe);
    vector<thread> becario_threads;
    for (int i = 1; i <= NUM_BECARIOS; ++i) {
        becario_threads.push_back(thread(becario, i));
    }

    // Esperar a que hilos terminen
    jefe_thread.join();
    for (auto& t : becario_threads) {
        t.join();
    }

    cout << "Todas las tareas han sido asignadas y realizadas." << endl;
    return 0;
}
