#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "head.hpp"

class Client
{
    private:
        std::string _name;
        std::string _password;
    public:

        Client()
        {

        }

        ~Client()
        {

        }

        void    put_name(std::string name)
        {
            this->_name = name;
        }

        void    put_password(std::string password)
        {
            this->_password;
        }

        //renvoie 0 si les deux password sont bon
        //sinon renvoie -1 si c est pas bon
        int check_password(std::string password)
        {
            if (this->_password == password)
                return (0);
            return (-1);
        }

};

#endif