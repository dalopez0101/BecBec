#include<vector>
#include <string>
#ifndef CATEGORY_H
#define CATEGORY_H

using namespace std;
vector<string> roles = { "software", "hardware", "bases de datos", "redes" };

vector<vector<string>> tareas = {
    {"programas", "revision del SO", "se", "sr", "sa"}, // software
    {"revision de componentes", "reparacion", "ee", "erw", "efwf"}, // hardware
    {"actualizaciones", "revision por accesos no autorizados", "archivos corruptos", "desconexion", "almacenamiento"}, // redes
    {"configuracion de red", "monitorizacion", "seguridad", "optimizacion", ""}
};

#endif // !CATEGORY_H
