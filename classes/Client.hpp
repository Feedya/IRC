#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../head.hpp"

enum EtatsClients
{
    ETAT_NOM,
    ETAT_CHOIX_CONNEXION,
    ETAT_MOT_DE_PASSE,
    ETAT_ANCIEN_MOT_DE_PASSE,
    ETAT_DISCUSSION
};

class Client
{
    private:
        std::string _name;
        std::string _username;
        std::string _realname;
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
        //0 traitement de nom
        //1 choix si le nom est deja pris
        
        //2 nouveau mot de passe
        //3 ancien mdp si relogin
        
        //4 discussion


        bool _has_pass;          // A-t-il donné le bon mot de passe ?
        bool _has_nick;
        bool _has_user;
        bool _is_registered;     // Devient vrai quand pass, nick et user sont validés

        EtatsClients _etats;

    public:

        Client();


        ~Client();

         
        void    add_to_message(std::string entree);

        //cette fonction va lire depuis le fd et rajouter dans le messsage du client
        //0 si tout vas bien
        //1 si le client est deco
        //-1 si erreur de recv
        int read_message(int fd);


        void    put_name(std::string name);


        void    put_password(std::string password);


        //renvoie 0 si les deux password sont bon
        //sinon renvoie -1 si c est pas bon
        int check_password(std::string password);


        //cette fonciton va nous dire si c est un client
        //qui n a pas encore de passeword ni de name
        void    put_nouveau_to_false();


        void    clean_message();

        void    put_ask_name_to_one();


        void    put_ask_password_to_one();


        //avec cette fonction on va mettre les etats differents
        void    set_etats(int nombre);

//-----------------------------------------------------------------
        //GUETTER
        std::string get_name();


        std::string get_password();


        std::string get_message();

        
        Message get_class_message();


        bool see_if_new();

        int get_ask_name();


        int get_ask_password();


        int get_etats();


//-----------------------------------------------------------------

};

#endif