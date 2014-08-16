SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

DROP SCHEMA IF EXISTS `delivery_management` ;
CREATE SCHEMA IF NOT EXISTS `delivery_management` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci ;
USE `delivery_management` ;

-- -----------------------------------------------------
-- Table `branches`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `branches` (
  `b_id` INT NOT NULL,
  `b_name` CHAR(30) NOT NULL,
  `b_email` CHAR(45) NOT NULL,
  `b_zipcode` CHAR(8) NOT NULL,
  PRIMARY KEY (`b_id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `customers`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `customers` (
  `c_id` INT NOT NULL,
  `c_last_name` CHAR(15) NOT NULL,
  `c_first_name` CHAR(15) NOT NULL,
  `c_email` CHAR(45) NOT NULL,
  `c_zipcode` CHAR(8) NOT NULL,
  PRIMARY KEY (`c_id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `parts`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `parts` (
  `p_id` INT NOT NULL,
  `p_name` CHAR(30) NOT NULL,
  `p_price` INT NOT NULL,
  `p_stock` INT NOT NULL,
  `p_production_per_week` INT NOT NULL,
  PRIMARY KEY (`p_id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `orders`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `orders` (
  `o_id` INT NOT NULL,
  `o_bid` INT NOT NULL,
  `o_cid` INT NOT NULL,
  `o_pid` INT NOT NULL,
  `o_quantity` INT NOT NULL,
  `o_order_datetime` DATETIME NOT NULL,
  `o_due_date` DATE NOT NULL,
  `o_delivery_date` DATE NULL,
  PRIMARY KEY (`o_id`),
  INDEX `o_pid_idx` (`o_pid` ASC),
  INDEX `o_bid_idx` (`o_bid` ASC),
  INDEX `o_cid_idx` (`o_cid` ASC),
  CONSTRAINT `o_bid`
    FOREIGN KEY (`o_bid`)
    REFERENCES `branches` (`b_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `o_cid`
    FOREIGN KEY (`o_cid`)
    REFERENCES `customers` (`c_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `o_pid`
    FOREIGN KEY (`o_pid`)
    REFERENCES `parts` (`p_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
