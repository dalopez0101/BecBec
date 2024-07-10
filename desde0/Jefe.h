#ifndef JEFE_H
#define JEFE_H
#include "Becario.h"

class Jefe
{
public:
	Jefe(int grupo);
	void asignarGrupo();
	void ayudarBecario();


private:
	int grupo;
};




#endif // !JEFE_H

