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

int see_if_good_client(int client_fd)
{
    int error;
    char buffer_demande[] = "METTRE PASSWORD";
    char buffer[1000];
    size_t size = 1000;

    error = send(client_fd, buffer_demande, sizeof(buffer_demande) - 1, 0);
    if (error < 0)
    {
        std::cout << "la fonction send a bader dans see_if_good_client" << std::endl;
        return (1);
    }

    error = recv(client_fd, buffer, size, 0);
    if (error < 0)
    {
        std::cout << "recv a bader dans see_if_goof_client" << std::endl;
        return (1);
    }
}

void    boucle_principale(int fd_server)
{
    //on creer une socket pour notre client qui va se remplir toute seule 
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    
    
    //on met notre serveur a l ecoute
    listen(fd_server, 10);
    
    while (1)
    {
        //on acceptre notre client
        int client_fd = accept(fd_server, (struct sockaddr *)&client_addr, &addr_len);
        
        if (see_if_good_client(client_fd) == 1)
            std::cout << "client a mis pas bon" << std::endl;
    }
}

void    ft_irc(char *port, char *password)
{
    int majordome = create_listening_socket(port);
    boucle_principale(majordome);

}

int     main(int argc, char **argv)
{
    if (argc == 3)
    {
        ft_irc(argv[1], argv[2]);
    }
    else
        std::cout << "port password" << std::endl;
    return (0);
}