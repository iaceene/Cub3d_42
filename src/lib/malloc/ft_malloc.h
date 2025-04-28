#ifndef FT_MALLOC_H
#define FT_MALLOC_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_gb
{
    void *ptr;
    struct s_gb *next;
} t_gb;

void *ft_malloc(ssize_t len);

#endif