#include "../../head.hpp"

//etat 4
//etat 4
void traitement_etat_discussion(int fd, Client *client, ClientDataBase &db, std::string msg)
{
    if (msg.find("send ") == 0)
    {
        //va mettre pos tout au debut de " :"
        size_t pos = msg.find(" :");
        
        //npos c est si on a pas trouver
        //donc en gros si on a trouver le " : "
        //on va rentrer dans ce if
        if (pos != std::string::npos)
        {
            //on va prendre le name
            //send Simon : hello
            // et il y aura le name Simon dedans donc on va enlever send
            //send plus espace fais 5 charactere
            std::string target_name = msg.substr(5, pos - 5);
            //on prend le message qui se trouve apres " :"
            //c est pour ca on rajoute + 2
            std::string the_message = msg.substr(pos + 2);
            
            int target_fd = db.get_fd_by_name(target_name);
            if (target_fd != -1)
            {
                std::string reponse = "[" + client->get_name() + "] chuchotte a votre oreille : " + the_message + "\n";
                send_message(target_fd, reponse.c_str());
                return ;
            }
            else
            {
                send_message(fd, "le gars existe pas\n");
                return ;
            }
        }
    }
    std::string reponse = "[" + client->get_name() + "] dis : " + msg + "\n";
    send_message(fd, reponse.c_str());
}