/*=====[Module Name]===========================================================
 * Copyright 2019 Esteban Daniel VOLENTINI <evolentini@gmail.com>
 * All rights reserved.
 * License: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 0.1.0
 * Creation Date: 2019/03/01
 */
 
/*=====[Inclusion of own header]=============================================*/

#include "alumnos.h"
#include <stdio.h>
#include <string.h>

/*=====[Inclusions of private function dependencies]=========================*/

/*=====[Definition macros of private constants]==============================*/

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/
/**
 * @brief Constante alumno Gastón valdez 17 cese catedra IDS 
 * 
 */

static const struct alumno_s VALDEZ_GASTON = {
    .apellidos = "VALDEZ",
    .nombres = "Gaston Valdez",
    .documento = "34.818.081"
};

/**
 * @brief vector que almacena a todos los alumnos correspondientes !
 *  
 * 
 */
const alumno_t ALUMNOS[] = {
    &VALDEZ_GASTON,
};

const int CANTIDAD_ALUMNOS = (sizeof(ALUMNOS) / sizeof(alumno_t));

/*=====[Definitions of private global variables]=============================*/

/*=====[Prototypes (declarations) of private functions]======================*/

/*=====[Implementations of public functions]=================================*/

/*=====[Implementations of interrupt functions]==============================*/
/**
 * @brief Realiza la serialización de un alumno por vez 
 *  Posible mejora: 
 * @param cadena numbre y apellido correspondiente a los alumnos
 * @param espacio tamaño de memoria ocupada por el char 
 * @param alumno variable de estructura que almacena los datos del alumno que deben ser serializados
 * @return true : se pudo serializar 
 * @return false : no se pudo serializar 
 * 
 */
bool SerializarAlumno(char * cadena, size_t espacio, const alumno_t alumno) {
    int resultado;
    const char FORMATO[] = "{"
        "\"documento\":\"%s\","  
        "\"apellidos\":\"%s\","  
        "\"nombres\":\"%s\"" 
    "}";

    resultado = snprintf(cadena, espacio, FORMATO, 
             alumno->documento, alumno->apellidos, alumno->nombres);

    return (resultado >= 0);
}


bool SerializarAlumnos(char * cadena, size_t espacio) {
    static const int  cantidad = sizeof(ALUMNOS) / sizeof(alumno_t);
    int posicion = snprintf(cadena, espacio, "[\r\n  ");
    bool resultado = (posicion > 0);

    if (resultado){
        for(int indice = 0; indice < cantidad; indice++ ) {
            resultado = SerializarAlumno(&cadena[posicion], espacio - posicion, ALUMNOS[indice]);
            if (resultado) {
                posicion += strlen(&cadena[posicion]);
                posicion += snprintf(&cadena[posicion], espacio - posicion, ",\r\n  ");
            } else {
                break;
            }
        }
    }

    snprintf(&cadena[posicion] - 5, espacio - posicion + 5, "\r\n]");
    return resultado;
}

/*=====[Implementations of private functions]================================*/
