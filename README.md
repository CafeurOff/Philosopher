# Projet Philosopher - 42

## Table des matières
1. [Description](#description)
2. [Objectif](#objectif)
3. [Compilation](#compilation)
4. [Utilisation](#utilisation)
5. [Exemples](#exemples)
6. [Auteurs](#auteurs)
7. [Licence](#licence)

## Description
Le projet Philosopher est une implémentation en langage C de la problématique classique du "Dining Philosophers". Il explore la synchronisation de processus et la gestion des ressources partagées dans un environnement multithreaded.

## Objectif
L'objectif principal de ce projet est d'implémenter une solution robuste pour éviter les conflits de ressources entre les philosophes qui partagent une table et doivent alternativement manger et réfléchir.

## Compilation
Le projet peut être compilé en utilisant le Makefile fourni. Exécutez la commande suivante dans le répertoire du projet :
```bash
make
```

## Utilisation
Une fois compilé, l'exécutable peut être lancé avec la commande suivante :

```bash
./philo [nombre_de_philosophes] [temps_de_mange] [temps_de_penser] [temps_de_dormir] [nombre_de_repas (optionnel)]
```
**nombre_de_philosophes**: _Le nombre de philosophes assis autour de la table._
**temps_de_mange**: _Le temps en millisecondes nécessaire pour qu'un philosophe mange._
**temps_de_penser**: _Le temps en millisecondes nécessaire pour qu'un philosophe pense._
**temps_de_dormir**: _Le temps en millisecondes nécessaire pour qu'un philosophe dorme._
**nombre_de_repas** _(optionnel): Le nombre de repas que chaque philosophe doit manger avant de terminer. Si non spécifié, les philosophes mangeront indéfiniment._

## Exemples

```bash
./philo 5 200 200 200
```

## Auteurs

Ce projet a été réalisé par [lduthill](https://github.com/CafeurOff) dans le cadre du cursus 42.

