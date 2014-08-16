-- mysql -u dblec --local-infile < load-data.sql
LOAD DATA LOCAL INFILE 'branches.tsv' INTO TABLE `delivery_management`.`branches`;
LOAD DATA LOCAL INFILE 'customers.tsv' INTO TABLE `delivery_management`.`customers`;
LOAD DATA LOCAL INFILE 'parts.tsv' INTO TABLE `delivery_management`.`parts`;
LOAD DATA LOCAL INFILE 'orders.tsv' INTO TABLE `delivery_management`.`orders`;
