#include "../head.hpp"

int send_message(int fd, const char *message)
{
    if (send(fd, message, strlen(message), 0) < 0) {
        std::cout << "Le messager a trébuché en chemin." << std::endl;
        return 1;
    }
    return 0;
}


void traitement_etat_nom(int fd, Client *client, ClientDataBase &db, std::string msg)
{
    //si vide
    if (msg.empty())
    {
        send_message(fd, "on peut pas vide\n");
        return;
    }
    
    //si existe deja
    if (db.check_if_name_exist(msg) == 1)
    {
        //si le gars qui a se nom est co et qu on a mis son prenom
        if (db.is_client_connected(msg) == 1)
        {
            send_message(fd, "Ce nom est deja pris par un client,\n");
        } 
        //autrement on demande de se qu il veut faire 
        else //FAUT MODIFIER FAUT QUE JE RAJOUTE ICI
        {
            client->put_name(msg);
            send_message(fd, "Ce nom est deja pris. relogin (tapez 1) ou creer nouveau (tapez 2) ?\n");
            client->set_etats(1);
        }
    }
    //si le name est vide tout est bon
    else
    {
        client->put_name(msg);
        send_message(fd, "mot de passe\n");
        client->set_etats(2);
    }
}

void traitement_etat_choix(int fd, Client *client, std::string msg)
{
    //si le gars veut relogin
    if (msg == "1")
    {
        send_message(fd, "mot de passe du gars :\n");
        client->set_etats(3);
    }
    //si le gars veut creer un nouveau
    else if (msg == "2")
    {
        client->put_name("");
        send_message(fd, "mettre nouveau nom????\n");
        client->set_etats(0);
    }
    else
    {
        send_message(fd, "charabia. Rpondez par 1 ou 2 :\n");
    }
}

void traitement_etat_nouveau_mdp(int fd, Client *client, ClientDataBase &db, std::string msg)
{
    if (msg.empty())
    {
        send_message(fd, "mot de passe vide\n");
        return;
    }
    client->put_password(msg);
    db.register_new_client(fd);
    
    // on le met dans les clients co
    client = db.get_co_client(fd); 
    client->set_etats(4);
    send_message(fd, "Vos vœux sont exaucés. Vous voici des nôtres !\n");
}

void traitement_etat_ancien_mdp(int fd, Client *client, ClientDataBase &db, std::string msg)
{
    if (db.check_password(client->get_name(), msg) == 1)
    {
        db.relogin_client(fd, client->get_name());
        
        // on relog
        client = db.get_co_client(fd);
        client->set_etats(4);
        send_message(fd, "rebonjour bonjour !\n");
    }
    else
    {
        send_message(fd, "NOON LE MOT DE PASSE EST MAUVAIS:\n");
    }
}

void traitement_etat_discussion(int fd, Client *client, std::string msg)
{
    std::string reponse = "[" + client->get_name() + "] déclame : " + msg + "\n";
    send_message(fd, reponse.c_str());
}


int handle_client_data(int fd, ClientDataBase &db)
{
    Client *client = db.get_co_client(fd);
    if (client == NULL) 
        return (0);

    char buffer[1000];
    memset(buffer, 0, sizeof(buffer));
    int octets = recv(fd, buffer, sizeof(buffer) - 1, 0);

    if (octets <= 0)
    {
        std::cout << "client ses deco" << std::endl;
        db.move_co_client_to_deco(fd);
        close(fd);
        return (1);
    }

    client->put_to_string(buffer);
    
    // Si la missive est arrivée à son terme
    if (string_finished(client->get_message()) == 1)
    {
        std::string msg = client->get_message();
        if (!msg.empty())
        {
            msg.erase(msg.find_last_not_of(" \n\r\t") + 1);
        }
        client->clean_message();

        int etat = client->get_etats();

        if (etat == 0)
            traitement_etat_nom(fd, client, db, msg);
        else if (etat == 1)
            traitement_etat_choix(fd, client, msg);
        else if (etat == 2)
            traitement_etat_nouveau_mdp(fd, client, db, msg);
        else if (etat == 3)
            traitement_etat_ancien_mdp(fd, client, db, msg);
        else if (etat == 4)
            traitement_etat_discussion(fd, client, msg);
    }
    
    return 0;
}