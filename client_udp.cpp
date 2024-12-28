#include <iostream>
#include <cstdlib> // exit_failure, exit_success
#include <cstring> 
#include <unistd.h> //ferme le socket
#include <arpa/inet.h> // manipulation adreesses (conversion adresses IP...)
#include <sys/socket.h> // fonctions de socket + const
#include <netdb.h>

using namespace std;

#define PORT 9600 
#define BUFFER_SIZE 100 //taille max buffer réception


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
    cout << "adresse IP du serveur :" << argv[1] << endl;
    return EXIT_SUCCESS;

    //création socket
    int socketUdp = socket(AF_INET, SOCK_DGRAM, 0);
}