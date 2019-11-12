#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "programm.h"

Teil* erzeugeStueckliste(Teil *teil, char *argv[]) {
	leseDatei(teil, argv[2], argv[3], argv[4]);
	sucheEinzelteile(teil, argv[2]);
	erzeugeAusgabe(teil);
	berechneMenge(teil);
	sortTrackList(teil);
	Teil *t = neuesTeil();
	t = loescheDuplikate(teil);
	befuelleTextdatei(t);
	return t;
}

void befuelleTextdatei(Teil *teil) {
	FILE *datei = fopen("bestandteil.dat", "w");
	if (datei == NULL) {
		exit(1);
	}
	int i;
	for (i = 0; i < teil->ausgabenZaehler; i++) {
		fprintf(datei, "%s %s %.2lf\n", teil->ausgaben[i]->typ,
				teil->ausgaben[i]->bez, teil->ausgaben[i]->menge);
	}
	fclose(datei);
}

void schreibeLoesung(Teil *t) {
	for (int i = 0; i < t->ausgabenZaehler; i++) {
		printf("%s %s %.2lf\n", t->ausgaben[i]->typ, t->ausgaben[i]->bez,
				t->ausgaben[i]->menge);
	}
}

Ausgabe* neueAusgabe(Teil *t) {
	if (t->ausgabenZaehler >= t->ausgabenAlloziert) {
		t->ausgabenAlloziert *= 2;
		t->ausgaben = (Ausgabe**) realloc(t->ausgaben,
				t->ausgabenAlloziert * sizeof(Ausgabe*));
	}
	Ausgabe *b = (Ausgabe*) malloc(sizeof(Ausgabe));
	b->besucht = 0;
	t->ausgaben[t->ausgabenZaehler++] = b;
	return b;
}

//fuege alle Einzelteile von Hauptteil (typ, bezeichnung) laut argv in die Ausgabe
void erzeugeAusgabe(Teil *t) {
	if (t->bauteileZaehler > 0) {
		Ausgabe *ausGabePtr;
		ausGabePtr = neueAusgabe(t);

		//fuege das Hauptteil (typ, bezeichnung) laut argv in die Ausgabe
		strcpy(ausGabePtr->typ, t->bauteile[0]->zielTyp);
		strcpy(ausGabePtr->bez, t->bauteile[0]->zielBez);
		ausGabePtr->menge = t->bauteile[0]->menge;

		int i;

		for (i = 0; i < t->bauteileZaehler; i++) {
			ausGabePtr = neueAusgabe(t);
			strcpy(ausGabePtr->typ, t->bauteile[i]->quellTyp);
			strcpy(ausGabePtr->bez, t->bauteile[i]->quellBez);
			ausGabePtr->menge = t->bauteile[i]->menge;
		}
	}
}

void setzeMenge(Teil *t, char typ[], char bez[], double menge) {
	int i;
	for (i = 0; i < t->ausgabenZaehler; i++) {
		if (strcmp(t->ausgaben[i]->typ, typ) == 0
				&& strcmp(t->ausgaben[i]->bez, bez) == 0) {
			t->ausgaben[i]->menge = menge;
		}
	}
}
//berechne die Menge aller Teilen mit gleichem typ, bezeichnung und schreibe es in die Struktur
void berechneMenge(Teil *t) {
	int i, j, hilfe;
	double zaehler;
	hilfe = t->ausgabenZaehler;
	for (i = 0; i < hilfe; i++) {
		zaehler = 0;
		if (t->ausgaben[i]->besucht == 0) {
			for (j = 0; j < hilfe; j++) {
				if (strcmp(t->ausgaben[i]->typ, t->ausgaben[j]->typ) == 0
						&& strcmp(t->ausgaben[i]->bez, t->ausgaben[j]->bez)
								== 0) {
					zaehler += t->ausgaben[j]->menge;
					t->ausgaben[j]->besucht = 1;
				}
			}
			setzeMenge(t, t->ausgaben[i]->typ, t->ausgaben[i]->bez, zaehler);
		}
	}
	t->ausgaben[0]->menge = 1;
}

void loescheTeil(Teil *t) {
	int i, j;
	for (i = 0; i < t->ausgabenZaehler; i++)
		free(t->ausgaben[i]);
	for (j = 0; j < t->bauteileZaehler; j++)
		free(t->bauteile[j]);
	free(t->ausgaben);
	free(t->bauteile);
	free(t);
}

Teil* loescheDuplikate(Teil *t) {
	int c, d, count = 0;

	Teil *hilfeTeil = neuesTeil();
	Ausgabe *hilfeAus;
	for (c = 0; c < t->ausgabenZaehler; c++) {
		for (d = 0; d < count; d++) {
			if (strcmp(t->ausgaben[c]->typ, hilfeTeil->ausgaben[d]->typ) == 0
					&& strcmp(t->ausgaben[c]->bez, hilfeTeil->ausgaben[d]->bez)
							== 0)
				break;
		}
		if (d == count) {
			hilfeAus = neueAusgabe(hilfeTeil);
			strcpy(hilfeAus->typ, t->ausgaben[c]->typ);
			strcpy(hilfeAus->bez, t->ausgaben[c]->bez);
			hilfeAus->menge = t->ausgaben[c]->menge;
			count++;
		}
	}
	loescheTeil(t);
	return hilfeTeil;
}
