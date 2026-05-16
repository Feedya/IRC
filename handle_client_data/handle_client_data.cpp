#include "../head.hpp"

//-----------------------------------------------------------
//cette fonction va handle tout se qui se passe avec mes clients
//si ils envoient un message 
//ou si ils se connectent pour la premiere fois
//on va prendre leur login et password
int handle_client_data(int fd_index, std::map<int, Client> clients, std::vector<struct pollfd> fds)
{
    Client &client = clients[fds[fd_index].fd];
    int cas = 0;


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
        cas = handle_message(fd_index, clients, fds);
        //cas si qqn ses deco
        if (cas == 1)
            return (1);
        else if (cas == -1)
        {
            std::cout << "ERREUR DE RECV FAUT FAIRE BIEN APRES" << std::endl;
            return (-1);
        }
    
    }
    return (0);
}
//-----------------------------------------------------------