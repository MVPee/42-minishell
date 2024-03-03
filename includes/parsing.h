/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:01:20 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/03 12:24:16 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../srcs/libft/includes/libft.h"
# include "minishell.h"
# include <stdbool.h>

typedef struct s_parsing
{
	char	*cmd;
	char	**cmd_args;
	int		input;
	int		output;
	bool	isbuiltins;
	char	*heredoc;
	char	*path;
}			t_parsing;

t_parsing	*ft_parsing(t_lexer *lexer, t_data *data, t_env *head);
char		*ft_heredoc(char *stop);
char		*checker(char *line, t_env *head, t_data data);
char		*path_checker(char **paths, char *cmd);
char		**get_args(char *line, t_env *head, t_data data);

#endif