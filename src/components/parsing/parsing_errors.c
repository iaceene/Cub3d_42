#include "../../include/cub3d.h"

// the msg to be in yellow in a case of 3
// if the flag is 0; is an error
// else cases will be in green color

void exit_cub(void)
{
    write(1, COLOR_RED, ft_strlen(COLOR_RED));
    write(1, " --> EXITING ]\n", 15);
    write(1, COLOR_RESET, ft_strlen(COLOR_RESET));
    ft_malloc(-1);
    exit(1);
}

void log_state(char *msg, int flag)
{
    int i;
    int fd;
    char *clr;

    if (!msg)
        return;
    fd = 1;
    clr = COLOR_GREEN;
    i = 0;
    if (!flag)
    {
        fd = 2;
        clr = COLOR_RED;
    }
    else if (flag == 3)
        clr = COLOR_YELLOW;
    write(fd, clr, ft_strlen(clr));
    if (fd == 2)
        write(2, "[ Error ]\n", 10);
    if (flag == 1)
        write(fd, "[ ✅ ", 7);
    else if (flag == 3)
        write(fd, "[ ⏳ ", 7);
    else
        write(fd, "[ ", 2);
    while (msg[i])
    {
        write(fd, &msg[i], 1);
        i++;
    }
    if (fd == 2)
        exit_cub();
    else
        write(fd, " ]\n", 3);
    write(fd, COLOR_RESET, ft_strlen(COLOR_RESET));
}
