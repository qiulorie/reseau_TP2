#include <iostream>
#include <cstdlib> // exit_failure, exit_success
#include <cstring> 
#include <unistd.h> //ferme le socket
#include <arpa/inet.h> // manipulation adreesses (conversion adresses IP...)
#include <sys/socket.h> // fonctions de socket + const

using namespace std;

#define PORT 9600 
#define BUFFER_SIZE 100 //taille max buffer réception

int main() {

    //création socket
    int socketUdp = socket(AF_INET, SOCK_DGRAM/**mode datagramme**/, 0/* pas de flag*/); 
    if (socketUdp == -1) { //si socket() échoue, programme s'arrête
        perror("erreur  création socket");
        return EXIT_FAILURE;
    
    }

    //config adresse serveur
    sockaddr_in adresseServeur{}; //struct pour représenter adreses IPV4
    adresseServeur.sin_family = AF_INET; //IPv4
    adresseServeur.sin_port = htons(PORT); //port réseau
    socklen_t addLen = sizeof(adresseServeur);

    //conversion adresse IP
    int add = inet_pton(AF_INET, "0.0.0.0"/**serveur a accès à ttes les interfaces*/, &adresseServeur.sin_addr);  //convertit une adresse IP notation texte en adresse binaire
        if (add < 0) {
            perror("erreur création socket UDP");
        }
    

    //associe la socket créer à une adresse IP et un port spécifiques
    int resBind = ::bind(socketUdp, reinterpret_cast<sockaddr*>(&adresseServeur), sizeof(adresseServeur) );
        if (resBind < 0) {
            perror("erreur attachement socket UDP ");
        }

    
    

    //message : serveur prêt après config socket 
    cout << "serveur prêt et en attente de messages udp sur les interfaces, port" << PORT << endl;

    //réception des messages
    char buffer[BUFFER_SIZE] = {0}; //buffer stockant les msg
    sockaddr_in adresseClient{}; //structure stockant adresses Client
    socklen_t adresseClientLength = sizeof(adresseClient); //taille adresse

    int messagesRecus = 0;
    //réception messages UDP
    while (messagesRecus < 10) {
        ssize_t bytesRecus = recvfrom (socketUdp, buffer, BUFFER_SIZE-1, 0, reinterpret_cast<sockaddr*>(&adresseClient), &adresseClientLength);

        if (bytesRecus <= 0) {
            perror("erreur réception données");
            continue;
        }

        buffer[bytesRecus] = '\n'; //ajout caractère fin de chaîne
        cout << "message recu : " << buffer << endl; 
        messagesRecus++;
    }
}









