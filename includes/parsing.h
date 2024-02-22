#ifndef PARSING_H
# define PARSING_H

# include "../srcs/libft/includes/libft.h"

typedef enum e_token
{
	CMD = 0,
	INPUT = 1,
	OUTPUT = 2,
	APPEND = 3,
	HEREDOC = 4
}					t_token;

typedef struct s_node
{
	char			*name;
	enum e_token	token;
	struct s_node	*next;
}					t_node;

typedef struct s_cmd
{
	char			*cmd;
	pid_t			pid;
	struct s_node	*head;
	struct s_cmd	*next;
}					t_cmd;

t_cmd				*parsing(char *line);

t_cmd				*ft_cmd_new(char *cmd);
void				ft_cmd_add(t_cmd **head, t_cmd *new);
t_node				*ft_node_new(char *name, t_token token);
void				ft_node_add(t_node **head, t_node *new);

#endif