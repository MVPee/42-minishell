/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:26:27 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/11 13:20:46 by mvan-pee         ###   ########.fr       */
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
	parsing.path = NULL;
	parsing.flag = false;
	return (parsing);
}

void	free_parsing(t_parsing *parsing, t_data data)
{
	int	i;

	i = -1;
	while (++i < data.nbr_cmd)
	{
		ft_free_matrix(1, &parsing[i].cmd);
		ft_free(1, &parsing[i].path);
		if (parsing[i].input != -1)
			close(parsing[i].input);
		if (parsing[i].output != -1)
			close(parsing[i].output);
	}
	ft_free(1, &parsing);
}
