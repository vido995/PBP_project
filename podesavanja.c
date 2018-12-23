#include "podesavanja.h"

void izborStola(Sql *sql) {
	strcpy(sql->query, "");
	sprintf(sql->query, "select s.idStola as Sifra,  s.naziv as Naziv, s.brojMesta as BrojMesta from Sto s");
	
	if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
	
	sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);
    int n = mysql_field_count(sql->connection);

    for(int i = 0; i<n; i++){
        printf("%s\t",sql->column[i].name);
    }
	
	printf("\n\n");
	
	while((sql->row = mysql_fetch_row(sql->result))){
        for(int i = 0; i<n; i++){
            printf("%s\t",sql->row[i]);
        }
        printf("\n");
    }
	
	printf("Izaberite sifru stola: ");
	
	int sifraStola = 0;
	scanf("%i", &sifraStola);
	
	prikaziMeni(sql, sifraStola, 1, 1);
    
    mysql_free_result(sql->result);
    printf("\n\n");
}

void prikaziMeni(Sql *sql, int sifraStola, int novaNarudzbina, int noviRacun) {
	printf("***** Prikaz za goste *****\n\n");
	
	if (noviRacun) {
		strcpy(sql->query,"");
		sprintf(sql->query, "insert into Racun (iznos) values (%i, %lf);", 0);

		if (mysql_query (sql->connection, sql->query) != 0) {
			printf ("Neuspesno izvrsavanje upita\n");
			exit (EXIT_FAILURE);
		}
	}
	
	strcpy(sql->query, "");
	sprintf(sql->query, "select r.idRacuna, r.iznos " +
						"from Racun r join Narudzbina n on r.idRacuna = n.idRacuna " + 
						"order by idRacuna desc " +
						"limit 1;");
	
	sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);
	
	sql->row = mysql_fetch_row(sql->result);

	int idRacuna = 0;
	double iznos = 0;
	
	idRacuna = sql->row[0];
	iznos = sql->row[1];
	
	if (novaNarudzbina) {
		strcpy(sql->query,"");
		sprintf(sql->query, "insert into Narudzbina (idStola, idRacuna, usluzeno) values (%i, %d, %d);", sifraStola, idRacuna , 0);

		if (mysql_query (sql->connection, sql->query) != 0) {
			printf ("Neuspesno izvrsavanje upita\n");
			exit (EXIT_FAILURE);
		}	
	}
	
	int stanje = 0;
	
	strcpy(sql->query, "");
	sprintf(sql->query, "select m.idMenija, m.popust, m.vaziOd, m.vaziDo " +
						"from Meni m " + 
						"where m.vaziDo is null or now() between m.vaziOd and m.vaziDo;");
	
	sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);
	
	sql->row = mysql_fetch_row(sql->result);

	char *vremeOd = (char *) malloc(100);
    char *vremeDo = (char *) malloc(100);
	int popust = 0;
	int idMenija = 0;
	
	idMenija = sql->row[0];
	if (sql->row[1] != NULL) {
		popust = sql->row[1];
	}
	
	strcpy(vremeOd, sql->row[2]);
	
	if (sql->row[3] != NULL) {
		strcpy(vremeDo, sql->row[3]);
		printf("Ovaj meni vazi od %s do %s.\n", vremeOd, vremeDo); 
	} else {
		printf("Ovaj meni vazi od %s.\n", vremeOd);
	}
	
	if (popust != 0) {
		printf("Popust na ovom meniju je %d\%.\n", popust);
	}
	
	printf("%s:\n%s\n%s\n\n",
		"Izaberite opciju",
		"1. Jelovnik", 
		"2. Picovnik");
	scanf("%i", &stanje);

	if (stanje == 1) {
		prikazJelovnika(sql, idMenija);
	} else if (stanje == 2) {
		prikazPicovnika(sql, idMenija);
	} else {
		printf("Niste uneli dobru opciju.\n");
		prikaziMeni(sql, sifraStola, 0, 0);
	}
	
	char[50] s = stanje == 1 ? "picovnik" : "jelovnik";
	
	printf("Ako zelite da zavrsite narudzbinu unesite \'naruci\', a ako zelite da se prebacite na %s unesite \'%s\'.\n", s, s);
	
	printf("Izaberite sifru stavki koju zelite da narucite: \n");
	
	char[50] akcija;
	scanf("%s", akcija);
	
	while (strcmp(akcija, "naruci")) {
		if (!strcmp(akcija, "jelovnik")) {
			prikaziJelovnik(sql, idMenija);
		} else if (!strcmp(akcija, "naruci")) {
			prikazPicovnika(sql, idMenija);
		} else {
			int sifraStavke = strtol(akcija, NULL, 10);
			
			//DODAJ STAVKU U NIZ
			
			strcpy(sql->query, "");
			sprintf(sql->query, "select d.idDodatka SifraDodatka, d.naziv as Naziv, d.opis as Opis, d.cena as Cena, d.kolicina as Kolicina " +
							"from Dodatak d join StavkaDodatak sd on sd.idDodatka = d.idDodatka " + 
							"where sd.idStavke = %d;", sifraStavke);
			sql->result = mysql_use_result(sql->connection);
			sql->column = mysql_fetch_fields(sql->result);
			int n = mysql_field_count(sql->connection);

			if ((sql->row = mysql_fetch_row(sql->result))) {
				for(int i = 0; i<n; i++){
					printf("%s\t",sql->column[i].name);
				}
				
				printf("\n\n");
				
				for(int i = 0; i<n; i++){
					printf("%s\t",sql->row[i]);
				}
				printf("\n");
				
				while((sql->row = mysql_fetch_row(sql->result))){
					for(int i = 0; i<n; i++){
						printf("%s\t",sql->row[i]);
					}
					printf("\n");
				}
				
				printf("Izaberite dodatake uz izabranu stavku tako sto cete navesti sifre zeljenih dodataka ili \'kraj\' kada ih sve unesete.\n")
				
				char[30] dodatak;
				scanf("%s", dodatak);
				
				while(strcmp(dodatak, "kraj")) {
					int sifraDodatka = strtol(dodatak, NULL, 10);
					
					//DODAJ DODATAKA U NIZ
					
					scanf("%s", akcija);
				}
			}
		}
		scanf("%s", akcija);
	}
	
	//NAPRAVI NARUDZBINU
	//PRODJI KROZ NIZOVE STAVKI I DODATAKA
	
	printf("Uspesno ste izvrsili narudzbinu!\n");
	prikaziMeni(sql, sifraStola);
	
	prikazMogucihDodatakaUzStavku(sifraStavke);
}

void prikazJelovnika(Sql *sql, int idMenija) {
	strcpy(sql->query, "");
	sprintf(sql->query, "select s.idStavke SifraStavke, s.naziv as Naziv, s.opis as Opis, s.cena as Cena " +
						"from Stavka s join MeniStavka ms on s.idStavke = ms.idStavke join Jelo j where j.idJela = s.idStavke " + 
						"where ms.idMenija = %d;", idMenija);
	
	if (mysql_query(sql->connection, sql->query)) {
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
	
	sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);
	int n = mysql_field_count(sql->connection);

    for (int i = 0; i<n; i++) {
        printf("%s\t",sql->column[i].name);
    }
	
	while ((sql->row = mysql_fetch_row(sql->result))) {
        for(int i = 0; i<n; i++){
            printf("%s\t",sql->row[i]);
        }
        printf("\n");
    }
}