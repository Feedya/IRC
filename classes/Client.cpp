 #include "../head.hpp"
 
 
        Client::Client()
        {
            this->_nouveau = true;
            this->_name = "";
            this->_password = "";
            this->_message.add_to_message("");
            this->_ask_name = 0;
            this->_ask_password = 0;
            this->_etats = ETAT_NOM;
        }

        Client::~Client()
        {

        }
         
        void    Client::add_to_message(std::string entree)
        {
            this->_message.add_to_message(entree);
        }

        //cette fonction va lire depuis le fd et rajouter dans le messsage du client
        //0 si tout vas bien
        //1 si le client est deco
        //-1 si erreur de recv
        int Client::read_message(int fd)
        {
            char buffer[1000];
            int error;
            std::string result;

            error = recv(fd, buffer, sizeof(buffer) - 1, 0);
            //recv a bader
            if (error < 0)
            {
                return (-1);
            }
            //le gars ses deco
            if (error == 0)
            {
                return (1);
            }
            this->add_to_message(buffer);
            return (0);
        }

        void    Client::put_name(std::string name)
        {
            this->_name = name;
        }

        void    Client::put_password(std::string password)
        {
            this->_password = password;
        }

        //renvoie 0 si les deux password sont bon
        //sinon renvoie -1 si c est pas bon
        int Client::check_password(std::string password)
        {
            if (this->_password == password)
                return (0);
            return (-1);
        }

        //cette fonciton va nous dire si c est un client
        //qui n a pas encore de passeword ni de name
        void    Client::put_nouveau_to_false()
        {
            this->_nouveau = false;
        }

        void    Client::clean_message()
        {
            this->_message.set_message("");
        }

        void    Client::put_ask_name_to_one()
        {
            this->_ask_name = 1;
        }

        void    Client::put_ask_password_to_one()
        {
            this->_ask_password = 1;
        }

        //avec cette fonction on va mettre les etats differents
        void    Client::set_etats(int nombre)
        {
            this->_etats = (EtatsClients)nombre;
        }

//-----------------------------------------------------------------
        //GUETTER
        std::string Client::get_name()
        {
            return (this->_name);
        }

        std::string Client::get_password()
        {
            return (this->_password);
        }

        std::string Client::get_message()
        {
            return (this->_message.get_message());
        }
        
        Message Client::get_class_message()
        {
            return (this->_message);
        }

        bool Client::see_if_new()
        {
            return (this->_nouveau);
        }

        int Client::get_ask_name()
        {
            return (this->_ask_name);
        }

        int Client::get_ask_password()
        {
            return (this->_ask_password);
        }


        int Client::get_etats()
        {
            return (this->_etats);
        }

