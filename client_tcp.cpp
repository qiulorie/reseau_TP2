#include <iostream>
#include <cstdlib> // exit_failure, exit_success
#include <cstring> 
#include <unistd.h> //ferme le socket
#include <arpa/inet.h> // manipulation adreesses (conversion adresses IP...)
#include <sys/socket.h> // fonctions de socket + const

using namespace std;

#define PORT 9600
#define BUFFER_SIZE 100

int main(int argc, char* argv[]) {
    //vérification arguments ligne de commande
        if (argc < 2) { //vérifie que l'ip a bien été mis en argument
            cerr << "Rentrez l'adresse du serveur" << endl;
            return EXIT_FAILURE;
    }

    //création socket
    int socketClient = socket(AF_INET, SOCK_STREAM/**mode flux**/, 0/* pas de flag*/); 
    if (socketClient == -1) { //si socket() échoue, programme s'arrête
        perror("erreur  création socket");
        return EXIT_FAILURE;
    
    }

    //config adresse serveur
    sockaddr_in adresseServeur{}; //struct pour représenter adreses IPV4
    adresseServeur.sin_family = AF_INET; //IPv4
    adresseServeur.sin_port = htons(PORT); //port réseau
    socklen_t addLen = sizeof(adresseServeur);

    //conversion adresse IP donnée en arg
    int add = inet_pton(AF_INET, argv[1], &adresseServeur.sin_addr);
    if (add <= 0) {
        perror("erreur création socket UDP");
    }

    //connexion au serveur
    int con = connect(socketClient, reinterpret_cast<const sockaddr*>(&adresseServeur), sizeof(adresseServeur));
    if (con < 0) {
        perror("erreur connexion ");
    }

    cout << "connexion établie avec le serveur : " << argv[1] << endl;

    //lecture message à envoyer
    char buffer[BUFFER_SIZE];
    cout << "entrez un message à envoyer au serveur : ";
    cin.getline(buffer, BUFFER_SIZE);

    //envoi du message au serveur
    ssize_t ecritureOctets = write(socketClient, buffer, strlen(buffer));
    if (ecritureOctets < 0) {
        perror("erreur envoi message");
        close(socketClient);
        return EXIT_FAILURE;
    }

    cout << "message envoyé au serveur" << endl;

    //fermeture socket
    close(socketClient);
    cout << "connexion terminée" << endl;

    return EXIT_SUCCESS;

}