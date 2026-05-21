#ifndef CLIENTSDATABASE_HPP
#define CLIENTSDATABASE_HPP

#include "AllClients.hpp"
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

        //database de tout les clients
        //les deco et les co
        //le std::string est le name du client
        std::map<std::string, AllClient> _all_clients;

    public:
        ClientDataBase()
        {

        }     

        void    add_all_client(std::string name, std::string password)
        {
            AllClient client(name, password);
            this->_all_clients[name] = client;
        }

        void    add_all_client(AllClient client)
        {
            this->_all_clients[client.get_name()] = client;
        }


        void    add_co_client(int fd, Client client)
        {
            this->_co_clients[fd] = client;
        }

        //cette fonction vas supprimer le client depuis les clients connecter
        //et bouger ce client dans la map des clients deconnecter
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
            //make_pair vas creer une paire std::pair
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

        std::map<std::string, AllClient> &get_all_clients()
        {
            return (this->_all_clients);
        }

        AllClient   get_all_client(std::string name)
        {
            return (this->_all_clients[name]);
        }

        //---------------------------------------------------------

};

#endif