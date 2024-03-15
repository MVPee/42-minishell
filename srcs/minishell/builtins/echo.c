/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:46:20 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/03/15 17:31:05 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	check_after_option(char *str)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		if (!str[i])
			break ;
		if (str[i] != 'n')
			return (true);
	}
	return (false);
}

static void	echo_option(char **split, bool *flag, int *i)
{
	int	j;

	j = 0;
	while (split[++(*i)])
	{
		if (split[*i][0] == '-')
		{
			if (check_after_option(split[*i]))
			{
				(*i)--;
				break ;
			}
			else
				*flag = true;
		}
		else
		{
			(*i)--;
			break ;
		}
	}
}

void	ft_echo(t_data *data, char **split)
{
	bool	flag;
	int		i;

	flag = false;
	i = 0;
	if (!split[1])
	{
		data->env_var = 0;
		ft_printf("\n");
		return ;
	}
	echo_option(split, &flag, &i);
	while (split[++i])
	{
		ft_printf("%s", split[i]);
		if (split[i + 1])
			ft_printf(" ");
	}
	if (!flag)
		ft_printf("\n");
	data->env_var = 0;
}
