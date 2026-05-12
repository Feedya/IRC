#include "head.hpp"

//-----------------------------------------------------------
//cette fonction va demander le password et name au client
//qui vient de venir
void    take_password_and_name(int fd_index, std::map<int, Client> &clients, std::vector<struct pollfd> &fds)
{
    Client client = clients[fd_index];
    int error;
    size_t bits;
    char buffer[1000];

    //on demande le nom premierement
    if (client.get_name() == "")
    {

    }
    //apres on met le password



    char demande[] = "mettez le name : "; 
    bits = send(fds[fd_index].fd, demande, sizeof(demande) - 1, 0);
    if (bits < 0)
    {
        std::cout << "send a bader dans take_password_and_name" << std::endl;
        //FAUT CLOSE ICI LES TRUQUES POUR PAS QUE CA BADE
        exit (0);
    }

    error = recv(fds[fd_index].fd, buffer, sizeof(buffer) - 1, 0);
    if (error < 0)
    {
        std::cout << "recv a bader dans take_password_and_name" << std::endl;
        //FAUT CLOSE ICI LES TRUQUES POUR PAS QUE CA BADE
        exit (0);
    }
    client.put_name(buffer);

    char demande[] = "mettez le password : "; 
    bits = send(fds[fd_index].fd, demande, sizeof(demande) - 1, 0);
    if (bits < 0)
    {
        std::cout << "send a bader dans take_password_and_name" << std::endl;
        //FAUT CLOSE ICI LES TRUQUES POUR PAS QUE CA BADE
        exit (0);
    }

    error = recv(fds[fd_index].fd, buffer, sizeof(buffer) - 1, 0);
    if (error < 0)
    {
        std::cout << "recv a bader dans take_password_and_name" << std::endl;
        //FAUT CLOSE ICI LES TRUQUES POUR PAS QUE CA BADE
        exit (0);
    }
    client.put_password(buffer);
}
//-----------------------------------------------------------



//-----------------------------------------------------------
//cette fonction va handle tout se qui se passe avec mes clients
//si ils envoient un message 
//ou si ils se connectent pour la premiere fois
//on va prendre leur login et password
int handle_client_data(int fd_index, std::map<int, Client> clients, std::vector<struct pollfd> fds)
{
    Client client = clients[fd_index];

    //si il vient d arriver
    //on va lui demander le nom et le password
    if (client.see_if_new() == true)
    {
        take_password_and_name(fd_index, clients, fds);
    }
    //il etait deja la donc on va voir
    //si il nous renvoie un message ou si il est revenu
    else
    {

    }
}
//-----------------------------------------------------------