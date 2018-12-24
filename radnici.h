#ifndef RADNICI_H
#define RADNICI_H

#include "main.h"


void prikazZaRadnike(Sql *sql);
void prikazZaSefaSale(Sql *sql);
void dodajRadnika(Sql *sql);
void dodajKonobara(Sql *sql, int sifra);
void dodajSankeraKuvara(Sql *sql, int sifra, char* tipStavke);
void dodajStavku(Sql *sql);
void dodajJelo(Sql *sql, int sifra);
void dodajPice(Sql *sql, int sifra);
void dodajNoviMeni(Sql *sql);
void ispisiSveStavke(Sql *sql);
void prikazZaKonobare(Sql *sql);
void prikaziStavkeIzNarudzbine(Sql *sql, int sifraNarudzbine);
void prikazZaSankereIKuvare(Sql *sql);

#endif
