USE mydb;
DROP TRIGGER IF EXISTS iznosRacuna;
DELIMITER @
CREATE DEFINER = CURRENT_USER TRIGGER iznosRacuna BEFORE UPDATE ON Narudzbina
FOR EACH ROW
BEGIN
	declare stavke double;
    declare dodaci double;
    declare popust double;
    declare iznosZaNarudzbinu double;
    
    declare postavljenIznos double;
    declare ukupanIznos double;
    
    set postavljenIznos = (select r.iznos
							from Racun r
							where r.idRacun = new.idRacuna);
     
    if (new.idRacuna is not null and old.idRacuna is null) then
		set popust = (select m.popust
						from Meni m 
                        join NarudzbinaStavka ns on ns.idMenija = m.idMenija
                        where ns.idNarudzbine = new.idNarudzbine
						limit 1);
		
		set stavke = (select sum(s.cena)
						from Narudzbina n join NarudzbinaStavka ns on n.idNarudzbine = ns.idNarudzbine
						join Meni m on m.idMenija = ns.idMenija
						join Stavka s on s.idStavke = ns.idStavke 
						where n.idRacuna is null and n.idNarudzbine = new.idNarudzbine and n.idStola = new.idStola
						group by n.idStola);
		set dodaci = (select sum(d.cena)
						from Narudzbina n join NarudzbinaStavka ns on n.idNarudzbine = ns.idNarudzbine
                        join DodatakStavkeIzNarudzbine dsn on ns.idStavkeIzNarudzbine = dsn.idStavkeIzNarudzbine 
						join Meni m on m.idMenija = ns.idMenija
						join Dodatak d on d.idDodatak = dsn.idDodatka 
						where n.idRacuna is null and n.idNarudzbine = new.idNarudzbine and n.idStola = new.idStola
						group by n.idStola);
		if (dodaci is not null and stavke is not null) then 
			set iznosZaNarudzbinu = (stavke + dodaci) * (100 - popust)/100;
        end if;
        if (dodaci is null) then
			set iznosZaNarudzbinu = (stavke) * (100 - popust)/100;
		end if;
        if (stavke is null) then
			set iznosZaNarudzbinu = (dodaci) * (100 - popust)/100;
		end if;
        if (postavljenIznos is null) then
			set ukupanIznos = iznosZaNarudzbinu;
		else
			set ukupanIznos = iznosZaNarudzbinu + postavljenIznos;
		end if;
        update Racun r set r.iznos = ukupanIznos where r.idRacun = new.idRacuna;
    end if;
END @

drop trigger if exists uvecajDnevniPazar@

create trigger uvecajDnevniPazar before update on Racun
for each row
begin

	declare prethodniPazar double;
	declare id int;
    declare noviPazar double;
	if (new.naplaceno = true) then
		set prethodniPazar = (select k.dnevniPazar
							from Konobar k
							join Narudzbina n on k.idKonobara = n.idKonobara
							join Racun r on n.idRacuna = old.idRacun
							limit 1);
		
		set id = (select k.idKonobara
							from Konobar k
							join Narudzbina n on k.idKonobara = n.idKonobara
							join Racun r on n.idRacuna = old.idRacun
							limit 1);
		if (prethodniPazar is null) then
			set noviPazar = old.iznos;
		else
			set noviPazar = prethodniPazar + old.iznos;
		end if;
		update Konobar k set dnevniPazar = noviPazar where k.idKonobara = id;
    end if;
end;@

DELIMITER ;