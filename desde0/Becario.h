#include <string>
#ifndef BECARIO_H
#define BECARIO_H
#include "Rol.h"
#include <ctime>

using namespace std;


class Becario {
public:
    Becario();
    string getRol();
    string getTarea();
    int getGrupo();

    void setGrupo(int n);
    void asignarTarea();

private:
    int nrol;
    string rol;
    string tarea;
    int grupo=NULL;
};

#endif // BECARIO_H