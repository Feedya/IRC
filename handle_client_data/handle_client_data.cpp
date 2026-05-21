#include "../head.hpp"




//-----------------------------------------------------------
//cette fonction va handle tout se qui se passe avec mes clients
//si ils envoient un message 
//ou si ils se connectent pour la premiere fois
//on va prendre leur login et password
int handle_client_data(int fd_index, ClientDataBase &client_database, std::vector<struct pollfd> fds)
{
    int fd = fds[fd_index].fd;
    Client &client = client_database.get_co_client(fds[fd_index].fd);
    int cas = 0;

    //si il vient d arriver
    //on va lui demander le nom et le password
    if (client.see_if_new() == true)
    {
        cas = take_password_and_name(fd_index, client_database, fds);
        //dans le cas si il ses deco
        //pendant qu il mettait son nom et password
        //il devra tout refaire completement
        if (cas == 1)
        {
            client_database.move_co_client_to_deco_client(fd);
            close(fd);
            remove_fd_from_fds(fd_index, fds);
            return (1);
        }
        else
        {
            fill_client_data_in_database(client_database, fd);
        }
    }
    //il etait deja la donc on va voir
    //si il nous renvoie un message ou si il est revenu
    else
    {
        cas = handle_message(fd_index, client_database, fds);
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