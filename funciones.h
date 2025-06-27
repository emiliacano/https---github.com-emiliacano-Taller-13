#ifndef FUNCIONES_H
#define FUNCIONES_H

struct Jugador {
    char nombre[30];
    int goles;
};

struct Equipo {
    char nombre[30];
    struct Jugador jugadores[3];
    int puntos;
};

struct Partido {
    char equipo1[30];
    char equipo2[30];
    int goles1;
    int goles2;
};

int menu();
void leerCadena(char *cadena, int tam);
void inicializarEquipos(struct Equipo equipos[], int *totalEquipos);
void mostrarEquipos(struct Equipo equipos[], int totalEquipos);
void registrarPartido(struct Partido partidos[], int *totalPartidos, struct Equipo equipos[], int totalEquipos);
void mostrarPartidos(struct Partido partidos[], int totalPartidos);
void mostrarGoleador(struct Equipo equipos[], int totalEquipos);
void mostrarTabla(struct Equipo equipos[], int totalEquipos);
void guardarEquipos(struct Equipo equipos[], int totalEquipos);
int cargarEquipos(struct Equipo equipos[]);
void guardarPartidos(struct Partido partidos[], int totalPartidos);
int cargarPartidos(struct Partido partidos[]);

#endif
