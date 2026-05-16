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


#include "classes/Message.hpp"
#include "classes/Client.hpp"
#include "classes/OldClients.hpp"

void    boucle_principale(int fd_server);
int handle_client_data(int fd_index, std::map<int, Client> clients, std::vector<struct pollfd> fds);
int    create_listening_socket(char *port_char);

//login/first_time
void    take_password_and_name(int fd_index, std::map<int, Client> &clients, std::vector<struct pollfd> &fds);
int get_name(int fd_index, std::map<int, Client> &clients, std::vector<struct pollfd> &fds);
int get_password(int fd_index, std::map<int, Client> &clients, std::vector<struct pollfd> &fds);

//HANDLE CLIENT DATA
int handle_message(int fd_index, std::map<int, Client> &clients, std::vector<struct pollfd> &fds);





//UTILS
int string_finished(std::string str);

//utils fds
void    remove_fd_from_fds(int index, std::vector<struct pollfd> &fds);




#endif