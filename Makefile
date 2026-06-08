C++ = c++
C++_FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic
#------------------------------------------------------------------
#DIRECTION - DIRECTION - DIRECTION - DIRECTION - DIRECTION


LOGIN_DIR = handle_client_data

HANDLE_DISCUSSION_DIR = handle_client_data/handle_discussion

CLASSES_DIR = classes/

#------------------------------------------------------------------
#FICHIER SOURCE - FICHIER SOURCE - FICHIER SOURCE - FICHIER SOURCE


LOGIN_SRC = $(LOGIN_DIR)/handle_client_data.cpp

HANDLE_DISCUSSION_SRC = $(HANDLE_DISCUSSION_DIR)/traitement_etat_discussion.cpp

CLASSES_SRC = $(CLASSES_DIR)/Client.cpp $(CLASSES_DIR)/DataBase.cpp\
			$(CLASSES_DIR)/Message.cpp $(CLASSES_DIR)/channel.cpp
#------------------------------------------------------------------

INFILES = 	main.cpp boucle_principale.cpp create_listening_socket.cpp utils.cpp\
			$(LOGIN_SRC)\
			$(HANDLE_DISCUSSION_SRC)\
			$(CLASSES_SRC)
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