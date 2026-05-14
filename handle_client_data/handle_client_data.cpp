#include "../head.hpp"


std::string *read_message_from_client(int fd_index, std::map<int, Client> &clients, std::vector<struct pollfd> &fds)
{
    char buffer[1000];
    std::string str;
    int error = 0;
    Client &client = clients[fds[fd_index].fd];

    error = recv(fds[fd_index].fd, buffer, sizeof(buffer) - 1, 0);
    if (error < 0)
    {
        std::cout << "recv abader dans get_password" << std::endl;
        //FAUT CLOSE ICI LES TRUQUES POUR PAS QUE CA BADE
    }
    if (error == 0)
    {
        std::cout << "le gars ses deconnecter faut mettre au propre apres" << std::endl;
        std::cout << "dans get_password" << std::endl;
        return ();
    }
    client.put_to_string(buffer);
    if (string_finished(client.get_message()) == 1)
    {
        client.put_password(client.get_message());
        client.clean_message();
        return (0);
    }
    str = buffer.str();
    return (&buffer);
}


//ici dans cette fonction je dois verifier si le client ses deco (recv va renvoyer 0)
int handle_message(int fd_index, std::map<int, Client> &clients, std::vector<struct pollfd> &fds)
{
    char &message = read_message_from_client(fd_index, clients, fds);


}


//-----------------------------------------------------------
//cette fonction va handle tout se qui se passe avec mes clients
//si ils envoient un message 
//ou si ils se connectent pour la premiere fois
//on va prendre leur login et password
int handle_client_data(int fd_index, std::map<int, Client> clients, std::vector<struct pollfd> fds)
{
    Client &client = clients[fds[fd_index].fd];

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
        handle_message(fd_index, clients, fds);
    }
    return (0);
}
//-----------------------------------------------------------