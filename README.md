# TP 2 de réseau : serveur et client (TCP, UDP)

## Description du TP

Ce tp implémente des clients et serveur en utilisant les protocoles **UDP** et **TCP** afin de communiquer sur un réseau. Il regroupe en tout 4 programmes codés en C++

- `serveur_udp`
- `client_udp`
- `serveur_tcp`
- `client_tcp`

## Présentation des fichiers du TP

### 1. **`serveur_udp`**
le programme `serveur_udp` : 
- met en place un serveur UDP écoutant sur le port 9600
- la taille maximum du buffer est de 20
- écoute toutes les interfaces
- attend les messages des clients et les affiche
- gère jusqu'à 10 messages avant de fermer le socket

### 2. **`client_udp`**
Le programme `client_udp` :
- permet à un client d'envoyer des messages au serveur UDP
- reste en boucle, jusqu'à que l'utilisateur écrit 'quit' afin de terminer la connexion
- traite les erreurs d'envoi de message 

### 3. **`serveur_tcp`**
Le programme `serveur_tcp` :
- le buffer est de taille maximale 100 
- met en place un serveur TCP écoutant sur un port spécifique
- accepte connexions clients et permet de recevoir des messages de différentes connexions avant de fermer la connexion
- affiche les messages reçus de chaque client, avec l'adresse du client concerné
- gère plusieurs clients en 1 séquence (1 à la fois)

### 4. **`client_tcp`**
Le programme `client_tcp` :
- permet à un client de se connecter au serveur TCP
- vérifie les erreurs de connexion et d'envoi de messages

## Compilation

Pour compiler les fichiers : compilateur **Clang++** avec la norme `C++17`.
On utilise l'adresse 127.0.0.1 afin de tester localement.

### Commandes de Compilation

```bash
clang++ -std=c++17 -o serveur_udp serveur_udp.cpp
clang++ -std=c++17 -o client_udp client_udp.cpp
clang++ -std=c++17 -o serveur_tcp serveur_tcp.cpp
clang++ -std=c++17 -o client_tcp client_tcp.cpp
```
### Exécution
```bash
./serveur_udp 
./client_udp 127.0.0.1
./serveur_tcp 127.0.0.1
./client_tcp 127.0.0.1
```




