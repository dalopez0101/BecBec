#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;

std::atomic<bool> want_to_enter[2];  // Flags to indicate interest
std::atomic<int> turn;                // Turn variable

void dekker(int process_id) {
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
        std::cout << "Process " << process_id << " is in the critical section.\n";

        // Simulate some processing time
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Exit critical section
        turn = other_process_id; // Pass turn to the other process
        want_to_enter[process_id] = false; // No longer want to enter
    }
}

int main() {
    // Create two threads for the two processes
    std::thread t1(dekker, 0); // Process 0
    std::thread t2(dekker, 1); // Process 1

    // Wait for both threads to finish
    t1.join();
    t2.join();

    return 0;
}