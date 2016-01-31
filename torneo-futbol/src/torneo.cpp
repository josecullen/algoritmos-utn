//
//  torneo.cpp
//  Trabajo Práctico
//

#include "torneo.h"
#include <stdlib.h>
#include <strings.h>
#include <math.h>

double randomNumber()
{
    return ((double)rand()) / RAND_MAX;
}

void trimString(char *txt)
{
    size_t len = strlen(txt);
    size_t s = 0;
    while(txt[s] == ' ' && txt[s] != '\0') {
        s++;
    }
    for(size_t i = 0; i <= len - s; i++) {
        txt[i] = txt[i + s];
    }
    len -= s;
    if (len > 0 && txt[len - 1] == '\n') {
        txt[len - 1] = '\0';
    }
}

void generarPartido(int equipos, int fecha, int partido, int &local, int &visitante)
{
    local = equipos + fecha - partido;
    visitante = equipos + fecha + partido;
    if (equipos % 2 == 0) {
        if(fecha < partido - 1) {
            visitante--;
        }
        else if(fecha * 2 >= equipos && fecha + partido >= equipos) {
            local++;
        }
        else if(partido - fecha == 1 || partido + fecha == equipos - 1) {
            local = fecha;
            visitante = equipos - 1;
        }
    }
    if(fecha % 2 == 0) {
        int aux = local;
        local = visitante;
        visitante = aux;
    }
    local = local % equipos;
    visitante = visitante % equipos;
}

void simularPartido(int ataqueLocal, int defensaLocal, int ataqueVisitante, int defensaVisitante, int &golesLocal, int &golesVisitante)
{
    golesLocal = round(sqrt(100 + ataqueLocal - defensaVisitante) * pow(randomNumber(), 2) * randomNumber());
    golesVisitante = round(sqrt(100 + ataqueVisitante - defensaLocal) * pow(randomNumber(), 2) * randomNumber());
}
