#include <stdio.h>
#ifndef PROGRAMM_H_
#define PROGRAMM_H_

typedef struct {
	char typ[100];
	char bez[100];
	int besucht;
	double menge;
} Ausgabe;

typedef struct {
	char zielTyp[101];
	char zielBez[101];
	double nr;
	char quellTyp[101];
	char quellBez[101];
	double menge;
	char taetigkeit[101];
	double zeit;
} Bauteil;

typedef struct {
	int bauteileZaehler;
	int bauteileAlloziert;
	int ausgabenZaehler;
	int ausgabenAlloziert;
	Ausgabe **ausgaben;
	Bauteil **bauteile;
} Teil;

Teil* neuesTeil();
void loescheTeil(Teil *t);
Bauteil* neuesBauteil(Teil *t);
Ausgabe* neueAusgabe(Teil *t);
void leseDatei(Teil *t, char *dateiName, char *typ, char *bezeichnung);
void sucheEinzelteile(Teil *t, char *dateiName);
void berechneMenge(Teil *t);
void sortTrackList(Teil *t);
Teil* loescheDuplikate(Teil *t);
void erzeugeAusgabe(Teil *t);
Teil* erzeugeStueckliste(Teil *teil, char *argv[]);
void befuelleTextdatei(Teil *teil);
void schreibeLoesung(Teil *t);

#endif
