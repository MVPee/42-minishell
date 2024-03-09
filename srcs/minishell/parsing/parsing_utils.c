/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:26:27 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/08 18:24:13 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_parsing	init_parsing(void)
{
	t_parsing	parsing;

	parsing.cmd = NULL;
	parsing.input = -1;
	parsing.output = -1;
	parsing.isbuiltins = false;
	parsing.isspecial = false;
	parsing.heredoc = NULL;
	parsing.path = NULL;
	return (parsing);
}

void	free_parsing(t_parsing *parsing, t_data data)
{
	int	i;

	i = -1;
	while (++i < data.nbr_cmd)
	{
		ft_free_matrix(1, &parsing[i].cmd);
		ft_free(2, &parsing[i].heredoc, &parsing[i].path);
		if (parsing[i].input != -1)
			close(parsing[i].input);
		if (parsing[i].output != -1)
			close(parsing[i].output);
	}
	ft_free(1, &parsing);
	return ;
}