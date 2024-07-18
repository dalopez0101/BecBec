#include "Jefe.h"





Jefe::Jefe(int grupo, std::vector<Becario> becarios){
	becarios[grupo];
	id = grupo;
	this->becarios = becarios;
}

//funcion utilizada cuando becario pida ayuda
void Jefe::ayudarBecario(int nBecario, string tarea){

	printf("jefe de grupo %i auda a completar la tarea (%s)", nBecario, tarea);
}

//funcion que asigna tarea a becario
void Jefe::asignarTarea(int idBecario, vector<Becario> becario)
{
	becario[idBecario].nuevaTarea();
	printf("el jefe asigna la tarea %s al becario n# %i\n\n", becario[idBecario].getTarea().c_str(), idBecario);
}


