/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:46:20 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/03/15 17:28:07 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	echo_option(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
	{
		if (!str[1] || str[1] == ' ')
			return (false);
		while (str[++i])
			if (str[i] != 'n')
				return (false);
	}
	else
		return (false);
	return (true);
}

void	ft_echo(t_data *data, char **split)
{
	bool	flag;
	int		i;

	i = 0;
	if (!split[1])
	{
		ft_printf("\n");
		return ;
	}
	flag = echo_option(split[1]);
	if (flag)
		i++;
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
