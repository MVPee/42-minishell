/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:18:05 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/21 10:41:32 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	check_cmd(char *str)
{
	int		i;
	char	**split;
	char	*cmds;
	char	*temp;

	i = -1;
	split = ft_split(str, " ");
	cmds = ft_strdup("");
	while (split[++i])
	{
		if (!ft_strcmp(split[i], "<<"))
        {
			i++;
			ft_printf("heredoc: %s\n", split[i]);
		}
		else if (!ft_strcmp(split[i], "<"))
		{
			i++;
			ft_printf("input: %s\n", split[i]);
		}
        else if (!ft_strcmp(split[i], ">"))
		{
			i++;
			ft_printf("output: %s\n", split[i]);
		}
        else if (!ft_strcmp(split[i], ">>"))
		{
			i++;
			ft_printf("append: %s\n", split[i]);
		}
        else
		{
			temp = ft_strjoin(cmds, split[i]);
			cmds = ft_strjoin(temp, " ");
			free(temp);
		}
        if (!split[i])
            break;
	}
	ft_printf("cmds: %s\n", cmds);
}

void	parsing(char *line)
{
	char	**split;
	int		i;

	split = ft_split(line, "|");
	i = -1;
	while (split[++i])
	{
		check_cmd(split[i]);
	}
}
