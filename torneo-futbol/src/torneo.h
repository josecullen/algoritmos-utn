//
//  torneo.h
//  Trabajo Práctico
//

#ifndef __torneo__
#define __torneo__

#include <stdio.h>

/// Devuelve los equipos participantes en un partido dados la fecha y orden de partido.
/// Si hay un número impar de equipos la cantidad de fechas es igual a la de equipos.
/// Si hay un número par de equipos la cantidad de fechas es igual a la de equipos - 1.
/// La cantidad de partidos es igual a la mitad de la cantidad de equipos,
/// redondeando hacia abajo.
/// parámetros:
///     equipos           la cantidad de equipos en el torneo
///     fecha             la fecha que se quiere generar (1 a fechas)
///     partido           el numero de orden del partido (1 a partidos)
///     local             el indice de equipo local (0 a equipos - 1) (salida)
///     visitante         el indice de equipo visitante (0 a equipos - 1) (salida)
void generarPartido(int equipos, int fecha, int partido, int &local, int &visitante);

/// Simula los resultados de un partido.
/// parámetros:
///     ataqueLocal       paramA del equipo local
///     defensaLocal      paramB del equipo local
///     ataqueVisitante   paramA del equipo visitante
///     defensaVisitante  paramB del equipo visitante
///     golesLocal        goles del equipo local (salida)
///     golesVisitante    goles del equipo visitante (salida)
void simularPartido(int ataqueLocal, int defensaLocal, int ataqueVisitante, int defensaVisitante, int &golesLocal, int &golesVisitante);

/// Pueden usar esta función para quitar los espacios al ingresar los identificadores
/// de equipo después de ingresarlos, de manera tal de poder comparar correctamente al
/// buscar un equipo.
void trimString(char *txt);

#endif /* defined(__torneo__) */
