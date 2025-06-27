#include <stdio.h>
#include <string.h>
#include "funciones.h"

int menu() {
    int opc;
    printf("\n--- MENU FUTBOL ---\n");
    printf("1. Inicializar equipos y jugadores\n");
    printf("2. Ver equipos y jugadores\n");
    printf("3. Registrar partido\n");
    printf("4. Ver partidos\n");
    printf("5. Mostrar goleador\n");
    printf("6. Tabla de posiciones\n");
    printf("7. Salir\n");
    printf("Opci\u00f3n: ");
    scanf("%d", &opc);
    return opc;
}

void leerCadena(char *cadena, int tam) {
    fflush(stdin);
    fgets(cadena, tam, stdin);
    cadena[strcspn(cadena, "\n")] = '\0';
}

void inicializarEquipos(struct Equipo equipos[], int *totalEquipos) {
    printf("\u00bfCu\u00e1ntos equipos desea ingresar? (m\u00e1x 5): ");
    scanf("%d", totalEquipos);
    for (int i = 0; i < *totalEquipos; i++) {
        printf("Nombre del equipo %d: ", i + 1);
        leerCadena(equipos[i].nombre, 30);
        equipos[i].puntos = 0;
        for (int j = 0; j < 3; j++) {
            printf("  Nombre del jugador %d: ", j + 1);
            leerCadena(equipos[i].jugadores[j].nombre, 30);
            equipos[i].jugadores[j].goles = 0;
        }
    }
    guardarEquipos(equipos, *totalEquipos);
}

void mostrarEquipos(struct Equipo equipos[], int totalEquipos) {
    for (int i = 0; i < totalEquipos; i++) {
        printf("\nEquipo: %s\n", equipos[i].nombre);
        for (int j = 0; j < 3; j++) {
            printf("  Jugador: %s | Goles: %d\n", equipos[i].jugadores[j].nombre, equipos[i].jugadores[j].goles);
        }
        printf("  Puntos: %d\n", equipos[i].puntos);
    }
}

void registrarPartido(struct Partido partidos[], int *totalPartidos, struct Equipo equipos[], int totalEquipos) {
    int eq1, eq2, goles, jugador;

    printf("Seleccione el equipo 1:\n");
    for (int i = 0; i < totalEquipos; i++)
        printf("%d. %s\n", i, equipos[i].nombre);
    scanf("%d", &eq1);

    printf("Seleccione el equipo 2:\n");
    for (int i = 0; i < totalEquipos; i++)
        if (i != eq1)
            printf("%d. %s\n", i, equipos[i].nombre);
    scanf("%d", &eq2);

    partidos[*totalPartidos].goles1 = 0;
    partidos[*totalPartidos].goles2 = 0;

    printf("Goles del equipo %s: ", equipos[eq1].nombre);
    scanf("%d", &goles);
    partidos[*totalPartidos].goles1 = goles;

    for (int i = 0; i < goles; i++) {
        printf("  \u00bfQui\u00e9n anot\u00f3 el gol %d? (0-2): ", i + 1);
        scanf("%d", &jugador);
        equipos[eq1].jugadores[jugador].goles++;
    }

    printf("Goles del equipo %s: ", equipos[eq2].nombre);
    scanf("%d", &goles);
    partidos[*totalPartidos].goles2 = goles;

    for (int i = 0; i < goles; i++) {
        printf("  \u00bfQui\u00e9n anot\u00f3 el gol %d? (0-2): ", i + 1);
        scanf("%d", &jugador);
        equipos[eq2].jugadores[jugador].goles++;
    }

    strcpy(partidos[*totalPartidos].equipo1, equipos[eq1].nombre);
    strcpy(partidos[*totalPartidos].equipo2, equipos[eq2].nombre);

    if (partidos[*totalPartidos].goles1 > partidos[*totalPartidos].goles2)
        equipos[eq1].puntos += 3;
    else if (partidos[*totalPartidos].goles1 < partidos[*totalPartidos].goles2)
        equipos[eq2].puntos += 3;
    else {
        equipos[eq1].puntos += 1;
        equipos[eq2].puntos += 1;
    }

    (*totalPartidos)++;
    guardarPartidos(partidos, *totalPartidos);
    guardarEquipos(equipos, totalEquipos);
}

void mostrarPartidos(struct Partido partidos[], int totalPartidos) {
    printf("\nPartidos jugados:\n");
    for (int i = 0; i < totalPartidos; i++) {
        printf("%s %d - %d %s\n", partidos[i].equipo1, partidos[i].goles1, partidos[i].goles2, partidos[i].equipo2);
    }
}

void mostrarGoleador(struct Equipo equipos[], int totalEquipos) {
    int maxGoles = -1;
    char nombre[30] = "";

    for (int i = 0; i < totalEquipos; i++) {
        for (int j = 0; j < 3; j++) {
            if (equipos[i].jugadores[j].goles > maxGoles) {
                maxGoles = equipos[i].jugadores[j].goles;
                strcpy(nombre, equipos[i].jugadores[j].nombre);
            }
        }
    }

    if (maxGoles > 0)
        printf("Goleador del torneo: %s con %d %s\n", nombre, maxGoles, (maxGoles == 1 ? "gol" : "goles"));
    else
        printf("No hay goles a\u00fan.\n");
}

void mostrarTabla(struct Equipo equipos[], int totalEquipos) {
    printf("\nTabla de posiciones:\n");
    for (int i = 0; i < totalEquipos; i++) {
        printf("%s - %d puntos\n", equipos[i].nombre, equipos[i].puntos);
    }
}

void guardarEquipos(struct Equipo equipos[], int totalEquipos) {
    FILE *f = fopen("equipos.dat", "wb");
    if (f != NULL) {
        fwrite(&totalEquipos, sizeof(int), 1, f);
        fwrite(equipos, sizeof(struct Equipo), totalEquipos, f);
        fclose(f);
    }
}

int cargarEquipos(struct Equipo equipos[]) {
    FILE *f = fopen("equipos.dat", "rb");
    int total = 0;
    if (f != NULL) {
        fread(&total, sizeof(int), 1, f);
        fread(equipos, sizeof(struct Equipo), total, f);
        fclose(f);
    }
    return total;
}

void guardarPartidos(struct Partido partidos[], int totalPartidos) {
    FILE *f = fopen("partidos.dat", "wb");
    if (f != NULL) {
        fwrite(&totalPartidos, sizeof(int), 1, f);
        fwrite(partidos, sizeof(struct Partido), totalPartidos, f);
        fclose(f);
    }
}

int cargarPartidos(struct Partido partidos[]) {
    FILE *f = fopen("partidos.dat", "rb");
    int total = 0;
    if (f != NULL) {
        fread(&total, sizeof(int), 1, f);
        fread(partidos, sizeof(struct Partido), total, f);
        fclose(f);
    }
    return total;
}
