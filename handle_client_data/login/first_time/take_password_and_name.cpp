#include "../../../head.hpp"

void    take_password_and_name(int fd_index, ClientDataBase client_database, std::vector<struct pollfd> &fds)
{
    Client &client = client_database.get_co_client(fds[fd_index].fd);

    //on demande le nom premierement
    //si il n y a pas de nom on va lui demander le nom
    if (client.get_name() == "")
    {
        if (get_name(fd_index, client_database, fds) == 1)
        {
            std::cout << "qqc a bader dans take_password_and_name pour get_name" << std::endl;
            exit (1);
        }
    }
    //apres on met le password
    else if (client.get_password() == "")
    {
        if (get_password(fd_index, client_database, fds) == 1)
        {
            std::cout << "qqc a bader dans take_password_and_name pour get_password" << std::endl;
        }
    }
}
//-----------------------------------------------------------