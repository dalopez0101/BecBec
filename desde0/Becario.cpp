#include "Becario.h"

Becario::Becario()
	: nrol(rand() % cntRoles), rol(roles[nrol]), tarea("sin tareas") {
	srand(static_cast<unsigned>(time(nullptr)));
}

void Becario::asignarTarea(){
	int ntarea = rand() % cntTareas;
	this->tarea = tareas[nrol][ntarea];
}

string Becario::getRol()
{
	return this->rol;
}

string Becario::getTarea()
{
	return this->tarea;
}