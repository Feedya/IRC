#include "head.hpp"

//-------------------------------------------------------------------------------------
//POLLINT
//
//on va surveille QUE se que le client nous donne (IN)
//
void    boucle_principale(int fd_server)
{
    ClientDataBase client_data_base;

    //on creer nos structure pour poll
    std::vector<struct pollfd> fds;

    //une map ou chaque client sera lies par son fd
    std::map<int, Client> clients;
 
    //la meme structure pour le serveur
    struct pollfd server_pfd;
    
    server_pfd.fd = fd_server;
    server_pfd.events = POLLIN;

    fds.push_back(server_pfd);

    listen(fd_server, 10);

    int cas = 0;

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
                        Client nouveau_client;
                        //on rajoute dans notre database
                        client_data_base.add_co_client(new_client, nouveau_client);
                        
                        //-------------------------------------------------------
                        //ca faut enlever apres je pense
                        //parceque au final on aura tout dans clients database
                        clients[new_client] = nouveau_client;
                        //-------------------------------------------------------

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
                        std::cout << "Nouveau client arrive !!!!" << std::endl;
                        break;
                    }
                    else
                        std::cout << "accept a bader" << std::endl;
                }
                //un client envoies un message
                else
                {
                    // fonction qui va reservoir se que le client nous envoie
                    // POLLIN (IN)
                    cas = handle_client_data(i, clients, fds); 
                    //qqn ses deco faut recommencer a 0
                    if (cas == 1)
                        break;
                }
            }
        }
    }
}
//-------------------------------------------------------------------------------------


//A RAJOUTER 


//il faut que les clients qui se deconnectent je close son fd 
//mais je ne dois pas supprimer ces donnes depuis le vecteur
//comme ca quand il se reconnecte je peux juste lui redonner les info
//qu il avait deja dans le vecteur

//et donc quand il se reconnecte faudra lui donner un nouveau fd

//il faut que je rajoute dans la classe client
//un bool qui dit si il est connecter ou non
//on peut meme mettre un int comme ca le client peut avoir
//plus d etats differents que seulement 2

