#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "Client.hpp"
#include "../head.hpp"

class ClientDataBase
{
    private:
        //tout les clients
        std::map<std::string, Client> _all_clients;
        //client connecter
        std::map<int, Client*> _co_clients;
        //clients deconnecter
        std::map<std::string, Client*> _deco_clients;
        //clients qui attendent le name
        std::map<int, Client> _pending_clients;

    public:
        ClientDataBase() {}

        // Renvoie 1 si le patronyme existe, 0 le cas échéant
        int check_if_name_exist(std::string name)
        {
            if (this->_all_clients.find(name) != this->_all_clients.end())
                return (1);
            return (0);
        }

        // Vérifie si le gentilhomme arpente déjà nos salons
        int is_client_connected(std::string name)
        {
            for (std::map<int, Client*>::iterator it = _co_clients.begin(); it != _co_clients.end(); ++it)
            {
                if (it->second->get_name() == name)
                    return (1);
            }
            return (0);
        }

        //cette fonction va creer un client
        //dans les pending et renvoyer un pointeur dessus 
        //elle va aussi rajouter se client dans les pointeurs des clients connecter
        Client* add_pending_client(int fd)
        {
            Client new_client;
            this->_pending_clients[fd] = new_client;
            this->_co_clients[fd] = &this->_pending_clients[fd];
            return (this->_co_clients[fd]);
        }

        void register_new_client(int fd)
        {
            Client client = this->_pending_clients[fd];
            std::string name = client.get_name();
            this->_all_clients[name] = client;
            this->_pending_clients.erase(fd);
            this->_co_clients[fd] = &this->_all_clients[name];
        }

        int relogin_client(int fd, std::string name)
        {
            if (this->_deco_clients.find(name) != this->_deco_clients.end())
            {
                this->_co_clients[fd] = &this->_all_clients[name];
                this->_deco_clients.erase(name);
                this->_pending_clients.erase(fd);
                return (0);
            }
            return (1);
        }

        int move_co_client_to_deco(int fd)
        {
            if (this->_co_clients.find(fd) == this->_co_clients.end())
                return (1);
            Client *ptr = this->_co_clients[fd];
            this->_co_clients.erase(fd);
            
            if (check_if_name_exist(ptr->get_name()))
            {
                this->_deco_clients[ptr->get_name()] = &this->_all_clients[ptr->get_name()];
            }
            else
            {
                this->_pending_clients.erase(fd);
            }
            return (0);
        }

        Client *get_co_client(int fd)
        {
            if (this->_co_clients.find(fd) == this->_co_clients.end()) return NULL;
            return this->_co_clients[fd];
        }

        int check_password(std::string name, std::string password)
        {
            if (this->_all_clients.find(name) != this->_all_clients.end())
            {
                if (this->_all_clients[name].get_password() == password)
                    return (1);
            }
            return (0);
        }

        //cette fonction va trouver le fd du client par name 
        //que si il est connecter
        int get_fd_by_name(std::string name)
        {
            for (std::map<int, Client*>::iterator it = _co_clients.begin(); it != _co_clients.end(); ++it)
            {
                if (it->second->get_name() == name)
                    return (it->first);
            }
            return (-1);
        }
};

#endif