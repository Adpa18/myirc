/*
** array.h for PSU_2015_myirc
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 20 21:54:53 2016 Adrien WERY
** Last update	Wed May 04 14:30:53 2016 Adrien WERY
*/

#ifndef PSU_2015_MYIRC_COMMON_H
# define PSU_2015_MYIRC_COMMON_H

# define DEBUGING       true
# define DEBUG(s, ...)  {if(DEBUGING){printf(s, __VA_ARGS__);}};
# define CRLF           "\r\n\0"
# define SERVER_NAME    "AvengesIRC"
# define BUFF_SIZE      1024
# define DEFAULT_PORT   6697

typedef enum { false, true } bool;

char            *concat(int count, ...);
char            *replace(char *s, char c, char by);
const char      *getIP(const char *hostname);
struct passwd   *getUser();

#endif //PSU_2015_MYIRC_COMMON_H
