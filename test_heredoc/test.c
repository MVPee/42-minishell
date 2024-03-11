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
# include <string.h>

// void sigint_handler(int signum)
// {
//     if (signum == SIGINT)
//     {
//         rl_clear_screen(0, 0);
//         rl_replace_line("", 0);
//         rl_on_new_line();
//         rl_redisplay();
//     }
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void heredoc(int *pipe_fd)
{
    char stop[] = "stop";
    char *line;

    while ((line = readline("> ")))
    {
        if (!line || !strcmp(line, stop))
        {
            free(line);
            break;
        }
        else
        {
            write(pipe_fd[1], line, strlen(line));
            write(pipe_fd[1], "\n", 1);
            free(line);
        }
    }
    close(pipe_fd[1]);
    exit(0);
}

int main(void)
{
    int status;
    char buffer[100];
    char *str = NULL;

    int pipe_fd[2];

    pipe(pipe_fd);
    pid_t pid = fork();
    if (pid == 0)
    {
        close(pipe_fd[0]);
        heredoc(pipe_fd);
    }
    else
    {
        close(pipe_fd[1]);

        ssize_t bytes_read;
        int index = 0;

        while ((bytes_read = read(pipe_fd[0], buffer, sizeof(buffer))) > 0)
        {
            str = realloc(str, index + bytes_read + 1);
            if (str == NULL)
            {
                perror("Erreur lors de l'allocation de mémoire");
                return 1;
            }
            memcpy(&str[index], buffer, bytes_read);
            index += bytes_read;
        }
        if (bytes_read == -1)
        {
            perror("Erreur lors de la lecture depuis le tube");
            return 1;
        }
        waitpid(pid, &status, 0);

        printf("RESULT:\n%s\n", str);
        free(str);
    }
    return 0;
}

