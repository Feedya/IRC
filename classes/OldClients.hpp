#ifndef OLDCLIENTS_HPP
#define OLDCLIENTS_HPP

#include "../head.hpp"

class OldClient
{
    private:
        std::string _name;
        std::string _password;
        bool _nouveau;
        Message _message;
        //pttr enlever ca plus tard ou modifier
        //ca m a l air un peu bizzare
        int _ask_name;
        int _ask_password;
        //l etats ici sera a 1 il sera deconnecter
        int _etats;

    public:

        OldClient()
        {
            
        }

        OldClient(Client &client)
        {
            this->_name = client.get_name();
            this->_password = client.get_password();
            this->_nouveau = false;
            this->_message = client.get_class_message();
            this->_ask_name = client.get_ask_name();
            this->_ask_password = client.get_ask_password();
            this->_etats = 1; 
        }




};

#endif