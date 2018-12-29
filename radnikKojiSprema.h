#ifndef RADNIKKOJISPREMA_H
#define RADNIKKOJISPREMA_H

#include "main.h"

void prikazZaSankere(Sql *sql, int sifraRadnikaKojiSprema);
void prikazZaKuvare(Sql *sql, int sifraRadnikaKojiSprema);
void izborStavkeZaPripremu(Sql *sql, int sifraRadnikaKojiSprema, int sanker);

#endif