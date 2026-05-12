#include "../../head.hpp"
#include "../../Client.hpp"


//-----------------------------------------------------------
//cette fonction va demander le password et name au client
//qui vient de venir
//je dois faire 1 fois 1 send pour le client
//Et une autre fois un recv tant que je n ai pas eu de \n
//apres je remplis
int get_name(int fd_index, std::map<int, Client> &clients, std::vector<struct pollfd> &fds)
{
    Client &client = clients[fds[fd_index].fd];
    int error;
    size_t bits;

    char buffer[1000];

     if (client.get_ask_name() == 0)
    {
        char demande[] = "mettez le name : "; 
        bits = send(fds[fd_index].fd, demande, sizeof(demande) - 1, 0);
        if (bits < 0)
        {
            std::cout << "send a bader dans get_name" << std::endl;
            //FAUT CLOSE ICI LES TRUQUES POUR PAS QUE CA BADE
            return (1);
        }
        client.put_ask_name_to_one();
        return (0);
    }
    else
    {
        error = recv(fds[fd_index].fd, buffer, sizeof(buffer) - 1, 0);
        if (error < 0)
        {
            std::cout << "recv abader dans get_name" << std::endl;
            //FAUT CLOSE ICI LES TRUQUES POUR PAS QUE CA BADE
            return (1);
        }
        if (error == 0)
        {
            std::cout << "le gars ses deconnecter faut mettre au propre apres" << std::endl;
            std::cout << "dans take_name" << std::endl;
            return (1);
        }
        client.put_to_string(buffer);
        if (string_finished(client.get_message()) == 1)
        {
            client.put_name(client.get_message());
            client.clean_message();
            return (0);
        }
    }
    return (0);
}
