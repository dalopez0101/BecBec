#include "Rol.h"

const std::string roles[cntRoles] = { "software", "hardware", "bases de datos", "redes" };

const std::string tareas[cntRoles][cntTareas] = {
    {"programas", "revision del SO", "", "", ""}, // software
    {"revision de componentes", "reparacion", "", "", ""}, // hardware
    {"actualizaciones", "revision por accesos no autorizados", "archivos corruptos", "desconexion", "almacenamiento"}, // bases de datos
    {"configuracion de red", "monitorizacion", "seguridad", "optimizacion", ""} // redes
};