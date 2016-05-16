//
// Created by wery_a on 15/05/16.
//

#ifndef PSU_2015_MYIRC_COMMON_H
#define PSU_2015_MYIRC_COMMON_H

# define BUFF_SIZE  1024

typedef enum { false, true } bool;

char *concat(const char *s1, const char *s2, const char *s3);
char *replace(char *s, char c, char by);

#endif //PSU_2015_MYIRC_COMMON_H
