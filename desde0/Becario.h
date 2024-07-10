#include <string>
#ifndef BECARIO_H
#define BECARIO_H
#include "Rol.h"




using namespace std;


class Becario {
public:
    Becario();
    void asignarTarea();
    string getRol();
    string getTarea();
private:
    int nrol = rand() % (sizeof(roles) / sizeof(roles[0]));
    std::string rol = roles[nrol];
    std::string tarea="sin tareas";
};

#endif // BECARIO_H