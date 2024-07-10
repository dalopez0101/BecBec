#include <cstdio>
#include <time.h>
#include "Becario.h"

#define BECARIOS_CNT 5

int main()
{
	vector<Becario> becarios;//defino cuantos becarios hay


	for (size_t i = 0; i <= BECARIOS_CNT; i++){
		becarios.push_back(Becario());

	}
	for (auto& becario:becarios){
		becario.asignarTarea();
	}
	for (auto& becario:becarios) {
		printf("%s %s", becario.getRol().c_str(), becario.getTarea().c_str());
		
	}
	printf("\n");
	for (size_t i = 0; i < becarios.size(); i++)
	{
		printf("%s %s", becarios[i].getRol().c_str(), becarios[i].getTarea().c_str());

	}

    return 0;
}