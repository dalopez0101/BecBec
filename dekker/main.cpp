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
    int getRol() {
        return rol;
    }
private:
    int rol=rand()%4;               //rol aleatorio para el becario
};

class Jefe {
public:
    void asignarTarea(Becario& becario) {
        vector<string> tareas = { "programas", "revision del SO", "antivirus", "licencias", "ofimatica","revision de componentes", "reparacion","actualizaciones", "revision por accesos no autorizados" };//tareas que se podran asignar a los becarios
        vector<vector<string>> chamba = {
            {"programas","revision so","antivirus","licencias","ofimatica"},
            {"monitores","fuente de poder","procesador"},
            {"revision de redes","reinicio de servidores"},
            {"nones","algo","prueba"}};
        string tarea;
        string chambita;
        int rol = becario.getRol();
        
        for (size_t i = 0; i < 5; i++)
        {
            chambita = chamba[rol][rand() % chamba[rol].size()];
            cout << "jefe asigna tarea: " << chambita << endl << endl;
            becario.realizarTarea(chambita);
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

        if (process_id == 0) {                                                      //aqui comienzan nuestros procesos
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
#define NPROCESS 10
int main() {
    Jefe jefe;
    Becario becario;
    srand(time(0));

    // Initialize Dekker's algorithm variables
    want_to_enter[0] = false;
    want_to_enter[1] = false;
    turn = 0;
    cout << "===becarios del departamento de informatica===" << endl << endl;
    // Create two threads for the two processes
    thread t1(dekker, 0, ref(jefe), ref(becario)); // Process 0 (Jefe)
    vector<thread> t;
    for (size_t i = 0; i < NPROCESS; i++)
    {
        t.push_back(thread(dekker, 1, ref(jefe), ref(becario)));
    }
    

    // Wait for both threads to finish
    t1.join();
    for (size_t i = 0; i < NPROCESS; i++)
    {
        t[i].join();
    }

    return 0;
}
