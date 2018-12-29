#ifndef SEFSALE_H
#define SEFSALE_H

#include "main.h"

void prikazZaSefaSale(Sql *sql, int sifraRadnika);
void dodajRadnika(Sql *sql, int sifraUlogovanogRadnika);
void dodajKonobara(Sql *sql, int sifra);
void dodajSankeraKuvara(Sql *sql, int sifra, char* tipStavke);
void dodajStavku(Sql *sql, int sifraUlogovanogRadnika);
void dodajJelo(Sql *sql, int sifra);
void dodajPice(Sql *sql, int sifra);
void dodajNoviMeni(Sql *sql, int sifraUlogovanogRadnika);
void izborStola(Sql *sql);
void ispisiSveStavke(Sql *sql);
void dodajDodatak(Sql *sql, int sifraUlogovanogRadnika);
void oznaciDodatkeUzPice(Sql *sql, int sifraPica);
void oznaciTipPica(Sql *sql, int sifraPica);
void oznaciTipJela(Sql *sql, int sifraJela);

#endif
