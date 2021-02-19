26.02.2020 
=======================================================================================================================
1.Predpoklady pred spustením:

1.1 MySQl DB s nazvom bigd

1.2 Tabulka 1mIBM s datami z csv + dalsie slpce - ich hodnoty metoda mysql.update(Symbol) doplni

CREATE DATABASE bigd;
USE bigd;
CREATE TABLE 1mIBM (
id INT UNSIGNED NOT NULL AUTO_INCREMENT,
symbol CHAR(15) NOT NULL,
date DATE NOT NULL,
time TIME NOT NULL,
open DOUBLE(11,5) NOT NULL,
high DOUBLE(11,5) NOT NULL,
low  DOUBLE(11,5) NOT NULL,
close DOUBLE(11,5) NOT NULL,
vol INT NOT NULL,
PRIMARY KEY (id)
);

SET GLOBAL local_infile = 1;

LOAD DATA LOCAL INFILE 'IBM_adjusted.txt'   INTO TABLE 1mIBM FIELDS TERMINATED BY ',' LINES TERMINATED BY '\n'   (@date_converted,time,open,high,low,close,vol) SET date = STR_TO_DATE(@date_converted, '%m/%d/%Y'), symbol='IBM';
#add columns computed by index
ALTER TABLE 1mIBM ADD COLUMN openHash TINYINT UNSIGNED;
ALTER TABLE 1mIBM ADD COLUMN highHash TINYINT UNSIGNED;
ALTER TABLE 1mIBM ADD COLUMN lowHash TINYINT UNSIGNED;
ALTER TABLE 1mIBM ADD COLUMN closeHash TINYINT UNSIGNED;
ALTER TABLE 1mIBM ADD COLUMN maxRange DOUBLE(11,5);
ALTER TABLE 1mIBM ADD COLUMN trueRange DOUBLE(11,5);
ALTER TABLE 1mIBM ADD COLUMN pivotPocket TINYINT UNSIGNED;
ALTER TABLE 1mIBM ADD COLUMN change DOUBLE(11,5);


1.3 Tabulky UEnvelop a LEnvelop

use bigd;

ak existuje
drop table UEnvelops;
drop table LEnvelops;

create table UEnvelops(
UEnv_id int auto_increment primary key,
row_id int,
env1 double,
env2 double,
env3 double
);
create table LEnvelops(
LEnv_id int auto_increment primary key,
row_id int,
env1 double,
env2 double,
env3 double
)

TODO
Odstranit obmedzenie poctu envelopov(mame 3 splce) - v sucasnosti musime vopred vytvarat tabulky

2. MySql.c, riadok 20 - db username & password

3. main.c 
riadok 26,31 staci 1 spustit -POTOM zakomentovat