#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>


#define N_TAREAS 14
#define N_BECARIOS 4
#define N_GRUPOS 3
#define N_EDIFICIOS 2
#define TIEMPO_TAREA 1
#define TIEMPO_ENTORPECEDOR 3
#define SEM_JEFE 0
#define SEM_ENTORPECEDOR 1

union senum {
    int val;
};

void inicializar(int);

// Función para asignar un grupo a cada becario
int asignarGrupo(int idBecario) {
    return idBecario % N_GRUPOS + 1; // Asignar grupos de 1 a N_GRUPOS
}
//funcion string que devolvera una tarea
string nuevaTarea() {
    string tareas[4] = { "tarea 1", "tarea2", "tarea3", "tarea 4" };
    return tareas[rand() % 4];
}

int main() {
    int sem;
    int r;
    int c, idBecario;
    int tiempoJornada = 15;
    pid_t pid;
    union senum arg;
    struct sembuf arriba = { 0, 1, 0 };
    struct sembuf abajo = { 0, -1, 0 };

    int frecuenciaEntropecedor = 4;//define que tan seguido entrara el entorpecedor en los procesos
    string tarea;

    sem = semget(IPC_PRIVATE, 2, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

    if (sem == -1) {
        perror("Error creando semáforos.");
        return -1;
    }

    arg.val = 1;
    r = semctl(sem, SEM_JEFE, SETVAL, arg);

    if (r == -1)
        perror("Error inicializando semáforo del jefe.");

    arg.val = 1;
    r = semctl(sem, SEM_ENTORPECEDOR, SETVAL, arg);
    if (r == -1)
        perror("Error inicializando semáforo del entorpecedor.");

    printf("Becarios disponibles: %i / Tareas a resolver: %i\n", N_BECARIOS, N_TAREAS);

    // Arreglo para almacenar los IDs de grupo de los becarios
    int grupos[N_BECARIOS];

    // Crear grupos
    for (int i = 1; i <= N_GRUPOS; i++) {
        printf("Creando grupo %i\n", i);
    }
    // Asignar grupos
    for (c = 0; c < N_BECARIOS; c++) {
        grupos[c] = asignarGrupo(c);
        printf("becario %i asignado a grupo %i \n\n", c, (c % N_GRUPOS + 1));
    }

    

    for (c = 0; c < N_BECARIOS; c++) {
        pid = fork();
        if (pid == -1) {
            perror("Error creando procesos.");
            return -1;
        }

        if (pid == 0) {
            idBecario = c;
            printf("Becario %i asignado al grupo %i\n", idBecario, grupos[idBecario]);

            while (tiempoJornada >=0) {
                int c = 0;
                tarea = nuevaTarea();

                printf("El jefe del grupo %i asigna la tarea: %s al becario %i\n", grupos[idBecario], tarea.c_str(), idBecario);
                abajo.sem_num = SEM_JEFE;
                r = semop(sem, &abajo, 1);
                if (r == -1)
                    perror("Error bajando semáforo del jefe.");

                printf("El becario %i realiza %s\n", idBecario, tarea.c_str());
                c++;
                arriba.sem_num = SEM_JEFE;
                r = semop(sem, &arriba, 1);
                if (r == -1)
                    perror("Error subiendo semáforo del jefe.");

                printf("El becario %i llega al lugar de la tarea\n", idBecario);
                if (frecuenciaEntropecedor >= 1 && frecuenciaEntropecedor % 2 == 0) {
                    abajo.sem_num = SEM_ENTORPECEDOR;
                    r = semop(sem, &abajo, 1);
                    if (r == -1)
                        perror("Error bajando semáforo del entorpecedor.");

                    sleep(TIEMPO_ENTORPECEDOR);
                    printf("/*acciones de entorpecedor*/ a becario %i.\n", idBecario, c); //hacer el entorpecedor
                    tiempoJornada = tiempoJornada - TIEMPO_ENTORPECEDOR;
                    arriba.sem_num = SEM_ENTORPECEDOR;
                    r = semop(sem, &arriba, 1);
                    frecuenciaEntropecedor--;
                }
                sleep(TIEMPO_TAREA);
                printf("El becario %i terminó la tarea %i\n", idBecario, c);
                tiempoJornada = tiempoJornada - TIEMPO_TAREA;
                
                if (tiempoJornada < 0) {
                    printf("El becario %i abandona las tareas (ha terminado la jornada).\n\n", idBecario);
                    exit(0);
                }
                printf("El becario %i va por otra tarea.\n", idBecario);
                
            }
            exit(0);
        }
    }

    pid = wait(&r);
    while ((pid != -1) || (pid == -1 && errno == EINTR))
        pid = wait(&r);

    r = semctl(sem, 0, IPC_RMID);
    if (r == -1)
        perror("Error eliminando semáforos.");

    printf("Fin.\n");
    return 0;
}

void inicializar(int id) {
    union senum extra;
    int r;
    extra.val = 3;
    r = semctl(id, 1, SETVAL, extra);
    if (r == -1)
        perror("Error inicializando semaforo.");
}
