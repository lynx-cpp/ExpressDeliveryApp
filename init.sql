SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';

CREATE SCHEMA IF NOT EXISTS `ExpressDelivery` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci ;
USE `ExpressDelivery` ;

-- -----------------------------------------------------
-- Table `ExpressDelivery`.`order_category`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `ExpressDelivery`.`order_category` (
  `id` INT NULL AUTO_INCREMENT ,
  `order_category_name` VARCHAR(45) NULL ,
  `price` DOUBLE NULL ,
  `costing` DOUBLE NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `ExpressDelivery`.`account`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `ExpressDelivery`.`account` (
  `id` INT NULL AUTO_INCREMENT ,
  `account_name` VARCHAR(45) NULL ,
  `user_name` VARCHAR(45) NULL ,
  `address` VARCHAR(45) NULL ,
  `is_admin` TINYINT(1) NULL ,
  `password` VARCHAR(45) NULL ,
  `telephone` VARCHAR(45) NULL ,
  PRIMARY KEY (`id`) ,
  UNIQUE INDEX `account_name_UNIQUE` (`account_name` ASC) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `ExpressDelivery`.`place_to_place`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `ExpressDelivery`.`place_to_place` (
  `from_place` VARCHAR(45) NOT NULL ,
  `to_place` VARCHAR(45) NOT NULL ,
  `costing` DOUBLE NULL ,
  `price` VARCHAR(45) NULL ,
  PRIMARY KEY (`from_place`, `to_place`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `ExpressDelivery`.`order_list`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `ExpressDelivery`.`order_list` (
  `id` INT NULL AUTO_INCREMENT ,
  `from_place` VARCHAR(45) NULL ,
  `to_place` VARCHAR(45) NULL ,
  `order_sent_time` DATETIME NULL ,
  `order_category_id` INT NOT NULL ,
  `account_id` INT NOT NULL ,
  `costing` DOUBLE NULL ,
  `price` DOUBLE NULL ,
  `postman_name` VARCHAR(45) NULL ,
  `postman_phone` VARCHAR(45) NULL ,
  `delivery_start` DATETIME NULL ,
  `delivery_arrival` DATETIME NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_order_order_category1` (`order_category_id` ASC) ,
  INDEX `fk_order_account1` (`account_id` ASC) ,
  INDEX `fk_order_place` (`from_place` ASC, `to_place` ASC) ,
  CONSTRAINT `fk_order_order_category1`
    FOREIGN KEY (`order_category_id` )
    REFERENCES `ExpressDelivery`.`order_category` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_order_account1`
    FOREIGN KEY (`account_id` )
    REFERENCES `ExpressDelivery`.`account` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_order_place`
    FOREIGN KEY (`from_place` , `to_place` )
    REFERENCES `ExpressDelivery`.`place_to_place` (`from_place` , `to_place` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

-- -----------------------------------------------------
-- Data for table `ExpressDelivery`.`order_category`
-- -----------------------------------------------------
START TRANSACTION;
USE `ExpressDelivery`;
INSERT INTO `ExpressDelivery`.`order_category` (`id`, `order_category_name`, `price`, `costing`) VALUES (NULL, 'general', 1, 0.1);

COMMIT;
