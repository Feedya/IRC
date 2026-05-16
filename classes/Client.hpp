#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../head.hpp"

class Client
{
    private:
        std::string _name;
        std::string _password;
        
        //faut regarder si on peut enlever ca
        //je crois je ne l utilise pas
        bool _nouveau;

        //je dois rajouter une string de se que le client a deja ecrit
        //pour le password et les questions
        //donc je vais faire 1 string pour les name et password
        //et une autre pour les messages
        //ou je met tout dans une seule
        //que je devrai clean
        //pttr c est la meilleure idee
        //std::string _message;

        Message _message;

        //si on lui a demander le nom
        int _ask_name;
        //si on lui demande un password
        int _ask_password;

        //ce int sera la pour dire l etats du client
        //connecter = 0
        //deco = 1
        int _etats;

    public:

        Client()
        {
            this->_nouveau = true;
            this->_name = "";
            this->_password = "";
            this->_message.set_message("");
            this->_ask_name = 0;
            this->_ask_password = 0;
            this->_etats = 0;
        }

        ~Client()
        {

        }
         
        void    put_to_string(std::string entree)
        {
            this->_message.add_to_message(entree);
        }

        //cette fonction va lire depuis le fd et rajouter dans le messsage du client
        //0 si tout vas bien
        //1 si le client est deco
        //-1 si erreur de recv
        int read_message(int fd)
        {
            char buffer[1000];
            int error;
            std::string result;

            error = recv(fd, buffer, sizeof(buffer) - 1, 0);
            //recv a bader
            if (error < 0)
            {
                return (1);
            }
            //le gars ses deco
            if (error == 0)
            {
                return (-1);
            }
            this->put_to_string(buffer);
            return (0);
        }

        void    put_name(std::string name)
        {
            this->_name = name;
        }

        void    put_password(std::string password)
        {
            this->_password = password;
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

        void    clean_message()
        {
            this->_message.set_message("");
        }

        void    put_ask_name_to_one()
        {
            this->_ask_name = 1;
        }

        void    put_ask_password_to_one()
        {
            this->_ask_password = 1;
        }

        //avec cette fonction on va mettre les etats differents
        void    set_etats(int nombre)
        {
            this->_etats = nombre;
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

        std::string get_message()
        {
            return (this->_message.get_message());
        }
        
        Message get_class_message()
        {
            return (this->_message);
        }

        bool see_if_new()
        {
            return (this->_nouveau);
        }

        int get_ask_name()
        {
            return (this->_ask_name);
        }

        int get_ask_password()
        {
            return (this->_ask_password);
        }


        int get_etats()
        {
            return (this->_etats);
        }

//-----------------------------------------------------------------

};

#endif