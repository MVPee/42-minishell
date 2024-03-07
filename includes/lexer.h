/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:49:12 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/07 10:49:13 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../srcs/libft/includes/libft.h"
# include "minishell.h"
# include <stdbool.h>

typedef enum e_token
{
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
	struct s_node	*head;
}					t_lexer;

t_lexer				*ft_lexer(char *line, t_data *data, t_env *head);

void				free_lexer(t_lexer *lexer);
bool				syntax_check(char *line);
char				**get_cmd_splitted(char *line, int *count);
int					number_of_cmd(char *line);

#endif