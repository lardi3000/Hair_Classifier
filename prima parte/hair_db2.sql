-- phpMyAdmin SQL Dump
-- version 4.2.11
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Set 08, 2015 alle 10:21
-- Versione del server: 5.6.21
-- PHP Version: 5.6.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `hair_db2`
--

-- --------------------------------------------------------

--
-- Struttura della tabella `images`
--

CREATE TABLE IF NOT EXISTS `images` (
`ID` int(11) NOT NULL,
  `image_path` mediumtext NOT NULL,
  `map_path` mediumtext NOT NULL,
  `link_image` mediumtext NOT NULL,
  `common_creative` tinyint(1) NOT NULL DEFAULT '0'
) ENGINE=InnoDB AUTO_INCREMENT=62 DEFAULT CHARSET=latin1;

--
-- Dump dei dati per la tabella `images`
--

INSERT INTO `images` (`ID`, `image_path`, `map_path`, `link_image`, `common_creative`) VALUES
(1, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro565537224084_c56085f2cf_n_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro565537224084_c56085f2cf_n_resized_hair_map.jpg', 'https://c2.staticflickr.com/6/5180/5537224084_c56085f2cf_n.jpg', 1),
(2, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro563829446595_3d5f61bf9c_n_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro563829446595_3d5f61bf9c_n_resized_hair_map.jpg', 'https://c1.staticflickr.com/3/2506/3829446595_3d5f61bf9c_n.jpg', 1),
(3, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56Blonde_hair_resized.JPG', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56Blonde_hair_resized_hair_map.JPG', 'https://upload.wikimedia.org/wikipedia/commons/3/31/Blonde_hair.JPG', 1),
(4, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro5614804535712_44427edb6b_o_d_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro5614804535712_44427edb6b_o_d_resized_hair_map.jpg', 'https://farm3.staticflickr.com/2939/14804535712_44427edb6b_o_d.jpg', 1),
(5, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56Beautiful_healty_hair_resized.JPG', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56Beautiful_healty_hair_resized_hair_map.JPG', 'https://upload.wikimedia.org/wikipedia/commons/4/43/Beautiful_healty_hair.JPG', 1),
(6, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro566172213873_d69a86153f_o_d_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro566172213873_d69a86153f_o_d_resized_hair_map.jpg', 'https://farm7.staticflickr.com/6164/6172213873_d69a86153f_o_d.jpg', 1),
(7, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56Woman_With_Red_Hair_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56Woman_With_Red_Hair_resized_hair_map.jpg', 'https://upload.wikimedia.org/wikipedia/commons/f/f3/Woman_With_Red_Hair.jpg', 1),
(8, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56Hair_In_Wind_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56Hair_In_Wind_resized_hair_map.jpg', 'https://upload.wikimedia.org/wikipedia/commons/3/35/Hair_In_Wind.jpg', 1),
(9, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro569661260315_60a5b5d260_z_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro569661260315_60a5b5d260_z_resized_hair_map.jpg', 'https://c1.staticflickr.com/3/2841/9661260315_60a5b5d260_z.jpg', 1),
(10, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro566776474992_e26b87b077_b_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro566776474992_e26b87b077_b_resized_hair_map.jpg', 'https://c2.staticflickr.com/8/7052/6776474992_e26b87b077_b.jpg', 1),
(11, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56400768630_cb6dd91599_o_d_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56400768630_cb6dd91599_o_d_resized_hair_map.jpg', 'https://farm1.staticflickr.com/161/400768630_cb6dd91599_o_d.jpg', 1),
(12, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro566776475056_9f75afa3a4_b_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro566776475056_9f75afa3a4_b_resized_hair_map.jpg', 'https://c2.staticflickr.com/8/7061/6776475056_9f75afa3a4_b.jpg', 1),
(13, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro568541186192_387a38c165_b_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro568541186192_387a38c165_b_resized_hair_map.jpg', 'https://c1.staticflickr.com/9/8228/8541186192_387a38c165_b.jpg', 1),
(14, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56hair-flying-142210_640_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56hair-flying-142210_640_resized_hair_map.jpg', 'https://pixabay.com/static/uploads/photo/2013/06/30/02/55/hair-flying-142210_640.jpg', 1),
(15, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56390250185_009c784612_b_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56390250185_009c784612_b_resized_hair_map.jpg', 'https://c1.staticflickr.com/1/137/390250185_009c784612_b.jpg', 1),
(16, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro5633861262_9a8e5cef8d_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro5633861262_9a8e5cef8d_resized_hair_map.jpg', 'http://farm1.staticflickr.com/22/33861262_9a8e5cef8d.jpg', 1),
(17, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro565504986368_747a27b067_z_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro565504986368_747a27b067_z_resized_hair_map.jpg', 'https://c2.staticflickr.com/6/5173/5504986368_747a27b067_z.jpg', 1),
(18, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56red_hair_men_british_by_2846mn-d7ug0ew_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56red_hair_men_british_by_2846mn-d7ug0ew_resized_hair_map.jpg', 'http://orig12.deviantart.net/175c/f/2014/221/0/0/red_hair_men_british_by_2846mn-d7ug0ew.jpg', 1),
(19, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56jade_dyed_her_hair__by_littlemixfans-d5mskvx_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56jade_dyed_her_hair__by_littlemixfans-d5mskvx_resized_hair_map.jpg', 'http://orig08.deviantart.net/8e85/f/2012/336/4/2/jade_dyed_her_hair__by_littlemixfans-d5mskvx.jpg', 1),
(20, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro564224492360_e4e4af9013_b_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro564224492360_e4e4af9013_b_resized_hair_map.jpg', 'https://c1.staticflickr.com/3/2674/4224492360_e4e4af9013_b.jpg', 1),
(21, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro565605614737_91778c0c0a_b_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro565605614737_91778c0c0a_b_resized_hair_map.jpg', 'https://c2.staticflickr.com/6/5063/5605614737_91778c0c0a_b.jpg', 1),
(22, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro566475941183_07debf4c16_o_d_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro566475941183_07debf4c16_o_d_resized_hair_map.jpg', 'https://farm8.staticflickr.com/7162/6475941183_07debf4c16_o_d.jpg', 1),
(23, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56woman-83173_640_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56woman-83173_640_resized_hair_map.jpg', 'https://pixabay.com/static/uploads/photo/2013/02/18/18/36/woman-83173_640.jpg', 1),
(24, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56hair-315053_640_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56hair-315053_640_resized_hair_map.jpg', 'https://pixabay.com/static/uploads/photo/2014/04/05/11/19/hair-315053_640.jpg', 1),
(25, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro568518191543_717de621f8_z_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro568518191543_717de621f8_z_resized_hair_map.jpg', 'https://c1.staticflickr.com/9/8520/8518191543_717de621f8_z.jpg', 1),
(26, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56bleached_hair_o3o_daid_by_mischievousgirl-d65oyat_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56bleached_hair_o3o_daid_by_mischievousgirl-d65oyat_resized_hair_map.jpg', 'http://orig09.deviantart.net/ff32/f/2013/138/f/c/bleached_hair_o3o_daid_by_mischievousgirl-d65oyat.jpg', 1),
(27, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56girl-684688_640_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56girl-684688_640_resized_hair_map.jpg', 'https://pixabay.com/static/uploads/photo/2015/03/22/14/26/girl-684688_640.jpg', 1),
(28, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56167825234_d5ab883f90_o_d_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56167825234_d5ab883f90_o_d_resized_hair_map.jpg', 'https://farm1.staticflickr.com/69/167825234_d5ab883f90_o_d.jpg', 1),
(29, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56Natalie_Portman_2010_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56Natalie_Portman_2010_resized_hair_map.jpg', 'https://upload.wikimedia.org/wikipedia/commons/d/d0/Natalie_Portman_2010.jpg', 1),
(30, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro569139652368_e42061dd70_o_resized.png', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro569139652368_e42061dd70_o_resized_hair_map.png', 'https://farm4.staticflickr.com/3681/9139652368_e42061dd70_o.png', 1),
(31, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro5614117585793_c41639c280_o_d_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro5614117585793_c41639c280_o_d_resized_hair_map.jpg', 'https://farm8.staticflickr.com/7453/14117585793_c41639c280_o_d.jpg', 1),
(32, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56Sylvester_Stallone_Comic-Con_2010_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56Sylvester_Stallone_Comic-Con_2010_resized_hair_map.jpg', 'https://upload.wikimedia.org/wikipedia/commons/e/eb/Sylvester_Stallone_Comic-Con_2010.jpg', 1),
(33, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro568608844838_1f96873da7_o_d_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro568608844838_1f96873da7_o_d_resized_hair_map.jpg', 'https://farm9.staticflickr.com/8244/8608844838_1f96873da7_o_d.jpg', 1),
(34, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56252964050_a43e9f9b11_b_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56252964050_a43e9f9b11_b_resized_hair_map.jpg', 'https://c1.staticflickr.com/1/65/252964050_a43e9f9b11_b.jpg', 1),
(35, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro563913149205_a0c11eb615_o_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro563913149205_a0c11eb615_o_resized_hair_map.jpg', 'https://farm4.staticflickr.com/3429/3913149205_a0c11eb615_o.jpg', 1),
(36, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro566588510827_2c4850d9a9_b_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro566588510827_2c4850d9a9_b_resized_hair_map.jpg', 'https://c2.staticflickr.com/8/7018/6588510827_2c4850d9a9_b.jpg', 1),
(37, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro565656741706_4dbfe21d4c_o_d_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro565656741706_4dbfe21d4c_o_d_resized_hair_map.jpg', 'https://farm6.staticflickr.com/5228/5656741706_4dbfe21d4c_o_d.jpg', 1),
(38, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro5614771563171_b50ddfb7f2_o_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro5614771563171_b50ddfb7f2_o_resized_hair_map.jpg', 'https://farm3.staticflickr.com/2936/14771563171_b50ddfb7f2_o.jpg', 1),
(39, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro5614775913076_97d6fc9520_o_d_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro5614775913076_97d6fc9520_o_d_resized_hair_map.jpg', 'https://farm6.staticflickr.com/5554/14775913076_97d6fc9520_o_d.jpg', 1),
(40, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro566902383241_4909ed0472_o_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro566902383241_4909ed0472_o_resized_hair_map.jpg', 'https://farm8.staticflickr.com/7046/6902383241_4909ed0472_o.jpg', 1),
(41, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro569362849194_bae0f9dbef_b_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro569362849194_bae0f9dbef_b_resized_hair_map.jpg', 'https://c2.staticflickr.com/8/7351/9362849194_bae0f9dbef_b.jpg', 1),
(42, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro563329060387_c472590729_b_d_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro563329060387_c472590729_b_d_resized_hair_map.jpg', 'https://farm4.staticflickr.com/3397/3329060387_c472590729_b_d.jpg', 1),
(43, '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56Hand_combed_hair_resized.JPG', '/opt/lampp/htdocs/hairdetector2/db_images/b71k4ketbm7g04pki4seabro56Hand_combed_hair_resized_hair_map.JPG', 'https://upload.wikimedia.org/wikipedia/commons/d/db/Hand_combed_hair.JPG', 1),
(44, '/opt/lampp/htdocs/hairdetector2/db_images/n1j9j7fadge78o6mu7v8tqr7239448570254_000d3c8e3f_o_d_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/n1j9j7fadge78o6mu7v8tqr7239448570254_000d3c8e3f_o_d_resized_hair_map.jpg', 'https://farm8.staticflickr.com/7420/9448570254_000d3c8e3f_o_d.jpg', 1),
(45, '/opt/lampp/htdocs/hairdetector2/db_images/n1j9j7fadge78o6mu7v8tqr72315315003921_c46e202d54_o_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/n1j9j7fadge78o6mu7v8tqr72315315003921_c46e202d54_o_resized_hair_map.jpg', 'https://farm4.staticflickr.com/3835/15315003921_c46e202d54_o.jpg', 1),
(46, '/opt/lampp/htdocs/hairdetector2/db_images/n1j9j7fadge78o6mu7v8tqr723CobieSmulders2008_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/n1j9j7fadge78o6mu7v8tqr723CobieSmulders2008_resized_hair_map.jpg', 'https://upload.wikimedia.org/wikipedia/commons/7/7e/CobieSmulders2008.jpg', 1),
(47, '/opt/lampp/htdocs/hairdetector2/db_images/n1j9j7fadge78o6mu7v8tqr7239448892182_69dcf3f532_b_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/n1j9j7fadge78o6mu7v8tqr7239448892182_69dcf3f532_b_resized_hair_map.jpg', 'https://c2.staticflickr.com/8/7334/9448892182_69dcf3f532_b.jpg', 1),
(48, '/opt/lampp/htdocs/hairdetector2/db_images/n1j9j7fadge78o6mu7v8tqr7239445699687_fedc3d3592_b_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/n1j9j7fadge78o6mu7v8tqr7239445699687_fedc3d3592_b_resized_hair_map.jpg', 'https://c2.staticflickr.com/4/3834/9445699687_fedc3d3592_b.jpg', 1),
(49, '/opt/lampp/htdocs/hairdetector2/db_images/n1j9j7fadge78o6mu7v8tqr723388559903_b6ae21cf05_o_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/n1j9j7fadge78o6mu7v8tqr723388559903_b6ae21cf05_o_resized_hair_map.jpg', 'https://farm1.staticflickr.com/160/388559903_b6ae21cf05_o.jpg', 1),
(50, '/opt/lampp/htdocs/hairdetector2/db_images/n1j9j7fadge78o6mu7v8tqr72316211221467_42c522fa69_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/n1j9j7fadge78o6mu7v8tqr72316211221467_42c522fa69_resized_hair_map.jpg', 'https://c4.staticflickr.com/8/7417/16211221467_42c522fa69.jpg', 1),
(51, '/opt/lampp/htdocs/hairdetector2/db_images/n1j9j7fadge78o6mu7v8tqr723Jennifer_Lawrence_at_the_83rd_Academy_Awards_crop_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/n1j9j7fadge78o6mu7v8tqr723Jennifer_Lawrence_at_the_83rd_Academy_Awards_crop_resized_hair_map.jpg', 'https://upload.wikimedia.org/wikipedia/commons/4/4f/Jennifer_Lawrence_at_the_83rd_Academy_Awards_crop.jpg', 1),
(52, '/opt/lampp/htdocs/hairdetector2/db_images/n1j9j7fadge78o6mu7v8tqr723Kaley_Cuoco_at_PaleyFest_2013_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/n1j9j7fadge78o6mu7v8tqr723Kaley_Cuoco_at_PaleyFest_2013_resized_hair_map.jpg', 'https://upload.wikimedia.org/wikipedia/commons/1/1c/Kaley_Cuoco_at_PaleyFest_2013.jpg', 1),
(53, '/opt/lampp/htdocs/hairdetector2/db_images/n4ieusqhnbt0nva0i44gm3dhe4Natural_blonde_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/n4ieusqhnbt0nva0i44gm3dhe4Natural_blonde_resized_hair_map.jpg', 'https://upload.wikimedia.org/wikipedia/commons/3/30/Natural_blonde.jpg', 1),
(54, '/opt/lampp/htdocs/hairdetector2/db_images/n4ieusqhnbt0nva0i44gm3dhe4Lucy_Merriam_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/n4ieusqhnbt0nva0i44gm3dhe4Lucy_Merriam_resized_hair_map.jpg', 'https://upload.wikimedia.org/wikipedia/commons/e/e7/Lucy_Merriam.jpg', 1),
(55, '/opt/lampp/htdocs/hairdetector2/db_images/n4ieusqhnbt0nva0i44gm3dhe46236306045_452c2fc42a_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/n4ieusqhnbt0nva0i44gm3dhe46236306045_452c2fc42a_resized_hair_map.jpg', 'https://c1.staticflickr.com/7/6051/6236306045_452c2fc42a.jpg', 1),
(56, '/opt/lampp/htdocs/hairdetector2/db_images/n4ieusqhnbt0nva0i44gm3dhe46922590071_b8e215e63f_b_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/n4ieusqhnbt0nva0i44gm3dhe46922590071_b8e215e63f_b_resized_hair_map.jpg', 'https://c2.staticflickr.com/8/7036/6922590071_b8e215e63f_b.jpg', 1),
(57, '/opt/lampp/htdocs/hairdetector2/db_images/n4ieusqhnbt0nva0i44gm3dhe4blond-487075_640_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/n4ieusqhnbt0nva0i44gm3dhe4blond-487075_640_resized_hair_map.jpg', 'https://pixabay.com/static/uploads/photo/2014/10/13/18/10/blond-487075_640.jpg', 1),
(58, '/opt/lampp/htdocs/hairdetector2/db_images/n4ieusqhnbt0nva0i44gm3dhe42798839533_8ba47f9b70_o_d_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/n4ieusqhnbt0nva0i44gm3dhe42798839533_8ba47f9b70_o_d_resized_hair_map.jpg', 'https://farm4.staticflickr.com/3064/2798839533_8ba47f9b70_o_d.jpg', 1),
(59, '/opt/lampp/htdocs/hairdetector2/db_images/n4ieusqhnbt0nva0i44gm3dhe4753060250_50621c8a8e_o_d_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/n4ieusqhnbt0nva0i44gm3dhe4753060250_50621c8a8e_o_d_resized_hair_map.jpg', 'https://farm2.staticflickr.com/1293/753060250_50621c8a8e_o_d.jpg', 1),
(60, '/opt/lampp/htdocs/hairdetector2/db_images/n4ieusqhnbt0nva0i44gm3dhe46747577235_cd2d4d76f1_b_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/n4ieusqhnbt0nva0i44gm3dhe46747577235_cd2d4d76f1_b_resized_hair_map.jpg', 'https://c2.staticflickr.com/8/7033/6747577235_cd2d4d76f1_b.jpg', 1),
(61, '/opt/lampp/htdocs/hairdetector2/db_images/n4ieusqhnbt0nva0i44gm3dhe41849450523_799a5d8707_o_d_resized.jpg', '/opt/lampp/htdocs/hairdetector2/db_images/n4ieusqhnbt0nva0i44gm3dhe41849450523_799a5d8707_o_d_resized_hair_map.jpg', 'https://farm3.staticflickr.com/2057/1849450523_799a5d8707_o_d.jpg', 1);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `images`
--
ALTER TABLE `images`
 ADD PRIMARY KEY (`ID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `images`
--
ALTER TABLE `images`
MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=62;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
