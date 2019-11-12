#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "programm.h"


Bauteil* neuesBauteil(Teil *t) {
	if (t->bauteileZaehler >= t->bauteileAlloziert) {
		t->bauteileAlloziert *= 2;
		t->bauteile = (Bauteil**) realloc(t->bauteile,
				t->bauteileAlloziert * sizeof(Bauteil*));
	}
	Bauteil *b = (Bauteil*) malloc(sizeof(Bauteil));
	t->bauteile[t->bauteileZaehler++] = b;
	return b;
}
