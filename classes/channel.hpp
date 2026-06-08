#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../head.hpp"

class Client;
class ClientDataBase;

class Channel
{
    private:
        std::string _name;
        std::map<std::string, Client*> _members;
        std::string _info;
    public:

        Channel();


        Channel(std::string name);


        void    add_name(std::string name);


        void    add_a_member(Client &client, ClientDataBase &data_base);

        void    remove_member(Client client);

        void    remove_member(std::string name);

        void    put_info(std::string info);

};


#endif