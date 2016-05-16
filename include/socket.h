//
// Created by wery_a on 15/05/16.
//

#ifndef PSU_2015_MYIRC_SOCKET_H
# define PSU_2015_MYIRC_SOCKET_H

# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

bool    write_socket(SOCKET sock, const char *buffer);
char    *read_socket(SOCKET sock);
SOCKET  init_server(unsigned int port);

#endif //PSU_2015_MYIRC_SOCKET_H
