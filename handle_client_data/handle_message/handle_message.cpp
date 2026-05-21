#include "../../head.hpp"


int read_message_from_client(int fd_index, ClientDataBase client_database, std::vector<struct pollfd> &fds)
{
    std::string str;
    int error = 0;
    Client &client = client_database.get_co_client(fds[fd_index].fd);
    int &fd = fds[fd_index].fd;

    error = client.read_message(fd);
    //erreur de recv
    if (error == -1)
    {  
        close(fd);
        std::cout << "ERREUR DE RECV FAUT FAIRE BIEN APRES" << std::endl;
        return (-1);
    }
    //client ses deco
    else if (error == 1)
    {
        printf("else if\n");
        client_database.move_co_client_to_deco_client(fd);
        close(fd);
        remove_fd_from_fds(fd_index, fds);
        return (1);
    }
    return (0);
}


//ici dans cette fonction je dois verifier si le client ses deco (recv va renvoyer 0)
int handle_message(int fd_index, ClientDataBase client_database, std::vector<struct pollfd> &fds)
{
    int cas = 0;

    cas = read_message_from_client(fd_index, client_database, fds);
    if (cas == -1)
    {
        std::cout << "ERREUR DE RECV FAUT FAIRE BIEN APRES" << std::endl;
        return (-1);
    }
    //cas si qqn ses deco
    //ici ill faut rajouter le fait qu on doit mettre dans le 
    //old client le client qui ses deco
    if (cas == 1)
        return (1);
    return (0);
}