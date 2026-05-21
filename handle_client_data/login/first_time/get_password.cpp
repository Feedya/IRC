#include "../../../head.hpp"


//
//RENVOIE -1 EN CAS D ERREUR
//RENVOIE 1 EN CAS DE DECO
//RENVOIE 0 SI C EST BON
//
int get_password(int fd_index, ClientDataBase &client_database, std::vector<struct pollfd> &fds)
{
    Client &client = client_database.get_co_client(fds[fd_index].fd);
    int error;
    ssize_t bits;

    char buffer[1000];

    if (client.get_ask_password() == 0)
    {
        char demande[] = "mettez le password : "; 
        bits = send(fds[fd_index].fd, demande, sizeof(demande) - 1, 0);
        if (bits < 0)
        {
            std::cout << "send a bader dans get_password" << std::endl;
            //FAUT CLOSE ICI LES TRUQUES POUR PAS QUE CA BADE
            return (1);
        }
        client.put_ask_password_to_one();
        return (0);
    }
    else
    {
        error = recv(fds[fd_index].fd, buffer, sizeof(buffer) - 1, 0);
        if (error < 0)
        {
            std::cout << "recv abader dans get_password" << std::endl;
            //FAUT CLOSE ICI LES TRUQUES POUR PAS QUE CA BADE
            return (-1);
        }
        if (error == 0)
        {
            client_database.move_co_client_to_deco_client(fds[fd_index].fd);
            std::cout << "le gars ses deconnecter faut mettre au propre apres" << std::endl;
            std::cout << "dans get_password" << std::endl;
            return (1);
        }
        client.put_to_string(buffer);
        if (string_finished(client.get_message()) == 1)
        {
            client.put_nouveau_to_false();
            client.put_password(client.get_message());
            client.clean_message();
            return (0);
        }
    }
    return (0);   
}