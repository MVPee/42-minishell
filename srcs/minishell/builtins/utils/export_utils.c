/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:48:08 by nechaara          #+#    #+#             */
/*   Updated: 2024/03/07 15:40:30 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	*non_valid_arg(char *line)
{
	if (!line)
		return (NULL);
	ft_printf_fd(2, "export : « %s » : not a valid identifier\n", line);
	return (NULL);
}

void	error_handler_export(char *s1, char *s2)
{
	if (!s2)
		ft_printf_fd(2, "export : « %s=  »", s1);
	else
		ft_printf_fd(2, "export : « %s=%s »", s1, s2);
	ft_printf_fd(2, " not a valid identifier\n");
}

bool	is_key_valid(char *str)
{
	size_t	index;

	index = 0;
	while (str[index])
	{
		if (index == 0 && ft_isdigit(str[index]))
			return (false);
		else if (!ft_isalnum(str[index]) && !(str[index] == '_'))
			return (false);
		index++;
	}
	return (true);
}

char	*reconstructed_entry(char *s1, char *s2)
{
	char *joined_string;

	joined_string = NULL;
	if (!s1)
		return (NULL);
	joined_string = ft_strjoin(s1, "=");
	joined_string = ft_strjoin(joined_string, s2);
	return (joined_string);
}