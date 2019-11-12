default: programm

programm: programm.c ausgabe.c bauteile.c leseDatei.c teil.c
	cc -o programm programm.c ausgabe.c bauteile.c leseDatei.c teil.c
