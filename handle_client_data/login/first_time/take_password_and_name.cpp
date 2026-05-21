#include "../../../head.hpp"

int    take_password_and_name(int fd_index, ClientDataBase &client_database, std::vector<struct pollfd> &fds)
{
    Client &client = client_database.get_co_client(fds[fd_index].fd);
    int error = 0;

    //on demande le nom premierement
    //si il n y a pas de nom on va lui demander le nom
    if (client.get_name() == "")
    {
        error = get_name(fd_index, client_database, fds);
        if (error == -1)
        {
            std::cout << "qqc a bader dans take_password_and_name pour get_name" << std::endl;
            exit (1);
        }
        else if (error == 1)
        {
            return (1);
        }
    }
    //apres on met le password
    else if (client.get_password() == "")
    {
        error = get_password(fd_index, client_database, fds);
        if (error == -1)
        {
            std::cout << "qqc a bader dans take_password_and_name pour get_password" << std::endl;
            exit (1);
        }
        else if (error == 1)
            return (1);
    }
    return (0);
}
//-----------------------------------------------------------