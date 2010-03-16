SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';

CREATE SCHEMA IF NOT EXISTS `shop` DEFAULT CHARACTER SET utf8 COLLATE utf8_bin ;
USE `shop`;

-- -----------------------------------------------------
-- Table `shop`.`Contact`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `shop`.`Contact` ;

CREATE  TABLE IF NOT EXISTS `shop`.`Contact` (
  `contactId` INT(11) NOT NULL DEFAULT NULL AUTO_INCREMENT ,
  `firstName` VARCHAR(50) NULL DEFAULT NULL ,
  `lastName` VARCHAR(50) NULL DEFAULT NULL ,
  `companyName` VARCHAR(50) NULL DEFAULT NULL ,
  `email` VARCHAR(50) NULL DEFAULT NULL ,
  `webUrl` VARCHAR(50) NULL DEFAULT NULL ,
  PRIMARY KEY (`contactId`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
PACK_KEYS = DEFAULT
ROW_FORMAT = DEFAULT;


-- -----------------------------------------------------
-- Table `shop`.`OrderHeader`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `shop`.`OrderHeader` ;

CREATE  TABLE IF NOT EXISTS `shop`.`OrderHeader` (
  `orderHeaderId` INT(11) NOT NULL DEFAULT NULL AUTO_INCREMENT ,
  `orginatorId` INT(11) NULL DEFAULT NULL ,
  PRIMARY KEY (`orderHeaderId`) ,
  INDEX `fk_OrderHeader_Contact` (`orginatorId` ASC) ,
  CONSTRAINT `fk_OrderHeader_Contact`
    FOREIGN KEY (`orginatorId` )
    REFERENCES `shop`.`Contact` (`contactId` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin;


-- -----------------------------------------------------
-- Table `shop`.`ProductType`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `shop`.`ProductType` ;

CREATE  TABLE IF NOT EXISTS `shop`.`ProductType` (
  `productTypeId` INT(11) NOT NULL DEFAULT NULL AUTO_INCREMENT ,
  `name` VARCHAR(50) NULL DEFAULT NULL ,
  PRIMARY KEY (`productTypeId`) ,
  INDEX `Name` (`name` ASC) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin;


-- -----------------------------------------------------
-- Table `shop`.`Product`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `shop`.`Product` ;

CREATE  TABLE IF NOT EXISTS `shop`.`Product` (
  `productId` INT(11) NOT NULL DEFAULT NULL AUTO_INCREMENT ,
  `productTypeId` INT(11) NOT NULL ,
  `name` VARCHAR(30) NULL DEFAULT NULL ,
  `description` VARCHAR(50) NULL DEFAULT NULL ,
  `manufacturerId` INT(11) NOT NULL DEFAULT NULL ,
  `supplierId` INT(11) NOT NULL DEFAULT NULL ,
  `externPartNo` VARCHAR(30) NULL DEFAULT NULL ,
  `internPartNo` VARCHAR(30) NULL DEFAULT NULL ,
  `minOrder` INT(11) NULL DEFAULT NULL ,
  `deliveryTime` INT(11) NULL DEFAULT NULL ,
  `supplierAmount` DOUBLE NULL DEFAULT NULL ,
  `supplierCurrency` VARCHAR(3) NULL DEFAULT NULL ,
  `salesAmount` DOUBLE NULL DEFAULT NULL ,
  `salesCurrency` VARCHAR(3) NULL DEFAULT NULL ,
  PRIMARY KEY (`productId`) ,
  INDEX `fk_Product_Manufacturer` (`manufacturerId` ASC) ,
  INDEX `fk_Product_Supplier` (`supplierId` ASC) ,
  INDEX `fk_Product_ProductType` (`productTypeId` ASC) ,
  CONSTRAINT `fk_Product_Manufacturer`
    FOREIGN KEY (`manufacturerId` )
    REFERENCES `shop`.`Contact` (`contactId` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Product_Supplier`
    FOREIGN KEY (`supplierId` )
    REFERENCES `shop`.`Contact` (`contactId` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Product_ProductType`
    FOREIGN KEY (`productTypeId` )
    REFERENCES `shop`.`ProductType` (`productTypeId` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin;


-- -----------------------------------------------------
-- Table `shop`.`OrderRow`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `shop`.`OrderRow` ;

CREATE  TABLE IF NOT EXISTS `shop`.`OrderRow` (
  `orderRowId` INT(11) NOT NULL DEFAULT NULL AUTO_INCREMENT ,
  `orderHeaderId` INT(11) NULL DEFAULT NULL ,
  `productId` INT(11) NULL DEFAULT NULL ,
  `number` INT(11) NULL DEFAULT NULL ,
  PRIMARY KEY (`orderRowId`) ,
  INDEX `fk_OrderRow_OrderHeader` (`orderHeaderId` ASC) ,
  INDEX `fk_OrderRow_Product` (`productId` ASC) ,
  CONSTRAINT `fk_OrderRow_OrderHeader`
    FOREIGN KEY (`orderHeaderId` )
    REFERENCES `shop`.`OrderHeader` (`orderHeaderId` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_OrderRow_Product`
    FOREIGN KEY (`productId` )
    REFERENCES `shop`.`Product` (`productId` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin;



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
