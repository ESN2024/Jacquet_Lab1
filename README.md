# ESN11 - Rapport Lab1

## Objectifs
Construire et programmer un système de base Nios II sur un FPGA DE10-Lite pour contrôler un ensemble de périphériques présent sur la carte électronique. Nous devrons mettre en place un chenillard de led, déclencher par un boutton poussoirs et à vitesse réglable par plusieurs switchs.

## Introduction
Nous allons ainsi voir chaque étape de la réalisation de ce projet, les difficultés, les points clés, les raisons qui nous ont poussés aux différents choix d'implémentation spécifique de notre système.

## Réalisation du système
Nous allons dans un premier construire une représentation du système finale avant de passer à l'étape de la réalisation.

### Schéma bloc fonctionnel

<img width="750" alt="image" src="https://github.com/ESN2024/Jacquet_Lab1/assets/127327962/e43b916c-166f-418b-aadc-7f19f364fbc9">

Ce schéma présente l'architecture finale de notre système, la liaison entre notre pc et le système cible, ici la DE10 lite, via un câble USB Blaster. Ici nous visualisons uniquement les périphériques décris dans nos objectifs, évidemment la clock n'apparaît pas, ainsi que le signal de reset présent sur un second bouton poussoire.
L'architecture comporte ainsi différents modules important : 
1. RAM : La mémoire avec une capacité de 40 Mo, amplement suffisant pour cette implémentation.
2. 3 blocs PIO (Parrallel input/output) permettant au FPGA de communiquer avec l'extérieur en lisant des signaux d'entrées (récuperer les états des boutons poussoirs, switchs) et en envoyant des signaux de sortie (Allumage de leds). Deux de ces blocs PIO comporte des interuptions, mécanisme qui va signaler au processeur un évenement, celui ci va interrompre l'éxecution du programme en cours pour exécuter la fonction d'interuption. Ce processus remplace le polling qui scrutte en permanance l'arrivée du signal cherché, les interuptions sont un énorme gain de consomation.
3. Processeur Nios II : Processeur soft-core configurable du FPGA présent sur la DE10 lite. En tant que soft-core, il est implémenté en logique programmable plutôt que fabriqué en tant que puce physique, Ce qui lui donne une nature configurable et nous permet de personnaliser le processeur en fonction de nos besoins spécifiques, réel gain de performances.

### Création du système
Après avoir crée sous Quartus 18.1 notre projet nous allons pouvoir avec l'outil Platform Designer crée notre système en déclarant l'ensemble des modules nécessaires ainsi que leurs configurations respectives.
<img width="352" alt="image" src="https://github.com/ESN2024/Jacquet_Lab1/assets/127327962/68c118c0-71ff-4f41-a909-7796294b890b">

<img width="356" alt="image" src="https://github.com/ESN2024/Jacquet_Lab1/assets/127327962/27643f2e-2be2-4f49-aa25-0eee4cf3a65c">

Il faudra relier minutieusement ces différents modules pour les interconnecter de façon intelligente, en veillant à bien renseigner les interuptions de nos deux modules PIO_1 et PIO_2, le nombre de bit alloué ainsi que la direction, c'est à dire si les périphériques seront des sorties ou des entrées.

<img width="260" alt="image" src="https://github.com/ESN2024/Jacquet_Lab1/assets/127327962/132083b4-fa53-48ba-b258-22f681b6a225">

Lorsque ces étapes ont été réalisé et que Platform Designer ne renvois aucune erreur nous pouvons généré le VHDL correspondant à ce système en l'exportant.


