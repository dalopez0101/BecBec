#include <cstdio>
#include <time.h>
#include "Rol.h"
#include "Becario.h"

#define BECARIOS_CNT 5

int main()
{
	Becario becarios[BECARIOS_CNT];//defino cuantos becarios hay
	printf("hola %s", becarios->getRol());
	/*for (size_t i = 0; i <= BECARIOS_CNT; i++){
		becarios[i].asignarTarea();
	}
	for (size_t i = 0; i <= BECARIOS_CNT; i++) {
		printf("%s %s", becarios[i].getTarea().c_str(), becarios[i].getRol().c_str());
		
	}*/

    return 0;
}