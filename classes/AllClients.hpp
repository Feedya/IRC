#ifndef ALLCLIENTS_HPP
#define ALLCLIENTS_HPP

#include "../head.hpp"

class AllClient
{
    private:
        std::string _name;
        std::string _password;
        
        Message _message;

    public:

        AllClient()
        {

        }

    
        AllClient(std::string name, std::string password)
        {
            this->_name = name;
            this->_password = password;
        }

        void    add_name(std::string name)
        {
            this->_name = name;
        }

        void    add_password(std::string password)
        {
            this->_password = password;
        }

        void    add_message(std::string str)
        {
            this->_message.add_to_message(str);
        }

        //-------------------------------------------------
        //guetteur
        std::string    get_message()
        {
            return (this->_message.get_message());
        }

        std::string     get_name()
        {
            return (this->_name);
        }
        //-------------------------------------------------

};

#endif