#ifndef HEAD_HPP
#define HEAD_HPP

#include <sys/socket.h> // Pour socket, bind, listen, accept
#include <netinet/in.h> // Pour sockaddr_in et htons
#include <sys/select.h> // Pour select et les macros FD_
#include <unistd.h>     // Pour close, read et write
#include <arpa/inet.h>  // Pour la manipulation des adresses IP
#include <ostream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <poll.h>
#include <fcntl.h>
#include <cstring>
#include <signal.h>

#define BUFFER_SIZE 1000

class Client;
class OldClient;

#include "classes/Message.hpp"
#include "classes/Client.hpp"
#include "classes/DataBase.hpp"

int handle_client_data(int fd, ClientDataBase &db);
void    boucle_principale(int fd_server);

int    create_listening_socket(char *port_char);





int string_finished(std::string str);


void traitement_etat_discussion(int fd, Client *client, ClientDataBase &db, std::string msg);

int send_message(int fd, const char *message);
#endif