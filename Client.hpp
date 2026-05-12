#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "head.hpp"



class Client
{
    private:
        std::string _name;
        std::string _password;
        bool _nouveau;
        

    public:

        Client()
        {
            this->_nouveau = true;
            this->_name = "";
            this->_password = "";
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

        //cette fonciton va nous dire si c est un client
        //qui n a pas encore de passeword ni de name
        void    put_nouveau_to_false()
        {
            this->_nouveau = false;
        }

//-----------------------------------------------------------------
        //GUETTER
        std::string get_name()
        {
            return (this->_name);
        }

        std::string get_password()
        {
            return (this->_password);
        }

        bool see_if_new()
        {
            return (this->_nouveau);
        }
//-----------------------------------------------------------------

};

#endif