#ifndef PARSING_H
# define PARSING_H

typedef struct s_node
{
	char			*name;
	struct s_node	*next;
}			t_node;

typedef struct s_cmd
{
	char			*cmd;
	struct s_node	*args;
	struct s_node	*heredoc;
	struct s_node	*input;
	struct s_node	*output;
	struct s_node	*append;
	struct s_cmd	*next;
	struct s_cmd	*prv;
}					t_cmd;

void				parsing(char *line);

#endif