#include "Becario.h"

Becario::Becario(){
	rol=roles[rand()%cntRoles];
}

void Becario::setGrupo(int n){
	this->grupo = n;
}

void Becario::nuevaTarea(){
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

int Becario::getGrupo()
{
	return this->grupo;
}
