C++ = c++
C++_FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic
#------------------------------------------------------------------
#DIRECTION - DIRECTION - DIRECTION - DIRECTION - DIRECTION

#------------------------------------------------------------------
#FICHIER SOURCE - FICHIER SOURCE - FICHIER SOURCE - FICHIER SOURCE


#------------------------------------------------------------------

INFILES = 	main.cpp boucle_principale.cpp create_listening_socket.cpp handle_client_data.cpp
#------------------------------------------------------------------

OBJFILES = $(INFILES:.cpp=.o)

NAME = web

all: $(NAME)

$(NAME):$(OBJFILES)
	$(C++) $(C++_FLAGS) $(OBJFILES) -o $(NAME) 

%.o: %.cpp
	$(C++) $(C++_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re