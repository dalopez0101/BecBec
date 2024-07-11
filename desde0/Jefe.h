#ifndef JEFE_H
#define JEFE_H
#include "Becario.h"
#include <cstdlib>

class Jefe
{
public:
	Jefe(int grupo, vector<Becario> becarios);
	void asignarGrupo();
	void ayudarBecario();


private:
	vector<Becario> becario;
};




#endif // !JEFE_H

