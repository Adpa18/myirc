/*
** client.c for PSU_2015_myirc
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Mon May 16 11:55:19 2016 Axel Vencatareddy
** Last update	Mon May 16 21:10:35 2016 Axel Vencatareddy
*/

#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include "client.h"
#include "array.h"
#include "cmd_client.h"

bool    killed = false;

void        kill_sig(int sig)
{
    if (sig == SIGINT)
    {
        write(1, KILL_SIGINT, strlen(KILL_SIGINT));
        killed = true;
    }
}

COMMAND getCMD(const char *cmd_line)
{
    if (cmd_line[0] == '\n')
        return (false);
    for (unsigned  int i = 0; i < sizeof(cmdlist_str) / sizeof(char *); ++i)
    {
        if (strcasecmp(cmd_line, cmdlist_str[i]) == 0)
        {
            return (i);
        }
    }
    return (NO_CMD);
}

bool  handle_cmd(t_client *cl)
{
    COMMAND   cmd;
    char      **array;
    char      *buffer;
    bool      ret;

    ret = true;
    if ((buffer = read_socket(0)) == NULL || buffer[0] == '\n')
        return (false);
    if ((array = split(buffer, " ")) == NULL)
        return (false);
    if ((cmd = getCMD(array[0])) == NO_CMD && cl->isConnected)
        write_socket(cl->sock, buffer);
    else if (cl->isConnected || cmd == SERVER || cmd == HELP)
        ret = cmdlist_func[cmd](cl, (const char **)&array[1]);
    else
        write_socket(STDOUT_FILENO, NEED_CO);
    free(buffer);
    return (ret);
}

bool    init_select(fd_set *rdfs, t_client *cl)
{
    FD_ZERO(rdfs);
    FD_SET(STDIN_FILENO, rdfs);
    if (cl->isConnected)
        FD_SET(cl->sock, rdfs);
    if (select(cl->max_fd + 1, rdfs, NULL, NULL, NULL) == -1)
    {
        perror("select");
        close(cl->sock);
        return (false);
    }
    return (true);
}

void  client()
{
    t_client  cl;
    fd_set    rdfs;
    char      *buffer;

    cl.max_fd = STDIN_FILENO;
    cl.isConnected = false;
    while (!killed)
    {
        if (!init_select(&rdfs, &cl))
            break;
        if (FD_ISSET(STDIN_FILENO, &rdfs))
            handle_cmd(&cl);
        else if (FD_ISSET(cl.sock, &rdfs))
        {
            if (!(buffer = read_socket(cl.sock)))
            {
                write_socket(STDOUT_FILENO, EOT_SERVER);
                cl.isConnected = false;
            }
            else
            {
                write_socket(STDOUT_FILENO, buffer);
                write(STDOUT_FILENO, "\n", 1);
                free(buffer);
            }
        }
    }
}

#include <gtk/gtk.h>

static void activate (GtkApplication* app, gpointer user_data)
{
    GtkWidget *window;

    (void)user_data;
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "IRC Client");
    gdk_screen_get_height();
    gtk_window_set_default_size (GTK_WINDOW (window), -1, -1);
    gtk_widget_show_all (window);
}

int		main(int ac, char **av)
{
    GtkApplication  *app;
    int status;

    app = gtk_application_new ("IRC.Client.org", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run (G_APPLICATION (app), ac, av);
    g_object_unref (app);

    return status;
    signal(SIGINT, &kill_sig);
    client();
    return (0);
}
