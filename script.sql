-- MySQL Script generated by MySQL Workbench
-- Sat Dec 15 09:44:01 2018
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS mydb ;

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS mydb DEFAULT CHARACTER SET utf8 ;
USE mydb ;

-- -----------------------------------------------------
-- Table Radnik
-- -----------------------------------------------------
DROP TABLE IF EXISTS Radnik ;

CREATE TABLE IF NOT EXISTS Radnik (
  idRadnika INT NOT NULL,
  ime VARCHAR(45) NOT NULL,
  prezime VARCHAR(45) NOT NULL,
  PRIMARY KEY (idRadnika))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table RadnikKojiPriprema
-- -----------------------------------------------------
DROP TABLE IF EXISTS RadnikKojiPriprema ;

CREATE TABLE IF NOT EXISTS RadnikKojiPriprema (
  idRadnikaKojiPriprema INT NOT NULL,
  tipStavke VARCHAR(45) NOT NULL,
  PRIMARY KEY (idRadnikaKojiPriprema),
  CONSTRAINT fk_RadnikKojiPriprema_Radnik
    FOREIGN KEY (idRadnikaKojiPriprema)
    REFERENCES Radnik (idRadnika)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table Konobar
-- -----------------------------------------------------
DROP TABLE IF EXISTS Konobar ;

CREATE TABLE IF NOT EXISTS Konobar (
  idKonobara INT NOT NULL,
  depozit DOUBLE NULL,
  dnevniPazar DOUBLE NULL,
  PRIMARY KEY (idKonobara),
  CONSTRAINT fk_Konobar_Radnik
    FOREIGN KEY (idKonobara)
    REFERENCES Radnik (idRadnika)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table Sto
-- -----------------------------------------------------
DROP TABLE IF EXISTS Sto ;

CREATE TABLE IF NOT EXISTS Sto (
  idStola INT NOT NULL AUTO_INCREMENT,
  naziv VARCHAR(45) NULL,
  brojMesta INT NOT NULL,
  PRIMARY KEY (idStola))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table Meni
-- -----------------------------------------------------
DROP TABLE IF EXISTS Meni ;

CREATE TABLE IF NOT EXISTS Meni (
  idMenija INT NOT NULL,
  vaziOd DATE NOT NULL,
  vaziDo DATE NOT NULL,
  popust INT NULL,
  PRIMARY KEY (idMenija))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table Stavka
-- -----------------------------------------------------
DROP TABLE IF EXISTS Stavka ;

CREATE TABLE IF NOT EXISTS Stavka (
  idStavke INT NOT NULL,
  opis VARCHAR(500) NULL,
  cena DOUBLE NOT NULL,
  naziv VARCHAR(45) NOT NULL,
  PRIMARY KEY (idStavke))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table Jelo
-- -----------------------------------------------------
DROP TABLE IF EXISTS Jelo ;

CREATE TABLE IF NOT EXISTS Jelo (
  idJela INT NOT NULL,
  gramaza INT NULL,
  brojOsoba INT NULL,
  PRIMARY KEY (idJela),
  CONSTRAINT fk_Jelo_Stavka
    FOREIGN KEY (idJela)
    REFERENCES Stavka (idStavke)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table Pice
-- -----------------------------------------------------
DROP TABLE IF EXISTS Pice ;

CREATE TABLE IF NOT EXISTS Pice (
  idPica INT NOT NULL,
  kolicina DOUBLE NULL,
  PRIMARY KEY (idPica),
  CONSTRAINT fk_Pice_Stavka
    FOREIGN KEY (idPica)
    REFERENCES Stavka (idStavke)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table Dodatak
-- -----------------------------------------------------
DROP TABLE IF EXISTS Dodatak ;

CREATE TABLE IF NOT EXISTS Dodatak (
  idDodatak INT NOT NULL,
  naziv VARCHAR(45) NOT NULL,
  kolicina VARCHAR(45) NULL,
  opis VARCHAR(500) NULL,
  cena DOUBLE NULL,
  PRIMARY KEY (idDodatak))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table Racun
-- -----------------------------------------------------
DROP TABLE IF EXISTS Racun ;

CREATE TABLE IF NOT EXISTS Racun (
  idRacun INT NOT NULL,
  iznos DOUBLE NOT NULL,
  PRIMARY KEY (idRacun))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table MeniStavka
-- -----------------------------------------------------
DROP TABLE IF EXISTS MeniStavka ;

CREATE TABLE IF NOT EXISTS MeniStavka (
  idMenija INT NOT NULL,
  idStavke INT NOT NULL,
  PRIMARY KEY (idMenija, idStavke),
  INDEX fk_Stavka_idx (idStavke ASC),
  CONSTRAINT fk_MeniStavka_Meni
    FOREIGN KEY (idMenija)
    REFERENCES Meni (idMenija)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT fk_MeniStavka_Stavka
    FOREIGN KEY (idStavke)
    REFERENCES Stavka (idStavke)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table StavkaDodatak
-- -----------------------------------------------------
DROP TABLE IF EXISTS StavkaDodatak ;

CREATE TABLE IF NOT EXISTS StavkaDodatak (
  idStavke INT NOT NULL,
  idDodatka INT NOT NULL,
  PRIMARY KEY (idStavke, idDodatka),
  INDEX fk_Dodatak_idx (idDodatka ASC),
  CONSTRAINT fk_StavkaDodatak_Stavka
    FOREIGN KEY (idStavke)
    REFERENCES Stavka (idStavke)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT fk_StavkaDodatak_Dodatak
    FOREIGN KEY (idDodatka)
    REFERENCES Dodatak (idDodatak)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table Narudzbina
-- -----------------------------------------------------
DROP TABLE IF EXISTS Narudzbina ;

CREATE TABLE IF NOT EXISTS Narudzbina (
  idNarudzbine INT NOT NULL,
  idStola INT NOT NULL,
  idRacuna INT NOT NULL,
  idKonobara INT NULL,
  usluzeno TINYINT(1) NULL,
  PRIMARY KEY (idNarudzbine),
  INDEX fk_Sto_idx (idStola ASC),
  INDEX fk_Racun_idx (idRacuna ASC),
  INDEX fk_Konobar_idx (idKonobara ASC),
  CONSTRAINT fk_Narudzbina_Sto
    FOREIGN KEY (idStola)
    REFERENCES Sto (idStola)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT fk_Narudzbina_Racun
    FOREIGN KEY (idRacuna)
    REFERENCES Racun (idRacun)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT fk_Narudzbina_Konobar
    FOREIGN KEY (idKonobara)
    REFERENCES Konobar (idKonobara)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table NarudzbinaStavka
-- -----------------------------------------------------
DROP TABLE IF EXISTS NarudzbinaStavka ;

CREATE TABLE IF NOT EXISTS NarudzbinaStavka (
  idNarudzbine INT NOT NULL,
  idMenija INT NOT NULL,
  idStavke INT NOT NULL,
  idRadnikPorudzbina INT NULL,
  spremno VARCHAR(45) NULL,
  PRIMARY KEY (idNarudzbine, idMenija, idStavke),
  INDEX fk_Menija_idx (idMenija ASC),
  INDEX fk_Stavka_idx (idStavke ASC),
  INDEX fk_RadnikPorudzbina_idx (idRadnikPorudzbina ASC),
  CONSTRAINT fk_NarudzbinaStavka_Narudzbina
    FOREIGN KEY (idNarudzbine)
    REFERENCES Narudzbina (idNarudzbine)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT fk_NarudzbinaStavka_Meni
    FOREIGN KEY (idMenija)
    REFERENCES MeniStavka (idMenija)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT fk_NarudzbinaStavka_Stavka
    FOREIGN KEY (idStavke)
    REFERENCES MeniStavka (idMenija)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT fk_NarudzbinaStavka_RadnikPorudzbina
    FOREIGN KEY (idRadnikPorudzbina)
    REFERENCES RadnikKojiPriprema (idRadnikaKojiPriprema)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table DodatakStavkeIzNarudzbine
-- -----------------------------------------------------
DROP TABLE IF EXISTS DodatakStavkeIzNarudzbine ;

CREATE TABLE IF NOT EXISTS DodatakStavkeIzNarudzbine (
  idNarudzbine INT NOT NULL,
  idMenija INT NOT NULL,
  idStavke INT NOT NULL,
  idDodatka INT NOT NULL,
  PRIMARY KEY (idNarudzbine, idMenija, idStavke, idDodatka),
  INDEX fk_Meni_idx (idMenija ASC),
  INDEX fk_Stavka_idx (idStavke ASC),
  INDEX fk_Dodatak_idx (idDodatka ASC),
  CONSTRAINT fk_DodatakStavkeIzNarudzbine_Narudzbina
    FOREIGN KEY (idNarudzbine)
    REFERENCES NarudzbinaStavka (idNarudzbine)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT fk_DodatakStavkeIzNarudzbine_Meni
    FOREIGN KEY (idMenija)
    REFERENCES NarudzbinaStavka (idNarudzbine)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT fk_DodatakStavkeIzNarudzbine_Stavka
    FOREIGN KEY (idStavke)
    REFERENCES NarudzbinaStavka (idNarudzbine)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT fk_DodatakStavkeIzNarudzbine_Dodatak
    FOREIGN KEY (idDodatka)
    REFERENCES Dodatak (idDodatak)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table TipJela
-- -----------------------------------------------------
DROP TABLE IF EXISTS TipJela ;

CREATE TABLE IF NOT EXISTS TipJela (
  idTipJela INT NOT NULL,
  naziv VARCHAR(45) NOT NULL,
  PRIMARY KEY (idTipJela))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table TipPica
-- -----------------------------------------------------
DROP TABLE IF EXISTS TipPica ;

CREATE TABLE IF NOT EXISTS TipPica (
  idTipPica INT NOT NULL,
  naziv VARCHAR(45) NOT NULL,
  PRIMARY KEY (idTipPica))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table JeloTipJela
-- -----------------------------------------------------
DROP TABLE IF EXISTS JeloTipJela ;

CREATE TABLE IF NOT EXISTS JeloTipJela (
  idJela INT NOT NULL,
  idTipJela INT NOT NULL,
  PRIMARY KEY (idJela, idTipJela),
  INDEX fk_tipJela_idx (idTipJela ASC),
  CONSTRAINT fk_JeloTipJela_Jelo
    FOREIGN KEY (idJela)
    REFERENCES Jelo (idJela)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT fk_JeloTipJela_TipJela
    FOREIGN KEY (idTipJela)
    REFERENCES TipJela (idTipJela)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table PiceTipPica
-- -----------------------------------------------------
DROP TABLE IF EXISTS PiceTipPica ;

CREATE TABLE IF NOT EXISTS PiceTipPica (
  idPica INT NOT NULL,
  idTipPica INT NOT NULL,
  PRIMARY KEY (idPica, idTipPica),
  INDEX fk_tipPica_idx (idTipPica ASC),
  CONSTRAINT fk_PiceTipPica_Pice
    FOREIGN KEY (idPica)
    REFERENCES Pice (idPica)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT fk_PiceTipPica_TipPica
    FOREIGN KEY (idTipPica)
    REFERENCES TipPica (idTipPica)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
