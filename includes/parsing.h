#ifndef PARSING_H
# define PARSING_H

# include "../srcs/libft/includes/libft.h"

typedef struct s_node
{
	char			*name;
	struct s_node	*next;
}					t_node;

typedef struct s_cmd
{
	char			*cmd;
	pid_t			pid;
	struct s_node	*input;
	struct s_node	*output;
	struct s_node	*append;
	struct s_node	*heredoc;
	struct s_cmd	*next;
	struct s_cmd	*prv;
}					t_cmd;

t_cmd				*parsing(char *line);
size_t				cmd_count(t_cmd *cmd);

#endif