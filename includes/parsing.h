/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:01:20 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/26 16:17:00 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../srcs/libft/includes/libft.h"
# include <stdbool.h>

typedef struct s_parsing
{
	char	*cmd;
	int		input;
	int		output;
	bool	append;
	char	*heredoc;
}			t_parsing;

bool		ft_parsing(t_parsing *parsing, t_lexer *lexer);
void		init_parsing(t_parsing *parsing);

#endif