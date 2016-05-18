/*
** array.h for PSU_2015_myirc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 20 21:54:53 2016 Adrien WERY
** Last update	Wed May 04 14:30:53 2016 Adrien WERY
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <pwd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "common.h"

inline char *concat(int count, ...)
{
    va_list argp;
    size_t  full_len;
    size_t  len;
    char    *dest;
    char    *s;

    va_start(argp, count);
    len = 0;
    for (int i = 0; i < count; ++i)
        len += strlen(va_arg(argp, char *));
    va_end(argp);
    if ((dest = malloc(len + 1)) == NULL)
        return (NULL);
    dest[len] = 0;
    va_start(argp, count);
    full_len = 0;
    for (int i = 0; i < count; ++i)
    {
        if (!(s = va_arg(argp, char *)) || s[0] == 0 || (len = strlen(s)) == 0)
            continue;
        memcpy(dest + full_len, s, len);
        full_len += len;
    }
    va_end(argp);
    return (dest);
}

inline char *replace(char *s, char c, char by)
{
    int     i;

    i = -1;
    while (s[++i])
    {
        if (s[i] == c)
            s[i] = by;
    }
    return (s);
}

inline struct passwd    *getUser()
{
    return (getpwuid(geteuid()));
}

inline const char *getIP(const char *hostname)
{
    struct hostent  *he;
    struct in_addr  **addr_list;

    if (!(he = gethostbyname(hostname)))
        return (hostname);
    addr_list = (struct in_addr **) he->h_addr_list;
    return (inet_ntoa(*addr_list[0]));
}