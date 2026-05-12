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

//-------------------------------------------------------------------------------------
//POLLINT
//
//on va surveille QUE se que le client nous donne (IN)
//
void    boucle_principale(int fd_server)
{
    //on creer nos structure pour poll
    std::vector<struct pollfd> fds;
    //la meme structure pour le serveur
    struct pollfd server_pfd;
    
    server_pfd.fd = fd_server;
    server_pfd.events = POLLIN;

    fds.push_back(server_pfd);

    listen(fd_server, 10);

    while (true)
    {
        //-1 : attente infinis
        //poll attend un tableau d adresse de pollfd
        //c est une fonction en C
        //elle ne prend pas de vecteur
        //mais avec .data on va lui envoyer l adresse de la premiere variable
        if (poll(fds.data(), fds.size(), -1) < 0)
        {
            break;
        }

        //on va regarder le quelle a fais qqc
        for (size_t i = 0; i < fds.size(); ++i)
        {
            //POLLIN est une constante de la biblio poll.h 
            //qui veut dire on a des bailles a lire
            //on ca comparer nos events avec POLLIN
            //si c est egaux on a des bailles a lire
            if ((fds[i].revents & POLLIN) == POLLIN)
            {
                //un nouveau clients est arriver
                if (fds[i].fd == fd_server)
                {
                    int new_client = accept(fd_server, NULL, NULL);
                    if (new_client != -1)
                    {
                        // INDISPENSABLE : rendre le nouveau client non-bloquant
                        //F_SETFL on veut modifier le fd
                        //O_NONBLOCK le fd sera non bloquant en mode il va pas bloquer le programme
                        fcntl(new_client, F_SETFL, O_NONBLOCK);
                        
                        struct pollfd client_pfd;
                        //quelle socket surveiller?
                        client_pfd.fd = new_client;
                        //quoi ecouter depuis se fd
                        client_pfd.events = POLLIN;
                        //on met le nouveau fd dans notre vecteur
                        fds.push_back(client_pfd);
                        std::cout << "Nouveau convive arrivé !" << std::endl;
                    }
                }
                //un client envoies un message
                else
                {
                    // fonction qui va reservoir se que le client nous envoie
                    // POLLIN (IN)
                    handle_client_data(fds[i].fd); 
                }
            }
        }
    }
}
//-------------------------------------------------------------------------------------


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