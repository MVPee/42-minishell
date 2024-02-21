#ifndef PARSING_H
# define PARSING_H

# include "../srcs/libft/includes/libft.h"

typedef enum e_token
{
	CMD,
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
}	t_token;

typedef struct s_node
{
	char *name;
	enum e_token token;
	struct s_list *next;
}				t_node;

typedef struct s_cmd
{
	char *cmd;
	pid_t pid;
	struct s_node *head;
	struct s_cmd *next;
}				t_cmd;

void				parsing(char *line);

#endif