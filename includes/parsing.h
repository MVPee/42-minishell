/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:01:20 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/28 17:03:26 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../srcs/libft/includes/libft.h"
# include "minishell.h"
# include <stdbool.h>

typedef struct s_parsing
{
	char				*cmd;
	int					input;
	int					output;
	bool				append;
	bool				isbuiltins;
	char				*heredoc;
	struct s_parsing	*next;
}						t_parsing;

t_parsing				*ft_parsing(t_lexer *lexer, t_data *data);
void					init_parsing(t_parsing *parsing);
char					*ft_heredoc(char *stop);

#endif