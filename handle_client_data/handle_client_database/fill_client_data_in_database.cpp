#include "../../head.hpp"

//-----------------------------------------------------------
//cette fonction doit ajouter le client dans la data base
//de tout les clients
int fill_client_data_in_database(ClientDataBase &data_base, int fd)
{
    Client client = data_base.get_co_client(fd);
    AllClient nouveau_client(client.get_name(), client.get_password());
    data_base.add_all_client(nouveau_client);
    return (0);
}
//-----------------------------------------------------------
