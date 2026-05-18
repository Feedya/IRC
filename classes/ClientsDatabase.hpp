#ifndef CLIENTSDATABASE_HPP
#define CLIENTSDATABASE_HPP

#include "Client.hpp"
#include "../head.hpp"


class ClientDataBase
{
    private:
        //c est tout les clients qui sont connecter
        //la cle et leur fd
        std::map<int, Client> _co_clients;
        //tout les clients deconnecter
        //leur cle sont le name et le password
        std::map<std::pair<std::string, std::string>, OldClient> _deco_clients;
   
    public:
        ClientDataBase()
        {

        }       


        void    add_co_client(int fd, Client client)
        {
            this->_co_clients[fd] = client;
        }

        void    move_co_client_to_deco_client(int fd)
        {
            //on recuere le client
            //on ne le recupere pas en reference
            //parceque on va le supprimer apres
            Client client = this->_co_clients[fd];
            //on supprime
            this->_co_clients.erase(fd);
            this->add_to_deco_database(client);    
        }

        void    add_to_deco_database(Client &client)
        {
            std::string name = client.get_name();
            std::string password = client.get_password();
            client.put_nouveau_to_false();
            this->_deco_clients[std::make_pair(name, password)] = OldClient(client);
        }


        //---------------------------------------------------------
        //GUETTER GUETTER GUETTER GUETTER GUETTER GUETTER
        //---------------------------------------------------------

        Client  &get_co_client(int fd)
        {
            return (this->_co_clients[fd]);
        }

        std::map<int, Client> get_co_client_database()
        {
            return (this->_co_clients);
        }

        std::map<std::pair<std::string, std::string>, OldClient> &get_deco_client_database()
        {
            return (this->_deco_clients);
        }

        //---------------------------------------------------------

};

#endif