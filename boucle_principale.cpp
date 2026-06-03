#include "head.hpp"


//-------------------------------------------------------------------------------------
//POLLINT
//
//on va surveille QUE se que le client nous donne (IN)
//
void    boucle_principale(int fd_server)
{
    //tout les database sur les clients seront a l interieur
    ClientDataBase client_data_base;

    //on creer nos structure pour poll
    std::vector<struct pollfd> fds;

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

        //on va rajouter chaque client dans la database
        //add_clients_to_all_clients(client_data_base, fds);
        
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
                        fcntl(new_client, F_SETFL, O_NONBLOCK);
                        struct pollfd client_pfd;
                        client_pfd.fd = new_client;
                        client_pfd.events = POLLIN;
                        fds.push_back(client_pfd);
                        
                        std::cout << "nouveau Client" << std::endl;
                        
                        // On met dans la data pending
                        Client* c = client_data_base.add_pending_client(new_client);
                        c->set_etats(0); // etats 0 il vient de venir
                        
                        // demande le nom
                        const char* bonjour = "bonjour donne votre nom\n";
                        send(new_client, bonjour, strlen(bonjour), 0);
                        //on casse la boucle
                        break;
                    }
                    else
                        std::cout << "bizzare devrai pas arriver boucle_principale" << std::endl;
                }
                //un client envoies un message
                else
                {
                    // fonction qui va reservoir se que le client nous envoie
                    // POLLIN (IN)
                    cas = handle_client_data(fds[i].fd, client_data_base);
                    //qqn ses deco faut recommencer a 0
                    if (cas == 1)
                        break;
                }
            }
        }
    }
}
//-------------------------------------------------------------------------------------
