#include <stdio.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>

void sigint_handler(int signum)
{
    if (signum == SIGINT)
    {
        rl_clear_screen(0, 0);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

void heredoc(int fd)
{
    char stop[] = "stop";
    char *line;

    while(line = readline("> "))
    {
        if(!line || !strcmp(line, stop))
        {
            free(line);
            break;
        }
        else
        {
            write(fd, line, strlen(line));
            write(fd, "\n", 1);
            free(line);
        }
    }
    printf("END\n");
    exit(0);
}

int main(void)
{
    int status;
    int fd = open(".heredoc_temp", O_CREAT | O_TRUNC | O_WRONLY | O_RDONLY, 0644);
    if (fd == -1)
        return (1);

    signal(SIGINT, sigint_handler);

    write(fd, "", 1);
    pid_t pid = fork();
    if (pid == 0)
        heredoc(fd);
    waitpid(pid, &status, 0);
    close(fd);
    printf("Finish!\n");
    return (0);
}
