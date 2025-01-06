#include <iostream>
#include <cstdlib> // exit_failure, exit_success
#include <cstring> 
#include <unistd.h> //ferme le socket
#include <arpa/inet.h> // manipulation adreesses (conversion adresses IP...)
#include <sys/socket.h> // fonctions de socket + const
#include <netdb.h>

using namespace std;

#define PORT 9600 
#define BUFFER_SIZE 20 //taille max buffer réception


/** 
 * int argc : nb total d'arguments passés à l'éxecution
 * char*argv[] : tableau de pointeurs vers char qui correspondent à arguments passé en ligne de commande
 * argv[0] : chemin/nom exécutable
 * argv[1] : 1e argument (ex : adresse IP...)
 * argv[2] : 2e argument (ex : port...)
*/
int main(int argc, char*argv[]) { 

    //vérification arguments ligne de commande
    if (argc < 2) { //vérifie que l'ip a bien été mis en argument
        cerr << "Rentrez l'adresse du serveur" << endl;
        return EXIT_FAILURE;
    }

    //vérifier l'adresse du serveur
    cout << "adresse IP du serveur : " << argv[1] << endl;

    //création socket et ouverture de celui-ci
    int socketUdp = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketUdp == -1) {
        perror("erreur création socket");
        return EXIT_FAILURE;
    };

    //configuration adresse serveur
    sockaddr_in adresseServeur;
    adresseServeur.sin_family = AF_INET;
    adresseServeur.sin_port = htons(PORT);
    socklen_t addLen = sizeof(adresseServeur);

    //conversion adresse IP donnée en arg
    int add = inet_pton(AF_INET, argv[1], &adresseServeur.sin_addr);
    if (add <= 0) {
        perror("erreur création socket UDP");
    }

    cout << "client connecté à : " << argv[1] << "sur le port : " << PORT << endl;

    //envoi des messages
    char buffer[BUFFER_SIZE];
    //boucle pour pouvoir envoyer plusieurs messages au serveur
    while (true) {
    
        cout << "entrez un message :";
        cin.getline(buffer, BUFFER_SIZE); //lecture entrée user
        //envoi message au serveur

        //si l'utilisateur rentre quit il termine la connexion
        if (strcmp(buffer, "quit") == 0) {
            cout << "fermeture de la connexion" << endl;
            break;
        }

        //envoi du message au serveur
        ssize_t tailleBytes = sendto(socketUdp, buffer, strlen(buffer), 0, reinterpret_cast<sockaddr*>(&adresseServeur), sizeof(adresseServeur));
        if (tailleBytes <= 0) {
            perror("erreur envoi du message");
            break;
                
        }

        cout << "message envoyé : " << buffer << endl;
    }   

    //fermeture socket
    close(socketUdp);
    cout << "client terminé" << endl;
    return EXIT_SUCCESS;



}