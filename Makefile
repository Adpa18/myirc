CC		    =	gcc -g

RM		    =   rm -rf

NAME		=   myirc

SERVER		=   server
CLIENT		=   client

OBJ_DIR		=   obj/

OBJ_SERVER_DIR  =   $(OBJ_DIR)server/

OBJ_CLIENT_DIR	=   $(OBJ_DIR)client/

SRC_DIR		    =   src/

SRC_SERVER_DIR	=   $(SRC_DIR)server/

SRC_CLIENT_DIR	=   $(SRC_DIR)client/

SRC		    =   $(SRC_DIR)common.c			\
                $(SRC_DIR)array.c			\
                $(SRC_DIR)socket.c			\

SRC_SERVER	=   $(SRC)

SRC_CLIENT	=   $(SRC)

SRC_SERVER	+=  $(SRC_SERVER_DIR)server.c		    \
		        $(SRC_SERVER_DIR)socket.c		    \
		        $(SRC_SERVER_DIR)manage_client.c	\
		        $(SRC_SERVER_DIR)manage_channel.c	\
		        $(SRC_SERVER_DIR)cmd.c		        \
		        $(SRC_SERVER_DIR)channel.c	        \
		        $(SRC_SERVER_DIR)msg.c		        \
		        $(SRC_SERVER_DIR)user.c		        \

SRC_CLIENT  +=  $(SRC_CLIENT_DIR)client.c		\
                $(SRC_CLIENT_DIR)cmd.c		    \


CFLAGS		=   -W -Wall -Wextra -Werror -D_GNU_SOURCE -std=c99 -pthread

CFLAGS		+=  -I./include -I./include/libs

LD_FLAGS	=

LD_FLAGS_CLIENT =   -L./libs -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0

OBJ_CLIENT	=   $(SRC_CLIENT:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

OBJ_SERVER	=   $(SRC_SERVER:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

$(OBJ_DIR)%.o	:   $(SRC_DIR)%.c
		  @mkdir -p $(OBJ_DIR)
		  @mkdir -p $(OBJ_SERVER_DIR)
		  @mkdir -p $(OBJ_CLIENT_DIR)
		  @echo -e "Compiling $< to $@"
		  @$(CC) -c $(CFLAGS) $(CFLAGS_CLIENT) $< -o $@

$(NAME) :   $(SERVER) $(CLIENT)

all     :   $(NAME)

$(CLIENT)   :   $(OBJ_CLIENT)
		  @echo -e "\033[32mLinking $@\033[00m"
		  @$(CC) $(CFLAGS_CLIENT) $(OBJ_CLIENT) -o $(CLIENT) $(LD_FLAGS) $(LD_FLAGS_CLIENT)
		  @echo -e "\033[33m${CLIENT} Compiled\033[00m"

$(SERVER)   :   $(OBJ_SERVER)
		  @echo -e "\033[32mLinking $@\033[00m"
		  @$(CC) $(OBJ_SERVER) -o $(SERVER) $(LD_FLAGS)
		  @echo -e "\033[33m${SERVER} Compiled\033[00m"

clean       :
		  @echo -e "\033[31mRemoving Objects\033[00m"
		  @$(RM) $(OBJ_SERVER)
		  @$(RM) $(OBJ_CLIENT)

fclean      :   clean
		  @echo -e "\033[31mRemoving ${CLIENT}\033[00m"
		  @echo -e "\033[31mRemoving ${SERVER}\033[00m"
		  @$(RM) $(SERVER)
		  @$(RM) $(CLIENT)

re          :   fclean all

.PHONY      :   all ${SERVER} ${CLIENT} clean fclean re
