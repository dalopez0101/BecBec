#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <vector>

using namespace std;

atomic<bool> want_to_enter[2];  // Flags to indicate interest
atomic<int> turn;                // Turn variable

class Becario {
public:
    void realizarTarea(string tarea) {
        cout << "Becario realizando tarea: " << tarea << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
};

class Jefe {
public:
    void asignarTarea(Becario& becario) {
        vector<string> tareas = { "reparacion de hardware", "revision de software", "revision de redes" };
        string tarea;
        tarea = tareas[rand() % tareas.size()];
        for (int i = 0; i < tareas.size(); i++){
            cout << "jefe asigna tarea: " << tarea << endl;
            becario.realizarTarea(tarea);
        }
    }
};

void dekker(int process_id, Jefe& jefe, Becario& becario) {
    int other_process_id = 1 - process_id; // The other process's ID

    for (int i = 0; i < 5; ++i) { // Simulate some work
        // Indicate intention to enter critical section
        want_to_enter[process_id] = true;

        // Wait until it's our turn or the other process does not want to enter
        while (want_to_enter[other_process_id]) {
            if (turn != process_id) {
                want_to_enter[process_id] = false; // Withdraw interest
                while (turn != process_id) {} // Busy wait
                want_to_enter[process_id] = true; // Reassert interest
            }
        }

        // Critical section
        cout << "Process " << process_id << " is in the critical section.\n";

        if (process_id == 0) {
            jefe.asignarTarea(becario);
        }
        else {
            becario.realizarTarea("tarea adicional asignada por el becario mismo");
        }

        // Exit critical section
        turn = other_process_id; // Pass turn to the other process
        want_to_enter[process_id] = false; // No longer want to enter

        // Simulate some processing time
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    Jefe jefe;
    Becario becario;

    // Initialize Dekker's algorithm variables
    want_to_enter[0] = false;
    want_to_enter[1] = false;
    turn = 0;

    // Create two threads for the two processes
    thread t1(dekker, 0, ref(jefe), ref(becario)); // Process 0 (Jefe)
    thread t2(dekker, 1, ref(jefe), ref(becario)); // Process 1 (Becario)

    // Wait for both threads to finish
    t1.join();
    t2.join();

    return 0;
}
