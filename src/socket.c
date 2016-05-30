/*
** array.h for PSU_2015_myirc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 20 21:54:53 2016 Adrien WERY
** Last update	Wed May 18 14:12:13 2016 Adrien WERY
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "socket.h"

bool    write_socket(SOCKET sock, const char *buffer)
{
    if (!buffer)
        return (false);
    write(sock, buffer, strlen(buffer));
    return (true);
}

char    *read_socket(SOCKET sock)
{
    char    buffer[BUFF_SIZE];
    int     n;

    if ((n = read(sock, buffer, BUFF_SIZE - 1)) == -1)
    {
        perror("read");
        return (NULL);
    }
    if (n == 0)
        return (NULL);
    if (n > 1 && buffer[n - 1] == '\n')
        buffer[n - 1] = 0;
    buffer[n] = 0;
    return (concat(1, buffer));
}
