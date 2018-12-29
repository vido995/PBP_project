#ifndef KONOBAR_H
#define KONOBAR_H

#include "main.h"

void prikazZaKonobare(Sql *sql, int sifraKonobara);
void prikaziStavkeIzNarudzbine(Sql *sql, int sifraNarudzbine, int sifraKonobara);

#endif