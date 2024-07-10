#include <cstdio>
#include <time.h>
#include "Becario.h"

#define BECARIOS_CNT 5
#define JEFES_CNT 2

int main()
{
	vector<Becario> becarios;


	for (size_t i = 0; i < BECARIOS_CNT; i++){//defino cuantos becarios hay Y AUTOMATICAMENTE SU ROL
		becarios.push_back(Becario());


		//asignar grupos, mas tarde la mando a clase de jefe
		if (becarios[i-1].getGrupo()<JEFES_CNT && becarios[i - 1].getGrupo() >= 0)
		{
			becarios[i].setGrupo(becarios[i - 1].getGrupo() + 1);
		}
		else
		{
			becarios[i].setGrupo(1);
		}
	}
	for (int i = 0; i < becarios.size(); i++) {//esta accion le corresponde a jefe
		becarios[i].asignarTarea();
	}

	//printf("%s %s", becario.getRol().c_str(), becario.getTarea().c_str());
	/*for (auto& becario : becarios) {//sirve pero no como quiero
		printf("%s %s", becario.getRol().c_str(), becario.getTarea().c_str());
		
	}*/
	printf("\n");
	for (size_t i = 0; i < becarios.size(); i++)
	{
		printf("becario %i encargado de %s del grupo %i esta haciendo la tarea: %s\n", i, becarios[i].getRol().c_str(), becarios[i].getGrupo(), becarios[i].getTarea().c_str());

	}

    return 0;
}