/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:48:08 by nechaara          #+#    #+#             */
/*   Updated: 2024/02/20 16:36:23 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static void	error_handler_export(char **split)
{
	if (!split || !split[0] || !split[1])
		return ;
	ft_printf("export : « %s=%s »",split[0],split[1]);
	ft_printf(" identifiant non valable\n");
}

static bool	is_key_valid(char *str)
{
	size_t index;

	index = 0;

	while (str[index])
	{
		if(!ft_isalnum(str[index]))
			return (false);
		index++;
	}
	return (true);
}

static char	*ft_key_and_value_only(char *space_pos)
{
	while (!ft_isspace(*space_pos))
		space_pos--;
	if (ft_isspace(*space_pos))
		space_pos++;
	return (space_pos);
}

char	**splitter(char *current_equal_address, bool *do_concatenate)
{
	char	**split;
	char	*real_equal_address;
	char	*key_address;

	split = (char **)malloc(3 * (sizeof(char *)));
	if (!split)
		return (NULL);
	if (*do_concatenate)
		real_equal_address = current_equal_address - 1;
	else
		real_equal_address = current_equal_address;
	key_address = ft_key_and_value_only(real_equal_address);
	split[0] = ft_strndup(key_address, real_equal_address - key_address);
	if (!split[0])
		return (free(split), NULL);
	split[1] = ft_strtrim(ft_strdup(current_equal_address + 1), " ");
	if (!split[1])
		return (free(split[1]),free(split), NULL);
	split[2] = NULL;
	if (!is_key_valid(split[0]))
		error_handler_export(split);
	return (split);
}

char **export_split(char *line, bool *do_concatenate, bool *single_cmd)
{
	char	**split;
	char	*equal_address;
	
	*single_cmd = false;
	equal_address = ft_strchr(line, '=');
	if (!equal_address)
	{
		*single_cmd = true;
		return (NULL);
	}
	else if (equal_address > line && *(equal_address - 1) == 43)
		*do_concatenate = true;
	else
		*do_concatenate = false;
	split = splitter(equal_address, do_concatenate);
	return (split);
}