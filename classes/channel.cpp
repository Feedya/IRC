#include "../head.hpp"

        Channel::Channel()
        {

        }

        Channel::Channel(std::string name)
        {
            this->_name = name;
        }

        void    Channel::add_name(std::string name)
        {
            this->_name = name;
        }

        void    Channel::add_a_member(Client &client, ClientDataBase &data_base)
        {
            if (data_base.check_if_name_exist(client.get_name()) == 1)
            {
                std::string name = client.get_name();
                data_base.register_new_client(client);

            }
            else
            {
                std::cout << "on ne peut pas l ajouter parceque le client n existe pas" << std::endl;
                std::cout << "bizzare normalement devrai pas arriver" << std::endl;
                std::cout << "dans add_a_member dans channel.hpp" << std::endl;
            }
        }

        void    Channel::remove_member(Client client)
        {
            std::string name = client.get_name();
            this->_members.erase(name);
        }

        void    Channel::remove_member(std::string name)
        {
            this->_members.erase(name);
        }

        void    Channel::put_info(std::string info)
        {
            this->_info = info;
        }