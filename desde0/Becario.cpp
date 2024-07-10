#include "Becario.h"

Becario::Becario()
{
}

void Becario::asignarTarea(){
	this->tarea = tareas[nrol][rand()%(sizeof(tareas[nrol]) / sizeof(tareas[nrol][0]))].c_str();
}

string Becario::getRol()
{
	return this->tarea;
}

string Becario::getTarea()
{
	return string();
}