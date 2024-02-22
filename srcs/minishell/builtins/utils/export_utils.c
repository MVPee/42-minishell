/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:48:08 by nechaara          #+#    #+#             */
/*   Updated: 2024/02/22 17:22:06 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

bool	is_key_valid(char *str)
{
	size_t index;

	index = 0;

	while (str[index])
	{
		if(!ft_isalnum(str[index]) && !(str[index] == '_'))
			return (false);
		index++;
	}
	return (true);
}

char	*reconstructed_entry(char *s1, char *s2)
{
	char	*joined_string;
	
	joined_string = NULL;
	if (!s1)
		return (NULL);
	joined_string = ft_strjoin(s1, "=");
	joined_string = ft_strjoin(joined_string, s2);
	return (joined_string);
}