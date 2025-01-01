#include <iostream>
#include <cstdlib> // exit_failure, exit_success
#include <cstring> 
#include <unistd.h> //ferme le socket
#include <arpa/inet.h> // manipulation adreesses (conversion adresses IP...)
#include <sys/socket.h> // fonctions de socket + const

using namespace std;

#define PORT 9600
#define BUFFER_SIZE 100
#define BACKLOG  5 //taille fille d'attente pour connexions entrantes

int main(int argc, char* argv[]) {

    //vérification arguments ligne de commande
        if (argc < 2) { //vérifie que l'ip a bien été mis en argument
            cerr << "Rentrez l'adresse du serveur" << endl;
            return EXIT_FAILURE;
    }

        //création socket
    int socketServeur = socket(AF_INET, SOCK_DGRAM/**mode datagramme**/, 0/* pas de flag*/); 
    if (socketServeur == -1) { //si socket() échoue, programme s'arrête
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

    //liaison socket à adresse et au port
    int resBind = ::bind(socketServeur, reinterpret_cast<sockaddr*>(&adresseServeur), sizeof(adresseServeur) );
    if (resBind < 0) {
        perror("erreur attachement socket UDP ");
        close(socketServeur);
        return EXIT_FAILURE;
    }

    //écoute de la socket
    if (listen(socketServeur, BACKLOG) < 0) {
        perror("erreur mise en écoute");
        close(socketServeur);
        return EXIT_FAILURE;
    }

    cout << "le serveur TCP est en attente de connexions sur " << argv[1] << endl;

    //boucle pour accepter les connexions
    while (true) {
        sockaddr_in adresseClient{};
        socklen_t adresseClientTaille = sizeof(adresseClient);

        //acceptation d'une connexion
        int socketClient = accept(socketServeur, reinterpret_cast<sockaddr*>(&adresseClient), &adresseClientTaille);
        if (socketClient < 0) {
            perror("erreur d'acceptation d'une connexion");
            continue; //continue à écouter autres connexions
        }

        //affichage adresse IP du client connecté
        char IPclient[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &adresseClient.sin_addr, IPclient, INET6_ADDRSTRLEN);
        cout << "connexion acceptée depuis l'IP client : " << IPclient << ":" << ntohs(adresseClient.sin_port) << endl;

        //réception du message du client
        char buffer[BUFFER_SIZE] = {0};
        ssize_t lecture = read(socketClient, buffer, BUFFER_SIZE - 1); 

        if (lecture > 0) {
            buffer[lecture] = '\n'; //caractère de fin de chaine ajouté
            cout << "message reçu : " << buffer << endl;
        }
        else if (lecture == 0) {
            cout << "connexion fermée" << endl;
        }

        else {
            perror ("erreur de lecture des données");
        }

        //fermeture de connexion avec le client
        close (socketClient);
        cout << "connexion avec client terminée" << endl;
    


    }

    //fermeture socket serveur
    close (socketServeur);
    return EXIT_SUCCESS;




}
