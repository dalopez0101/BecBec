#include <string>
#ifndef ROL_H
#define ROL_H

using namespace std;
std::string roles[4] = { "software", "hardware", "bases de datos", "redes" }; // Lista de roles


std::string tareas[4][5] = {
        {"programas", "revision del SO", "", "", ""}, // software
        {"revision de componentes", "reparacion", "", "", ""}, // hardware
        {"actualizaciones", "revision por accesos no autorizados", "archivos corruptos", "desconexion", "almacenamiento"}, // redes
        {"configuracion de red", "monitorizacion", "seguridad", "optimizacion", ""} // no se
};

#endif // ROL_H

