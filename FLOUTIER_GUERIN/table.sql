-- phpMyAdmin SQL Dump
-- version 4.9.0.1
-- https://www.phpmyadmin.net/
--
-- Hôte : localhost:8889
-- Généré le :  lun. 03 fév. 2020 à 15:24
-- Version du serveur :  5.7.26
-- Version de PHP :  7.3.8

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

--
-- Base de données :  `hackerz`
--

-- --------------------------------------------------------

--
-- Structure de la table `utilisateur`
--

CREATE TABLE `utilisateur` (
  `nom_utilisateur` varchar(100) NOT NULL,
  `mot_de_passe` varchar(100) NOT NULL,
  `nom` varchar(100) DEFAULT NULL,
  `prenom` varchar(100) DEFAULT NULL,
  `mail` varchar(100) DEFAULT NULL,
  `adresse` varchar(100) DEFAULT NULL,
  `telephone` varchar(15) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `utilisateur`
--

INSERT INTO `utilisateur` (`nom_utilisateur`, `mot_de_passe`, `nom`, `prenom`, `mail`, `adresse`, `telephone`) VALUES
('julien', 'azerty', NULL, NULL, NULL, NULL, NULL),
('simon', 'poiuyt', 'simon', '\';UPDATE utilisateur SET telephone=\'001200\' WHERE nom_utilisateur=\'simon\' ;#', 'test', 'leiavbougbaeo', '001240'),
('test', 'test', NULL, NULL, NULL, NULL, NULL),
('test', 'testbis', NULL, NULL, NULL, NULL, NULL);
