#ifndef MESSAGE_HPP
#define MESSAGE_HPP


#include "../head.hpp"

class Message
{
    private:
        std::string _message;
    public:

        Message()
        {
            this->_message = "";
        }

        Message(std::string message)
        {
            this->_message = message;
        }

  
        void    add_to_message(std::string message)
        {

            this->_message = this->_message + message;
        }
  
        //-------------------------------------------------
        //setter
        void    set_message(std::string message)
        {
            this->_message = message;
        }
        //-------------------------------------------------
        

        //-------------------------------------------------
        //guetteur
        std::string get_message()
        {
            return (this->_message);
        }
        //----------------------------------------------------

};

#endif