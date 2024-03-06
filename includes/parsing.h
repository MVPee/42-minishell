/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:01:20 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/06 09:22:56 by mvpee            ###   ########.fr       */
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
char		**parsing_cmd(char *line, t_env *head, t_data data);
char		*ft_heredoc(char *stop, t_env *env, t_data data);
char		*path_checker(char **paths, char *cmd);

#endif