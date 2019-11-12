#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "programm.h"


void leseDatei(Teil *t, char *dateiName, char *typ, char *bezeichnung) {
	int r;
	char zielTypGelesen[100], zielBezeichnungGelesen[100], quellTypGelesen[100],
			quellBezGelesen[100], taetigkeitGelesen[100];
	double zeitGelesen, mengeGelesen, nrGelesen;
	Bauteil *bauTeil;

	FILE *datei = fopen(dateiName, "r");
	if (datei == NULL) {
		perror(dateiName);
		exit(1);
	}
	do {
		r = fscanf(datei, "%100s %100s %100lf  %100s %100s %lf %100s  %100lf",
				zielTypGelesen, zielBezeichnungGelesen, &nrGelesen,
				quellTypGelesen, quellBezGelesen, &mengeGelesen,
				taetigkeitGelesen, &zeitGelesen);
		if (r != EOF) {
			if (strcmp(typ, zielTypGelesen) == 0
					&& strcmp(bezeichnung, zielBezeichnungGelesen) == 0) {
				bauTeil = neuesBauteil(t);
				strcpy(bauTeil->zielTyp, zielTypGelesen);
				strcpy(bauTeil->zielBez, zielBezeichnungGelesen);
				bauTeil->nr = nrGelesen;
				strcpy(bauTeil->quellTyp, quellTypGelesen);
				strcpy(bauTeil->quellBez, quellBezGelesen);
				bauTeil->menge = mengeGelesen;
				strcpy(bauTeil->taetigkeit, taetigkeitGelesen);
				bauTeil->zeit = zeitGelesen;
			}
		}
	} while (r != EOF);
	fclose(datei);

}

//Ueberprueft, ob das gesuchte Teil aus Teilen besteht, die wiederum aus weiteren Teilen bestehen.
void sucheEinzelteile(Teil *t, char *dateiName) {
	int i;
	for (i = 0; i < t->bauteileZaehler; i++) {
		leseDatei(t, dateiName, t->bauteile[i]->quellTyp,
				t->bauteile[i]->quellBez);
	}
}

int sortiertungsRegeln(const void *a, const void *b) {
	int c;
	Ausgabe *ta = *(Ausgabe**) a;
	Ausgabe *tb = *(Ausgabe**) b;
	if (a == b)
		return 0;
	c = strcmp(ta->typ, tb->typ);
	if (c != 0)
		return c;
	c = strcmp(ta->bez, tb->bez);
	if (c != 0)
		return c;
	return 0;
}

void sortTrackList(Teil *t) {
	qsort(t->ausgaben, t->ausgabenZaehler, sizeof(Ausgabe*),
			&sortiertungsRegeln);
}

