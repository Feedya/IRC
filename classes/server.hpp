#include "../head.hpp"

class Server
{
    private:
        ClientDataBase db;
        Channel channel;
    public:
        Server()
        {

        }

        ClientDataBase &get_db()
        {
            return (this->db);
        }

        Channel &get_channel()
        {
            return (this->channel);
        }

};