#include <string>
#ifndef BECARIO_H
#define BECARIO_H
#include "Rol.h"
#include <ctime>

using namespace std;


class Becario {
public:
    Becario();
    void asignarTarea();
    string getRol();
    string getTarea();
private:
    int nrol;
    string rol;
    string tarea;
};

#endif // BECARIO_H