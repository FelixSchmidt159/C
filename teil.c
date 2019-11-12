#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "programm.h"

Teil* neuesTeil() {
	Teil *teil = (Teil*) malloc(sizeof(Teil));
	teil->bauteileZaehler = 0;
	teil->bauteileAlloziert = 10;
	teil->bauteile = (Bauteil**) calloc(teil->bauteileAlloziert,
			sizeof(Bauteil*));

	teil->ausgabenZaehler = 0;
	teil->ausgabenAlloziert = 10;
	teil->ausgaben = (Ausgabe**) calloc(teil->ausgabenAlloziert,
			sizeof(Ausgabe*));

	return teil;

}

