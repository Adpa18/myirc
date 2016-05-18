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
        if (!(s = va_arg(argp, char *)) || (len = strlen(s)) == 0)
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

#include <stdio.h>

inline char     *getHostName(const char *ip)
{
    struct hostent  *hp;
    long            addr;

    addr = inet_addr(ip);
    if ((hp = gethostbyaddr((char *) &addr, sizeof(addr), AF_INET)))
        return (NULL);
    printf("Hostname:\t%s\n", hp->h_name);
    printf("Aliases:\t");
    while (hp->h_aliases[0])
        printf("%s ", *hp->h_aliases++);
    printf("\n");
    printf("Addresses:\t");
    while (hp->h_addr_list[0])
        printf("%s ", inet_ntoa(*(struct in_addr *) * hp->h_addr_list++));
    printf("\n");
    return (hp->h_name);
}

inline struct passwd    *getUser()
{
    return (getpwuid(geteuid()));
}