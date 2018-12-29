#include"gost.h"

void prikaziMeni(Sql *sql, int sifraStola) {
	printf("***************************\n");
	printf("***** Prikaz za goste *****\n");
	printf("***************************\n");

	strcpy(sql->query, "");
	sprintf(sql->query, "select m.idMenija, m.popust, m.vaziOd, m.vaziDo from Meni m where m.vaziDo is null or now() between m.vaziOd and m.vaziDo;");
	
	if (mysql_query(sql->connection, sql->query)) {
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }

	sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);
	
	sql->row = mysql_fetch_row(sql->result);

	char *vremeOd = (char *) malloc(100);
    char *vremeDo = (char *) malloc(100);
	int popust = 0;
	int idMenija = 0;
	
	idMenija = strtol(sql->row[0], NULL, 10);
	if (sql->row[1] != NULL) {
		popust = strtol(sql->row[1], NULL, 10);
	}
	
	strcpy(vremeOd, sql->row[2]);
	
	if (sql->row[3] != NULL) {
		strcpy(vremeDo, sql->row[3]);
		printf("Ovaj meni vazi od %s do %s.\n", vremeOd, vremeDo); 
	} else {
		printf("Ovaj meni vazi od %s.\n", vremeOd);
	}
	
	if (popust != 0) {
		printf("Popust na ovom meniju je %d posto.\n", popust);
	}

	for(; mysql_fetch_row(sql->result) != 0;); 
	
	int stanje = 0;
	printf("%s:\n%s\n%s\n%s\n",
		"Izaberite opciju",
		"1. Jelovnik", 
		"2. Karta pica",
        "3. Racun");
	scanf("%d", &stanje);

	char s[50];

	if (stanje == 1) {
		prikazJelovnika(sql, idMenija);
		sprintf(s, "pice");
	} else if (stanje == 2) {
		prikazPicovnika(sql, idMenija);
		sprintf(s, "jelovnik");
	} else if (stanje == 3) {
        strcpy(sql->query,"");
		sprintf(sql->query, "insert into Racun (iznos, naplaceno) values (0, 0);");

		if (mysql_query (sql->connection, sql->query) != 0) {
			printf("%s\n",mysql_error(sql->connection));
			exit (EXIT_FAILURE);
		}

		strcpy(sql->query, "");
		sprintf(sql->query, "select r.idRacun from Racun r order by idRacun desc limit 1;");

        if(mysql_query(sql->connection, sql->query)){
            printf("%s\n",mysql_error(sql->connection));
            exit(EXIT_FAILURE);
        }
		
		sql->result = mysql_use_result(sql->connection);
		sql->column = mysql_fetch_fields(sql->result);
		
		sql->row = mysql_fetch_row(sql->result);

		int idRacuna = 0;
		
		idRacuna = strtol(sql->row[0], NULL, 10);

        mysql_free_result(sql->result);

		strcpy(sql->query, "");
		sprintf(sql->query, "update Narudzbina set idRacuna = %i where idStola = %i and idRacuna is null;", idRacuna, sifraStola);

		if(mysql_query(sql->connection, sql->query)){
			printf("%s\n",mysql_error(sql->connection));
			exit(EXIT_FAILURE);
		}

		printf("Molimo sacekajte konobara koji Vas je usluzivao da Vam donese racun.\n");

        prikaziMeni(sql, sifraStola);
    } else {
		printf("Niste uneli dobru opciju.\n");
		prikaziMeni(sql, sifraStola);
	}
	
	printf("Ako zelite da zavrsite narudzbinu unesite \'naruci\', a ako zelite da se prebacite na %s unesite \'%s\'.\n", s, s);
	
	printf("Izaberite sifru stavki koje zelite da narucite:\n");
	
	char akcija[50];

	scanf("%s", akcija);

	int stavkeNarudzbine[50];
	int brStavki = 0;

	DodatakStavka dodatakStavkeIzNarudzbine[50];
	int brDodataka = 0;

	if (strcmp(akcija, "racun") == 0) {
		strcpy(sql->query,"");
		sprintf(sql->query, "insert into Racun (iznos) values (0);");

		if (mysql_query (sql->connection, sql->query) != 0) {
			printf("%s\n",mysql_error(sql->connection));
			exit (EXIT_FAILURE);
		}

		strcpy(sql->query, "");
		sprintf(sql->query, "select r.idRacun from Racun r order by idRacun desc limit 1;");

        if(mysql_query(sql->connection, sql->query)){
            printf("%s\n",mysql_error(sql->connection));
            exit(EXIT_FAILURE);
        }
		
		sql->result = mysql_use_result(sql->connection);
		sql->column = mysql_fetch_fields(sql->result);
		
		sql->row = mysql_fetch_row(sql->result);

		int idRacuna = 0;
		
		idRacuna = strtol(sql->row[0], NULL, 10);

		strcpy(sql->query, "");
		sprintf(sql->query, "update Narudzbina set idRacuna = %i where idStola = %i and idRacuna is null;", idRacuna, sifraStola);

		if(mysql_query(sql->connection, sql->query)){
			printf("%s\n",mysql_error(sql->connection));
			exit(EXIT_FAILURE);
		}

	} else {
		while (strcmp(akcija, "naruci") != 0) {

			if (!strcmp(akcija, "jelovnik")) {
				prikazJelovnika(sql, idMenija);
			} else if (!strcmp(akcija, "pice")) {
				prikazPicovnika(sql, idMenija);
			} else {
				int sifraStavke = strtol(akcija, NULL, 10);

				//DODAJ STAVKU U NIZ
				stavkeNarudzbine[brStavki] = sifraStavke;
				brStavki++;
				
				strcpy(sql->query, "");
				sprintf(sql->query, "select d.idDodatak 'Sifra dodatka', d.naziv as Naziv, d.cena as Cena, d.kolicina as Kolicina, d.opis as Opis from Dodatak d join StavkaDodatak sd on sd.idDodatka = d.idDodatak where sd.idStavke = '%d';", sifraStavke);
				
				if(mysql_query(sql->connection, sql->query)){
					printf("%s\n",mysql_error(sql->connection));
					exit(EXIT_FAILURE);
				}
				
				int n = mysql_field_count(sql->connection);
                if (n > 0) {
                    sql->result = mysql_use_result(sql->connection);
                    sql->column = mysql_fetch_fields(sql->result);
                }

				if ((sql->row = mysql_fetch_row(sql->result))) {
					for(int i = 0; i<n; i++){
						printf("%s",sql->column[i].name);

                        for (int k = strlen(sql->column[i].name); k <= 18; k++) {
                            printf(" ");
                        }
					}
					
					printf("\n\n");
					
					for(int i = 0; i<n; i++){
						printf("%s",sql->row[i]);

                        for (int k = strlen(sql->row[i]); k <= 18; k++) {
                            printf(" ");
                        }
					}
					printf("\n");
					
					while((sql->row = mysql_fetch_row(sql->result))){
						for(int i = 0; i<n; i++){
							printf("%s",sql->row[i]);

                            for (int k = strlen(sql->row[i]); k <= 18; k++) {
                                printf(" ");
                            }
						}
						printf("\n");
					}
					
					printf("Izaberite dodatake uz izabranu stavku tako sto cete navesti sifre zeljenih dodataka ili \'kraj\' kada ih sve unesete.\n");
					
					char dodatak[30];
					scanf("%s", dodatak);
					
					while(strcmp(dodatak, "kraj")) {
						int sifraDodatka = strtol(dodatak, NULL, 10);
						
						DodatakStavka dodatakStavka;
						dodatakStavka.sifraDodatka = sifraDodatka;
						dodatakStavka.sifraStavke = sifraStavke;
						//DODAJ DODATAKA U NIZ
						dodatakStavkeIzNarudzbine[brDodataka] = dodatakStavka;
						brDodataka++;
						
						scanf("%s", dodatak);
					}
				}
			}
			scanf("%s", akcija);
		}
		
		//NAPRAVI NARUDZBINU
		strcpy(sql->query,"");
		sprintf(sql->query, "insert into Narudzbina (idStola, usluzeno) values (%i, %d);", sifraStola, 0);

		if (mysql_query (sql->connection, sql->query) != 0) {
			printf("%s\n",mysql_error(sql->connection));
			exit (EXIT_FAILURE);
		}

		strcpy(sql->query, "");
		sprintf(sql->query, "select n.idNarudzbine from Narudzbina n order by idNarudzbine desc limit 1;");

        if (mysql_query (sql->connection, sql->query) != 0) {
			printf("%s\n",mysql_error(sql->connection));
			exit (EXIT_FAILURE);
		}
		
		sql->result = mysql_use_result(sql->connection);
		sql->row = mysql_fetch_row(sql->result);

		int idNarudzbine = 0;
		
		idNarudzbine = strtol(sql->row[0], NULL, 10);

        mysql_fetch_row(sql->result);
		
		//PRODJI KROZ NIZOVE STAVKI I DODATAKA
		for (int i = 0; i < brStavki; i++) {
            printf("%d\n", stavkeNarudzbine[i]);
            printf("%d\n", idMenija);
			strcpy(sql->query,"");
			sprintf(sql->query, "insert into NarudzbinaStavka (idNarudzbine, idStavke, idMenija, spremno) values ('%d', '%d', '%d', '%d');", idNarudzbine, stavkeNarudzbine[i], idMenija, 0);

			if (mysql_query (sql->connection, sql->query) != 0) {
				printf("%s\n",mysql_error(sql->connection));
				exit (EXIT_FAILURE);
			}	
		}

		for (int i = 0; i < brDodataka; i++) {

            strcpy(sql->query, "");
            sprintf(sql->query, "select ns.idStavkeIzNarudzbine \
                                from NarudzbinaStavka ns \
                                where ns.idStavke = '%d' and ns.idNarudzbine = '%d' and ns.idMenija = '%d' \
                                limit 1;", dodatakStavkeIzNarudzbine[i].sifraStavke, idNarudzbine, idMenija);

            if(mysql_query(sql->connection, sql->query)){
                printf("%s\n",mysql_error(sql->connection));
                exit(EXIT_FAILURE);
            }
            
            sql->result = mysql_use_result(sql->connection);
            sql->column = mysql_fetch_fields(sql->result);
            
            sql->row = mysql_fetch_row(sql->result);

            int idStavkeIzNarudzbine = 0;
            
            idStavkeIzNarudzbine = strtol(sql->row[0], NULL, 10);

            for(; mysql_fetch_row(sql->result) != 0;){}

			strcpy(sql->query,"");
			sprintf(sql->query, "insert into DodatakStavkeIzNarudzbine (idStavkeIzNarudzbine, idDodatka) values (%i, %i);", 
			idStavkeIzNarudzbine, dodatakStavkeIzNarudzbine[i].sifraDodatka);

			if (mysql_query (sql->connection, sql->query) != 0) {
				printf("%s\n",mysql_error(sql->connection));
				exit (EXIT_FAILURE);
			}	
		}

		printf("Uspesno ste izvrsili narudzbinu!\n");
	}

	
	prikaziMeni(sql, sifraStola);
}

void prikazJelovnika(Sql *sql, int idMenija) {
	strcpy(sql->query, "");
	sprintf(sql->query, "select s.idStavke 'Sifra stavke', s.naziv as Naziv, s.cena as Cena, s.opis as Opis \
						from Stavka s join MeniStavka ms on s.idStavke = ms.idStavke join Jelo j on j.idJela = s.idStavke \
						where ms.idMenija = %d;", idMenija);
	
	if (mysql_query(sql->connection, sql->query)) {
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
	
	sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);
	int n = mysql_field_count(sql->connection);

    for (int i = 0; i<n; i++) {
        printf("%s",sql->column[i].name);

        for (int k = strlen(sql->column[i].name); k <= 18; k++) {
            printf(" ");
        }

        printf("\t");
    }

	printf("\n");
	
	while ((sql->row = mysql_fetch_row(sql->result))) {
        for(int i = 0; i<n; i++){
            printf("%s",sql->row[i]);

            for (int k = strlen(sql->row[i]); k <= 18; k++) {
                printf(" ");
            }

            printf("\t");
        }

        prikaziTipJela(sql);
    	printf("\n");
    }
}

void prikazPicovnika(Sql *sql, int idMenija) {
	strcpy(sql->query, "");
	sprintf(sql->query, "select s.idStavke 'Sifra stavke', s.naziv as Naziv, s.cena as Cena, p.kolicina Kolicina, s.opis as Opis \
						from Stavka s join MeniStavka ms on s.idStavke = ms.idStavke join Pice p on p.idPica = s.idStavke \
						where ms.idMenija = '%d';", idMenija);
	
	if (mysql_query(sql->connection, sql->query)) {
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
	
	sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);
	int n = mysql_field_count(sql->connection);

    for (int i = 0; i<n; i++) {
        printf("%s",sql->column[i].name);

        for (int k = strlen(sql->column[i].name); k <= 18; k++) {
            printf(" ");
        }

        printf("\t");
    }
    
	printf("\n");

	while ((sql->row = mysql_fetch_row(sql->result))) {
        for(int i = 0; i<n; i++){
            printf("%s",sql->row[i]);

            for (int k = strlen(sql->row[i]); k <= 18; k++) {
                printf(" ");
            }

            printf("\t");
        }
        prikaziTipPica(sql);
        printf("\n");
    }
}

void prikaziTipJela(Sql *sql) {
    Sql sql1;
    sql1.connection = mysql_init(NULL);
    
    if(mysql_real_connect(sql1.connection,"localhost", "root", "root", "mydb", 0, NULL, 0) == NULL){
        printf("Failed to connect to database\n\n");
        printf("%s\n",mysql_error(sql1.connection));
    }
    strcpy(sql1.query, "");
	sprintf(sql1.query, "select tj.naziv \
						from TipJela tj join JeloTipJela jtj on tj.idTipJela = jtj.idTipJela join Jelo j on j.idJela = jtj.idJela \
						where j.idJela = %d;", (int)strtol(sql->row[0], NULL, 10));
	
	if (mysql_query(sql1.connection, sql1.query)) {
        printf("%s\n",mysql_error(sql1.connection));
        exit(EXIT_FAILURE);
    }
	
	sql1.result = mysql_use_result(sql1.connection);
    sql1.column = mysql_fetch_fields(sql1.result);
	int m = mysql_field_count(sql1.connection);

    printf("(");
    while ((sql1.row = mysql_fetch_row(sql1.result))) {
        for(int r = 0; r<m; r++){
            printf("%s ",sql1.row[r]);
        }
    }

    printf(")");
}

void prikaziTipPica(Sql *sql) {
    Sql sql1;
    sql1.connection = mysql_init(NULL);
    
    if(mysql_real_connect(sql1.connection,"localhost", "root", "root", "mydb", 0, NULL, 0) == NULL){
        printf("Failed to connect to database\n\n");
        printf("%s\n",mysql_error(sql1.connection));
    }
    strcpy(sql1.query, "");
	sprintf(sql1.query, "select tp.naziv \
						from TipPica tp join PiceTipPica ptp on tp.idTipPica = ptp.idTipPica join Pice p on p.idPica = ptp.idPica \
						where p.idPica = %d;", (int)strtol(sql->row[0], NULL, 10));
	
	if (mysql_query(sql1.connection, sql1.query)) {
        printf("%s\n",mysql_error(sql1.connection));
        exit(EXIT_FAILURE);
    }
	
	sql1.result = mysql_use_result(sql1.connection);
    sql1.column = mysql_fetch_fields(sql1.result);
	int m = mysql_field_count(sql1.connection);

    printf("(");
    while ((sql1.row = mysql_fetch_row(sql1.result))) {
        for(int r = 0; r<m; r++){
            printf("%s ",sql1.row[r]);
        }
    }

    printf(")");
}