C++ = c++
C++_FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic
#------------------------------------------------------------------
#DIRECTION - DIRECTION - DIRECTION - DIRECTION - DIRECTION

LOGIN_FIRST_TIME_DIR = handle_client_data/login/first_time

LOGIN_DIR = handle_client_data/login
#------------------------------------------------------------------
#FICHIER SOURCE - FICHIER SOURCE - FICHIER SOURCE - FICHIER SOURCE

LOGIN_FIRST_TIME_SRC = $(LOGIN_FIRST_TIME_DIR)/get_name.cpp $(LOGIN_FIRST_TIME_DIR)/get_password.cpp\
						$(LOGIN_FIRST_TIME_DIR)/take_password_and_name.cpp

LOGIN_SRC = $(LOGIN_DIR)/handle_client_data.cpp
#------------------------------------------------------------------

INFILES = 	main.cpp boucle_principale.cpp create_listening_socket.cpp\
			$(LOGIN_SRC)\
			$(LOGIN_FIRST_TIME_SRC)
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