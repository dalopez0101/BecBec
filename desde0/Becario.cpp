#include "Becario.h"

Becario::Becario(){
	rol=roles[rand()%cntRoles];
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