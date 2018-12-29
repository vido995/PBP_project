-- -----------------------------------------------------
-- Data for table Konobar
-- -----------------------------------------------------
START TRANSACTION;
USE mydb;
INSERT INTO Radnik (idRadnika, ime, prezime) VALUES (1, 'Sef', 'Sale');
INSERT INTO Konobar (idKonobara, depozit, dnevniPazar, sefSale) VALUES (1, 2000, 0, 1);
COMMIT;

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
INSERT INTO Stavka (idStavke, opis, cena, naziv) VALUES (1, "Cureci file", 790, "CURETINA PARMA");
INSERT INTO Stavka (idStavke, opis, cena, naziv) VALUES (2, "Cureci file, med", 850, "CURETINA SA MEDOM");
INSERT INTO Stavka (idStavke, opis, cena, naziv) VALUES (3, "U sosu od crnog vina sa suvim šljivama", 910, "STEK DREN");
INSERT INTO Stavka (idStavke, opis, cena, naziv) VALUES (4, "Telece meso,pecurke,mlinci,pavlaka", 1150, "TELETINA SA MLINCIMA");
INSERT INTO Stavka (idStavke, opis, cena, naziv) VALUES (5, "Mix zelenih salata,tunjevina", 540, "TUNA SALATA");
INSERT INTO Stavka (idStavke, opis, cena, naziv) VALUES (6, "", 1250, "LIGNJE NA ZARU");
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

START TRANSACTION;
USE mydb;
INSERT INTO TipJela (idTipJela, naziv) VALUES (1, 'posno');
INSERT INTO TipJela (idTipJela, naziv) VALUES (2, 'vegansko');
INSERT INTO TipJela (idTipJela, naziv) VALUES (3, 'vegetarijansko');
INSERT INTO TipJela (idTipJela, naziv) VALUES (4, 'makrobioticko');
COMMIT;

START TRANSACTION;
USE mydb;
INSERT INTO TipPica (idTipPica, naziv) VALUES (1, 'alkohol');
INSERT INTO TipPica (idTipPica, naziv) VALUES (2, 'bezalkoholno');
INSERT INTO TipPica (idTipPica, naziv) VALUES (3, 'topli napici');
COMMIT;