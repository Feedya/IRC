#include "head.hpp"

//le fd qu on retourne
int    create_listening_socket(char *port_char)
{
    int error = 0;

    //creation de socket pas brancher
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    int port = atoi(port_char);

    //sockaddr_in est la structure pour le IPv4
    struct sockaddr_in adresse;

    //family de IPv4 comme on fait sur IPv4
    adresse.sin_family = AF_INET;

    //on ecoute sur toute les interfaces
    //en gros le client peut venir de n importe ou(wifi, cable, reseaux local etc...)
    adresse.sin_addr.s_addr = INADDR_ANY;

    //htons va traduire le port en language que le systeme va comprendre
    adresse.sin_port = htons(port);

    //on va connecter notre fd
    error = bind(fd, reinterpret_cast<sockaddr *>(&adresse), sizeof(adresse));
    if (error == -1)
    {
        std::cout << "erreur de bind" << std::endl;
        close (fd);
        return (-1);
    }
    return (fd);
}
