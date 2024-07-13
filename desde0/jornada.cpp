#include "jornada.h"

Jornadas::Jornadas(int jonradaActual){

}

int Jornadas::terminarJornada(int jornadaAcutal){
	if (jornadaAcutal>0 && jornadaAcutal<3){

		this->jornadaActual++;
	}
	else
	{
		this->jornadaActual = 0;
	}
}

int Jornadas::getJornada()
{
	return this->jornadaActual;
}

