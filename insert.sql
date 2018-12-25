-- -----------------------------------------------------
-- Data for table Sto
-- -----------------------------------------------------
START TRANSACTION;
USE mydb;
INSERT INTO Sto (naziv, brojMesta) VALUES ("Sto1", 2);
INSERT INTO Sto (naziv, brojMesta) VALUES ("Sto2", 2);
INSERT INTO Sto (naziv, brojMesta) VALUES ("Sto3", 4);
INSERT INTO Sto (naziv, brojMesta) VALUES ("Sto4", 4);
INSERT INTO Sto (naziv, brojMesta) VALUES ("Sto5", 6);
INSERT INTO Sto (naziv, brojMesta) VALUES ("Sto6", 6);
INSERT INTO Sto (naziv, brojMesta) VALUES ("Sto7", 8);
INSERT INTO Sto (naziv, brojMesta) VALUES ("Sto8", 8);
COMMIT;

-- -----------------------------------------------------
-- Data for table Stavka
-- -----------------------------------------------------
START TRANSACTION;
USE mydb;
INSERT INTO Stavka (idStavke, opis, cena, naziv) VALUES (1, "Cureci file,prsuta,parmezan,rukola", 790, "CURETINA PARMA");
INSERT INTO Stavka (idStavke, opis, cena, naziv) VALUES (2, "Cureci file, med, kari začin, vočrester sos, soja sos", 850, "CURETINA SA KARIJEM I MEDOM");
INSERT INTO Stavka (idStavke, opis, cena, naziv) VALUES (3, "U sosu od crnog vina sa suvim šljivama", 910, "STEK DREN");
INSERT INTO Stavka (idStavke, opis, cena, naziv) VALUES (4, "Telece meso,pecurke,mlinci,pavlaka", 1150, "TELETINA U SOSU OD PEČURAKA SA MLINCIMA");
INSERT INTO Stavka (idStavke, opis, cena, naziv) VALUES (5, "Mix zelenih salata,tunjevina, bareno jaje, masline, crveni luk, čeri paradajz ", 540, "TUNA SALATA");
INSERT INTO Stavka (idStavke, opis, cena, naziv) VALUES (6, "", 1250, "LIGNJE NA ŽARU");
COMMIT;

-- -----------------------------------------------------
-- Data for table Jelo
-- -----------------------------------------------------

START TRANSACTION;
USE mydb;
INSERT INTO Jelo (idJela, gramaza, brojOsoba) VALUES (1, 300, 1);
INSERT INTO Jelo (idJela, gramaza, brojOsoba) VALUES (2, 500, 2);
INSERT INTO Jelo (idJela, gramaza, brojOsoba) VALUES (3, 1000, 3);
INSERT INTO Jelo (idJela, gramaza, brojOsoba) VALUES (4, 250, 1);
INSERT INTO Jelo (idJela, gramaza, brojOsoba) VALUES (5, 300, 1);
INSERT INTO Jelo (idJela, gramaza, brojOsoba) VALUES (6, 400, 2);
COMMIT;
