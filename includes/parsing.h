/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:01:20 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/11 10:39:17 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../srcs/libft/includes/libft.h"
# include "minishell.h"
# include <stdbool.h>

typedef struct s_parsing
{
	char	**cmd;
	int		input;
	int		output;
	bool	isbuiltins;
	bool	isspecial;
	char	*heredoc;
	char	*path;
}			t_parsing;

t_parsing	*ft_parsing(t_lexer *lexer, t_data *data, t_env *head);
char		*path_checker(char **paths, t_parsing parsing);
bool		file_checker(t_parsing *parsing, t_lexer lexer, t_env *env,
				t_data data);

char		*ft_heredoc(char **stop, t_env *env, t_data data);

t_parsing	init_parsing(void);
void		free_parsing(t_parsing *parsing, t_data data);

char		**ft_expand(char *line, t_env *head, t_data data);
char		*ft_expand_env(char *line, t_env *head, t_data data, int *i);
void		ft_expand_home(char *line, int *i, char **buffer);

#endif