#include <stdio.h>
#include "funciones.h"

int main() {
    struct Equipo equipos[5];
    struct Partido partidos[20];
    int totalEquipos = 0, totalPartidos = 0;
    int opc;

    totalEquipos = cargarEquipos(equipos);
    totalPartidos = cargarPartidos(partidos);

    do {
        opc = menu();
        switch (opc) {
            case 1: inicializarEquipos(equipos, &totalEquipos); break;
            case 2: mostrarEquipos(equipos, totalEquipos); break;
            case 3: registrarPartido(partidos, &totalPartidos, equipos, totalEquipos); break;
            case 4: mostrarPartidos(partidos, totalPartidos); break;
            case 5: mostrarGoleador(equipos, totalEquipos); break;
            case 6: mostrarTabla(equipos, totalEquipos); break;
            case 7: printf("Saliendo...\n"); break;
            default: printf("Opci\u00f3n inv\u00e1lida\n");
        }
    } while (opc != 7);

    return 0;
}

