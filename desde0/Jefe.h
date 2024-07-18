#ifndef JEFE_H
#define JEFE_H
#include "Becario.h"
#include <cstdlib>

class Jefe
{
public:
	
	Jefe(int grupo, vector<Becario> becarios);
	void ayudarBecario(int nBecario, string tarea);
	void asignarTarea(int idBecario, vector<Becario> becario);

private:
};




#endif // !JEFE_H

