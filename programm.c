#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "programm.h"

int main(int argc, char *argv[]) {
	Teil *t = neuesTeil();
	t = erzeugeStueckliste(t, argv);
	schreibeLoesung(t);
	loescheTeil(t);
	return 0;
}

