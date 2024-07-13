#ifndef JORNADA_H
#define JORNADA_H
#include <string>

class Jornadas
{
public:
	Jornadas(int jonradaActual);
	int terminarJornada(int jornadaAcutal);
	int getJornada();

private:
	int jornada[3] = { 1, 2, 3};
	int jornadaActual;
};



#endif // !JORNADA_H

