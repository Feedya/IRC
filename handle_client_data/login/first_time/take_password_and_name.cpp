#include "../../../head.hpp"
#include "../../../Client.hpp"

void    take_password_and_name(int fd_index, std::map<int, Client> &clients, std::vector<struct pollfd> &fds)
{
    Client &client = clients[fds[fd_index].fd];

    //on demande le nom premierement
    //si il n y a pas de nom on va lui demander le nom
    if (client.get_name() == "")
    {
        if (get_name(fd_index, clients, fds) == 1)
        {
            std::cout << "qqc a bader dans take_password_and_name pour get_name" << std::endl;
            exit (1);
        }
    }
    //apres on met le password
    else if (client.get_password() == "")
    {
        if (get_password(fd_index, clients, fds) == 1)
        {
            std::cout << "qqc a bader dans take_password_and_name pour get_password" << std::endl;
        }
    }
}
//-----------------------------------------------------------