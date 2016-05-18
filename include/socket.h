/*
** array.h for PSU_2015_myirc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 20 21:54:53 2016 Adrien WERY
** Last update	Wed May 04 14:30:53 2016 Adrien WERY
*/

#ifndef PSU_2015_MYIRC_SOCKET_H
# define PSU_2015_MYIRC_SOCKET_H

# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include "common.h"

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

bool    write_socket(SOCKET sock, const char *buffer);
char    *read_socket(SOCKET sock);
SOCKET  init_server(unsigned int port);

#endif //PSU_2015_MYIRC_SOCKET_H
