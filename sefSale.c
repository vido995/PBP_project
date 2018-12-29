#include"sefSale.h"
#include"konobar.h"
#include"gost.h"


void prikazZaSefaSale(Sql *sql, int sifraRadnika) {
	int stanje = 0;

	printf("%s:\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
		"Izaberite opciju",
		"1. Podesavanja vezana za sto",
		"2. Prikaz za konobare", 
		"3. Dodaj radnika", 
		"4. Dodaj stavku",
		"5. Napravi dodatak",
		"6. Napravi novi meni");
	scanf("%i", &stanje);

	switch(stanje){
		case 1:
			izborStola(sql);
		break;
		case 2:
			prikazZaKonobare(sql, sifraRadnika);
		break;
		case 3:
			dodajRadnika(sql, sifraRadnika);
		break;
		case 4:
			dodajStavku(sql, sifraRadnika);
		break;
		case 5:
			dodajDodatak(sql, sifraRadnika);
		break;
		case 6:
			dodajNoviMeni(sql, sifraRadnika); // TODO: Triger kad se dodaje novi meni da se poslednjem vreme do postavi na sada. 
		break;
		default:
			printf("\nNiste izabrali nijednu validnu opciju!\n");
	}
}

void izborStola(Sql *sql) {
	strcpy(sql->query, "");
	sprintf(sql->query, "select s.idStola as Sifra, s.naziv as Naziv, s.brojMesta as 'Broj mesta' from Sto s;");
	
	if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
	
	sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);
    int n = mysql_field_count(sql->connection);

    for (int i = 0; i<n; i++) {
        printf("%s",sql->column[i].name);

		for (int k = strlen(sql->column[i].name); k <= WIDTH_CELL; k++) {
			printf(" ");
		}
    }
	
	printf("\n\n");
	
	while((sql->row = mysql_fetch_row(sql->result))){
        for(int i = 0; i<n; i++){
            printf("%s",sql->row[i]);

			for (int k = strlen(sql->row[i]); k <= WIDTH_CELL; k++) {
				printf(" ");
			}
        }
        printf("\n");
    }
	
	printf("Izaberite sifru stola: ");
	
	int sifraStola = 0;
	scanf("%i", &sifraStola);
	
	prikaziMeni(sql, sifraStola);
    
    mysql_free_result(sql->result);
}

void dodajRadnika(Sql *sql, int sifraUlogovanogRadnika) {
	printf ("Unesite:\n");
	printf("Sifru radnika:\n");
	int sifra = 0;
	scanf("%i", &sifra);
	char ime[45], prezime[45];
	printf("Ime:\n");
	scanf("%s", ime);
	printf("Prezime:\n");
	scanf("%s", prezime);

	strcpy(sql->query,"");
	sprintf(sql->query, "insert into Radnik (idRadnika, ime, prezime) values ('%d', '%s', '%s');", sifra, ime, prezime);
	
	if (mysql_query (sql->connection, sql->query) != 0) {
		printf ("Neuspesno izvrsavanje upita\n");
		exit (EXIT_FAILURE);
	}
	
	int stanje = 0;
	
	printf("%s:\n%s\n%s\n%s\n\n",
		"Kreirani radnik radi kao",
		"1. Konobar", 
		"2. Sanker",
		"3. Kuvar");
	
	scanf("%i", &stanje);
	
	switch(stanje){
		case 1:
			dodajKonobara(sql, sifra);
		break;
		case 2:
			dodajSankeraKuvara(sql, sifra, "pice");
		break;
		case 3:
			dodajSankeraKuvara(sql, sifra, "jelo");
		break;
		default:
			printf("\nNiste izabrali nijednu validnu opciju!\n");
	}

	prikazZaSefaSale(sql, sifraUlogovanogRadnika);
}

void dodajKonobara(Sql *sql, int sifra) {
	printf ("Za konobara unesite:\n");
	printf("Depozit:\n");
	double depozit = 0;
	scanf("%lf", &depozit);
	
	strcpy(sql->query,"");
	
	sprintf(sql->query, "insert into Konobar (idKonobara, depozit) values ('%i', '%lf');", sifra, depozit);
	
	if (mysql_query (sql->connection, sql->query) != 0) {
		printf ("Neuspesno izvrsavanje upita\n");
		exit (EXIT_FAILURE);
	}
}

void dodajSankeraKuvara(Sql *sql, int sifra, char* tipStavke) {
	strcpy(sql->query,"");
	
	sprintf(sql->query, "insert into RadnikKojiPriprema (idRadnikaKojiPriprema, tipStavke) values ('%i', '%s');", sifra, tipStavke);
	
	if (mysql_query (sql->connection, sql->query) != 0) {
		printf ("Neuspesno izvrsavanje upita\n");
		exit (EXIT_FAILURE);
	}
}

void dodajStavku(Sql *sql, int sifraUlogovanogRadnika) {
	int tipStavke = 0;
	
	printf("%s:\n%s\n%s\n\n",
		"Koji tip stavke unosite",
		"1. Jelo", 
		"2. Pice");
		
	scanf("%i", &tipStavke);
	
	printf ("Unesite:\n");
	printf("Sifru stavke:\n");
	int sifra = 0;
	scanf("%i", &sifra); 
	double cena = 0;

	printf("Naziv:\n");
	char *naziv = (char *) malloc(sizeof(char) * 1024);
	int j = 0;
	scanf("%c", &naziv[j]);
	while (1) {
		scanf("%c", &naziv[j]);
		if (naziv[j] == '\n') {
			naziv[j] = 0;
			break;
		} else {
			j++;
		}
	}

	printf("Cenu:\n");
	scanf("%lf", &cena);

	printf("Opis:\n");
	char *opis = (char *) malloc(sizeof(char) * 1024);
	j = 0;
	scanf("%c", &opis[j]);
	while (1) {
		scanf("%c", &opis[j]);
		if (opis[j] == '\n') {
			opis[j] = 0;
			break;
		} else {
			j++;
		}
	}
	
	strcpy(sql->query,"");
	sprintf(sql->query, "insert into Stavka (idStavke, naziv, cena, opis) values ('%i', '%s', '%lf', '%s');", sifra, naziv, cena, opis);
	
	if (mysql_query (sql->connection, sql->query) != 0) {
		printf ("Neuspesno izvrsavanje upita\n");
		exit (EXIT_FAILURE);
	}
	
	if (tipStavke == 1) {
		dodajJelo(sql, sifra);
	} else {
		dodajPice(sql, sifra);
	}

	prikazZaSefaSale(sql, sifraUlogovanogRadnika);
}

void dodajJelo(Sql *sql, int sifra) {
	printf("gramazu\n");
	int gramaza = 0;
	scanf("%i", &gramaza);
	printf("broj osoba\n");
	int brojOsoba = 0;
	scanf("%i", &brojOsoba);
	
	strcpy(sql->query,"");
	sprintf(sql->query, "insert into Jelo (idJela, gramaza, brojOsoba) values (%i, %i, %i);", sifra, gramaza, brojOsoba);
	
	if (mysql_query (sql->connection, sql->query) != 0) {
		printf ("Neuspesno izvrsavanje upita\n");
		exit (EXIT_FAILURE);
	}
	
	oznaciTipJela(sql, sifra);
}

void dodajPice(Sql *sql, int sifra) {
	printf("kolicinu\n");
	double kolicina = 0;
	scanf("%lf", &kolicina);
	
	strcpy(sql->query,"");
	sprintf(sql->query, "insert into Pice (idPica, kolicina) values (%i, %lf);", sifra, kolicina);
	
	if (mysql_query (sql->connection, sql->query) != 0) {
		printf ("Neuspesno izvrsavanje upita\n");
		exit (EXIT_FAILURE);
	}
	
	oznaciTipPica(sql, sifra);

	oznaciDodatkeUzPice(sql, sifra);

}

void dodajNoviMeni(Sql *sql, int sifraUlogovanogRadnika) {
	printf ("Unesite:\n");
	printf("sifru menija\n");
	int sifra = 0;
	scanf("%i", &sifra);
	printf("popust\n");
	int popust = 0;
	scanf("%i", &popust);
	
	strcpy(sql->query,"");
	sprintf(sql->query, "insert into Meni (idMenija, vaziOd, vaziDo, popust) values ('%i', now(), NULL, '%i');", sifra, popust);
	
	if (mysql_query (sql->connection, sql->query) != 0) {
		printf ("Neuspesno izvrsavanje upita\n");
		printf("%s\n",mysql_error(sql->connection));
		exit (EXIT_FAILURE);
	}
	
	// TODO: Ovo uraditi kroz triger
	strcpy(sql->query,"");
	sprintf(sql->query, "update Meni set vaziDo = now() where vaziDo is null and idMenija != %i;", sifra);
	
	if (mysql_query (sql->connection, sql->query) != 0) {
		printf ("Neuspesno izvrsavanje upita\n");
		printf("%s\n",mysql_error(sql->connection));
		exit (EXIT_FAILURE);
	}
	
	printf ("Izaberite sve stavke koje su deo Vaseg novog menija navodjenjem sifre stavke:\n");
	printf ("(Kada izaberete sve stavke ukucajte \"kraj\")\n");
	
	ispisiSveStavke(sql);
	
	char s[50];
	
	scanf ("%s", s);
	
	while(strcmp(s, "kraj")) {
		int sifraStavke = 0;
		sifraStavke = (int)strtol(s,NULL,10);

		strcpy(sql->query,"");
		sprintf(sql->query, "insert into MeniStavka (idMenija, idStavke) values ('%i', '%i');", sifra, sifraStavke);
		
		if (mysql_query (sql->connection, sql->query) != 0) {
			printf ("Neuspesno izvrsavanje upita\n");
			printf("%s\n",mysql_error(sql->connection));
			exit (EXIT_FAILURE);
		}

		scanf ("%s", s);
	}

	prikazZaSefaSale(sql, sifraUlogovanogRadnika);
}

void ispisiSveStavke(Sql *sql) {
	strcpy(sql->query, "");
    sprintf(sql->query, "select s.idStavke as Sifra, s.naziv as Naziv, s.cena as Cena from Stavka s");

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }

    sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);
    int n = mysql_field_count(sql->connection);

    for(int i = 0; i<n; i++){
        printf("%s",sql->column[i].name);

		for (int k = strlen(sql->column[i].name); k <= WIDTH_CELL; k++) {
			printf(" ");
		}
		printf("\t");
    }

    printf("\n\n");

    while((sql->row = mysql_fetch_row(sql->result))){
        for(int i = 0; i<n; i++){
            printf("%s",sql->row[i]);

			for (int k = strlen(sql->row[i]); k <= WIDTH_CELL; k++) {
				printf(" ");
			}

			printf("\t");
        }
        printf("\n\n");
    }
    
    mysql_free_result(sql->result);
}

void dodajDodatak(Sql *sql, int sifraUlogovanogRadnika) {
	printf ("Unesite:\n");
	printf("Sifru dodatka:\n");
	int sifra = 0;
	scanf("%i", &sifra); 
	double cena = 0, kolicina = 0;

	printf("Naziv:\n");
	char *naziv = (char *) malloc(sizeof(char) * 1024);
	int j = 0;
	scanf("%c", &naziv[j]);
	while (1) {
		scanf("%c", &naziv[j]);
		if (naziv[j] == '\n') {
			naziv[j] = 0;
			break;
		} else {
			j++;
		}
	}

	printf("Cenu:\n");
	scanf("%lf", &cena);

	printf("Kolicinu:\n");
	scanf("%lf", &kolicina);

	printf("Opis:\n");
	char *opis = (char *) malloc(sizeof(char) * 1024);
	j = 0;
	scanf("%c", &opis[j]);
	while (1) {
		scanf("%c", &opis[j]);
		if (opis[j] == '\n') {
			opis[j] = 0;
			break;
		} else {
			j++;
		}
	}
	
	strcpy(sql->query,"");
	sprintf(sql->query, "insert into Dodatak (idDodatak, naziv, cena, kolicina, opis) values ('%i', '%s', '%lf', '%lf', '%s');", sifra, naziv, cena, kolicina, opis);
	
	if (mysql_query (sql->connection, sql->query) != 0) {
		printf ("Neuspesno izvrsavanje upita\n");
		exit (EXIT_FAILURE);
	}

	prikazZaSefaSale(sql, sifraUlogovanogRadnika);
}
void oznaciDodatkeUzPice(Sql *sql, int sifraPica) {
	strcpy(sql->query, "");
	sprintf(sql->query, "select d.idDodatak as idDodatak, d.naziv as Naziv, d.opis as Opis, d.kolicina as Kolicina from Dodatak d;");
	
	if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
	
	sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);
    int n = mysql_field_count(sql->connection);

    for (int i = 0; i<n; i++) {
        printf("%s",sql->column[i].name);

		for (int k = strlen(sql->column[i].name); k <= WIDTH_CELL; k++) {
			printf(" ");
		}
    }
	
	printf("\n\n");
	
	while((sql->row = mysql_fetch_row(sql->result))){
        for(int i = 0; i<n; i++){
            printf("%s",sql->row[i]);

			for (int k = strlen(sql->row[i]); k <= WIDTH_CELL; k++) {
				printf(" ");
			}
        }
        printf("\n");
    }

	printf("Oznacite koji dodaci idu uz ovo pice. (Kada ste uneli sve moguce dodatke unesite 'kraj')\n");

	char s[50];
	
	scanf ("%s", s);
	
	while(strcmp(s, "kraj")) {
		int sifraDodatka = 0;
		sifraDodatka = (int)strtol(s,NULL,10);

		strcpy(sql->query,"");
		sprintf(sql->query, "insert into StavkaDodatak (idDodatka, idStavke) values ('%i', '%i');", sifraDodatka, sifraPica);
		
		if (mysql_query (sql->connection, sql->query) != 0) {
			printf ("Neuspesno izvrsavanje upita\n");
			printf("%s\n",mysql_error(sql->connection));
			exit (EXIT_FAILURE);
		}

		scanf ("%s", s);
	}
}

void oznaciTipPica(Sql *sql, int sifraPica) {
	strcpy(sql->query, "");
	sprintf(sql->query, "select tp.idTipPica as 'Sifra tipa', tp.naziv as Naziv from TipPica tp;");
	
	if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
	
	sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);
    int n = mysql_field_count(sql->connection);

    for (int i = 0; i<n; i++) {
        printf("%s",sql->column[i].name);

		for (int k = strlen(sql->column[i].name); k <= WIDTH_CELL; k++) {
			printf(" ");
		}
    }
	
	printf("\n\n");
	
	while((sql->row = mysql_fetch_row(sql->result))){
        for(int i = 0; i<n; i++){
            printf("%s",sql->row[i]);

			for (int k = strlen(sql->row[i]); k <= WIDTH_CELL; k++) {
				printf(" ");
			}
        }
        printf("\n");
    }

	printf("Oznacite kom tipu pripada ovo pice. (Kada ste uneli sve moguce dodatke unesite 'kraj')\n");

	char s[50];
	
	scanf ("%s", s);
	
	while(strcmp(s, "kraj")) {
		int sifraTipa = 0;
		sifraTipa = (int)strtol(s,NULL,10);

		strcpy(sql->query,"");
		sprintf(sql->query, "insert into PiceTipPica (idPica, idTipPica) values ('%i', '%i');", sifraPica, sifraTipa);
		
		if (mysql_query (sql->connection, sql->query) != 0) {
			printf ("Neuspesno izvrsavanje upita\n");
			printf("%s\n",mysql_error(sql->connection));
			exit (EXIT_FAILURE);
		}

		scanf ("%s", s);
	}
}

void oznaciTipJela(Sql *sql, int sifraJela) {
	strcpy(sql->query, "");
	sprintf(sql->query, "select tj.idTipJela as 'Sifra tipa', tj.naziv as Naziv from TipJela tj;");
	
	if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
	
	sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);
    int n = mysql_field_count(sql->connection);

    for (int i = 0; i<n; i++) {
        printf("%s",sql->column[i].name);

		for (int k = strlen(sql->column[i].name); k <= WIDTH_CELL; k++) {
			printf(" ");
		}
    }
	
	printf("\n\n");
	
	while((sql->row = mysql_fetch_row(sql->result))){
        for(int i = 0; i<n; i++){
            printf("%s",sql->row[i]);

			for (int k = strlen(sql->row[i]); k <= WIDTH_CELL; k++) {
				printf(" ");
			}
        }
        printf("\n");
    }

	printf("Oznacite kom tipu pripada ovo jelo. (Kada ste uneli sve moguce dodatke unesite 'kraj')\n");

	char s[50];
	
	scanf ("%s", s);
	
	while(strcmp(s, "kraj")) {
		int sifraTipa = 0;
		sifraTipa = (int)strtol(s,NULL,10);

		strcpy(sql->query,"");
		sprintf(sql->query, "insert into JeloTipJela (idJela, idTipJela) values ('%i', '%i');", sifraJela, sifraTipa);
		
		if (mysql_query (sql->connection, sql->query) != 0) {
			printf ("Neuspesno izvrsavanje upita\n");
			printf("%s\n",mysql_error(sql->connection));
			exit (EXIT_FAILURE);
		}

		scanf ("%s", s);
	}
}