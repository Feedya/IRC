#include "head.hpp"


//renvoie 1 si la string est finis
//sinon elle renvoie 0
int string_finished(std::string str)
{
    long unsigned int i = 0;

    while (i < str.size())
    {
        if (str[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}


//elle va effacer un fd a l index dans fds
void    remove_fd_from_fds(int index, std::vector<struct pollfd> &fds)
{
    std::vector<struct pollfd>::iterator it;

    if (index >= 0 && index < (int)fds.size())
    {
        fds.erase(fds.begin() + index);
    }
}