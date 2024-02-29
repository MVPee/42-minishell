#ifndef LEXER_H
# define LEXER_H

# include "../srcs/libft/includes/libft.h"
# include "minishell.h"
# include <stdbool.h>

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

typedef struct s_lexer
{
	char			*cmd;
	pid_t			pid;
	struct s_node	*head;
	struct s_lexer	*next;
}					t_lexer;

t_lexer				*ft_lexer(char *line, t_data *data, t_env *head);

t_lexer				*ft_lexer_new(char *cmd);
void				ft_lexer_add(t_lexer **head, t_lexer *new);
t_node				*ft_node_new(char *name, t_token token);
bool				ft_node_add(t_node **head, t_node *new);
void				free_lexer(t_lexer *lexer);

char 				*checker(char *line, t_env *head, t_data data);

#endif