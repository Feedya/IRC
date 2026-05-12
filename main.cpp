#include "head.hpp"

void    ft_irc(char *port, char *password)
{
    int majordome = create_listening_socket(port);
    boucle_principale(majordome);

}

int     main(int argc, char **argv)
{
    if (argc == 3)
    {
        ft_irc(argv[1], argv[2]);
    }
    else
        std::cout << "port password" << std::endl;
    return (0);
}